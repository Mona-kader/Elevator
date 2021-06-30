#ifndef _SEVEN_SEGEMENT_H_
#define _SEVEN_SEGEMENT_H_
#include <stdint.h>



char SEVEN_seg[10]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XB8,0X80,0X90};
#define SEGMENTS_1ST_CONTROL_PIN	0
#define SEGMENTS_1ST_CONTROL_IN		PINC
#define SEGMENTS_1ST_CONTROL_OUT	PORTC
#define SEGMENTS_1ST_CONTROL_DIR	DDRC


#define SEGMENTS_SEC_CONTROL_PIN	1
#define SEGMENTS_SEC_CONTROL_IN		PINC
#define SEGMENTS_SEC_CONTROL_OUT	PORTC
#define SEGMENTS_SEC_CONTROL_DIR	DDRC



#define SEGMENTS_PORT_IN			PIND
#define SEGMENTS_PORT_OUT			PORTD
#define SEGMENTS_PORT_DIR			DDRD

#define SEGMENT_SET_VALUE(num)	(SEGMENTS_PORT_OUT=SEVEN_seg[num])

#define segement_init()	 			SEGMENTS_PORT_DIR|=0x7F;\
									SEGMENTS_1ST_CONTROL_DIR|=(1<<SEGMENTS_1ST_CONTROL_PIN);\
									SEGMENTS_1ST_CONTROL_DIR|=(1<<SEGMENTS_SEC_CONTROL_PIN)

#define SEGEMENT_1ST_SEC_OFF_ON()		 ( SEGMENTS_1ST_CONTROL_OUT=( (( ~(1<<SEGMENTS_1ST_CONTROL_PIN) )&SEGMENTS_1ST_CONTROL_OUT) |(1<<SEGMENTS_SEC_CONTROL_PIN) ) )

#define SEGEMENT_1ST_SEC_ON_OFF()	( SEGMENTS_1ST_CONTROL_OUT=( (1<<SEGMENTS_1ST_CONTROL_PIN)|(SEGMENTS_1ST_CONTROL_OUT&(~(1<<SEGMENTS_SEC_CONTROL_PIN))) ) )


#endif