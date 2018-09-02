package org.automatix.net.modules;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 29, 2008
 * Time: 10:18:25 PM
 * To change this template use File | Settings | File Templates.
 */
public class IPGrabber extends Thread {
    public static String getIPAddress(String url) {
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader((new URL(url)).openStream()));
			return reader.readLine();
		} catch(IOException ioe) {
			return "IOException thrown: " + ioe.toString();
		}
	}
    public void run() {
        try {
            IRCReader.ircWriter.sayChannel("My IP Address is: "+getIPAddress("http://whatismyip.com/automation/n09230945.asp"));
        } catch (IOException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
    }

}
