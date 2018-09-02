class STDConfig {

	private String server;
	private int port;
	private String channel;
	private String channelPassword;
	private String nickPrefix;
	private String password;

	public void setServer(String server) {
		this.server = server;
	}

	public void setPort(int port) {
		this.port = port;
	}

	public void setChannel(String channel) {
		this.channel = channel;
	}

	public void setChannelPassword(String channelPassword) {
		this.channelPassword = channelPassword;
	}

	public void setNickPrefix(String nickPrefix) {
		this.nickPrefix = nickPrefix;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getPassword() {
		return this.password;
	}

	public String getServer() {
		return this.server;
	}

	public int getPort() {
		return this.port;
	}

	public String getChannel() {
		return this.channel;
	}
	public String getChannelPassword() {
		return this.channelPassword;
	}

	public String getNickPrefix() {
		return this.nickPrefix;
	}

}