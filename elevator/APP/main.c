
#ifndef F_CPU
# define F_CPU 8000000UL
#endif
#include "../HAL/seven_segment.h"
#include "../HAL/keypad/KEYBOARD.h"
#include "util/delay.h"
#include "../MCAL/timer/timer.h"
#include<avr/io.h>

//alarm
#define ALARM_BUTTON_PIN		0
#define ALARM_BUTTON_DIR 		DDRB
#define ALARM_BUTTON_OUT		PORTB
#define ALARM_BUTTON_IN			PINB
#define ALARM_BUTTON_READ()		( (ALARM_BUTTON_IN & (1<<ALARM_BUTTON_PIN))!=0 )

#define ALARM_PIN				1
#define ALARM_DIR 				DDRB
#define ALARM_OUT				PORTB
#define ALARM_IN				PINB

//fan

#define FAN_BUTTON_PIN			2
#define FAN_BUTTON_DIR 			DDRB
#define FAN_BUTTON_OUT			PORTB
#define FAN_BUTTON_IN			PINB
#define FAN_BUTTON_READ()		( (FAN_BUTTON_IN & (1<<FAN_BUTTON_PIN)) !=0  )

#define FAN_PIN					3
#define FAN_DIR 				DDRB
#define FAN_OUT					PORTB
#define FAN_IN					PINB

#define LIFT1_PIN				4
#define LIFT1_DIR 				DDRB
#define LIFT1_OUT				PORTB
#define LIFT1_IN				PINB

#define LIFT1_UP_PIN				5
#define LIFT1_UP_DIR 				DDRB
#define LIFT1_UP_OUT				PORTB
#define LIFT1_UP_IN					PINB

#define DOOR1_PIN				6
#define DOOR1_DIR 				DDRC
#define DOOR1_OUT				PORTC
#define DOOR1_IN				PINC

#define LIFT1_UP()						LIFT1_UP_OUT|=(1<<LIFT1_UP_PIN);\
										LIFT1_OUT&=~(1<<LIFT1_PIN)

#define LIFT1_DOWM()					LIFT1_UP_OUT&=~(1<<LIFT1_UP_PIN);\
										LIFT1_OUT|=(1<<LIFT1_PIN)

#define LIFT1_STOP()					LIFT1_OUT&=~(1<<LIFT1_PIN);\
										LIFT1_UP_OUT&=~(1<<LIFT1_UP_PIN);\
										DOOR1_OUT|=(1<<DOOR1_PIN);\
										_delay_ms(1000);\
										DOOR1_OUT&=~(1<<DOOR1_PIN)







#define LIFT2_PIN				6
#define LIFT2_DIR 				DDRB
#define LIFT2_OUT				PORTB
#define LIFT2_IN				PINB

#define LIFT2_UP_PIN				7
#define LIFT2_UP_DIR 				DDRB
#define LIFT2_UP_OUT				PORTB
#define LIFT2_UP_IN					PINB

#define DOOR2_PIN				7
#define DOOR2_DIR 				DDRC
#define DOOR2_OUT				PORTC
#define DOOR2_IN				PINC

#define LIFT2_UP()						LIFT2_UP_OUT|=(1<<LIFT2_UP_PIN);\
										LIFT2_OUT&=~(1<<LIFT2_PIN)

#define LIFT2_DOWM()					LIFT2_UP_OUT&=~(1<<LIFT2_UP_PIN);\
										LIFT2_OUT|=(1<<LIFT2_PIN)

#define LIFT2_STOP()					LIFT2_OUT&=~(1<<LIFT2_PIN);\
										LIFT2_UP_OUT&=~(1<<LIFT2_UP_PIN);\
										DOOR2_OUT|=(1<<DOOR2_PIN);\
										_delay_ms(1000);\
										DOOR2_OUT&=~(1<<DOOR2_PIN)




volatile uint8_t timer_elev1=0,elev1_current_floor=1;
volatile uint8_t timer_elev2=0,elev2_current_floor=1;
uint8_t reguested_floor=20;





int main()
{


	char key;
	ALARM_BUTTON_DIR&=~(1<<ALARM_BUTTON_PIN);
	ALARM_BUTTON_OUT|=(1<<ALARM_BUTTON_PIN);

	FAN_BUTTON_DIR&=~(1<<FAN_BUTTON_PIN);
	FAN_BUTTON_OUT|=(1<<FAN_BUTTON_PIN);
	ALARM_DIR|=(1<<ALARM_PIN);
	FAN_DIR|=(1<<FAN_PIN);
	LIFT1_DIR|=(1<<LIFT1_PIN);
	LIFT1_UP_DIR|=(1<<LIFT1_UP_PIN);
	DOOR1_DIR|=(1<<DOOR1_PIN);
	LIFT2_DIR|=(1<<LIFT2_PIN);
	LIFT2_UP_DIR|=(1<<LIFT2_UP_PIN);
	DOOR2_DIR|=(1<<DOOR2_PIN);
	segement_init();
	timer1_init_OCI_10ms();
	keyboardIntiat();
	    while (1)
	    {
	    	do
	    	{
	    	key=keyboardScan();
	    	}while(key < '1' || key > '3');

	    	reguested_floor=key-0x30;

	    }

}

ISR(TIMER1_COMPA_vect)
{
	static uint8_t counter=0,elev1_counter=0,elev2_counter=0;

	++counter;
	if( counter%2 ==1 )
	{
		SEGEMENT_1ST_SEC_OFF_ON();
		SEGMENT_SET_VALUE(elev1_current_floor);
	}
	else
	{
    	SEGEMENT_1ST_SEC_ON_OFF();
    	SEGMENT_SET_VALUE(elev2_current_floor);

	}

	if(FAN_BUTTON_READ()==0 )
	{
		FAN_OUT|=(1<<FAN_PIN);
	}
	else
	{
		FAN_OUT&=~(1<<FAN_PIN);
	}

	if( ALARM_BUTTON_READ()==0)
	{
		ALARM_OUT|=(1<<ALARM_PIN);
		elev1_counter=elev2_counter=1;
		reguested_floor=20;

	}
	else
	{
		ALARM_OUT&=~(1<<ALARM_PIN);
	}

	if(reguested_floor !=20)
	{

		if( (elev2_current_floor !=2 && reguested_floor !=2) || (elev1_counter==0 &&elev2_counter !=0) )
		{
			if(elev1_current_floor > reguested_floor)
			{
				LIFT1_DOWM();
				elev1_counter=255;
			}
			else if(elev1_current_floor < reguested_floor)
			{
				LIFT1_UP();
				elev1_counter=255;
			}
			elev1_current_floor=reguested_floor;
		}
		else
		{
			if(elev2_current_floor > reguested_floor)
			{
				LIFT2_DOWM();
				elev2_counter=255;
			}
			else if(elev2_current_floor < reguested_floor)
			{
				LIFT2_UP();
				elev2_counter=255;
			}

			elev2_current_floor=reguested_floor;
		}

		reguested_floor=20;
	}

	if(elev1_counter==1)
	{
		LIFT1_STOP();
		--elev1_counter;
	}
	else if(elev1_counter > 1)
	{
		--elev1_counter;
	}

	if(elev2_counter==1)
	{
		LIFT2_STOP();
		--elev2_counter;
	}
	else if (elev2_counter > 1)
	{
		--elev2_counter;
	}




}

