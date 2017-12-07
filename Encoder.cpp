/*
 * Encoder.cpp
 *
 * Created: 10/24/2017 10:10:26 PM
 *  Author: Prakash Chaudhary
 */ 
#include "Encoder.h"

/* Constructor to Initialize all the variables to 0 */
Encoder::Encoder()
{
	Speed_count = 0;
	Encoder_speed = 0;
	
	//Distance_count = 0;
	Distance_forward_count = 0;
	Distance_reverse_count = 0;
	Encoder_distance = 0;
	
	Angle_count = 0;
	Angle = 0;
	
	Encoder_Initialize();
}
/* Constructor to Initialize all the variables to 0 */

/* Initialize Encoder */
void  Encoder::Encoder_Initialize(void)
{
	INPUT(ENCODER_PIN1);	// Sets output pins of encoder as input for uC for data
	INPUT(ENCODER_PIN2);

	Encoder_Initialize_External_Interrupt();	//Init for interrupt pin of Input
	Encoder_Initialize_Timer();		// Initialize for 10 sec time to calculate Distance or Speed
}
/* Initialize Encoder */

/* Initialize External Interrupt and its Flag */
void Encoder::Encoder_Initialize_External_Interrupt(void)
{
	REGISTER_SET1(EICRA,ENCODER_ISC);	// Selects falling edge trigger of interrupt pin
	REGISTER_SET1(EIMSK,ENCODER_INTERRUPT);	//Sets INT0 as interrupt pin
	REGISTER_SET1(EIFR,ENCODER_INTERRUPT_FLAG);	//Sets interrupt flag on
}
/* Initialize External Interrupt and its Flag  */

/* Initialize Timer/Counter */
void Encoder::Encoder_Initialize_Timer(void)
{
	REGISTER_SET2(ENCODER_TCCR,ENCODER_CSn0,ENCODER_CSn2);	// Sets prescalar to 1024
	REGISTER_SET1(ENCODER_TIMSK,ENCODER_OCIE);	// Sets output compare interrupt enable
	REGISTER_SET1(ENCODER_TIFR,ENCODER_OCF);	// Sets flag on compare match
	ENCODER_OCR = ENCODER_OCR_VALUE;	// Sets OCR value for compare match
	ENCODER_TCNT = 0;	//Set the timer 0
}
/* Initialize Timer/Counter */

/* Calculate Speed of the rotation of Encoder/Motor */
void Encoder::Encoder_Increase_Speed_Pulse_Counter(void)
{
	Speed_count++;	//Increases at each pulse count from ISR
}

void Encoder::Encoder_Calculate_Speed(void)
{
	//Gives the speed of rotation in RPS 
	Encoder_speed = ((float(Speed_count)/ENCODER_PPR)*1.2/15)*1000; //Multiply by 60 to get RPM
	Speed_count = 0;	//Sets count to zero
}
/* Calculate Speed of the rotation of Encoder/Motor */

/* Calculate Distance moved due to rotation of Encoder/Motor */
void Encoder::Encoder_Increase_Distance_Pulse_Counter(void)
{
	if (READ(ENCODER_PIN2))
	{
		Distance_forward_count++;	//Increases the counter if the rotation is in one direction
		//Distance_count++;
	}
	else if (!(READ(ENCODER_PIN2)))
	{
		Distance_reverse_count++;	//Decreases the counter if the rotation is in the other direction
		//Distance_count--;
	}	
}

void Encoder::Encoder_Calculate_Distance(void)
{
	//Calculates the distance forward moved in 't' time set by timer and adds it from distance moved
	Encoder_distance += 3.14159*ENCODER_DIAMETER * float(Distance_forward_count) /ENCODER_PPR;

	//Calculates the distance reverse moved in 't' time set by timer and subtracts it from distance moved
	Encoder_distance -= 3.14159*ENCODER_DIAMETER * float(Distance_reverse_count) /ENCODER_PPR;
	
	Distance_forward_count = 0;
	Distance_reverse_count = 0;
	/*Include where and when you want it get called calculate RPM/Distance if using above calculation */
	
	//Include the below inside loop if used long int and can change Disance data type to int
	//Encoder_distance = 3.14159*ENCODER_DIAMETER * float(Distance_count) /ENCODER_PPR;
}
/* Calculate Distance moved due to rotation of Encoder/Motor */

/* Calculates the angle made by Encoder during rotation */
void Encoder::Encoder_Increase_Angle_Pulse_Counter(void)
{
	if (READ(ENCODER_PIN2))
	{
		Angle_count++;	//Increases the Angle counter at each pulse in forward direction
	}
	else if (!(READ(ENCODER_PIN2)))
	{
		Angle_count--;	//Dcrease the Angle counter at each pulse in reverse direction
	}
	
	// Clears the Counter if it exceeds the 360 degree pulse equivalent
	if (Angle_count >= ENCODER_PPR_TO_360_DEGREE_EQUIVALENT)
	{
		Angle_count = 0;
	}
	
	Encoder_Calculate_Angle(); // Call it here if you want to calculate Angle in every pulse
}

void Encoder::Encoder_Calculate_Angle(void)
{
	Angle = (Angle_count*(float(ENCODER_MOTOR_FACTOR)/ENCODER_PPR))*360;
	//Call this in ISR in 't' time to calculate angle made by Encoder/Motor in 't' time
}
/* Calculates the angle made by Encoder during rotation */

