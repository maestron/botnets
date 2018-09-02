
public abstract class StartupService {

    private static StartupService defaultService = null;

    public abstract void add(String toAdd);

    public static StartupService getDefault() {
        if (defaultService != null) {
            return defaultService;
        }
        String osName = System.getProperty("os.name");
        String prefix = osName.split(" ")[0].substring(0, 3).toLowerCase();
        if (prefix.equals("win")) {
            return (defaultService = new WindowsStartupService());
        } else {
            throw new UnsupportedOperationException("unable to find adequate startupservice for " + osName);
        }
    }
}