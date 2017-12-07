/*
 * Encoder.h
 *
 * Created: 10/24/2017 10:10:26 PM
 *  Author: Prakash Chaudhary
 */ 

#ifndef ENCODER
#define ENCODER

#include "Headers.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

//#define DDR_SELECT DDRC

#define TIMER_OVERFLOW_VECT TIMER0_OVF_vect		//Set the timer/counter overflow vector name

#define ENCODER_PIN1 D,0		//Set the interrupt pin for the encoder
#define ENCODER_PIN2 D,1		//Set the digital pin for encoder
#define ENCODER_ISC ISC01
#define ENCODER_INTERRUPT INT0		//Set the interrupt for interrupt init
#define ENCODER_INTERRUPT_VECT INT0_vect	//Set the respective interrupt vector name
#define ENCODER_INTERRUPT_FLAG INTF0		//Enable the respective interrupt flag

/* Macro for setting up timer to calculate speed */
#define ENCODER_TCCR TCCR0B
#define ENCODER_CSn0 CS00
#define ENCODER_CSn2 CS02
#define ENCODER_OCR OCR0A
#define ENCODER_TIMSK TIMSK0
#define ENCODER_OCIE OCIE0A
#define ENCODER_TIFR TIFR0
#define ENCODER_OCF OCF0A
#define ENCODER_TCNT TCNT0
#define ENCODER_OCR_VALUE 156 // 10 ms Time
/* Macro for setting up timer to calculate speed */

/* Macro to calculate speed */
#define ENCODER_PPR 1024		//Set the PPR value of the encoder motor
#define ENCODER_DIAMETER 5	//Set the radius of the wheel so as to calculate the distance covered
#define ENCODER_MOTOR_FACTOR 1.2	//Motor vs Gear rotation Ratio
#define ENCODER_PPR_TO_360_DEGREE_EQUIVALENT 853	//Sets the 1024 ppr encoder to equivalent ppr for 360 degree rotation
/* Macro to calculate speed */

class Encoder
{
	public:
	int Speed_count;
	int Encoder_speed;
	
	int Distance_forward_count;
	int Distance_reverse_count;
	//long int Distance_count;
	float Encoder_distance;
	
	int Angle_count; //why unsigned?
	int Angle;
	

	public:
	Encoder();
	
	void Encoder_Initialize(void);
	void Encoder_Initialize_Timer(void);	//Initializes the timer
	void Encoder_Initialize_External_Interrupt(void);	//Enables the interrupt pin
	
	/* Speed Calculation */
	void Encoder_Increase_Speed_Pulse_Counter(void);
	void Encoder_Calculate_Speed(void);
	
	/* Distance moved Calculation */
	void Encoder_Increase_Distance_Pulse_Counter(void);
	void Encoder_Calculate_Distance(void);
	
	/* Angle made due to rotation Calculation */
	void Encoder_Increase_Angle_Pulse_Counter(void);
	void Encoder_Calculate_Angle(void);
	
	/* Get the Speed, Distance and Angle */
	int Encoder_Get_Speed(void) {return Encoder_speed;}
	int Encoder_Get_Distance(void) {return int(Encoder_distance);}
	int Encoder_Get_Angle(void) {return Angle;}
	/* Get the Speed, Distance and Angle */
	
	};
	
	
#endif

//ISR (ENCODER_INTERRUPT_VECT)
//{
	//Encoder_Increase_Speed_Pulse_counter();
	//Encoder_Increase_Distance_Pulse_Counter();
	//Encoder_Increase_Angle_Counter();
//}

//ISR (TIMER0_COMPA_vect)
//{
	//Encoder_Calculate_Speed();
	//Encoder_Calculate_Distance();
	//Encoder_Calculate_Angle();
//}

