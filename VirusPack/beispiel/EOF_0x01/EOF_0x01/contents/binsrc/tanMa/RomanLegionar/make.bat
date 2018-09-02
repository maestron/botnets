tasm32 start.asm
bcc32 -RT- -x- -c -w-8064 -Ie:\bcc55\include RL32.c
tlink32 -aa -n -LRTL start RL32 ,RL32.exe
