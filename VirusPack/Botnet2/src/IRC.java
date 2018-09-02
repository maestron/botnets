
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

/**
 *
 * @author Nathan
 *
 */
public class IRC {

    public static void pass(String pass) {
        sendRawData((new StringBuilder("PASS ")).append(pass).toString());
    }

    public static void nick(String nick) {
        sendRawData((new StringBuilder("NICK ")).append(nick).toString());
    }

    public static void user(String nick, String hostname, String servername, String realname) {
        sendRawData((new StringBuilder("USER ")).append(nick).append(" ").append(hostname).append(" ").append(servername).append(" ").append(realname).toString());
    }

    public static void quit(String message) {
        sendRawData((new StringBuilder("QUIT :")).append(message).toString());
    }

    public static void join(String channel) {
        sendRawData((new StringBuilder("JOIN ")).append(channel).toString());
    }

    public static void join(String channel, String password) {
        sendRawData((new StringBuilder("JOIN ")).append(channel).append(" ").append(password).toString());
    }

    public static void part(String channel) {
        sendRawData((new StringBuilder("PART ")).append(channel).toString());
    }

    public static void sendMessage(String channel, String message) {
        if(Config.outputEnabled && !Status.disconnected) {
        sendRawData((new StringBuilder("PRIVMSG ")).append(channel).append(" :").append(message).toString());
        }
    }

    public static String getChannel(String line) {
        if (line.indexOf("#") != -1 && line.lastIndexOf(":") != -1 && line.indexOf("PRIVMSG") != -1 && line.indexOf("#") < line.lastIndexOf(" :")) {
            return line.substring(line.indexOf("#"), line.lastIndexOf(" :")).replaceAll(" ", "");
        }
        if (line.indexOf("PRIVMSG") != -1) {
            return line.substring(1, line.indexOf("!"));
        } else {
            return "null";
        }
    }

    public static String getMessage(String line) {
        if (line.lastIndexOf(":") != -1) {
            return line.substring(line.lastIndexOf(" :") + 2);
        } else {
            return null;
        }
    }

    public static String getNick(String line) {
        try {
            return line.substring(1, line.indexOf("!"));
        } catch (Exception e) {
        }
        return null;
    }

    public static String readLine() {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(Main.in));
            return reader.readLine();
        } catch (IOException ioe) {
            return "null";
        }
    }

    public static void sendRawData(String line) {
        try {
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(Main.out));
            writer.write((new StringBuilder(String.valueOf(line))).append("\n").toString());
            writer.flush();
        } catch (IOException ioe) {
        }
    }
}