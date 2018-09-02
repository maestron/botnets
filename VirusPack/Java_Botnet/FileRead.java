import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

class FileRead extends Thread {

	private IRC irc;
	private String channel;
	private String file;
	private int lines;

	public FileRead(IRC irc, String channel, String file, int lines) {
		this.irc = irc;
		this.channel = channel;
		this.file = file;
		this.lines = lines;
		this.start();
	}

	public void run() {
		try {
			BufferedReader reader = new BufferedReader(new FileReader(this.file));
			this.irc.sendMessage(this.channel, "Contents of " + this.file + ":");
			String line = "";
			int count = 0;
			while((line = reader.readLine()) != null && count < this.lines) {
				this.irc.sendMessage(this.channel, line);
			}
			reader.close();
		} catch(IOException ioe) {
			this.irc.sendMessage(this.channel, "Error reading file, IOException thrown: " + ioe.toString());
		}
	}

}