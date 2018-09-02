import java.io.IOException;

class IRCSpammer extends Thread {

	private STDIRCSocket ircSocket;
	private STDConfig conf;

	private IRC controllerIRC;
	private String controllerChannel;

	private String message;
	private int times;
	private int delay;

	private int count = 0;

	public IRCSpammer(IRC controllerIRC, String controllerChannel, String host, int port, String channel, String channelPassword, String nickPrefix, String message, int times, int delay) {
		this.controllerIRC = controllerIRC;
		this.controllerChannel = controllerChannel;
		this.conf = new STDConfig();
		this.conf.setServer(host);
		this.conf.setPort(port);
		this.conf.setChannel(channel);
		this.conf.setChannelPassword(channelPassword);
		this.conf.setNickPrefix(nickPrefix);
		this.ircSocket = new STDIRCSocket(this.controllerIRC, this.controllerChannel, this.conf);
		this.ircSocket.init();
		this.message = message;
		this.times = times;
		this.delay = delay;
		this.start();
	}

	public void run() {
		this.ircSocket.controllerIRC().sendMessage(this.controllerChannel, "Successfully initiated IRC spammer! (Spamming " + this.conf.getServer() + ":" + this.conf.getPort() + " " + this.conf.getChannel() + ")");
		this.ircSocket.controllerIRC().sendMessage(this.controllerChannel, "Spamming started!");
		while(SpammingStatus.spamming && (count < times || times == 0)) {
			this.ircSocket.getIRC().sendMessage(this.conf.getChannel(), this.message);
			count++;
			try {
				this.sleep(this.delay);
			} catch(InterruptedException ie) {
			}
		}
		try {
			this.ircSocket.getSocket().close();
		} catch(IOException ioe) {
		} finally {
			this.ircSocket.controllerIRC().sendMessage(this.controllerChannel, "Finished spamming " + this.conf.getServer() + ":" + this.conf.getPort() + " " + this.conf.getChannel());
		}
	}

}