#include "Main.h"

//todo:
//Finish Parse Data function, Special char " | "
		
FBIPACKETA ParseData(char main [4096] = "")
{
int I = 0;
int P = 0;
int Y = 0;
int Count = 0;
FBIPACKETA Info;
ZeroMemory(&Info, sizeof(FBIPACKETA));
	while(main[I] != NULL)
	{
		switch(Count)
			{
			case 0: // ScreenResA
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
				  Info.Buf[P]= main[I];
				  P++;
				  Y++;
			break;
			case 1: // AdminA
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf1[P]= main[I];
				  P++;
				  Y++;
			break;
			case 2: // ProcessorName
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf2[P]= main[I];
				  P++;
				  Y++;
			break;
			case 3: // UserName
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf3[P]= main[I];
				  P++;
				  Y++;;
				
			break;
			case 4: // CompIp
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf4[P]= main[I];
				  P++;
			break;
			case 5: // OS
			
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf5[P] = main[I];
				  P++;
			break;
			
			case 6: // OS
			
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf6[P] = main[I];
				  P++;
				  break;
			case 7: // OS
			
				  if(main[I] == '|' || main[I] == NULL )
				  {
					P = 0;
					Count++;
					break;
				  }
			      Info.Buf7[P] = main[I];
				  P++;
				  break;
			}
		
		I++;

	}
return Info;
}
