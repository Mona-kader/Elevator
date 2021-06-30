
#include "timer.h"

void timer1_init_OCI_10ms()
{
	 sei();
	 TIMSK=(1<<OCIE1A);
	 TCNT1=0;
	 OCR1A=1250;
	 TCCR1A=0;
	 TCCR1B=(1<<CS12)|(1<<WGM12);
}



