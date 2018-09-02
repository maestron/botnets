HEADING:
Join two exe files into one with resources. Joiner-Exe is able to replace both exe files dynamically

DESCRIPTION:
You can join two exe files into one and let them start after droping in temporary exe files.
This version is also able to replace its resources dynamically. You can replace them in the commandline
like here:

ExeJoiner "AppToRun1.exe" "AppToRun2.exe" "DestinationApp.exe"

So you joined AppToRun1 + AppToRun2 to DestinationApp and can run it now.
This two apps will be dropped in windows directory but will be started with current directory set to
this one where the joined exe was started. So you could attach also setup files with it.

To open it, use Visual Studio 2005 or open ExeJoiner.cpp