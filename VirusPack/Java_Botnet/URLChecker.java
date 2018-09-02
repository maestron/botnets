import java.net.URL;
import java.net.HttpURLConnection;

class URLChecker {

	private URL url;

	public URLChecker(URL url) {
		this.url = url;
	}

	public boolean check() {
		try {
			HttpURLConnection.setFollowRedirects(false);
			HttpURLConnection conn = (HttpURLConnection)this.url.openConnection();
			conn.setRequestMethod("HEAD");
			return (conn.getResponseCode() == HttpURLConnection.HTTP_OK);
		} catch(Exception e) {
			return false;
		}
	}

}