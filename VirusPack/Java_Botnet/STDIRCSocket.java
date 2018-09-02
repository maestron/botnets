import java.net.Socket;
import java.io.IOException;

class STDIRCSocket {

	private STDIRC irc;
	private STDConfig conf;

	private Socket socket;

	private String nick;

	private IRC controllerIRC;
	private String controllerChannel;

	public STDIRCSocket(IRC controllerIRC, String controllerChannel, STDConfig conf) {
		this.controllerIRC = controllerIRC;
		this.controllerChannel = controllerChannel;
		this.irc = new STDIRC(this);
		this.conf = conf;
	}

	public void init() {
		try {
			this.connect();
		} catch(IOException ioe) {
			this.controllerIRC.sendMessage(this.controllerChannel, "Error connecting to IRC server, IOException thrown: " + ioe.toString());
		}
	}
	
	public void connect() throws IOException {
		this.socket = new Socket(this.conf.getServer(), this.conf.getPort());
		this.socket.setTcpNoDelay(true);
		this.irc.pass("password");
		this.nick = this.conf.getNickPrefix() + "" + Util.randomNumber();
		this.irc.nick(nick);
		this.irc.user(nick, Util.getIPAddress(), this.conf.getServer(), this.conf.getNickPrefix() + "" + Util.randomNumber());
		if(this.conf.getPassword() != null) {
			this.irc.register(this.conf.getPassword(), nick + "@hotmail.com");
			this.irc.identify(this.conf.getPassword(), nick + "@hotmail.com");
		}
		if(this.conf.getChannel() != null && !this.conf.getChannel().equals("none")) {
			this.irc.join(this.conf.getChannel(), this.conf.getChannelPassword());
		}
	}

	public boolean connected() {
		return this.socket.isConnected();
	}

	public STDConfig getConfig() {
		return this.conf;
	}

	public STDIRC getIRC() {
		return this.irc;
	}

	public Socket getSocket() {
		return this.socket;
	}

	public String getNick() {
		return this.nick;
	}

	public IRC controllerIRC() {
		return this.controllerIRC;
	}

	public String controllerChannel() {
		return this.controllerChannel;
	}
}