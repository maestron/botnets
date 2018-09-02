{******************************************************************************}
{                                                       	               }
{ Basic Encoding Rules API interface Unit for Object Pascal                    }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winber.h, released August 2001. The original Pascal    }
{ code is: WinBer.pas, released December 2000. The initial developer of the    }
{ Pascal code is Marcel van Brakel (brakelm@chello.nl).                        }
{                                                                              }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Obtained through: Joint Endeavour of Delphi Innovators (Project JEDI)        }
{								               }
{ You may retrieve the latest version of this file at the Project JEDI home    }
{ page, located at http://delphi-jedi.org or my personal homepage located at   }
{ http://members.chello.nl/m.vanbrakel2                                        }
{								               }
{ The contents of this file are used with permission, subject to the Mozilla   }
{ Public License Version 1.1 (the "License"); you may not use this file except }
{ in compliance with the License. You may obtain a copy of the License at      }
{ http://www.mozilla.org/MPL/MPL-1.1.html                                      }
{                                                                              }
{ Software distributed under the License is distributed on an "AS IS" basis,   }
{ WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for }
{ the specific language governing rights and limitations under the License.    }
{                                                                              }
{ Alternatively, the contents of this file may be used under the terms of the  }
{ GNU Lesser General Public License (the  "LGPL License"), in which case the   }
{ provisions of the LGPL License are applicable instead of those above.        }
{ If you wish to allow use of your version of this file only under the terms   }
{ of the LGPL License and not to allow others to use your version of this file }
{ under the MPL, indicate your decision by deleting  the provisions above and  }
{ replace  them with the notice and other provisions required by the LGPL      }
{ License.  If you do not delete the provisions above, a recipient may use     }
{ your version of this file under either the MPL or the LGPL License.          }
{ 								               }
{ For more information about the LGPL: http://www.gnu.org/copyleft/lesser.html }
{ 								               }
{******************************************************************************}

unit JwaWinBer;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "WinBer.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinLDAP, JwaWinType;

const
  LBER_ERROR   = DWORD($ffffffff);
  {$EXTERNALSYM LBER_ERROR}
  LBER_DEFAULT = DWORD($ffffffff);
  {$EXTERNALSYM LBER_DEFAULT}

type
  ber_tag_t = Cardinal;   // for BER tags
  {$EXTERNALSYM ber_tag_t}
  ber_int_t = Integer;    // for BER ints, enums, and Booleans
  {$EXTERNALSYM ber_int_t}
  ber_uint_t = Cardinal;  // unsigned equivalent of ber_int_t
  {$EXTERNALSYM ber_uint_t}
  ber_slen_t = Integer;   // signed equivalent of ber_len_t
  {$EXTERNALSYM ber_slen_t}

//
// This constructs a new BerElement structure containing a copy of the
// data in the supplied berval structure.
//

function ber_init(pBerVal: PBerVal): PBerElement; cdecl;
{$EXTERNALSYM ber_init}

//
// This frees a BerElement which is returned from ber_alloc_t()
// or ber_init(). The second argument - fbuf should always be set
// to 1.
//
//

procedure ber_free(pBerElement: PBerElement; fbuf: Integer); cdecl;
{$EXTERNALSYM ber_free}

//
// Frees a BERVAL structure. Applications should not call
// this API to free BERVAL structures which they themselves
// have allocated
//

procedure ber_bvfree(pBerVal: PBerVal); cdecl;
{$EXTERNALSYM ber_bvfree}

//
// Frees an array of BERVAL structures.
//

procedure ber_bvecfree(pBerVal: PBerVal); cdecl;
{$EXTERNALSYM ber_bvecfree}

//
// Returns a copy of a the supplied berval structure
//

function ber_bvdup(pBerVal: PBerVal): PBerVal; cdecl;
{$EXTERNALSYM ber_bvdup}

//
// Constructs and returns a BerElement structure. The options field
// contains a bitwise-or of options which are to be used when generating
// the encoding of the BerElement
//
// The LBER_USE_DER options should always be specified.
//

function ber_alloc_t(options: Integer): PBerElement; cdecl;
{$EXTERNALSYM ber_alloc_t}

//
// This skips over the current tag and returns the tag of the next
// element in the supplied BerElement. The lenght of this element is
// stored in the pLen argument.
//
// LBER_DEFAULT is returned if there is no further data to be read
// else the tag of the next element is returned.
//
// The difference between ber_skip_tag() and ber_peek_tag() is that the
// state pointer is advanced past the first tag+lenght and is pointed to
// the value part of the next element
//

function ber_skip_tag(pBerElement: PBerElement; var pLen: ULONG): ULONG; cdecl;
{$EXTERNALSYM ber_skip_tag}

//
// This returns the tag of the next element to be parsed in the
// supplied BerElement. The length of this element is stored in the
// pLen argument.
//
// LBER_DEFAULT is returned if there is no further data to be read
// else the tag of the next element is returned.
//

function ber_peek_tag(pBerElement: PBerElement; var pLen: ULONG): ULONG; cdecl;
{$EXTERNALSYM ber_peek_tag}

//
// This returns the tag and length of the first element in a SET, SET OF
// or SEQUENCE OF data value.
//
// LBER_DEFAULT is returned if the constructed value is empty else, the tag
// is returned. It also returns an opaque cookie which has to be passed to
// subsequent invocations of ber_next_element().
//

function ber_first_element(pBerElement: PBerElement; var pLen: ULONG; var ppOpaque: PChar): ULONG; cdecl;
{$EXTERNALSYM ber_first_element}

//
// This positions the state at the start of the next element in the
// constructed type.
//
// LBER_DEFAULT is returned if the constructed value is empty else, the tag
// is returned.
//

function ber_next_element(pBerElement: PBerElement; var pLen: ULONG; opaque: PChar): ULONG; cdecl;
{$EXTERNALSYM ber_next_element}

//
// This allocates a BerVal structure whose contents are taken from the
// supplied BerElement structure.
//
// The return values are 0 on success and -1 on error.
//

function ber_flatten(pBerElement: PBerElement; var pBerVal: PBerVal): Integer; cdecl;
{$EXTERNALSYM ber_flatten}

(*
The ber_printf() routine is used to encode a BER element in much the
same way that sprintf() works.  One important difference, though, is
that state information is kept in the ber argument so that multiple
calls can be made to ber_printf() to append to the end of the BER ele-
ment. ber MUST be a pointer to a BerElement returned by ber_alloc_t().
ber_printf() interprets and formats its arguments according to the for-
mat string fmt.  ber_printf() returns -1 if there is an error during
encoding and a non-negative number if successful.  As with sprintf(),
each character in fmt refers to an argument to ber_printf().
 
The format string can contain the following format characters:

't'     Tag.  The next argument is a ber_tag_t specifying the tag to
        override the next element to be written to the ber.  This works
        across calls.  The integer tag value SHOULD contain the tag
        class, constructed bit, and tag value.  For example, a tag of
        "[3]" for a constructed type is 0xA3U.  All implementations MUST
        support tags that fit in a single octet (i.e., where the tag
        value is less than 32) and they MAY support larger tags.

'b'     Boolean.  The next argument is an ber_int_t, containing either 0
        for FALSE or 0xff for TRUE.  A boolean element is output.  If
        this format character is not preceded by the 't' format modif-
        ier, the tag 0x01U is used for the element.

'e'     Enumerated.  The next argument is a ber_int_t, containing the
        enumerated value in the host's byte order.  An enumerated ele-
        ment is output.  If this format character is not preceded by the
        't' format modifier, the tag 0x0AU is used for the element.

'i'     Integer.  The next argument is a ber_int_t, containing the
        integer in the host's byte order.  An integer element is output.
        If this format character is not preceded by the 't' format
        modifier, the tag 0x02U is used for the element.

'n'     Null.  No argument is needed.  An ASN.1 NULL element is output.
        If this format character is not preceded by the 't' format
        modifier, the tag 0x05U is used for the element.
        
'o'     Octet string.  The next two arguments are a char *, followed by
        a ber_len_t with the length of the string.  The string MAY con-
        tain null bytes and are do not have to be zero-terminated.   An
        octet string element is output, in primitive form.  If this for-
        mat character is not preceded by the 't' format modifier, the
        tag 0x04U is used for the element.

's'     Octet string.  The next argument is a char * pointing to a
        zero-terminated string.  An octet string element in primitive
        form is output, which does not include the trailing '\0' (null)
        byte. If this format character is not preceded by the 't' format
        modifier, the tag 0x04U is used for the element.

'v'     Several octet strings.  The next argument is a char **, an array
        of char * pointers to zero-terminated strings.  The last element
        in the array MUST be a NULL pointer. The octet strings do not
        include the trailing '\0' (null) byte.  Note that a construct
        like '{v}' is used to get an actual SEQUENCE OF octet strings.
        The 't' format modifier cannot be used with this format charac-
        ter.

'V'     Several octet strings.  A NULL-terminated array of struct berval
        *'s is supplied.  Note that a construct like '{V}' is used to
        get an actual SEQUENCE OF octet strings. The 't' format modifier
        cannot be used with this format character.

'{'     Begin sequence.  No argument is needed.  If this format charac-
        ter is not preceded by the 't' format modifier, the tag 0x30U is
        used.

'}'     End sequence.  No argument is needed.  The 't' format modifier
        cannot be used with this format character.

'['     Begin set.  No argument is needed.  If this format character is
        not preceded by the 't' format modifier, the tag 0x31U is used.

']'     End set.  No argument is needed.  The 't' format modifier cannot
        be used with this format character.
*)

//WINBERAPI INT BERAPI ber_printf( BerElement *pBerElement, PCHAR fmt, ... );

(*
The ber_scanf() routine is used to decode a BER element in much the same
way that sscanf() works.  One important difference, though, is that some
state information is kept with the ber argument so that multiple calls
can be made to ber_scanf() to sequentially read from the BER element.
The ber argument SHOULD be a pointer to a BerElement returned by
ber_init().  ber_scanf interprets the bytes according to the format
string fmt, and stores the results in its additional arguments.
ber_scanf() returns LBER_ERROR on error, and a different value on suc-
cess.

The format string contains conversion specifications which are used to
direct the interpretation of the BER element.  The format string can
contain the following characters:

'a'     Octet string.  A char ** argument MUST be supplied.  Memory is
        allocated, filled with the contents of the octet string, zero-
        terminated, and the pointer to the string is stored in the argu-
        ment.  The returned value SHOULD be freed using ldap_memfree.
        The tag of the element MUST indicate the primitive form
        (constructed strings are not supported) but is otherwise ignored
        and discarded during the decoding.  This format cannot be used
        with octet strings which could contain null bytes.

'O'     Octet string.  A struct berval ** argument MUST be supplied,
        which upon return points to an allocated struct berval contain-
        ing the octet string and its length.  ber_bvfree() SHOULD be
        called to free the allocated memory.  The tag of the element
        MUST indicate the primitive form (constructed strings are not
        supported) but is otherwise ignored during the decoding.

'b'     Boolean.  A pointer to a ber_int_t MUST be supplied. The
        ber_int_t value stored will be 0 for FALSE or nonzero for TRUE.
        The tag of the element MUST indicate the primitive form but is
        otherwise ignored during the decoding.

'e'     Enumerated.  A pointer to a ber_int_t MUST be supplied. The
        enumerated value stored will be in host byte order.  The tag of
        the element MUST indicate the primitive form but is otherwise
        ignored during the decoding.  ber_scanf() will return an error
        if the value of the enumerated value cannot be stored in a
        ber_int_t.

'i'     Integer.  A pointer to a ber_int_t MUST be supplied. The
        ber_int_t value stored will be in host byte order.  The tag of
        the element MUST indicate the primitive form but is otherwise
        ignored during the decoding.  ber_scanf() will return an error
        if the integer cannot be stored in a ber_int_t.

'B'     Bitstring.  A char ** argument MUST be supplied which will point
        to the allocated bits, followed by a ber_len_t * argument, which
        will point to the length (in bits) of the bitstring returned.
        ldap_memfree SHOULD be called to free the bitstring.  The tag of
        the element MUST indicate the primitive form (constructed bit-
        strings are not supported) but is otherwise ignored during the
        decoding.

'n'     Null.  No argument is needed.  The element is verified to have a
        zero-length value and is skipped.  The tag is ignored.

'v'     Several octet strings.  A char *** argument MUST be supplied,
        which upon return points to an allocated NULL-terminated array
        of char *'s containing the octet strings.  NULL is stored if the
        sequence is empty.  ldap_memfree SHOULD be called to free each
        element of the array and the array itself.  The tag of the
        sequence and of the octet strings are ignored.

'V'     Several octet strings (which could contain null bytes).  A
        struct berval *** MUST be supplied, which upon return points to
        a allocated NULL-terminated array of struct berval *'s contain-
        ing the octet strings and their lengths.  NULL is stored if the
        sequence is empty. ber_bvecfree() can be called to free the
        allocated memory.  The tag of the sequence and of the octet
        strings are ignored.

'x'     Skip element.  The next element is skipped.  No argument is
        needed.

'{'     Begin sequence.  No argument is needed.  The initial sequence
        tag and length are skipped.

'}'     End sequence.  No argument is needed.

'['     Begin set.  No argument is needed.  The initial set tag and
        length are skipped.

']'     End set.  No argument is needed.

*)

//WINBERAPI ULONG BERAPI ber_scanf( BerElement *pBerElement, PCHAR fmt, ... );


implementation

const
  winberapi = 'wldap32.dll';

function ber_init; external winberapi name 'ber_init';
procedure ber_free; external winberapi name 'ber_free';
procedure ber_bvfree; external winberapi name 'ber_bvfree';
procedure ber_bvecfree; external winberapi name 'ber_bvecfree';
function ber_bvdup; external winberapi name 'ber_bvdup';
function ber_alloc_t; external winberapi name 'ber_alloc_t';
function ber_skip_tag; external winberapi name 'ber_skip_tag';
function ber_peek_tag; external winberapi name 'ber_peek_tag';
function ber_first_element; external winberapi name 'ber_first_element';
function ber_next_element; external winberapi name 'ber_next_element';
function ber_flatten; external winberapi name 'ber_flatten';
//function ber_printf; external winberapi name 'ber_printf';
//function ber_scanf; external winberapi name 'ber_scanf';

end.
