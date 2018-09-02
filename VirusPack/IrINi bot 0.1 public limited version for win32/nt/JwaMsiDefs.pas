{******************************************************************************}
{                                                       	               }
{ Windows Installer API interface Unit for Object Pascal                       }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: msidefs.h, released June 2000. The original Pascal     }
{ code is: MsiDefs.pas, released June 2001. The initial developer of the       }
{ Pascal code is Marcel van Brakel (brakelm@chello.nl).                        }
{                                                                              }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Obtained through: Joint Endeavour of Delphi Innovators (Project JEDI)        }
{								               }
{ You may retrieve the latest version of this file at the Project JEDI home    }
{ page, located at http://delphi-jedi.org or my personal homepage located at   }
{ http://members.chello.nl/m.vanbrakel2                                        }
{								               }
{ The contents of this file are used with permission, subject to the Mozilla   }
{ Public License Version 1.1 (the "License"); you may not use this file except }
{ in compliance with the License. You may obtain a copy of the License at      }
{ http://www.mozilla.org/MPL/MPL-1.1.html                                      }
{                                                                              }
{ Software distributed under the License is distributed on an "AS IS" basis,   }
{ WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for }
{ the specific language governing rights and limitations under the License.    }
{                                                                              }
{ Alternatively, the contents of this file may be used under the terms of the  }
{ GNU Lesser General Public License (the  "LGPL License"), in which case the   }
{ provisions of the LGPL License are applicable instead of those above.        }
{ If you wish to allow use of your version of this file only under the terms   }
{ of the LGPL License and not to allow others to use your version of this file }
{ under the MPL, indicate your decision by deleting  the provisions above and  }
{ replace  them with the notice and other provisions required by the LGPL      }
{ License.  If you do not delete the provisions above, a recipient may use     }
{ your version of this file under either the MPL or the LGPL License.          }
{ 								               }
{ For more information about the LGPL: http://www.gnu.org/copyleft/lesser.html }
{ 								               }
{******************************************************************************}

unit JwaMsiDefs;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "msidefs.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//------------------------------------------------------------------------------
// INSTALLER PROPERTY DEFINITIONS
//------------------------------------------------------------------------------

const

// Required properties: set in Property table

  IPROPNAME_PRODUCTNAME     = TEXT('ProductName'); // name registered for display
  {$EXTERNALSYM IPROPNAME_PRODUCTNAME}
  IPROPNAME_PRODUCTCODE     = TEXT('ProductCode'); // unique string GUID for product
  {$EXTERNALSYM IPROPNAME_PRODUCTCODE}
  IPROPNAME_PRODUCTVERSION  = TEXT('ProductVersion'); // string product version
  {$EXTERNALSYM IPROPNAME_PRODUCTVERSION}
  IPROPNAME_INSTALLLANGUAGE = TEXT('ProductLanguage'); // install language of product, use to load resources
  {$EXTERNALSYM IPROPNAME_INSTALLLANGUAGE}
  IPROPNAME_MANUFACTURER    = TEXT('Manufacturer'); // name of manufacturer
  {$EXTERNALSYM IPROPNAME_MANUFACTURER}

// Customization properties: set in Property table

  IPROPNAME_UPGRADECODE       = TEXT('UpgradeCode'); // unique string GUID for product family
  {$EXTERNALSYM IPROPNAME_UPGRADECODE}
  IPROPNAME_PIDTEMPLATE       = TEXT('PIDTemplate'); // drives Product ID processing
  {$EXTERNALSYM IPROPNAME_PIDTEMPLATE}
  IPROPNAME_DISKPROMPT        = TEXT('DiskPrompt'); // prompt for CD
  {$EXTERNALSYM IPROPNAME_DISKPROMPT}
  IPROPNAME_LEFTUNIT          = TEXT('LeftUnit'); // name of unit placed to left of number instead of right
  {$EXTERNALSYM IPROPNAME_LEFTUNIT}
  IPROPNAME_ADMIN_PROPERTIES  = TEXT('AdminProperties'); // properties to stuff in admin package
  {$EXTERNALSYM IPROPNAME_ADMIN_PROPERTIES}
  IPROPNAME_DEFAULTUIFONT     = TEXT('DefaultUIFont'); // the font used in the UI if no other font is specified
  {$EXTERNALSYM IPROPNAME_DEFAULTUIFONT}
  IPROPNAME_ALLOWEDPROPERTIES = TEXT('SecureCustomProperties');
  {$EXTERNALSYM IPROPNAME_ALLOWEDPROPERTIES}
  IPROPNAME_ENABLEUSERCONTROL = TEXT('EnableUserControl'); // allows user to specify any public property
  {$EXTERNALSYM IPROPNAME_ENABLEUSERCONTROL}
  IPROPNAME_HIDDEN_PROPERTIES = TEXT('MsiHiddenProperties');  // properties that should not be dumped into the log file
  {$EXTERNALSYM IPROPNAME_HIDDEN_PROPERTIES}  

// Customization properties: set on command-line or in Property table

  IPROPNAME_USERNAME     = TEXT('USERNAME');
  {$EXTERNALSYM IPROPNAME_USERNAME}
  IPROPNAME_COMPANYNAME  = TEXT('COMPANYNAME');
  {$EXTERNALSYM IPROPNAME_COMPANYNAME}
  IPROPNAME_PIDKEY       = TEXT('PIDKEY'); // used with PIDTemplate to form ProductID
  {$EXTERNALSYM IPROPNAME_PIDKEY}
  IPROPNAME_PATCH        = TEXT('PATCH'); // patch package to apply - SET BY INSTALLER
  {$EXTERNALSYM IPROPNAME_PATCH}
  IPROPNAME_TARGETDIR    = TEXT('TARGETDIR'); // target location - defaults to ROOTDRIVE
  {$EXTERNALSYM IPROPNAME_TARGETDIR}
  IPROPNAME_ACTION       = TEXT('ACTION'); // top-level action to perform - default to INSTALL
  {$EXTERNALSYM IPROPNAME_ACTION}
  IPROPNAME_LIMITUI      = TEXT('LIMITUI'); // limit ui level to Basic
  {$EXTERNALSYM IPROPNAME_LIMITUI}
  IPROPNAME_LOGACTION    = TEXT('LOGACTION'); // log only these actions
  {$EXTERNALSYM IPROPNAME_LOGACTION}
  IPROPNAME_ALLUSERS     = TEXT('ALLUSERS'); // install for all users
  {$EXTERNALSYM IPROPNAME_ALLUSERS}
  IPROPNAME_INSTALLLEVEL = TEXT('INSTALLLEVEL');
  {$EXTERNALSYM IPROPNAME_INSTALLLEVEL}
  IPROPNAME_REBOOT       = TEXT('REBOOT'); // force or suppress reboot
  {$EXTERNALSYM IPROPNAME_REBOOT}

  IPROPNAME_REBOOTPROMPT = TEXT('REBOOTPROMPT'); // allow or suppress reboot prompt
  {$EXTERNALSYM IPROPNAME_REBOOTPROMPT}

  IPROPNAME_EXECUTEMODE          = TEXT('EXECUTEMODE'); // NONE or SCRIPT
  {$EXTERNALSYM IPROPNAME_EXECUTEMODE}
  IPROPVALUE_EXECUTEMODE_NONE    = TEXT('NONE'); // do not update system
  {$EXTERNALSYM IPROPVALUE_EXECUTEMODE_NONE}
  IPROPVALUE_EXECUTEMODE_SCRIPT  = TEXT('SCRIPT'); // default - run script to update system
  {$EXTERNALSYM IPROPVALUE_EXECUTEMODE_SCRIPT}
  IPROPNAME_EXECUTEACTION        = TEXT('EXECUTEACTION'); // run action on server side
  {$EXTERNALSYM IPROPNAME_EXECUTEACTION}
  IPROPNAME_SOURCELIST           = TEXT('SOURCELIST');
  {$EXTERNALSYM IPROPNAME_SOURCELIST}
  IPROPNAME_ROOTDRIVE            = TEXT('ROOTDRIVE'); // default drive to install - SET BY INSTALLER
  {$EXTERNALSYM IPROPNAME_ROOTDRIVE}
  IPROPNAME_TRANSFORMS           = TEXT('TRANSFORMS'); // transforms to apply
  {$EXTERNALSYM IPROPNAME_TRANSFORMS}
  IPROPNAME_TRANSFORMSATSOURCE   = TEXT('TRANSFORMSATSOURCE'); // transforms can be found at source
  {$EXTERNALSYM IPROPNAME_TRANSFORMSATSOURCE}
  IPROPNAME_TRANSFORMSSECURE     = TEXT('TRANSFORMSSECURE'); // file transforms are secured
  {$EXTERNALSYM IPROPNAME_TRANSFORMSSECURE}
  IPROPNAME_SEQUENCE             = TEXT('SEQUENCE'); // sequence table to run with SEQUENCE action
  {$EXTERNALSYM IPROPNAME_SEQUENCE}
  IPROPNAME_SHORTFILENAMES       = TEXT('SHORTFILENAMES'); // force short file names
  {$EXTERNALSYM IPROPNAME_SHORTFILENAMES}
  IPROPNAME_PRIMARYFOLDER        = TEXT('PRIMARYFOLDER'); // Folder on the volume the author wants costing info for
  {$EXTERNALSYM IPROPNAME_PRIMARYFOLDER}
  IPROPNAME_AFTERREBOOT          = TEXT('AFTERREBOOT'); // install is after a ForceReboot triggered reboot
  {$EXTERNALSYM IPROPNAME_AFTERREBOOT}
  IPROPNAME_NOCOMPANYNAME        = TEXT('NOCOMPANYNAME');
  {$EXTERNALSYM IPROPNAME_NOCOMPANYNAME}
  IPROPNAME_NOUSERNAME           = TEXT('NOUSERNAME');
  {$EXTERNALSYM IPROPNAME_NOUSERNAME}
  IPROPNAME_DISABLEROLLBACK      = TEXT('DISABLEROLLBACK'); // disable rollback for this install
  {$EXTERNALSYM IPROPNAME_DISABLEROLLBACK}
  IPROPNAME_AVAILABLEFREEREG     = TEXT('AVAILABLEFREEREG'); // set up the free space in the registry before commencing the install
  {$EXTERNALSYM IPROPNAME_AVAILABLEFREEREG}
  IPROPNAME_DISABLEADVTSHORTCUTS = TEXT('DISABLEADVTSHORTCUTS'); // disable creating darwin shortcuts even if supported
  {$EXTERNALSYM IPROPNAME_DISABLEADVTSHORTCUTS}
  IPROPNAME_PATCHNEWPACKAGECODE  = TEXT('PATCHNEWPACKAGECODE'); // added to property table by patch transforms - used to update
  {$EXTERNALSYM IPROPNAME_PATCHNEWPACKAGECODE}
  // PackageCode of admin packages when patching admin installs
  IPROPNAME_PATCHNEWSUMMARYSUBJECT = TEXT('PATCHNEWSUMMARYSUBJECT'); // added to property table by patch transforms - used to update
  {$EXTERNALSYM IPROPNAME_PATCHNEWSUMMARYSUBJECT}
  // Subject summary info property of admin packages when patching admin installs
  IPROPNAME_PATCHNEWSUMMARYCOMMENTS = TEXT('PATCHNEWSUMMARYCOMMENTS'); // added to property table by patch transforms - used to update
  {$EXTERNALSYM IPROPNAME_PATCHNEWSUMMARYCOMMENTS}
  // Comments summary info property of admin packages when patching admin installs
  IPROPNAME_PRODUCTLANGUAGE = TEXT('PRODUCTLANGUAGE'); // requested language, must be one in summary information list, selects language transform
  {$EXTERNALSYM IPROPNAME_PRODUCTLANGUAGE}

  IPROPNAME_CHECKCRCS         = TEXT('MSICHECKCRCS');       // requests Darwin to check CRCs after copying, moving, patching & duplicating files.
  {$EXTERNALSYM IPROPNAME_CHECKCRCS}
  IPROPNAME_MSINODISABLEMEDIA = TEXT('MSINODISABLEMEDIA');  // if set, DISABLEMEDIA won't be set in the AdminProperties stream during an admin install of
  {$EXTERNALSYM IPROPNAME_MSINODISABLEMEDIA}                // a package with compressed source

// property used for URT bootstrapping

  IPROPNAME_CARRYINGNDP	                = TEXT('CARRYINGNDP');
  {$EXTERNALSYM IPROPNAME_CARRYINGNDP}
  IPROPVALUE__CARRYINGNDP_URTREINSTALL  = TEXT('URTREINSTALL');   // reinstalling/ uninstalling core URT files
  {$EXTERNALSYM IPROPVALUE__CARRYINGNDP_URTREINSTALL}
  IPROPVALUE__CARRYINGNDP_URTUPGRADE    = TEXT('URTUPGRADE');     // upgrading core URT files
  {$EXTERNALSYM IPROPVALUE__CARRYINGNDP_URTUPGRADE}

// property used for multiple instance support

  IPROPNAME_MSINEWINSTANCE = TEXT('MSINEWINSTANCE');
  {$EXTERNALSYM IPROPNAME_MSINEWINSTANCE}
  IPROPNAME_MSIINSTANCEGUID = TEXT('MSIINSTANCEGUID');
  {$EXTERNALSYM IPROPNAME_MSIINSTANCEGUID}

// properties used for URL download reduction for admins

  IPROPNAME_MSIPACKAGEDOWNLOADLOCALCOPY = TEXT('MSIPACKAGEDOWNLOADLOCALCOPY');
  {$EXTERNALSYM IPROPNAME_MSIPACKAGEDOWNLOADLOCALCOPY}
  IPROPNAME_MSIPATCHDOWNLOADLOCALCOPY = TEXT('MSIPATCHDOWNLOADLOCALCOPY');
  {$EXTERNALSYM IPROPNAME_MSIPATCHDOWNLOADLOCALCOPY}

// Properties used to populate Add/Remove Control Panel values

  IPROPNAME_ARPAUTHORIZEDCDFPREFIX = TEXT('ARPAUTHORIZEDCDFPREFIX');
  {$EXTERNALSYM IPROPNAME_ARPAUTHORIZEDCDFPREFIX}
  IPROPNAME_ARPCOMMENTS            = TEXT('ARPCOMMENTS');
  {$EXTERNALSYM IPROPNAME_ARPCOMMENTS}
  IPROPNAME_ARPCONTACT             = TEXT('ARPCONTACT');
  {$EXTERNALSYM IPROPNAME_ARPCONTACT}
  IPROPNAME_ARPHELPLINK            = TEXT('ARPHELPLINK');
  {$EXTERNALSYM IPROPNAME_ARPHELPLINK}
  IPROPNAME_ARPHELPTELEPHONE       = TEXT('ARPHELPTELEPHONE');
  {$EXTERNALSYM IPROPNAME_ARPHELPTELEPHONE}
  IPROPNAME_ARPINSTALLLOCATION     = TEXT('ARPINSTALLLOCATION');
  {$EXTERNALSYM IPROPNAME_ARPINSTALLLOCATION}
  IPROPNAME_ARPNOMODIFY            = TEXT('ARPNOMODIFY');
  {$EXTERNALSYM IPROPNAME_ARPNOMODIFY}
  IPROPNAME_ARPNOREMOVE            = TEXT('ARPNOREMOVE');
  {$EXTERNALSYM IPROPNAME_ARPNOREMOVE}
  IPROPNAME_ARPNOREPAIR            = TEXT('ARPNOREPAIR');
  {$EXTERNALSYM IPROPNAME_ARPNOREPAIR}
  IPROPNAME_ARPREADME              = TEXT('ARPREADME');
  {$EXTERNALSYM IPROPNAME_ARPREADME}
  IPROPNAME_ARPSIZE                = TEXT('ARPSIZE');
  {$EXTERNALSYM IPROPNAME_ARPSIZE}
  IPROPNAME_ARPSYSTEMCOMPONENT     = TEXT('ARPSYSTEMCOMPONENT');
  {$EXTERNALSYM IPROPNAME_ARPSYSTEMCOMPONENT}
  IPROPNAME_ARPURLINFOABOUT        = TEXT('ARPURLINFOABOUT');
  {$EXTERNALSYM IPROPNAME_ARPURLINFOABOUT}
  IPROPNAME_ARPURLUPDATEINFO       = TEXT('ARPURLUPDATEINFO');
  {$EXTERNALSYM IPROPNAME_ARPURLUPDATEINFO}
  IPROPNAME_ARPPRODUCTICON = TEXT('ARPPRODUCTICON');
  {$EXTERNALSYM IPROPNAME_ARPPRODUCTICON}

// Dynamic properties set by installer during install

  IPROPNAME_INSTALLED                    = TEXT('Installed'); // product already installed
  {$EXTERNALSYM IPROPNAME_INSTALLED}
  IPROPNAME_PRODUCTSTATE                 = TEXT('ProductState'); // state of product (installed,advertised,etc...)
  {$EXTERNALSYM IPROPNAME_PRODUCTSTATE}
  IPROPNAME_PRESELECTED                  = TEXT('Preselected'); // selections made on command line
  {$EXTERNALSYM IPROPNAME_PRESELECTED}
  IPROPNAME_RESUME                       = TEXT('RESUME'); // resuming suspended install
  {$EXTERNALSYM IPROPNAME_RESUME}
  IPROPNAME_UPDATESTARTED                = TEXT('UpdateStarted'); // have begun to update system
  {$EXTERNALSYM IPROPNAME_UPDATESTARTED}
  IPROPNAME_PRODUCTID                    = TEXT('ProductID'); // the complete validated Product ID
  {$EXTERNALSYM IPROPNAME_PRODUCTID}
  IPROPNAME_OUTOFDISKSPACE               = TEXT('OutOfDiskSpace');
  {$EXTERNALSYM IPROPNAME_OUTOFDISKSPACE}
  IPROPNAME_OUTOFNORBDISKSPACE           = TEXT('OutOfNoRbDiskSpace');
  {$EXTERNALSYM IPROPNAME_OUTOFNORBDISKSPACE}
  IPROPNAME_COSTINGCOMPLETE              = TEXT('CostingComplete');
  {$EXTERNALSYM IPROPNAME_COSTINGCOMPLETE}
  IPROPNAME_SOURCEDIR                    = TEXT('SourceDir'); // source location - SET BY INSTALLER
  {$EXTERNALSYM IPROPNAME_SOURCEDIR}
  IPROPNAME_REPLACEDINUSEFILES           = TEXT('ReplacedInUseFiles'); // need reboot to completely install one or more files
  {$EXTERNALSYM IPROPNAME_REPLACEDINUSEFILES}
  IPROPNAME_PRIMARYFOLDER_PATH           = TEXT('PrimaryVolumePath');
  {$EXTERNALSYM IPROPNAME_PRIMARYFOLDER_PATH}
  IPROPNAME_PRIMARYFOLDER_SPACEAVAILABLE = TEXT('PrimaryVolumeSpaceAvailable');
  {$EXTERNALSYM IPROPNAME_PRIMARYFOLDER_SPACEAVAILABLE}
  IPROPNAME_PRIMARYFOLDER_SPACEREQUIRED  = TEXT('PrimaryVolumeSpaceRequired');
  {$EXTERNALSYM IPROPNAME_PRIMARYFOLDER_SPACEREQUIRED}
  IPROPNAME_PRIMARYFOLDER_SPACEREMAINING = TEXT('PrimaryVolumeSpaceRemaining');
  {$EXTERNALSYM IPROPNAME_PRIMARYFOLDER_SPACEREMAINING}
  IPROPNAME_ISADMINPACKAGE               = TEXT('IsAdminPackage');
  {$EXTERNALSYM IPROPNAME_ISADMINPACKAGE}
  IPROPNAME_ROLLBACKDISABLED             = TEXT('RollbackDisabled');
  {$EXTERNALSYM IPROPNAME_ROLLBACKDISABLED}
  IPROPNAME_RESTRICTEDUSERCONTROL        = TEXT('RestrictedUserControl');
  {$EXTERNALSYM IPROPNAME_RESTRICTEDUSERCONTROL}

// Dynamic properties evaluated upon use

  IPROPNAME_TIME     = TEXT('Time');
  {$EXTERNALSYM IPROPNAME_TIME}
  IPROPNAME_DATE     = TEXT('Date');
  {$EXTERNALSYM IPROPNAME_DATE}
  IPROPNAME_DATETIME = TEXT('DateTime');
  {$EXTERNALSYM IPROPNAME_DATETIME}

// Hardware properties: set by installer at initialization

  IPROPNAME_INTEL = TEXT('Intel');
  {$EXTERNALSYM IPROPNAME_INTEL}
//#if (_WIN32_MSI >= 150)
  IPROPNAME_AMD64          = TEXT('AMD64');
  {$EXTERNALSYM IPROPNAME_AMD64}
  IPROPNAME_INTEL64        = TEXT('Intel64');
  {$EXTERNALSYM IPROPNAME_INTEL64}
//#else // (_WIN32_MSI >= 150)
  IPROPNAME_IA64           = TEXT('IA64');
  {$EXTERNALSYM IPROPNAME_IA64}
//#endif // (_WIN32_MSI >= 150)
  IPROPNAME_TEXTHEIGHT     = TEXT('TextHeight');
  {$EXTERNALSYM IPROPNAME_TEXTHEIGHT}
  IPROPNAME_SCREENX        = TEXT('ScreenX');
  {$EXTERNALSYM IPROPNAME_SCREENX}
  IPROPNAME_SCREENY        = TEXT('ScreenY');
  {$EXTERNALSYM IPROPNAME_SCREENY}
  IPROPNAME_CAPTIONHEIGHT  = TEXT('CaptionHeight');
  {$EXTERNALSYM IPROPNAME_CAPTIONHEIGHT}
  IPROPNAME_BORDERTOP      = TEXT('BorderTop');
  {$EXTERNALSYM IPROPNAME_BORDERTOP}
  IPROPNAME_BORDERSIDE     = TEXT('BorderSide');
  {$EXTERNALSYM IPROPNAME_BORDERSIDE}
  IPROPNAME_COLORBITS      = TEXT('ColorBits');
  {$EXTERNALSYM IPROPNAME_COLORBITS}
  IPROPNAME_PHYSICALMEMORY = TEXT('PhysicalMemory');
  {$EXTERNALSYM IPROPNAME_PHYSICALMEMORY}
  IPROPNAME_VIRTUALMEMORY  = TEXT('VirtualMemory');
  {$EXTERNALSYM IPROPNAME_VIRTUALMEMORY}
  IPROPNAME_TEXTHEIGHT_CORRECTION = TEXT('TextHeightCorrection');
  {$EXTERNALSYM IPROPNAME_TEXTHEIGHT_CORRECTION}

// Operating System properties: set by installer at initialization

  IPROPNAME_VERSIONNT        = TEXT('VersionNT');
  {$EXTERNALSYM IPROPNAME_VERSIONNT}
  IPROPNAME_VERSION9X        = TEXT('Version9X');
  {$EXTERNALSYM IPROPNAME_VERSION9X}
  IPROPNAME_VERSIONNT64      = TEXT('VersionNT64');
  {$EXTERNALSYM IPROPNAME_VERSIONNT64}
  IPROPNAME_WINDOWSBUILD     = TEXT('WindowsBuild');
  {$EXTERNALSYM IPROPNAME_WINDOWSBUILD}
  IPROPNAME_SERVICEPACKLEVEL = TEXT('ServicePackLevel');
  {$EXTERNALSYM IPROPNAME_SERVICEPACKLEVEL}
  IPROPNAME_SERVICEPACKLEVELMINOR = TEXT('ServicePackLevelMinor');
  {$EXTERNALSYM IPROPNAME_SERVICEPACKLEVELMINOR}
  IPROPNAME_SHAREDWINDOWS    = TEXT('SharedWindows');
  {$EXTERNALSYM IPROPNAME_SHAREDWINDOWS}
  IPROPNAME_COMPUTERNAME     = TEXT('ComputerName');
  {$EXTERNALSYM IPROPNAME_COMPUTERNAME}
  IPROPNAME_SHELLADVTSUPPORT = TEXT('ShellAdvtSupport');
  {$EXTERNALSYM IPROPNAME_SHELLADVTSUPPORT}
  IPROPNAME_OLEADVTSUPPORT   = TEXT('OLEAdvtSupport');
  {$EXTERNALSYM IPROPNAME_OLEADVTSUPPORT}
  IPROPNAME_SYSTEMLANGUAGEID = TEXT('SystemLanguageID');
  {$EXTERNALSYM IPROPNAME_SYSTEMLANGUAGEID}
  IPROPNAME_TTCSUPPORT       = TEXT('TTCSupport');
  {$EXTERNALSYM IPROPNAME_TTCSUPPORT}
  IPROPNAME_TERMSERVER       = TEXT('TerminalServer');
  {$EXTERNALSYM IPROPNAME_TERMSERVER}
  IPROPNAME_REMOTEADMINTS        = TEXT('RemoteAdminTS');
  {$EXTERNALSYM IPROPNAME_REMOTEADMINTS}
  IPROPNAME_REDIRECTEDDLLSUPPORT = TEXT('RedirectedDllSupport');
  {$EXTERNALSYM IPROPNAME_REDIRECTEDDLLSUPPORT}
  IPROPNAME_NTPRODUCTTYPE                  = TEXT('MsiNTProductType');
  {$EXTERNALSYM IPROPNAME_NTPRODUCTTYPE}
  IPROPNAME_NTSUITEBACKOFFICE              = TEXT('MsiNTSuiteBackOffice');
  {$EXTERNALSYM IPROPNAME_NTSUITEBACKOFFICE}
  IPROPNAME_NTSUITEDATACENTER              = TEXT('MsiNTSuiteDataCenter');
  {$EXTERNALSYM IPROPNAME_NTSUITEDATACENTER}
  IPROPNAME_NTSUITEENTERPRISE              = TEXT('MsiNTSuiteEnterprise');
  {$EXTERNALSYM IPROPNAME_NTSUITEENTERPRISE}
  IPROPNAME_NTSUITESMALLBUSINESS           = TEXT('MsiNTSuiteSmallBusiness');
  {$EXTERNALSYM IPROPNAME_NTSUITESMALLBUSINESS}
  IPROPNAME_NTSUITESMALLBUSINESSRESTRICTED = TEXT('MsiNTSuiteSmallBusinessRestricted');
  {$EXTERNALSYM IPROPNAME_NTSUITESMALLBUSINESSRESTRICTED}
  IPROPNAME_NTSUITEPERSONAL                = TEXT('MsiNTSuitePersonal');
  {$EXTERNALSYM IPROPNAME_NTSUITEPERSONAL}
  IPROPNAME_NTSUITEWEBSERVER               = TEXT('MsiNTSuiteWebServer');
  {$EXTERNALSYM IPROPNAME_NTSUITEWEBSERVER}
  IPROPNAME_NETASSEMBLYSUPPORT             = TEXT('MsiNetAssemblySupport');
  {$EXTERNALSYM IPROPNAME_NETASSEMBLYSUPPORT}
  IPROPNAME_WIN32ASSEMBLYSUPPORT           = TEXT('MsiWin32AssemblySupport');
  {$EXTERNALSYM IPROPNAME_WIN32ASSEMBLYSUPPORT}

// User properties: set by installer at initialization

  IPROPNAME_LOGONUSER      = TEXT('LogonUser');
  {$EXTERNALSYM IPROPNAME_LOGONUSER}
  IPROPNAME_USERSID        = TEXT('UserSID');
  {$EXTERNALSYM IPROPNAME_USERSID}
  IPROPNAME_ADMINUSER      = TEXT('AdminUser');
  {$EXTERNALSYM IPROPNAME_ADMINUSER}
  IPROPNAME_USERLANGUAGEID = TEXT('UserLanguageID');
  {$EXTERNALSYM IPROPNAME_USERLANGUAGEID}
  IPROPNAME_PRIVILEGED     = TEXT('Privileged');
  {$EXTERNALSYM IPROPNAME_PRIVILEGED}

// System folder properties: set by installer at initialization

  IPROPNAME_WINDOWS_FOLDER      = TEXT('WindowsFolder');
  {$EXTERNALSYM IPROPNAME_WINDOWS_FOLDER}
  IPROPNAME_SYSTEM_FOLDER       = TEXT('SystemFolder');
  {$EXTERNALSYM IPROPNAME_SYSTEM_FOLDER}
  IPROPNAME_SYSTEM16_FOLDER     = TEXT('System16Folder');
  {$EXTERNALSYM IPROPNAME_SYSTEM16_FOLDER}
  IPROPNAME_WINDOWS_VOLUME      = TEXT('WindowsVolume');
  {$EXTERNALSYM IPROPNAME_WINDOWS_VOLUME}
  IPROPNAME_TEMP_FOLDER         = TEXT('TempFolder');
  {$EXTERNALSYM IPROPNAME_TEMP_FOLDER}
  IPROPNAME_PROGRAMFILES_FOLDER = TEXT('ProgramFilesFolder');
  {$EXTERNALSYM IPROPNAME_PROGRAMFILES_FOLDER}
  IPROPNAME_COMMONFILES_FOLDER  = TEXT('CommonFilesFolder');
  {$EXTERNALSYM IPROPNAME_COMMONFILES_FOLDER}
  IPROPNAME_SYSTEM64_FOLDER     = TEXT('System64Folder');
  {$EXTERNALSYM IPROPNAME_SYSTEM64_FOLDER}
  IPROPNAME_PROGRAMFILES64_FOLDER = TEXT('ProgramFiles64Folder');
  {$EXTERNALSYM IPROPNAME_PROGRAMFILES64_FOLDER}
  IPROPNAME_COMMONFILES64_FOLDER = TEXT('CommonFiles64Folder');
  {$EXTERNALSYM IPROPNAME_COMMONFILES64_FOLDER}
  IPROPNAME_STARTMENU_FOLDER    = TEXT('StartMenuFolder');
  {$EXTERNALSYM IPROPNAME_STARTMENU_FOLDER}
  IPROPNAME_PROGRAMMENU_FOLDER  = TEXT('ProgramMenuFolder');
  {$EXTERNALSYM IPROPNAME_PROGRAMMENU_FOLDER}
  IPROPNAME_STARTUP_FOLDER      = TEXT('StartupFolder');
  {$EXTERNALSYM IPROPNAME_STARTUP_FOLDER}
  IPROPNAME_NETHOOD_FOLDER      = TEXT('NetHoodFolder');
  {$EXTERNALSYM IPROPNAME_NETHOOD_FOLDER}
  IPROPNAME_PERSONAL_FOLDER     = TEXT('PersonalFolder');
  {$EXTERNALSYM IPROPNAME_PERSONAL_FOLDER}
  IPROPNAME_SENDTO_FOLDER       = TEXT('SendToFolder');
  {$EXTERNALSYM IPROPNAME_SENDTO_FOLDER}
  IPROPNAME_DESKTOP_FOLDER      = TEXT('DesktopFolder');
  {$EXTERNALSYM IPROPNAME_DESKTOP_FOLDER}
  IPROPNAME_TEMPLATE_FOLDER     = TEXT('TemplateFolder');
  {$EXTERNALSYM IPROPNAME_TEMPLATE_FOLDER}
  IPROPNAME_FONTS_FOLDER        = TEXT('FontsFolder');
  {$EXTERNALSYM IPROPNAME_FONTS_FOLDER}
  IPROPNAME_FAVORITES_FOLDER    = TEXT('FavoritesFolder');
  {$EXTERNALSYM IPROPNAME_FAVORITES_FOLDER}
  IPROPNAME_RECENT_FOLDER       = TEXT('RecentFolder');
  {$EXTERNALSYM IPROPNAME_RECENT_FOLDER}
  IPROPNAME_APPDATA_FOLDER      = TEXT('AppDataFolder');
  {$EXTERNALSYM IPROPNAME_APPDATA_FOLDER}
  IPROPNAME_PRINTHOOD_FOLDER    = TEXT('PrintHoodFolder');
  {$EXTERNALSYM IPROPNAME_PRINTHOOD_FOLDER}
  IPROPNAME_ADMINTOOLS_FOLDER    = TEXT('AdminToolsFolder');
  {$EXTERNALSYM IPROPNAME_ADMINTOOLS_FOLDER}
  IPROPNAME_COMMONAPPDATA_FOLDER = TEXT('CommonAppDataFolder');
  {$EXTERNALSYM IPROPNAME_COMMONAPPDATA_FOLDER}
  IPROPNAME_LOCALAPPDATA_FOLDER  = TEXT('LocalAppDataFolder');
  {$EXTERNALSYM IPROPNAME_LOCALAPPDATA_FOLDER}
  IPROPNAME_MYPICTURES_FOLDER    = TEXT('MyPicturesFolder');
  {$EXTERNALSYM IPROPNAME_MYPICTURES_FOLDER}

// Feature/Component installation properties: set on command-line

  IPROPNAME_FEATUREADDLOCAL   = TEXT('ADDLOCAL');
  {$EXTERNALSYM IPROPNAME_FEATUREADDLOCAL}
  IPROPNAME_FEATUREADDSOURCE  = TEXT('ADDSOURCE');
  {$EXTERNALSYM IPROPNAME_FEATUREADDSOURCE}
  IPROPNAME_FEATUREADDDEFAULT = TEXT('ADDDEFAULT');
  {$EXTERNALSYM IPROPNAME_FEATUREADDDEFAULT}
  IPROPNAME_FEATUREREMOVE     = TEXT('REMOVE');
  {$EXTERNALSYM IPROPNAME_FEATUREREMOVE}
  IPROPNAME_FEATUREADVERTISE  = TEXT('ADVERTISE');
  {$EXTERNALSYM IPROPNAME_FEATUREADVERTISE}
  IPROPVALUE_FEATURE_ALL      = TEXT('ALL');
  {$EXTERNALSYM IPROPVALUE_FEATURE_ALL}

  IPROPNAME_COMPONENTADDLOCAL   = TEXT('COMPADDLOCAL');
  {$EXTERNALSYM IPROPNAME_COMPONENTADDLOCAL}
  IPROPNAME_COMPONENTADDSOURCE  = TEXT('COMPADDSOURCE');
  {$EXTERNALSYM IPROPNAME_COMPONENTADDSOURCE}
  IPROPNAME_COMPONENTADDDEFAULT = TEXT('COMPADDDEFAULT');
  {$EXTERNALSYM IPROPNAME_COMPONENTADDDEFAULT}

  IPROPNAME_FILEADDLOCAL   = TEXT('FILEADDLOCAL');
  {$EXTERNALSYM IPROPNAME_FILEADDLOCAL}
  IPROPNAME_FILEADDSOURCE  = TEXT('FILEADDSOURCE');
  {$EXTERNALSYM IPROPNAME_FILEADDSOURCE}
  IPROPNAME_FILEADDDEFAULT = TEXT('FILEADDDEFAULT');
  {$EXTERNALSYM IPROPNAME_FILEADDDEFAULT}

  IPROPNAME_REINSTALL          = TEXT('REINSTALL');
  {$EXTERNALSYM IPROPNAME_REINSTALL}
  IPROPNAME_REINSTALLMODE      = TEXT('REINSTALLMODE');
  {$EXTERNALSYM IPROPNAME_REINSTALLMODE}
  IPROPNAME_PROMPTROLLBACKCOST = TEXT('PROMPTROLLBACKCOST');
  {$EXTERNALSYM IPROPNAME_PROMPTROLLBACKCOST}
  IPROPVALUE_RBCOST_PROMPT     = TEXT('P');
  {$EXTERNALSYM IPROPVALUE_RBCOST_PROMPT}
  IPROPVALUE_RBCOST_SILENT     = TEXT('D');
  {$EXTERNALSYM IPROPVALUE_RBCOST_SILENT}
  IPROPVALUE_RBCOST_FAIL       = TEXT('F');
  {$EXTERNALSYM IPROPVALUE_RBCOST_FAIL}

// Property for custom actions to communicate

  IPROPNAME_CUSTOMACTIONDATA = TEXT('CustomActionData');
  {$EXTERNALSYM IPROPNAME_CUSTOMACTIONDATA}

//------------------------------------------------------------------------------
// TOP-LEVEL ACTION NAMES
//------------------------------------------------------------------------------

  IACTIONNAME_INSTALL         = TEXT('INSTALL');
  {$EXTERNALSYM IACTIONNAME_INSTALL}
  IACTIONNAME_ADVERTISE       = TEXT('ADVERTISE');
  {$EXTERNALSYM IACTIONNAME_ADVERTISE}
  IACTIONNAME_ADMIN           = TEXT('ADMIN');
  {$EXTERNALSYM IACTIONNAME_ADMIN}
  IACTIONNAME_SEQUENCE        = TEXT('SEQUENCE');
  {$EXTERNALSYM IACTIONNAME_SEQUENCE}
  IACTIONNAME_COLLECTUSERINFO = TEXT('CollectUserInfo');
  {$EXTERNALSYM IACTIONNAME_COLLECTUSERINFO}
  IACTIONNAME_FIRSTRUN        = TEXT('FirstRun');
  {$EXTERNALSYM IACTIONNAME_FIRSTRUN}

//------------------------------------------------------------------------------
//  SummaryInformation property stream property IDs
//------------------------------------------------------------------------------

// standard property definitions, from OLE2 documentation

  PID_DICTIONARY   = 0; // integer count + array of entries
  {$EXTERNALSYM PID_DICTIONARY}
  PID_CODEPAGE     = 1; // short integer
  {$EXTERNALSYM PID_CODEPAGE}
  PID_TITLE        = 2; // string
  {$EXTERNALSYM PID_TITLE}
  PID_SUBJECT      = 3; // string
  {$EXTERNALSYM PID_SUBJECT}
  PID_AUTHOR       = 4; // string
  {$EXTERNALSYM PID_AUTHOR}
  PID_KEYWORDS     = 5; // string
  {$EXTERNALSYM PID_KEYWORDS}
  PID_COMMENTS     = 6; // string
  {$EXTERNALSYM PID_COMMENTS}
  PID_TEMPLATE     = 7; // string
  {$EXTERNALSYM PID_TEMPLATE}
  PID_LASTAUTHOR   = 8; // string
  {$EXTERNALSYM PID_LASTAUTHOR}
  PID_REVNUMBER    = 9; // string
  {$EXTERNALSYM PID_REVNUMBER}
  PID_EDITTIME     = 10; // datatime
  {$EXTERNALSYM PID_EDITTIME}
  PID_LASTPRINTED  = 11; // datetime
  {$EXTERNALSYM PID_LASTPRINTED}
  PID_CREATE_DTM   = 12; // datetime
  {$EXTERNALSYM PID_CREATE_DTM}
  PID_LASTSAVE_DTM = 13; // datetime
  {$EXTERNALSYM PID_LASTSAVE_DTM}
  PID_PAGECOUNT    = 14; // integer
  {$EXTERNALSYM PID_PAGECOUNT}
  PID_WORDCOUNT    = 15; // integer
  {$EXTERNALSYM PID_WORDCOUNT}
  PID_CHARCOUNT    = 16; // integer
  {$EXTERNALSYM PID_CHARCOUNT}
  PID_THUMBNAIL    = 17; // clipboard format + metafile/bitmap (not supported)
  {$EXTERNALSYM PID_THUMBNAIL}
  PID_APPNAME      = 18; // string
  {$EXTERNALSYM PID_APPNAME}
  PID_SECURITY     = 19; // integer
  {$EXTERNALSYM PID_SECURITY}

// PIDs given specific meanings for Installer

  PID_MSIVERSION  = PID_PAGECOUNT; // integer, Installer version number (major*100+minor)
  {$EXTERNALSYM PID_MSIVERSION}
  PID_MSISOURCE   = PID_WORDCOUNT; // integer, type of file image, short/long, media/tree
  {$EXTERNALSYM PID_MSISOURCE}
  PID_MSIRESTRICT = PID_CHARCOUNT; // integer, transform restrictions
  {$EXTERNALSYM PID_MSIRESTRICT}

//------------------------------------------------------------------------------
// INSTALLER DATABASE INTEGER COLUMN DEFINITIONS
//------------------------------------------------------------------------------

// BBControl.Attributes
// Control.Attributes

type
  msidbControlAttributes = DWORD;
  {$EXTERNALSYM msidbControlAttributes}

const
  msidbControlAttributesVisible            = $00000001;
  {$EXTERNALSYM msidbControlAttributesVisible}
  msidbControlAttributesEnabled            = $00000002;
  {$EXTERNALSYM msidbControlAttributesEnabled}
  msidbControlAttributesSunken             = $00000004;
  {$EXTERNALSYM msidbControlAttributesSunken}
  msidbControlAttributesIndirect           = $00000008;
  {$EXTERNALSYM msidbControlAttributesIndirect}
  msidbControlAttributesInteger            = $00000010;
  {$EXTERNALSYM msidbControlAttributesInteger}
  msidbControlAttributesRTLRO              = $00000020;
  {$EXTERNALSYM msidbControlAttributesRTLRO}
  msidbControlAttributesRightAligned       = $00000040;
  {$EXTERNALSYM msidbControlAttributesRightAligned}
  msidbControlAttributesLeftScroll         = $00000080;
  {$EXTERNALSYM msidbControlAttributesLeftScroll}
  msidbControlAttributesBiDi               = msidbControlAttributesRTLRO or
    msidbControlAttributesRightAligned or msidbControlAttributesLeftScroll;
  {$EXTERNALSYM msidbControlAttributesBiDi}

  // Text controls

  msidbControlAttributesTransparent       = $00010000;
  {$EXTERNALSYM msidbControlAttributesTransparent}
  msidbControlAttributesNoPrefix          = $00020000;
  {$EXTERNALSYM msidbControlAttributesNoPrefix}
  msidbControlAttributesNoWrap            = $00040000;
  {$EXTERNALSYM msidbControlAttributesNoWrap}
  msidbControlAttributesFormatSize        = $00080000;
  {$EXTERNALSYM msidbControlAttributesFormatSize}
  msidbControlAttributesUsersLanguage     = $00100000;
  {$EXTERNALSYM msidbControlAttributesUsersLanguage}

  // Edit controls

  msidbControlAttributesMultiline         = $00010000;
  {$EXTERNALSYM msidbControlAttributesMultiline}
  msidbControlAttributesPasswordInput     = $00200000;
  {$EXTERNALSYM msidbControlAttributesPasswordInput}

  // ProgressBar controls

  msidbControlAttributesProgress95        = $00010000;
  {$EXTERNALSYM msidbControlAttributesProgress95}

  // VolumeSelectCombo and DirectoryCombo controls

  msidbControlAttributesRemovableVolume   = $00010000;
  {$EXTERNALSYM msidbControlAttributesRemovableVolume}
  msidbControlAttributesFixedVolume       = $00020000;
  {$EXTERNALSYM msidbControlAttributesFixedVolume}
  msidbControlAttributesRemoteVolume      = $00040000;
  {$EXTERNALSYM msidbControlAttributesRemoteVolume}
  msidbControlAttributesCDROMVolume       = $00080000;
  {$EXTERNALSYM msidbControlAttributesCDROMVolume}
  msidbControlAttributesRAMDiskVolume     = $00100000;
  {$EXTERNALSYM msidbControlAttributesRAMDiskVolume}
  msidbControlAttributesFloppyVolume      = $00200000;
  {$EXTERNALSYM msidbControlAttributesFloppyVolume}

  // VolumeCostList controls

  msidbControlShowRollbackCost            = $00400000;
  {$EXTERNALSYM msidbControlShowRollbackCost}

  // ListBox and ComboBox controls

  msidbControlAttributesSorted            = $00010000;
  {$EXTERNALSYM msidbControlAttributesSorted}
  msidbControlAttributesComboList         = $00020000;
  {$EXTERNALSYM msidbControlAttributesComboList}

  // picture button controls

  msidbControlAttributesImageHandle       = $00010000;
  {$EXTERNALSYM msidbControlAttributesImageHandle}
  msidbControlAttributesPushLike          = $00020000;
  {$EXTERNALSYM msidbControlAttributesPushLike}
  msidbControlAttributesBitmap            = $00040000;
  {$EXTERNALSYM msidbControlAttributesBitmap}
  msidbControlAttributesIcon              = $00080000;
  {$EXTERNALSYM msidbControlAttributesIcon}
  msidbControlAttributesFixedSize         = $00100000;
  {$EXTERNALSYM msidbControlAttributesFixedSize}
  msidbControlAttributesIconSize16        = $00200000;
  {$EXTERNALSYM msidbControlAttributesIconSize16}
  msidbControlAttributesIconSize32        = $00400000;
  {$EXTERNALSYM msidbControlAttributesIconSize32}
  msidbControlAttributesIconSize48        = $00600000;
  {$EXTERNALSYM msidbControlAttributesIconSize48}

  // RadioButton controls

  msidbControlAttributesHasBorder         = $01000000;
  {$EXTERNALSYM msidbControlAttributesHasBorder}

// CompLocator.Type
// IniLocator.Type
// RegLocator.Type

type
  msidbLocatorType = DWORD;
  {$EXTERNALSYM msidbLocatorType}

const
  msidbLocatorTypeDirectory = $00000000;
  {$EXTERNALSYM msidbLocatorTypeDirectory}
  msidbLocatorTypeFileName  = $00000001;
  {$EXTERNALSYM msidbLocatorTypeFileName}
  msidbLocatorTypeRawValue  = $00000002;
  {$EXTERNALSYM msidbLocatorTypeRawValue}
  msidbLocatorType64bit     = $00000010;
  {$EXTERNALSYM msidbLocatorType64bit}

// Component.Attributes

type
  msidbComponentAttributes = DWORD;
  {$EXTERNALSYM msidbComponentAttributes}

const
  msidbComponentAttributesLocalOnly          = $00000000;
  {$EXTERNALSYM msidbComponentAttributesLocalOnly}
  msidbComponentAttributesSourceOnly         = $00000001;
  {$EXTERNALSYM msidbComponentAttributesSourceOnly}
  msidbComponentAttributesOptional           = $00000002; // local or source
  {$EXTERNALSYM msidbComponentAttributesOptional}
  msidbComponentAttributesRegistryKeyPath    = $00000004; // KeyPath is key to Registry table
  {$EXTERNALSYM msidbComponentAttributesRegistryKeyPath}
  msidbComponentAttributesSharedDllRefCount  = $00000008; // increment SharedDll count
  {$EXTERNALSYM msidbComponentAttributesSharedDllRefCount}
  msidbComponentAttributesPermanent          = $00000010; // never uninstall component
  {$EXTERNALSYM msidbComponentAttributesPermanent}
  msidbComponentAttributesODBCDataSource     = $00000020; // KeyFile is key to ODBCDataSource table
  {$EXTERNALSYM msidbComponentAttributesODBCDataSource}
  msidbComponentAttributesTransitive         = $00000040; // Can transition to/from installed/uninstalled based on changing conditional
  {$EXTERNALSYM msidbComponentAttributesTransitive}
  msidbComponentAttributesNeverOverwrite     = $00000080; // dont stomp over existing component if key path exists (file/ regkey)
  {$EXTERNALSYM msidbComponentAttributesNeverOverwrite}
  msidbComponentAttributes64bit              = $00000100; // designates a 64-bit component; 32-bit if missing.
  {$EXTERNALSYM msidbComponentAttributes64bit}

// Assembly.Attributes

type
  msidbAssemblyAttributes = DWORD;
  {$EXTERNALSYM msidbAssemblyAttributes}

const
  msidbAssemblyAttributesURT   = $00000000;
  {$EXTERNALSYM msidbAssemblyAttributesURT}
  msidbAssemblyAttributesWin32 = $00000001;
  {$EXTERNALSYM msidbAssemblyAttributesWin32}

// CustomAction.Type

type
  msidbCustomActionType = DWORD;
  {$EXTERNALSYM msidbCustomActionType}

const

  // executable types

  msidbCustomActionTypeDll              = $00000001;  // Target = entry point name
  {$EXTERNALSYM msidbCustomActionTypeDll}
  msidbCustomActionTypeExe              = $00000002;  // Target = command line args
  {$EXTERNALSYM msidbCustomActionTypeExe}
  msidbCustomActionTypeTextData         = $00000003;  // Target = text string to be formatted and set into property
  {$EXTERNALSYM msidbCustomActionTypeTextData}
  msidbCustomActionTypeJScript          = $00000005;  // Target = entry point name, null if none to call
  {$EXTERNALSYM msidbCustomActionTypeJScript}
  msidbCustomActionTypeVBScript         = $00000006;  // Target = entry point name, null if none to call
  {$EXTERNALSYM msidbCustomActionTypeVBScript}
  msidbCustomActionTypeInstall          = $00000007;  // Target = property list for nested engine initialization
  {$EXTERNALSYM msidbCustomActionTypeInstall}

  // source of code

  msidbCustomActionTypeBinaryData       = $00000000;  // Source = Binary.Name, data stored in stream
  {$EXTERNALSYM msidbCustomActionTypeBinaryData}
  msidbCustomActionTypeSourceFile       = $00000010;  // Source = File.File, file part of installation
  {$EXTERNALSYM msidbCustomActionTypeSourceFile}
  msidbCustomActionTypeDirectory        = $00000020;  // Source = Directory.Directory, folder containing existing file
  {$EXTERNALSYM msidbCustomActionTypeDirectory}
  msidbCustomActionTypeProperty         = $00000030;  // Source = Property.Property, full path to executable
  {$EXTERNALSYM msidbCustomActionTypeProperty}

  // return processing                  // default is syncronous execution, process return code

  msidbCustomActionTypeContinue         = $00000040;  // ignore action return status, continue running
  {$EXTERNALSYM msidbCustomActionTypeContinue}
  msidbCustomActionTypeAsync            = $00000080;  // run asynchronously
  {$EXTERNALSYM msidbCustomActionTypeAsync}

  // execution scheduling flags               // default is execute whenever sequenced

  msidbCustomActionTypeFirstSequence    = $00000100;  // skip if UI sequence already run
  {$EXTERNALSYM msidbCustomActionTypeFirstSequence}
  msidbCustomActionTypeOncePerProcess   = $00000200;  // skip if UI sequence already run in same process
  {$EXTERNALSYM msidbCustomActionTypeOncePerProcess}
  msidbCustomActionTypeClientRepeat     = $00000300;  // run on client only if UI already run on client
  {$EXTERNALSYM msidbCustomActionTypeClientRepeat}
  msidbCustomActionTypeInScript         = $00000400;  // queue for execution within script
  {$EXTERNALSYM msidbCustomActionTypeInScript}
  msidbCustomActionTypeRollback         = $00000100;  // in conjunction with InScript: queue in Rollback script
  {$EXTERNALSYM msidbCustomActionTypeRollback}
  msidbCustomActionTypeCommit           = $00000200;  // in conjunction with InScript: run Commit ops from script on success
  {$EXTERNALSYM msidbCustomActionTypeCommit}

  // security context flag, default to impersonate as user, valid only if InScript

  msidbCustomActionTypeNoImpersonate    = $00000800;  // no impersonation, run in system context
  {$EXTERNALSYM msidbCustomActionTypeNoImpersonate}

//#if (_WIN32_MSI >= 150)
  msidbCustomActionTypeTSAware          = $00004000;  // impersonate for per-machine installs on TS machines
  {$EXTERNALSYM msidbCustomActionTypeTSAware}
//#endif // (_WIN32_MSI >= 150)

  // script requires 64bit process
  msidbCustomActionType64BitScript      = $00001000;  // script should run in 64bit process
  {$EXTERNALSYM msidbCustomActionType64BitScript}

  // don't record the contents of the Target field in the log file.
  msidbCustomActionTypeHideTarget       = $00002000;
  {$EXTERNALSYM msidbCustomActionTypeHideTarget}

// Dialog.Attributes

type
  msidbDialogAttributes = DWORD;
  {$EXTERNALSYM msidbDialogAttributes}

const
  msidbDialogAttributesVisible          = $00000001;
  {$EXTERNALSYM msidbDialogAttributesVisible}
  msidbDialogAttributesModal            = $00000002;
  {$EXTERNALSYM msidbDialogAttributesModal}
  msidbDialogAttributesMinimize         = $00000004;
  {$EXTERNALSYM msidbDialogAttributesMinimize}
  msidbDialogAttributesSysModal         = $00000008;
  {$EXTERNALSYM msidbDialogAttributesSysModal}
  msidbDialogAttributesKeepModeless     = $00000010;
  {$EXTERNALSYM msidbDialogAttributesKeepModeless}
  msidbDialogAttributesTrackDiskSpace   = $00000020;
  {$EXTERNALSYM msidbDialogAttributesTrackDiskSpace}
  msidbDialogAttributesUseCustomPalette = $00000040;
  {$EXTERNALSYM msidbDialogAttributesUseCustomPalette}
  msidbDialogAttributesRTLRO            = $00000080;
  {$EXTERNALSYM msidbDialogAttributesRTLRO}
  msidbDialogAttributesRightAligned     = $00000100;
  {$EXTERNALSYM msidbDialogAttributesRightAligned}
  msidbDialogAttributesLeftScroll       = $00000200;
  {$EXTERNALSYM msidbDialogAttributesLeftScroll}
  msidbDialogAttributesBiDi             = msidbDialogAttributesRTLRO or
    msidbDialogAttributesRightAligned or msidbDialogAttributesLeftScroll;
  {$EXTERNALSYM msidbDialogAttributesBiDi}
  msidbDialogAttributesError            = $00010000;
  {$EXTERNALSYM msidbDialogAttributesError}

// Feature.Attributes

type
  msidbFeatureAttributes = DWORD;
  {$EXTERNALSYM msidbFeatureAttributes}

const
  msidbFeatureAttributesFavorLocal             = $00000000;
  {$EXTERNALSYM msidbFeatureAttributesFavorLocal}
  msidbFeatureAttributesFavorSource            = $00000001;
  {$EXTERNALSYM msidbFeatureAttributesFavorSource}
  msidbFeatureAttributesFollowParent           = $00000002;
  {$EXTERNALSYM msidbFeatureAttributesFollowParent}
  msidbFeatureAttributesFavorAdvertise         = $00000004;
  {$EXTERNALSYM msidbFeatureAttributesFavorAdvertise}
  msidbFeatureAttributesDisallowAdvertise      = $00000008;
  {$EXTERNALSYM msidbFeatureAttributesDisallowAdvertise}
  msidbFeatureAttributesUIDisallowAbsent       = $00000010;
  {$EXTERNALSYM msidbFeatureAttributesUIDisallowAbsent}
  msidbFeatureAttributesNoUnsupportedAdvertise = $00000020;
  {$EXTERNALSYM msidbFeatureAttributesNoUnsupportedAdvertise}

// File.Attributes

type
  msidbFileAttributes = DWORD;
  {$EXTERNALSYM msidbFileAttributes}

const
  msidbFileAttributesReadOnly       = $00000001;
  {$EXTERNALSYM msidbFileAttributesReadOnly}
  msidbFileAttributesHidden         = $00000002;
  {$EXTERNALSYM msidbFileAttributesHidden}
  msidbFileAttributesSystem         = $00000004;
  {$EXTERNALSYM msidbFileAttributesSystem}
  msidbFileAttributesReserved0      = $00000008; // Internal use only - must be 0
  {$EXTERNALSYM msidbFileAttributesReserved0}
  msidbFileAttributesReserved1      = $00000040; // Internal use only - must be 0
  {$EXTERNALSYM msidbFileAttributesReserved1}
  msidbFileAttributesReserved2      = $00000080; // Internal use only - must be 0
  {$EXTERNALSYM msidbFileAttributesReserved2}
  msidbFileAttributesReserved3      = $00000100; // Internal use only - must be 0
  {$EXTERNALSYM msidbFileAttributesReserved3}
  msidbFileAttributesVital          = $00000200;
  {$EXTERNALSYM msidbFileAttributesVital}
  msidbFileAttributesChecksum       = $00000400;
  {$EXTERNALSYM msidbFileAttributesChecksum}
  msidbFileAttributesPatchAdded     = $00001000; // Internal use only - set by patches
  {$EXTERNALSYM msidbFileAttributesPatchAdded}
  msidbFileAttributesNoncompressed  = $00002000;
  {$EXTERNALSYM msidbFileAttributesNoncompressed}
  msidbFileAttributesCompressed     = $00004000;
  {$EXTERNALSYM msidbFileAttributesCompressed}
  msidbFileAttributesReserved4      = $00008000; // Internal use only - must be 0
  {$EXTERNALSYM msidbFileAttributesReserved4}

// IniFile.Action
// RemoveIniFile.Action

type
  msidbIniFileAction = DWORD;
  {$EXTERNALSYM msidbIniFileAction}

const
  msidbIniFileActionAddLine    = $00000000;
  {$EXTERNALSYM msidbIniFileActionAddLine}
  msidbIniFileActionCreateLine = $00000001;
  {$EXTERNALSYM msidbIniFileActionCreateLine}
  msidbIniFileActionRemoveLine = $00000002;
  {$EXTERNALSYM msidbIniFileActionRemoveLine}
  msidbIniFileActionAddTag     = $00000003;
  {$EXTERNALSYM msidbIniFileActionAddTag}
  msidbIniFileActionRemoveTag  = $00000004;
  {$EXTERNALSYM msidbIniFileActionRemoveTag}

// MoveFile.Options

type
  msidbMoveFileOptions = DWORD;
  {$EXTERNALSYM msidbMoveFileOptions}

const
  msidbMoveFileOptionsMove = $00000001;
  {$EXTERNALSYM msidbMoveFileOptionsMove}

// ODBCDataSource.Registration

type
  msidbODBCDataSourceRegistration = DWORD;
  {$EXTERNALSYM msidbODBCDataSourceRegistration}

const
  msidbODBCDataSourceRegistrationPerMachine  = $00000000;
  {$EXTERNALSYM msidbODBCDataSourceRegistrationPerMachine}
  msidbODBCDataSourceRegistrationPerUser     = $00000001;
  {$EXTERNALSYM msidbODBCDataSourceRegistrationPerUser}

// Class.Attributes

type
  msidbClassAttributes = DWORD;
  {$EXTERNALSYM msidbClassAttributes}

const
  msidbClassAttributesRelativePath  = $00000001;
  {$EXTERNALSYM msidbClassAttributesRelativePath}

// Patch.Attributes

type
  msidbPatchAttributes = DWORD;
  {$EXTERNALSYM msidbPatchAttributes}

const
  msidbPatchAttributesNonVital = $00000001;
  {$EXTERNALSYM msidbPatchAttributesNonVital}

// Registry.Root
// RegLocator.Root
// RemoveRegistry.Root

type
  msidbRegistryRoot = DWORD;
  {$EXTERNALSYM msidbRegistryRoot}

const
  msidbRegistryRootClassesRoot  = 0;
  {$EXTERNALSYM msidbRegistryRootClassesRoot}
  msidbRegistryRootCurrentUser  = 1;
  {$EXTERNALSYM msidbRegistryRootCurrentUser}
  msidbRegistryRootLocalMachine = 2;
  {$EXTERNALSYM msidbRegistryRootLocalMachine}
  msidbRegistryRootUsers        = 3;
  {$EXTERNALSYM msidbRegistryRootUsers}

// RemoveFile.InstallMode

type
  msidbRemoveFileInstallMode = DWORD;
  {$EXTERNALSYM msidbRemoveFileInstallMode}

const
  msidbRemoveFileInstallModeOnInstall = $00000001;
  {$EXTERNALSYM msidbRemoveFileInstallModeOnInstall}
  msidbRemoveFileInstallModeOnRemove  = $00000002;
  {$EXTERNALSYM msidbRemoveFileInstallModeOnRemove}
  msidbRemoveFileInstallModeOnBoth    = $00000003;
  {$EXTERNALSYM msidbRemoveFileInstallModeOnBoth}

// ServiceControl.Event

type
  msidbServiceControlEvent = DWORD;
  {$EXTERNALSYM msidbServiceControlEvent}

const
  msidbServiceControlEventStart             = $00000001;
  {$EXTERNALSYM msidbServiceControlEventStart}
  msidbServiceControlEventStop              = $00000002;
  {$EXTERNALSYM msidbServiceControlEventStop}
  msidbServiceControlEventDelete            = $00000008;
  {$EXTERNALSYM msidbServiceControlEventDelete}
  msidbServiceControlEventUninstallStart    = $00000010;
  {$EXTERNALSYM msidbServiceControlEventUninstallStart}
  msidbServiceControlEventUninstallStop     = $00000020;
  {$EXTERNALSYM msidbServiceControlEventUninstallStop}
  msidbServiceControlEventUninstallDelete   = $00000080;
  {$EXTERNALSYM msidbServiceControlEventUninstallDelete}

// ServiceInstall.ErrorControl

type
  msidbServiceInstallErrorControl = DWORD;
  {$EXTERNALSYM msidbServiceInstallErrorControl}

const
  msidbServiceInstallErrorControlVital = $00008000;
  {$EXTERNALSYM msidbServiceInstallErrorControlVital}

// TextStyle.StyleBits

type
  msidbTextStyleStyleBits = DWORD;
  {$EXTERNALSYM msidbTextStyleStyleBits}

const
  msidbTextStyleStyleBitsBold         = $00000001;
  {$EXTERNALSYM msidbTextStyleStyleBitsBold}
  msidbTextStyleStyleBitsItalic       = $00000002;
  {$EXTERNALSYM msidbTextStyleStyleBitsItalic}
  msidbTextStyleStyleBitsUnderline    = $00000004;
  {$EXTERNALSYM msidbTextStyleStyleBitsUnderline}
  msidbTextStyleStyleBitsStrike       = $00000008;
  {$EXTERNALSYM msidbTextStyleStyleBitsStrike}

// Upgrade.Attributes

type
  msidbUpgradeAttributes = DWORD;
  {$EXTERNALSYM msidbUpgradeAttributes}

const
  msidbUpgradeAttributesMigrateFeatures     = $00000001;
  {$EXTERNALSYM msidbUpgradeAttributesMigrateFeatures}
  msidbUpgradeAttributesOnlyDetect          = $00000002;
  {$EXTERNALSYM msidbUpgradeAttributesOnlyDetect}
  msidbUpgradeAttributesIgnoreRemoveFailure = $00000004;
  {$EXTERNALSYM msidbUpgradeAttributesIgnoreRemoveFailure}
  msidbUpgradeAttributesVersionMinInclusive = $00000100;
  {$EXTERNALSYM msidbUpgradeAttributesVersionMinInclusive}
  msidbUpgradeAttributesVersionMaxInclusive = $00000200;
  {$EXTERNALSYM msidbUpgradeAttributesVersionMaxInclusive}
  msidbUpgradeAttributesLanguagesExclusive  = $00000400;
  {$EXTERNALSYM msidbUpgradeAttributesLanguagesExclusive}

//------------------------------------------------------------------------------
// SUMMARY INFORMATION PROPERTY DEFINITIONS
//------------------------------------------------------------------------------

type
  msidbSumInfoSourceType = DWORD;
  {$EXTERNALSYM msidbSumInfoSourceType}

const
  msidbSumInfoSourceTypeSFN            = $00000001;  // source uses short filenames
  {$EXTERNALSYM msidbSumInfoSourceTypeSFN}
  msidbSumInfoSourceTypeCompressed     = $00000002;  // source is compressed
  {$EXTERNALSYM msidbSumInfoSourceTypeCompressed}
  msidbSumInfoSourceTypeAdminImage     = $00000004;  // source is an admin image
  {$EXTERNALSYM msidbSumInfoSourceTypeAdminImage}

implementation

end.
