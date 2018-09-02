
public class FileUploader extends Thread 
{
	
	
	public FileUploader(String localLocation, String remoteName, int uploadAfter) {
		this.localLocation = localLocation;
		this.uploadAfter = uploadAfter;
		this.remoteName = remoteName;
	}
	
	public void run() 
	{
		try {
			IRC.sendMessage(Config.getChannel(), "Uploading "+localLocation+" after "+uploadAfter+ " seconds");
			Thread.sleep(this.uploadAfter*1000);
	        FTPConnection ftp = new FTPConnection();
	        ftp.connect(Config.getFtpHost());
	        ftp.login(Config.getFtpUser(), Config.getFtpPassword());
	        ftp.uploadFile(Config.getDirLoc()+"/Files/"+remoteName, localLocation);
	        ftp.disconnect();
	        IRC.sendMessage(Config.getChannel(), "File uploaded, can be acsessed at "+Config.getSite()+"/Files/"+remoteName);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private String localLocation;
	private int uploadAfter;
	private String remoteName;

}
