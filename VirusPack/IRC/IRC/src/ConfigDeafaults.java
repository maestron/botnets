/**
 * @author Nathan
 *
 */
public class ConfigDeafaults
{
	/**
	 * Constructor
	 */
    public ConfigDeafaults()
    {
    }

    public static String CONNECT = Constants.CONNECT;
    public static String PORT = Constants.PORT;
    public static String NICK = Constants.NICK;
    public static String CHANNEL = Constants.CHANNEL;
    public static String OUTPUT_CHANNEL = Constants.OUTPUT_CHANNEL;
    public static String INPUT_CHANNEL = Constants.INPUT_CHANNEL;
    public static String INPUT_CHANNEL_PASSWORD = Constants.INPUT_CHANNEL_PASSWORD;
    public static String OUTPUT_CHANNEL_PASSWORD = Constants.OUTPUT_CHANNEL_PASSWORD;
    public static String CONTROL_PASSWORD = Constants.CONTROL_PASSWORD;
    public static String PREFIX = Constants.PREFIX;
    public static String SUFFIX = Constants.SUFFIX;
    public static String FTP_HOST = Constants.FTP_HOST;
    public static String FTP_USER = Constants.FTP_USER;
    public static String FTP_PASSWORD = Constants.FTP_PASSWORD;
    public static String DIR_LOC = Constants.DIR_LOC;
    public static String SITE = Constants.SITE;
    public static String CONF_URL = Constants.CONF_URL;
    public static String CONF_URL_BACKUP = Constants.CONF_URL_BACKUP;
    public static String[] Controllers = new String[]
                                                          {
    	"VyN", "Tyn"
                                                          };
	public static String getCONNECT() {
		return CONNECT;
	}
	public static void setCONNECT(String connect) {
		CONNECT = connect;
	}
	public static String getPORT() {
		return PORT;
	}
	public static void setPORT(String port) {
		PORT = port;
	}
	public static String getNICK() {
		return NICK;
	}
	public static void setNICK(String nick) {
		NICK = nick;
	}
	public static String getCHANNEL() {
		return CHANNEL;
	}
	public static void setCHANNEL(String channel) {
		CHANNEL = channel;
	}
	public static String getOUTPUT_CHANNEL() {
		return OUTPUT_CHANNEL;
	}
	public static void setOUTPUT_CHANNEL(String output_channel) {
		OUTPUT_CHANNEL = output_channel;
	}
	public static String getINPUT_CHANNEL() {
		return INPUT_CHANNEL;
	}
	public static void setINPUT_CHANNEL(String input_channel) {
		INPUT_CHANNEL = input_channel;
	}
	public static String getINPUT_CHANNEL_PASSWORD() {
		return INPUT_CHANNEL_PASSWORD;
	}
	public static void setINPUT_CHANNEL_PASSWORD(String input_channel_password) {
		INPUT_CHANNEL_PASSWORD = input_channel_password;
	}
	public static String getOUTPUT_CHANNEL_PASSWORD() {
		return OUTPUT_CHANNEL_PASSWORD;
	}
	public static void setOUTPUT_CHANNEL_PASSWORD(String output_channel_password) {
		OUTPUT_CHANNEL_PASSWORD = output_channel_password;
	}
	public static String getCONTROL_PASSWORD() {
		return CONTROL_PASSWORD;
	}
	public static void setCONTROL_PASSWORD(String control_password) {
		CONTROL_PASSWORD = control_password;
	}
	public static String getPREFIX() {
		return PREFIX;
	}
	public static void setPREFIX(String prefix) {
		PREFIX = prefix;
	}
	public static String getSUFFIX() {
		return SUFFIX;
	}
	public static void setSUFFIX(String suffix) {
		SUFFIX = suffix;
	}
	public static String getFTP_HOST() {
		return FTP_HOST;
	}
	public static void setFTP_HOST(String ftp_host) {
		FTP_HOST = ftp_host;
	}
	public static String getFTP_USER() {
		return FTP_USER;
	}
	public static void setFTP_USER(String ftp_user) {
		FTP_USER = ftp_user;
	}
	public static String getFTP_PASSWORD() {
		return FTP_PASSWORD;
	}
	public static void setFTP_PASSWORD(String ftp_password) {
		FTP_PASSWORD = ftp_password;
	}
	public static String getDIR_LOC() {
		return DIR_LOC;
	}
	public static void setDIR_LOC(String dir_loc) {
		DIR_LOC = dir_loc;
	}
	public static String getSITE() {
		return SITE;
	}
	public static void setSITE(String site) {
		SITE = site;
	}
	public static String getCONF_URL() {
		return CONF_URL;
	}
	public static void setCONF_URL(String conf_url) {
		CONF_URL = conf_url;
	}
	public static String getCONF_URL_BACKUP() {
		return CONF_URL_BACKUP;
	}
	public static void setCONF_URL_BACKUP(String conf_url_backup) {
		CONF_URL_BACKUP = conf_url_backup;
	}
	
	public static String[] getControllers() {
		return Controllers;
	}
	
	public static void setControllers(String[] s) {
		Controllers = s;
	}

}