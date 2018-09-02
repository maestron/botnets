import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

class SystemExec extends Thread {

	private String exec;
	private IRC irc;
	private String channel;

	public SystemExec(String exec, IRC irc, String channel) {
		this.exec = exec;
		this.irc = irc;
		this.channel = channel;
		this.start();
	}

	public void run() {
		try {
			Process process = Runtime.getRuntime().exec(this.exec.split(" "));
			BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
			String line;
			while((line = reader.readLine()) != null) {
				this.irc.sendMessage(this.channel, line);
				try {
					this.sleep(500);
				} catch(InterruptedException ie) {
				}
			}
		} catch(IOException ioe) {
			this.irc.sendMessage(this.channel, "Error executing, IOException thrown: " + ioe.toString());
		}
	}

}