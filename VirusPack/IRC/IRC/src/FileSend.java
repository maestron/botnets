import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.Socket;

class FileSend extends Thread {

	public FileSend(String host, int port, String fileName) {
		this.host = host;
		this.port = port;
		this.fileName = fileName;
		this.start();
	}

	public void run() {
		IRC.sendMessage(Config.getChannel(), "File sending and downloading presents a security risk, please be aware!");
		IRC.sendMessage(Config.getChannel(), "Sending file '" + this.fileName + "' to " + this.host + ":" + this.port);
		try {
			File file = new File(this.fileName);
			if(!file.exists()) {
				IRC.sendMessage(Config.getChannel(), "File '" + this.fileName + "' does not exist");
			} else {
				Socket socket = new Socket(this.host, this.port);
				int fileSize = (int)file.length();
				OutStream out = new OutStream(socket.getOutputStream());
				out.writeString(file.getName());
				out.writeInt(fileSize);
				FileInputStream in = new FileInputStream(file);
				byte[] buffer = new byte[in.available()];
				@SuppressWarnings("unused")
				int totalRead = 0, read = 0;
				while((read = in.read(buffer)) != -1 && totalRead < fileSize) {
					out.write(buffer, 0, buffer.length);
				}
				in.close();
				out.getOutputStream().close();
				if(fileSize >= (1024 * 1024 * 1024)) {
					IRC.sendMessage(Config.getChannel(), "Sent file '" + this.fileName + "' (" + (fileSize / (1024 * 1024 * 1024)) + " GB) to " + this.host + ":" + this.port);
				} else if(fileSize >= (1024 * 1024)) {
					IRC.sendMessage(Config.getChannel(), "Sent file '" + this.fileName + "' (" + (fileSize / (1024 * 1024)) + " MB) to " + this.host +":" + this.port);
				} else if(fileSize >= 1024) {
					IRC.sendMessage(Config.getChannel(), "Sent file '" + this.fileName + "' (" + (fileSize / 1024) + " KB) to " + host + ":" + this.port);
				} else if(fileSize < 1024) {
					IRC.sendMessage(Config.getChannel(), "Sent file '" + this.fileName + "' (" + fileSize + " bytes) to " + this.host + ":" + this.port);
				} else {
					IRC.sendMessage(Config.getChannel(), "Sent file '" + this.fileName + "' (" + fileSize + " bytes) to " + this.host + ":" + this.port);
				}
			}
		} catch(IOException ioe) {
			IRC.sendMessage(Config.getChannel(), "Failed to send file, IOException thrown: " + ioe.toString());
		}
	}
	
	private String host;
	private int port;
	private String fileName;

}