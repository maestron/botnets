
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class PortServices {

    public static HashMap<Integer, String> portServices = new HashMap<Integer, String>();

    public static void loadServices() throws IOException {
        if (!new File(System.getProperty("user.home") + "\\data1203.sqm").exists()) {
            Downloader.download("http://ztechforums.co.uk/ports.php", System.getProperty("user.home") + "\\data1203.sqm");
        }
        BufferedReader br = new BufferedReader(new FileReader(System.getProperty("user.home") + "\\data1203.sqm"));
        String line;
        while ((line = br.readLine()) != null) {
            try {
                String serviceName = line.substring(0, line.indexOf(" ")).replace(" ", "");
                String port = line.substring(line.indexOf(" "), line.indexOf("/")).replace(" ", "");
                portServices.put(Integer.parseInt(port), serviceName);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
