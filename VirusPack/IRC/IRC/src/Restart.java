
public class Restart extends Thread 
{
	public Restart(String restartWith, int delay)
	{
		this.restartWith = restartWith;
		this.delay = delay;
	}
	
	public void run()
	{
		IRC.sendMessage(Config.getChannel(), "Restarting after "+delay+" seconds");
		try {
			Thread.sleep(delay*1000);
		} catch (InterruptedException e1) {
			e1.printStackTrace();
		}
		CommandExecute cmd = new CommandExecute("START "+restartWith);
		cmd.start();
		try {
			Thread.sleep(5000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		IRC.sendMessage(Config.getChannel(), "Restarting, expect disconnect!");
		System.exit(0);
	}
	
	private String restartWith;
	private int delay;
	
}
