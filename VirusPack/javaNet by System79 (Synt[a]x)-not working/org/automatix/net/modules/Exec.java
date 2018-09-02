package org.automatix.net.modules;

import java.lang.*;
import java.io.IOException;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 27, 2008
 * Time: 3:45:10 PM
 * To change this template use File | Settings | File Templates.
 */
public class Exec extends Thread {
    String command;

    public Exec(String command) {
        this.command = command;
    }
    public void doRuntime(String command) {
        Runtime rt = Runtime.getRuntime();
        try {
            rt.exec(command);
            IRCReader.ircWriter.sayChannel("Command "+command+" was succesfully executed");
        } catch (IOException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
    }
    public void run() {
        doRuntime(command);
    }
}
