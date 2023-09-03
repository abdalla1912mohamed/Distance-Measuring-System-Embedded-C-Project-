/*
 * ultrasonic.h
 *
 *  Created on: Jul 17, 2023
 *      Author: Abdalla
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"
#include "icu.h"
#endif /* ULTRASONIC_H_ */

#define trigger_pin 5







////////////////////////////// functions ///////////////
 void Ultrasonic_init(void) ;



  void Ultrasonic_Trigger(void) ;



  uint16 Ultrasonic_readDistance(void) ;





  void Ultrasonic_edgeProcessing(void) ;













