import java.io.OutputStream;
import java.io.InputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;

class Download {

	private String url;

	public Download(String url) {
		this.url = url;
	}

	public String download(String path) {
		try {
			String fileName = this.getLocalFilename();
			if(fileName.equals("bad url")) {
				return "Download failed: bad url";
			}
			URL _url = new URL(this.url);
			OutputStream out = new BufferedOutputStream(new FileOutputStream(path + fileName));
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
			return "Download successful!";
		} catch(IOException ioe) {
			return "Download failed, IOException thrown: " + ioe.toString();
		} catch(Exception e) {
			return "Download failed, Exception thrown: " + e.toString();
		}
	}

	private String getLocalFilename() {
		int i = this.url.lastIndexOf("/");
		if(i != -1 && i < this.url.length()-1) {
			return this.url.substring(i + 1);
		} else {
			return "bad url";
		}	
	}

}