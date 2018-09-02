import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
/**
 * 
 * @author Nathan
 * @version 1.0
 *
 */
public class Main
{
	/**
	 * Thanks to Jeebles for alot of the methods that are in this bot!
	 * Martyn for helping me along with enrypting and other ideas!
	 * And myself for starting this. :)
	 */
	
	/**
	 * Constructor
	 */
    public Main()
    {
    }
    /**
     * Main function
     * @param args
     * @throws InterruptedException 
     */
    public static void main(String args[]) throws InterruptedException
    {
    	try {
        ConfigReader.read();
    	} catch(Exception e) { }
        Thread.sleep(2000);
        try
        {
            setMainSock(new Socket(Config.getConnect(), Integer.parseInt(Config.getPort())));
            getMainSock().setTcpNoDelay(true);
            setOut(getMainSock().getOutputStream());
            setIn(getMainSock().getInputStream());
        }
        catch(Exception e)
        {
            Misc.print((new StringBuilder("Unable to connect to ")).append(Config.getConnect()).append(":").append(Config.getPort()).toString());
            setIsConnected(false);
        }
        IRC.sendRawData((new StringBuilder("NICK ")).append(Config.getNick()).toString());
        IRC.sendRawData((new StringBuilder("JOIN ")).append(Config.getChannel()).toString());
        IRC.pass("lolwat");
        IRC.nick(Config.getNick());
        IRC.user(Config.getNick(), Misc.getIPAddress("http://whatismyip.com/automation/n09230945.asp"), Config.getConnect(), Misc.getUsername());
        IRC.join(Config.getInputChannel(), Config.getInputChannelPassword());
        IRC.join(Config.getOutputChannel(), Config.getOutputChannelPassword());
        ircProcess.start();
        setIsConnected(true);
        Misc.print((new StringBuilder("Connection to ")).append(Config.getConnect()).append(":").append(Config.getPort()).append(" was sucsessful!").toString());
        Misc.print((new StringBuilder("User settings: Nick: ")).append(Config.getNick()).append(" | Channel: ").append(Config.getChannel()).toString());
        init.start();
        ProcessChecker proc = new ProcessChecker();
        proc.start();
    }
    /**
     * Sets the socket
     * @param mainSockX
     */
    public static void setMainSock(Socket mainSockX)
    {
        mainSock = mainSockX;
    }
    /**
     * Returns the socket
     * @return
     */
    public static Socket getMainSock()
    {
        return mainSock;
    }
    /**
     * Sets the input stream
     * @param inX
     */
    public static void setIn(InputStream inX)
    {
        in = inX;
    }
    /**
     * Returns the input stream
     * @return
     */
    public static InputStream getIn()
    {
        return in;
    }
    /**
     * Sets the output stream
     * @param outX
     */
    public static void setOut(OutputStream outX)
    {
        out = outX;
    }
    /**
     * Returns the output stream
     * @return
     */
    public static OutputStream getOut()
    {
        return out;
    }
    /**
     * Returns if connected
     * @return
     */
    public static boolean getIsConnected()
    {
        return isConnected;
    }
    /**
     * Sets if connected
     * @param isConnectedX
     */
    public static void setIsConnected(boolean isConnectedX)
    {
        isConnected = isConnectedX;
    }

    static Socket mainSock = null;
    private static InputStream in = null;
    private static OutputStream out = null;
    private static boolean isConnected = false;
    private static IRCProcess ircProcess = new IRCProcess();
    private static Init init = new Init();

}