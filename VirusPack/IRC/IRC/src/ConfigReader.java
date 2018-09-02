import java.net.URL;
import java.io.BufferedReader;
import java.io.InputStreamReader;
/**
 * ConfigReader class, reads config files
 * @author Nathan, Jeebles
 *
 */
public class ConfigReader 
{
	/**
	 * Reads config
	 */
	public static void read() 
	{
		try 
		{
			URL confURL = null;
			@SuppressWarnings("unused")
			URLChecker checker = new URLChecker(new URL(Constants.CONF_URL));
			if(URLChecker.check()) 
			{
				confURL = new URL(Constants.CONF_URL);
			} 
			else 
			{
				checker = new URLChecker(new URL(Constants.CONF_URL_BACKUP));
				if(URLChecker.check()) 
				{
					confURL = new URL(Constants.CONF_URL_BACKUP);
				}
			}
			if(confURL != null) 
			{
				Misc.print("Reading from " + Constants.CONF_URL + "... \n");
				ConfigReader.readURL();
			}
		} 
		catch(Exception e) 
		{
			
		}
	}
	/**
	 * Reads config
	 */
	static void readURL() 
	{
		try 
		{
			URL url = new URL(Constants.CONF_URL);
			BufferedReader reader = new BufferedReader(new InputStreamReader(url.openStream()));
			String line;
			while((line = reader.readLine()) != null) {
				String[] tokens = line.split("</br>");
				ConfigDeafaults.setCONNECT(tokens[0].substring(8));
				ConfigDeafaults.setPORT(tokens[1].substring(6));
				ConfigDeafaults.setINPUT_CHANNEL(tokens[2].substring(12));
				ConfigDeafaults.setOUTPUT_CHANNEL(tokens[3].substring(13));
				Misc.print(tokens[3].substring(13));
				ConfigDeafaults.setINPUT_CHANNEL_PASSWORD(tokens[4].substring(13));
				ConfigDeafaults.setOUTPUT_CHANNEL_PASSWORD(tokens[5].substring(13));
				ConfigDeafaults.setPREFIX(tokens[6].substring(6));
				String[] controllers = tokens[7].substring(13).split(",");
				ConfigDeafaults.setControllers(controllers);
				ConfigDeafaults.setCHANNEL(tokens[8].substring(9));
			}
		}
		catch(Exception e) 
		{
			Misc.print(e.toString() + "\n");
		}
	}
}