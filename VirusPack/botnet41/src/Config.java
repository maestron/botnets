class Config {

	private String server = ConfigDefaults.SERVER;
	private int port = ConfigDefaults.PORT;
	private String inChannel = ConfigDefaults.IN_CHANNEL;
	private String outChannel = ConfigDefaults.OUT_CHANNEL;
	private String inChannelPassword = ConfigDefaults.CHANNEL_IN_PASSWORD;
	private String botPassowrd = ConfigDefaults.PASSWORD_BOT;
	private String outChannelPassword = ConfigDefaults.CHANNEL_OUT_PASSWORD;
	private String nickPrefix = ConfigDefaults.NICK_PREFIX;
	private String[] controllers = ConfigDefaults.CONTROLLERS;
	public static boolean botsUnlocked = false;
	
	public static void setBotsUnlocked(boolean bots) {
		botsUnlocked = bots;
	}
	
	public static boolean getBotsUnlocked() {
		return botsUnlocked;
	}
	
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
		for (int i = 0; i < controllers.length; i++)
		Debug.print("Controllers "+controllers[i]+"\n");
		return this.controllers;
	}

	public void setBotPassowrd(String botPassowrd) {
		this.botPassowrd = botPassowrd;
	}
    public static String getNick()
    {
        return (new StringBuilder(getPrefix())).append(ConfigDefaults.NICK_PREFIX).append(getSuffix()).toString();
    }
    public static String getPrefix()
    {
        return ConfigDefaults.NICK_PREFIX;
    }
    public static String getSuffix()
    {
        return ConfigDefaults.NICK_PREFIX;
    }
}