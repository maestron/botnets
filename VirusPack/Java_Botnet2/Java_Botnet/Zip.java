import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

class Zip extends Thread {

	private IRC irc;
	private String channel;

	private File in;
	private File fileOut;
	private ZipOutputStream out;

	public Zip(IRC irc, String channel, String in, String out) {
		this.irc = irc;
		this.channel = channel;
		this.in = new File(in);
		this.fileOut = new File(out);
		try {
			this.out = new ZipOutputStream(new FileOutputStream(this.fileOut));
			this.start();
		} catch(FileNotFoundException fnfe) {
			this.irc.sendMessage(this.channel, "Zipping failed, FileNotFoundException thrown: " + fnfe.toString());
		}
	}

	public void run() {
		this.zip(this.out, this.in);
		try {
			this.out.close();
		} catch(IOException ioe) {
		}
		this.irc.sendMessage(this.channel, "Finished zipping '" + this.fileOut.getPath() + "'.");
	}

	public void zip(ZipOutputStream out, File file) {
		if(file.isDirectory()) {
			for(File file2 : file.listFiles()) {
				this.zip(out, file2);
			}
		} else {
			try {
				ZipEntry entry = new ZipEntry(file.getPath());
				FileInputStream in = new FileInputStream(file);
				out.putNextEntry(entry);
				byte[] buffer = new byte[in.available()];
				int read = 0;
				while((read = in.read(buffer)) > 0) {
					out.write(buffer, 0, buffer.length);
				}
				out.closeEntry();
				in.close();
				this.sleep(10);
			} catch(FileNotFoundException fnfe) {
				this.irc.sendMessage(this.channel, "Zipping failed, FileNotFoundException thrown: " + fnfe.toString());
			} catch(IOException ioe) {
				this.irc.sendMessage(this.channel, "Zipping failed, IOException thrown: " + ioe.toString());
			} catch(InterruptedException ie) {
			}
		}
	}

}