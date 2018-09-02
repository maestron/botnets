#ifndef _M_HOOK_h
#define _M_HOOK_h
//#define _WIN32_WINNT 0x0400
#define DLLEXPORT __declspec(dllexport)
#define WIN32_LEAN_AND_MEAN
#define WH_KEYBOARD_LL     13

typedef struct {
    DWORD vkCode;
    DWORD scanCode;
    DWORD flags;
    DWORD time;
    ULONG_PTR dwExtraInfo;
} KBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;

#endif // M_HOOK