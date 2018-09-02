using System;
using System.Globalization;
using System.IO;
using System.Management;
using System.Runtime.InteropServices;

internal class CollectInfos
{
    public static PCInfos Collect()
    {
        PCInfos infos = new PCInfos();
        CultureInfo installedUICulture = CultureInfo.InstalledUICulture;
        infos.PcName = Environment.MachineName;
        infos.WinVersion = GetVersionString();
        infos.Country = installedUICulture.EnglishName;
        infos.HWID = getUniqueID("C");
        infos.NatStatus = 1;
        return infos;
    }

    private static string getCPUID()
    {
        string str = "";
        ManagementObjectCollection instances = new ManagementClass("win32_processor").GetInstances();
        foreach (ManagementObject obj2 in instances)
        {
            if (str == "")
            {
                break;
            }
        }
        return "erhjfkljlkghjghjghjgjcdr";
    }

    private static string getUniqueID(string drive)
    {
        if (drive == string.Empty)
        {
            foreach (DriveInfo info in DriveInfo.GetDrives())
            {
                if (info.IsReady)
                {
                    drive = info.RootDirectory.ToString();
                    break;
                }
            }
        }
        if (drive.EndsWith(@":\"))
        {
            drive = drive.Substring(0, drive.Length - 2);
        }
        string str = getVolumeSerial(drive);
        string str2 = getCPUID();
        return (str2.Substring(13) + str2.Substring(1, 4) + str + str2.Substring(4, 4));
    }

    private static string GetVersionString()
    {
        OperatingSystem oSVersion = Environment.OSVersion;
        string str = "";
        if (oSVersion.Platform == PlatformID.Win32Windows)
        {
            if (oSVersion.Version.Minor == 10)
            {
                str = "Windows 98";
            }
            if (oSVersion.Version.Minor == 90)
            {
                str = "Windows Me";
            }
        }
        if (oSVersion.Platform == PlatformID.Win32NT)
        {
            if (oSVersion.Version.Major == 4)
            {
                str = "Windows NT 4.0";
            }
            if (oSVersion.Version.Major == 5)
            {
                switch (oSVersion.Version.Minor)
                {
                    case 0:
                        str = "Windows 2000";
                        break;

                    case 1:
                        str = "Windows XP";
                        break;

                    case 2:
                        str = "Windows Server 2003";
                        break;
                }
            }
            if ((oSVersion.Version.Major == 6) && (oSVersion.Version.Minor == 0))
            {
                str = "Windows Vista";
            }
        }
        if (str == "")
        {
            str = "Unbekannte Windows-Version";
        }
        return str;
    }

    private static string getVolumeSerial(string drive)
    {
        ManagementObject obj2 = new ManagementObject("win32_logicaldisk.deviceid=\"" + drive + ":\"");
        obj2.Get();
        string str = obj2["VolumeSerialNumber"].ToString();
        obj2.Dispose();
        return str;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct PCInfos
    {
        public string WinVersion;
        public string Country;
        public string HWID;
        public int NatStatus;
        public string PcName;
    }
}

