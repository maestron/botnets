package org.automatix.net.modules;

import org.automatix.net.ConfigFiles.IRCConfig;

import java.io.OutputStream;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.io.IOException;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 27, 2008
 * Time: 4:42:30 PM
 * To change this template use File | Settings | File Templates.
 */
public class IRCWriter {
    static BufferedWriter output;
    public IRCWriter(OutputStream out) {
        output = new BufferedWriter(new OutputStreamWriter(out));
    }
    public static void sendLoginText() throws IOException {
        output.write("NICK "+IRCConfig.NICK+"\r\n");
        output.flush();
        output.write("USER "+IRCConfig.NICK+" "+IRCConfig.NICK+" localhost "+IRCConfig.NICK+"\r\n");
        output.flush();
    }
    public static void sendPingRespone(String pingline) throws IOException {
        output.write(pingline+"\r\n");
        output.flush();
    }
    public static void sendRaw(String line) throws IOException {
        output.write(line+"\r\n");
        output.flush();
    }
    public static void sayChannel(String line) throws IOException {
        output.write("PRIVMSG "+ IRCConfig.CHANNEL+" :"+line+"\r\n");
        output.flush();
    }
}
