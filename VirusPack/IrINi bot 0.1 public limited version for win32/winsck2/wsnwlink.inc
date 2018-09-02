{
	wsnwlink.h

	Microsoft Windows
	Copyright (C) Microsoft Corporation, 1992-1999.
		Microsoft-specific extensions to the Windows NT IPX/SPX Windows
		Sockets interface.  These extensions are provided for use as
		necessary for compatibility with existing applications.  They are
		otherwise not recommended for use, as they are only guaranteed to
		work     over the Microsoft IPX/SPX stack.  An application which
		uses these     extensions may not work over other IPX/SPX
		implementations.  Include this header file after winsock.h and
		wsipx.h.

		To open an IPX socket where a particular packet type is sent in
		the IPX header, specify NSPROTO_IPX + n as the protocol parameter
		of the socket() API.  For example, to open an IPX socket that
		sets the packet type to 34, use the following socket() call:

    		s = socket(AF_IPX, SOCK_DGRAM, NSPROTO_IPX + 34);
}

// Below are socket option that may be set or retrieved by specifying
// the appropriate manifest in the "optname" parameter of getsockopt()
// or setsockopt().  Use NSPROTO_IPX as the "level" argument for the
// call.
const

//	Set/get the IPX packet type.  The value specified in the
//	optval argument will be set as the packet type on every IPX
//	packet sent from this socket.  The optval parameter of
//	getsockopt()/setsockopt() points to an int.
	IPX_PTYPE = $4000;

//	Set/get the receive filter packet type.  Only IPX packets with
//	a packet type equal to the value specified in the optval
//	argument will be returned; packets with a packet type that
//	does not match are discarded.  optval points to an int.
	IPX_FILTERPTYPE = $4001;

//	Stop filtering on packet type set with IPX_FILTERPTYPE.
	IPX_STOPFILTERPTYPE = $4003;

//	Set/get the value of the datastream field in the SPX header on
//	every packet sent.  optval points to an int.
	IPX_DSTYPE = $4002;

//	Enable extended addressing.  On sends, adds the element
//	"unsigned char sa_ptype" to the SOCKADDR_IPX structure,
//	making the total length 15 bytes.  On receives, add both
//	the sa_ptype and "unsigned char sa_flags" to the SOCKADDR_IPX
//	structure, making the total length 16 bytes.  The current
//	bits defined in sa_flags are:
//		0x01 - the received frame was sent as a broadcast
//		0x02 - the received frame was sent from this machine
//	optval points to a BOOL.
	IPX_EXTENDED_ADDRESS = $4004;

//	Send protocol header up on all receive packets.  optval points
//	to a BOOL.
	IPX_RECVHDR = $4005;

//	Get the maximum data size that can be sent.  Not valid with
//	setsockopt().  optval points to an int where the value is
//	returned.
	IPX_MAXSIZE = $4006;

//	Query information about a specific adapter that IPX is bound
//	to.  In a system with n adapters they are numbered 0 through n-1.
//	Callers can issue the IPX_MAX_ADAPTER_NUM getsockopt() to find
//	out the number of adapters present, or call IPX_ADDRESS with
//	increasing values of adapternum until it fails.  Not valid
//	with setsockopt().  optval points to an instance of the
//	IPX_ADDRESS_DATA structure with the adapternum filled in.
	IPX_ADDRESS = $4007;
type
	IPX_ADDRESS_DATA = packed record
		adapternum : Integer;                 // input: 0-based adapter number
		netnum     : Array [0..3] of Byte;    // output: IPX network number
		nodenum    : Array [0..5] of Byte;    // output: IPX node address
		wan        : Boolean;                 // output: TRUE = adapter is on a wan link
		status     : Boolean;                 // output: TRUE = wan link is up (or adapter is not wan)
		maxpkt     : Integer;                 // output: max packet size, not including IPX header
		linkspeed  : ULONG;                   // output: link speed in 100 bytes/sec (i.e. 96 == 9600 bps)
	end;
	PIPX_ADDRESS_DATA = ^IPX_ADDRESS_DATA;

const
//	Query information about a specific IPX network number.  If the
//	network is in IPX's cache it will return the information directly,
//	otherwise it will issue RIP requests to find it.  Not valid with
//	setsockopt().  optval points to an instance of the IPX_NETNUM_DATA
//	structure with the netnum filled in.
	IPX_GETNETINFO = $4008;
type
	IPX_NETNUM_DATA = packed record
		netnum   : Array [0..3] of Byte;  // input: IPX network number
		hopcount : Word;                  // output: hop count to this network, in machine order
		netdelay : Word;                  // output: tick count to this network, in machine order
		cardnum  : Integer;               // output: 0-based adapter number used to route to this net;
		                                  // can be used as adapternum input to IPX_ADDRESS
		router   : Array [0..5] of Byte;  // output: MAC address of the next hop router, zeroed if
																			// the network is directly attached
	end;
	PIPX_NETNUM_DATA = ^IPX_NETNUM_DATA;

const
//	Like IPX_GETNETINFO except it  does not  issue RIP requests. If the
//	network is in IPX's cache it will return the information, otherwise
//	it will fail (see also IPX_RERIPNETNUMBER which  always  forces a
//	re-RIP). Not valid with setsockopt().  optval points to an instance of
//	the IPX_NETNUM_DATA structure with the netnum filled in.
	IPX_GETNETINFO_NORIP = $4009;

//	Get information on a connected SPX socket.  optval points
//	to an instance of the IPX_SPXCONNSTATUS_DATA structure.
//  *** All numbers are in Novell (high-low) order. ***
	IPX_SPXGETCONNECTIONSTATUS = $400B;
type
	IPX_SPXCONNSTATUS_DATA = packed record
		ConnectionState         : Byte;
		WatchDogActive          : Byte;
		LocalConnectionId       : Word;
		RemoteConnectionId      : Word;
		LocalSequenceNumber     : Word;
		LocalAckNumber          : Word;
		LocalAllocNumber        : Word;
		RemoteAckNumber         : Word;
		RemoteAllocNumber       : Word;
		LocalSocket             : Word;
		ImmediateAddress        : Array [0..5] of Byte;
		RemoteNetwork           : Array [0..3] of Byte;
		RemoteNode              : Array [0..5] of Byte;
		RemoteSocket            : Word;
		RetransmissionCount     : Word;
		EstimatedRoundTripDelay : Word;                 // In milliseconds
		RetransmittedPackets    : Word;
		SuppressedPacket        : Word;
	end;
	PIPX_SPXCONNSTATUS_DATA = ^IPX_SPXCONNSTATUS_DATA;

const
//	Get notification when the status of an adapter that IPX is
//	bound to changes.  Typically this will happen when a wan line
//	goes up or down.  Not valid with setsockopt().  optval points
//	to a buffer which contains an IPX_ADDRESS_DATA structure
//	followed immediately by a HANDLE to an unsignaled event.
//
//	When the getsockopt() query is submitted, it will complete
//	successfully.  However, the IPX_ADDRESS_DATA pointed to by
//	optval will not be updated at that point.  Instead the
//	request is queued internally inside the transport.
//
//	When the status of an adapter changes, IPX will locate a
//	queued getsockopt() query and fill in all the fields in the
//	IPX_ADDRESS_DATA structure.  It will then signal the event
//	pointed to by the HANDLE in the optval buffer.  This handle
//	should be obtained before calling getsockopt() by calling
//	CreateEvent().  If multiple getsockopts() are submitted at
//	once, different events must be used.
//
//	The event is used because the call needs to be asynchronous
//	but currently getsockopt() does not support this.
//
//	WARNING: In the current implementation, the transport will
//	only signal one queued query for each status change.  Therefore
//	only one service which uses this query should be running at
//	once.
	IPX_ADDRESS_NOTIFY = $400C;

//	Get the maximum number of adapters present.  If this call returns
//	n then the adapters are numbered 0 through n-1.  Not valid
//	with setsockopt().  optval points to an int where the value
//	is returned.
	IPX_MAX_ADAPTER_NUM = $400D;

//	Like IPX_GETNETINFO except it forces IPX to re-RIP even if the
//	network is in its cache (but not if it is directly attached to).
//	Not valid with setsockopt().  optval points to an instance of
//	the IPX_NETNUM_DATA structure with the netnum filled in.
	IPX_RERIPNETNUMBER = $400E;

//	A hint that broadcast packets may be received.  The default is
//	TRUE.  Applications that do not need to receive broadcast packets
//	should set this sockopt to FALSE which may cause better system
//	performance (note that it does not necessarily cause broadcasts
//	to be filtered for the application).  Not valid with getsockopt().
//	optval points to a BOOL.
	IPX_RECEIVE_BROADCAST = $400F;


//	On SPX connections, don't delay before sending ack.  Applications
//	that do not tend to have back-and-forth traffic over SPX should
//	set this; it will increase the number of acks sent but will remove
//	delays in sending acks.  optval points to a BOOL.
	IPX_IMMEDIATESPXACK = $4010;

