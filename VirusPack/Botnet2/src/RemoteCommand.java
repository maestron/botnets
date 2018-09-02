
import java.io.BufferedReader;
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
public class RemoteCommand {

    public static String lastCommand = "";

    public static void readRemoteCommand() throws Exception {
        System.out.println("Reading remote cmd!");
        URL url = new URL("http://www.ztechforums.co.uk/command.php");
        BufferedReader br = new BufferedReader(new InputStreamReader(url.openStream()));
        String line = br.readLine();
        if(line.equals(lastCommand)) {
            return;
        }
        String[] args = Misc.splitArgs(line);
        new Command(args[0], "EpicPanda", args);
        lastCommand = line;
        br.close();
    }
}
