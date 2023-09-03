/*
 * ultrasonic.c
 *
 *  Created on: Jul 17, 2023
 *      Author: Abdalla
 */

#include "icu.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */
#include "ultrasonic.h"
#include "lcd.h"
#include"gpio.h"
#include "std_types.h"

uint8 g_edgeCount = 0;
float g_echo_high = 0.0;
ICU_EdgeType Ultrasonic_edge = RAISING  ;
ICU_ClockType Ultrasonic_clock = F_CPU_8 ;
float volatile echo_time  = 0.0;
float distance   = 0.0 ;







void Ultrasonic_edgeProcessing(void){

g_edgeCount++;

	if(g_edgeCount == 1){
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_echo_high = ICU_getInputCaptureValue();
		echo_time = g_echo_high ;
		ICU_clearTimerValue();
				/* Detect rising edge */
		ICU_setEdgeDetectionType(RAISING);  // wait again for the raising

	}
	}

void Ultrasonic_init(void){
	ICU_ConfigType Ultrasonic_Configurations ; // Build a configurable structure for ultrasonic sensor
	Ultrasonic_Configurations.clock = F_CPU_8 ; //initialize the value of the configurable clock
	Ultrasonic_Configurations.edge = RAISING ;   //initialize the value of the configurable edge
	const ICU_ConfigType *Ultrasonic_PTR = &Ultrasonic_Configurations ; // pointer to the ultrasonic_config

	ICU_init(Ultrasonic_PTR) ;
	GPIO_setupPinDirection(PORTB_ID,PB5, PIN_OUTPUT) ;  // set up the trigger pin as output
		GPIO_writePin(PORTB_ID, PB5, LOGIC_LOW) ;
		ICU_setCallBack(Ultrasonic_edgeProcessing);
	// the callback function is set in the ICU driver

}



void Ultrasonic_Trigger(void){
int i = 0 ;
GPIO_writePin(PORTB_ID, PB5, LOGIC_LOW) ;

GPIO_writePin(PORTB_ID, PB5, LOGIC_HIGH) ;   // send the pulse

while(i<10){
	i++ ;
}
GPIO_writePin(PORTB_ID, PB5, LOGIC_LOW) ;

}

uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger() ;  // after the trigger the ICU starts operating and waiting for edge 2
//	GPIO_writePin(PORTB,PB5, LOGIC_LOW) ;
	if(g_edgeCount == 2){
	g_edgeCount = 0;
      distance  =   (float) echo_time * ((float) 0.17) ;

      ICU_clearTimerValue();
      ICR1 = 0 ;
      g_echo_high = 0 ;
     // ICU_deInit() ;}}
     return distance ;



}}


int main(void){

    float real_distance  = 0.0 ;
	LCD_init();

	Ultrasonic_init() ;
	SREG |= (1<<7);


	while(1){
	real_distance  = Ultrasonic_readDistance() ;
        LCD_moveCursor(1, 1);
		// LCD_displayString("distance  = ");


				//	ICU_deInit(); /* Disable ICU Driver */

					LCD_displayString("distance = ");
					LCD_intgerToString(real_distance);
					 LCD_moveCursor(3, 3);
					LCD_displayString("CMs");
				}
			}






