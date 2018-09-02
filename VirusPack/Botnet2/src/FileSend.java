/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Nathan
 */
public class FileSend implements Handler {

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";upload")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Sending file " + args[1] + " to " + args[2]);
            sendFile(args[1], args[2]);
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " File sent!");
            return true;
        }
        return false;
    }

    public static void sendFile(String file, String nick) {
        IRC.sendRawData("DCC SEND" + nick + " " + file);
    }
}
