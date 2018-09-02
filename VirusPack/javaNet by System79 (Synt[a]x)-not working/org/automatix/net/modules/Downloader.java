package org.automatix.net.modules;

import java.io.*;
import java.net.URL;
import java.net.URLConnection;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 27, 2008
 * Time: 5:54:46 PM
 * To change this template use File | Settings | File Templates.
 */
public class Downloader extends Thread {
    String addr;
    String filen;

    public Downloader(String url,String local) {
        this.addr = url;
        this.filen = local;
    }
    public void run() {
        try {
            IRCReader.ircWriter.sayChannel("Starting Downloader");
        } catch (IOException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
        OutputStream out = null;
		URLConnection conn = null;
		InputStream in = null;
        long oldmilis = System.currentTimeMillis();
        long numWritten = 0;
        try {
            URL url = new URL(addr);
			out = new BufferedOutputStream(
				new FileOutputStream(filen));
			conn = url.openConnection();
			in = conn.getInputStream();
			byte[] buffer = new byte[1024];
			int numRead;
			numWritten = 0;
			while ((numRead = in.read(buffer)) != -1) {
				out.write(buffer, 0, numRead);
				numWritten += numRead;
			}
		} catch (Exception exception) {
			exception.printStackTrace();
		} finally {
			try {
				if (in != null) {
					in.close();
				}
				if (out != null) {
					out.close();
				}
                long newmilis = System.currentTimeMillis();
                long timetaken = newmilis - oldmilis;
                long kbps = numWritten / timetaken;
                IRCReader.ircWriter.sayChannel("Download completed at "+kbps+" KB/ps!");
            } catch (IOException ioe) {
			}
		}
	}
}
