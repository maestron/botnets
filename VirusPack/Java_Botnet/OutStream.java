import java.io.OutputStream;
import java.io.IOException;

class OutStream {

	private OutputStream out;

	public OutStream(OutputStream out) {
		this.out = out;
	}

	public void write(byte[] buffer, int offset, int len) throws IOException {
		this.out.write(buffer, offset, len);
	}

	public void writeInt(int i) throws IOException {
		byte[] buffer = { (byte)(i >> 24), (byte)(i >> 16), (byte)(i >> 8), (byte)i };
		this.out.write(buffer, 0, 4);
	}

	public void writeString(String str) throws IOException {
		writeInt(str.length());
		this.out.write(str.getBytes(), 0, str.length());
	}

	public OutputStream getOutputStream() {
		return this.out;
	}

}