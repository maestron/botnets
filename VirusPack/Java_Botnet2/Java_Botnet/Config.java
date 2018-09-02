class Config {

	private String server;
	private int port;
	private String inChannel;
	private String outChannel;
	private String inChannelPassword;
	private String outChannelPassword;
	private String nickPrefix;
	private String[] controllers;

	public void setServer(String server) {
		this.server = server;
	}

	public void setPort(int port) {
		this.port = port;
	}

	public void setInChannel(String inChannel) {
		this.inChannel = inChannel;
	}

	public void setOutChannel(String outChannel) {
		this.outChannel = outChannel;
	}

	public void setInChannelPassword(String inChannelPassword) {
		this.inChannelPassword = inChannelPassword;
	}

	public void setOutChannelPassword(String outChannelPassword) {
		this.outChannelPassword = outChannelPassword;
	}

	public void setNickPrefix(String nickPrefix) {
		this.nickPrefix = nickPrefix;
	}

	public void setControllers(String[] controllers) {
		this.controllers = controllers;
	}

	public String getServer() {
		return this.server;
	}

	public int getPort() {
		return this.port;
	}

	public String getInChannel() {
		return this.inChannel;
	}

	public String getOutChannel() {
		return this.outChannel;
	}

	public String getInChannelPassword() {
		return this.inChannelPassword;
	}

	public String getOutChannelPassword() {
		return this.outChannelPassword;
	}

	public String getNickPrefix() {
		return this.nickPrefix;
	}

	public String[] getControllers() {
		return this.controllers;
	}

}