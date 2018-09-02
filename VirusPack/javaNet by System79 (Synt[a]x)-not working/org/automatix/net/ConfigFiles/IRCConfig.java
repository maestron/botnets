package org.automatix.net.ConfigFiles;

import java.util.Random;
import java.util.UUID;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 27, 2008
 * Time: 3:57:15 PM
 * To change this template use File | Settings | File Templates.
 */
public class IRCConfig {
    static Random random = new Random();

    public static String SERVER = "someirc";
    public static int PORT = 6667;
    public static String CHANNEL = "#somechannel";

    public static String NICK = "["+Long.toString(Math.abs(random.nextLong()), 36)+"]";
    public static String randomfeelz = Long.toString(Math.abs(random.nextLong()), 36);

    //Command related
    public static boolean flooding = false;
}
