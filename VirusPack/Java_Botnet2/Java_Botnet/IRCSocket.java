import java.net.Socket;
import java.io.IOException;

class IRCSocket {

	private int trys = 0;

	private IRC irc;
	private Config conf;

	private Socket socket;

	private String nick;

	private ExternalSettings externalSettings;

	public IRCSocket(Config conf) {
		this.irc = new IRC(this);
		this.conf = conf;
		this.externalSettings = new ExternalSettings();
		if(this.externalSettings.iniExists()) {
			this.externalSettings.load();
		}
	}

	public void init() {
		if(this.trys > 5) {
			System.exit(-1);
		} else {
			try {
				this.connect();
			} catch(IOException ioe) {
				Debug.print(ioe.toString() + "\n");
				this.trys++;
				this.init();
			}
		}
	}
	
	public void connect() throws IOException {
		Debug.print("Connecting to  " + this.conf.getServer() + ":" + this.conf.getPort() + "... ");
		this.socket = new Socket(this.conf.getServer(), this.conf.getPort());
		Debug.print("connected\n");
		this.socket.setTcpNoDelay(true);
		this.irc.pass("password");
		if(!this.externalSettings.iniExists() || this.externalSettings.properties.getProperty("PERM_NICK") == null) {
			this.nick = this.conf.getNickPrefix() + "-" + Util.randomNumber();
		} else {
			this.nick = this.externalSettings.properties.getProperty("PERM_NICK"); //+ "-" + Util.randomNumber();
		}
		this.irc.nick(nick);
		this.irc.user(nick, Util.getIPAddress(), this.conf.getServer(), Util.getUsername());
		this.irc.join(this.conf.getInChannel(), this.conf.getInChannelPassword());
		this.irc.join(this.conf.getOutChannel(), this.conf.getOutChannelPassword());
	}

	public boolean connected() {
		return this.socket.isConnected();
	}

	public void disconnect() {
		try {
			this.socket.close();
		} catch(IOException ioe) {
			Debug.print("Couldn't disconnect, IOException thown: " + ioe.toString() + "\n");
		}
	}

	public Config getConfig() {
		return this.conf;
	}

	public IRC getIRC() {
		return this.irc;
	}

	public Socket getSocket() {
		return this.socket;
	}

	public String getNick() {
		return this.nick;
	}

	public ExternalSettings getExternalSettings() {
		return this.externalSettings;
	}
}