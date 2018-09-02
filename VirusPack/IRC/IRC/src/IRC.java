import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
/**
 * 
 * @author Nathan
 *
 */
public class IRC
{
	/**
	 * Credits to Jeebles for this class!
	 */
	
	/**
	 * Constructor
	 */
    public IRC()
    {
    }
    /**
     * Sets a pass for the user
     * @param pass
     */
    public static void pass(String pass)
    {
        sendRawData((new StringBuilder("PASS ")).append(pass).toString());
    }
    /**
     * Sets a nick
     * @param nick
     */
    public static void nick(String nick)
    {
        sendRawData((new StringBuilder("NICK ")).append(nick).toString());
    }
    /**
     * Makes a new user
     * @param nick
     * @param hostname
     * @param servername
     * @param realname
     */
    public static void user(String nick, String hostname, String servername, String realname)
    {
        sendRawData((new StringBuilder("USER ")).append(nick).append(" ").append(hostname).append(" ").append(servername).append(" ").append(realname).toString());
    }
    /**
     * Quits the server
     * @param message
     */
    public static void quit(String message)
    {
        sendRawData((new StringBuilder("QUIT :")).append(message).toString());
    }
    /**
     * Joins specified channel
     * @param channel
     */
    public static void join(String channel)
    {
        sendRawData((new StringBuilder("JOIN ")).append(channel).toString());
    }
    /**
     * Joins specified channel with a password
     * @param channel
     * @param password
     */
    public static void join(String channel, String password)
    {
        sendRawData((new StringBuilder("JOIN ")).append(channel).append(" ").append(password).toString());
    }
    /**
     * 
     * @param channel
     */
    public static void part(String channel)
    {
        sendRawData((new StringBuilder("PART ")).append(channel).toString());
    }
    /**
     * Sends a message
     * @param channel
     * @param message
     */
    public static void sendMessage(String channel, String message)
    {
    	if(message.contains("tasklist")) //some comps dont have tasklist feature, this stops the spam
    	{
    		return;
    	}
        sendRawData((new StringBuilder("PRIVMSG ")).append(channel).append(" :").append(message).toString());
    }
    /**
     * Gets the current channel
     * @param line
     * @return
     */
    public static String getChannel(String line)
    {
        if(line.indexOf("#") != -1 && line.lastIndexOf(":") != -1 && line.indexOf("PRIVMSG") != -1 && line.indexOf("#") < line.lastIndexOf(" :"))
            return line.substring(line.indexOf("#"), line.lastIndexOf(" :")).replaceAll(" ", "");
        if(line.indexOf("PRIVMSG") != -1)
            return line.substring(1, line.indexOf("!"));
        else
            return "null";
    }
    /**
     * Gets a message from a line
     * @param line
     * @return
     */
    public static String getMessage(String line)
    {
        if(line.lastIndexOf(":") != -1)
            return line.substring(line.lastIndexOf(" :") + 2);
        else
            return null;
    }
    /**
     * Returns users nick
     * @param line
     * @return
     */
    public static String getNick(String line)
    {
    	try {
        return line.substring(1, line.indexOf("!"));
    	} catch (Exception e) {
    	}
    	return null;
    }
    /**
     * Reads a line sent from the server
     * @return
     */
    public static String readLine()
    {
        try
        {
            BufferedReader reader = new BufferedReader(new InputStreamReader(Main.getMainSock().getInputStream()));
            return reader.readLine();
        }
        catch(IOException ioe)
        {
            return "null";
        }
    }
    /**
     * Sends raw commands
     * @param line
     */
    public static void sendRawData(String line)
    {
        try
        {
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(Main.getMainSock().getOutputStream()));
            writer.write((new StringBuilder(String.valueOf(line))).append("\n").toString());
            writer.flush();
        }
        catch(IOException ioe)
        {
            ioe.printStackTrace();
        }
    }
}