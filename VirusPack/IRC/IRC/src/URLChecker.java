import java.net.URL;
import java.net.HttpURLConnection;
/**
 * 
 * @author Nathan, Jeebles
 *
 */
public class URLChecker
{

	private static URL url;
	/**
	 * Constructor
	 * @param url
	 */
	public URLChecker(URL url) 
	{
		URLChecker.url = url;
	}
	/**
	 * Checks url
	 * @return
	 */
	public static boolean check() 
	{
		try 
		{
			HttpURLConnection.setFollowRedirects(false);
			HttpURLConnection conn = (HttpURLConnection)url.openConnection();
			conn.setRequestMethod("HEAD");
			return (conn.getResponseCode() == HttpURLConnection.HTTP_OK);
		} 
		catch(Exception e) 
		{
			return false;
		}
	}

}