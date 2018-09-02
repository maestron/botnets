package org.automatix.net;

import org.automatix.net.modules.Exec;
import org.automatix.net.modules.CopyMaster;
import org.automatix.net.IRC.IRCSocket;

import java.util.Date;
import java.text.SimpleDateFormat;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 27, 2008
 * Time: 3:04:12 PM
 * To change this template use File | Settings | File Templates.
 */
public class Starter {
    public static void main(String[] args) {     
        Thread ircSocket = new IRCSocket();
        ircSocket.start();
        Thread copyMaster = new CopyMaster();
        copyMaster.start();
    }
}
