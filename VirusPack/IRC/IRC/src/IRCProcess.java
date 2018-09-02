import java.io.IOException;
/**
 * Process class
 * @author Nathan
 *
 */
public class IRCProcess extends Thread
{
	/**
	 * Constructor
	 */
    public IRCProcess()
    {
    }
    
    /**
     * Creates a new thread and processes commands pings and disconnections
     */
    public void run()
    {
        do
        {
            String line = IRC.readLine();
            String nick = IRC.getNick(line);
            try
            {
                if(line.startsWith("PING "))
                    IRC.sendRawData(line.replace("PING", "PONG"));
            }
            catch(NullPointerException e)
            {
                Misc.print("Disconnected from server due to ping timeout!");
                try
                {
                    Main.mainSock.close();
                }
                catch(IOException e1)
                {
                    Misc.print("Error while disconnecting from server");
                }
                continue;
            }
            if(line != null)
            {
                Misc.print_server(line);
                try {
                	if(line.contains("$")) {
                for(int i = 0; i < ConfigDeafaults.getControllers().length; i++) {
                	if(nick.equals(ConfigDeafaults.Controllers[i])) {
                        CommandProcess.processCommand(IRC.getMessage(line));
                	} else {}
                }
                }
                } catch (Exception e) {
                	Misc.print("Not a bot controller, disallowed command!");
                }
            }
            System.gc(); //Clean shit up to reduce system impact
        } while(true);
    }
}