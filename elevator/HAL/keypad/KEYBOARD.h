#ifndef KEYBOARD_h_
#define KEYBOARD_h_

#include <avr/io.h>
#ifndef F_CPU
# define F_CPU 8000000UL
#endif
#include <util/delay.h>


void keyboardIntiat();
char keyboardScan();




#endif



