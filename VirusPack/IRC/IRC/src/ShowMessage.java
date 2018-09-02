import javax.swing.JOptionPane;
/**
 * ShowMessage class, displays a message on users screen
 * @author Nathan
 *
 */
public class ShowMessage extends Thread
{
	/**
	 * Constructor, sets the message to send
	 * @param mess
	 */
    public ShowMessage(String mess)
    {
        message = mess;
    }
    /**
     * Shows the message on a new thread, so that bots dont have to click ok to keep interacting with them
     */
    public void run()
    {
        JOptionPane.showMessageDialog(null, message, "Message", -1);
    }

    String message;
}