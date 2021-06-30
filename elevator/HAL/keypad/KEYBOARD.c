


#include "KEYBOARD.h"
#define keyboardDDR 	DDRA
#define KeyboardPORT 	PORTA
#define keyboardPIN 	PINA

char char_arr[4][4]={{'7','8','9','/'},
			{'4','5','6','*'},
			{'1','2','3','-'},
			{'<','0','=','+'}
	    };

void keyboardIntiat()
{
	/*Set columns Out - rows IN*/
	 keyboardDDR=0x0f;
		/*Activate Pull Up - and Outputs HIGH*/
	 KeyboardPORT=0xFF;

}
char keyboardScan()
{
	

	char ret_val = 0;
	char col, row;
	for(col = 0; col < 4; col++)
	{

		 KeyboardPORT&=~(1<<col);
		for(row = 4; row < 8; row++)
		{
			if( (keyboardPIN &(1<<row))== 0)
			{
				ret_val = char_arr[row - 4][col];
			}

			/*Wait until button released*/
			while(!(keyboardPIN &(1<<row)));

			/*Debouncing*/
			_delay_ms(10);
		}
	
		 KeyboardPORT|=(1<<col);
	}

	return ret_val;
		

}












