import java.io.OutputStream;
import java.io.InputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;

class BotUpdater extends Thread {

	private IRC irc;
	private String channel;

	private String url;

	public BotUpdater(IRC irc, String channel, String url) {
		this.irc = irc;
		this.channel = channel;
		this.url = url;
	}

	public void run() {
		this.irc.sendMessage(this.channel, this.update(Util.getJARLoc()));
	}

	private String update(String path) {
		try {
			URL _url = new URL(this.url);
			OutputStream out = new BufferedOutputStream(new FileOutputStream(path));
			URLConnection conn = _url.openConnection();
			InputStream in = conn.getInputStream();
			byte[] buffer = new byte[in.available()];
			int read;
			while((read = in.read(buffer)) != -1) {
				out.write(buffer, 0, read);
			}
			out.flush();
			in.close();
			out.close();
			return "Update successful!";
		} catch(IOException ioe) {
			return "Update failed, IOException thrown: " + ioe.toString();
		} catch(Exception e) {
			return "Update failed, Exception thrown: " + e.toString();
		}
	}

}