
import java.util.ArrayList;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class Log implements Handler {

    private static ArrayList<String> logList = new ArrayList<String>();

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";printlogs")) {
            printLogs();
            return true;
        } else if (args[0].equals(";searchlog")) {
            searchLogs(args[1]);
            return true;
        } else if (args[0].equals(";deletelogs")) {
            IRC.sendMessage(Config.channel, " Clearing logs!");
            clearLog();
            IRC.sendMessage(Config.channel, " All logs were cleared!");
            return true;
        } else if (args[0].equals(";deleteonelog")) {
            IRC.sendMessage(Config.channel, " Deleting log "+logList.get(Integer.parseInt(args[1])));
            deleteLog(Integer.parseInt(args[1]));
            IRC.sendMessage(Config.channel, " Log deleted!");
            return true;
        } else if (args[0].equals(";getlog")) {
            IRC.sendMessage(Config.channel, getLogLine(Integer.parseInt(args[1])));
        }
        return false;
    }

    public static void addLog(String s) {
        logList.add(s);
    }

    public static void printLogs() {
        int i = 0;
        for(String s : logList) {
            IRC.sendMessage(Config.channel, s+":"+i);
            i++;
        }
    }

    public static void searchLogs(String term) {
        for (String s : logList) {
            if (s.contains(term)) {
                IRC.sendMessage(Config.channel, "Term found: " + s);
            }
        }
        IRC.sendMessage(Config.channel, "Searching finished!");
    }

    public static void deleteLog(int log) {
        logList.remove(log);
    }

    public static String getLogLine(int line) {
        return logList.get(line);
    }

    public static int getLogSize() {
        return logList.size();
    }

    public static void clearLog() {
        logList.clear();
    }
}
