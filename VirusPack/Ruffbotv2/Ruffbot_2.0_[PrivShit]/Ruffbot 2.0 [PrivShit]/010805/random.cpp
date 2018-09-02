/*
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXXX  XXXXXXXXXXXXXX 
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX     
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXX    XXXXXXXXXXXX     
XXXXXXXXX        XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX    
XXXX XXXXX       XXXXX      XXXXX  XXXXX           XXXXX           
XXXX  XXXXX      XXXXX      XXXXX  XXXXX           XXXXX           
XXXX   XXXXX     XXXXX      XXXXX  XXXXX           XXXXX           
XXXX    XXXXX    XXXXXX    XXXXXX  XXXXX           XXXXX           
XXXX     XXXXX   XXXXXXXXXXXXXXXX  XXXXX           XXXXX           
XXXX      XXXXX   XXXXXXXXXXXXXX   XXXXX           XXXXX           
XXXX       XXXXX   XXXXXXXXXXXX    XXXXX           XXXXX 
     



        Ruffbot 2.0 [PrivShit] by Ruffnes

*/ 


#include "includes.h"
#include "functions.h"
#include "externs.h"

int brandom(int bot,int top) { return (int)((float)(top-bot)*rand()/(RAND_MAX+1.0))+bot; }
int get_random_number(int range) { return rand()%range; }
