import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;

class ExternalSettings {

	public Properties properties = new Properties();

	public boolean load() {
		try {
			FileInputStream in = new FileInputStream(new File(Constants.INI_FILE_LOC));
			this.properties.load(in);
			in.close();
			return true;
		} catch(IOException ioe) {
			return false;
		}
	}

	public boolean save() {
		try {
			FileOutputStream out = new FileOutputStream(new File(Constants.INI_FILE_LOC));
			this.properties.store(out, null);
			out.close();
			return true;
		} catch(IOException ioe) {
			return false;
		}
	}

	public boolean iniExists() {
		File file = new File(Constants.INI_FILE_LOC);
		return (file.exists() && !file.isDirectory());
	}

}