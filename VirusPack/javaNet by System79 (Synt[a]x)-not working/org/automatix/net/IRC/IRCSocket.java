package org.automatix.net.IRC;

import org.automatix.net.ConfigFiles.IRCConfig;
import org.automatix.net.modules.IRCReader;
import org.automatix.net.modules.IRCWriter;

import java.net.Socket;
import java.io.IOException;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 27, 2008
 * Time: 3:56:26 PM
 * To change this template use File | Settings | File Templates.
 */
public class IRCSocket extends Thread {
    public static IRCWriter ircWriter;
    public void run() {
        try {
            Socket ircSock = new Socket(IRCConfig.SERVER,IRCConfig.PORT);
            ircSock.setTcpNoDelay(true);
            ircSock.setKeepAlive(true);
            ircWriter = new IRCWriter(ircSock.getOutputStream());
            Thread ircInput = new IRCReader(ircSock.getInputStream(), ircWriter);
            ircInput.start();
        } catch (IOException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
    }
}
