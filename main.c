/****************** main.c ******************/

#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include <stdio.h>

// gpioSetMode(unsigned gpio, unsigned mode)
// gpio 0-53, mode 0-7
//
// uses GPIO## numbering
// examples: 
//	set GPIO17 as input:
//		gpioSetMode(17, PI_INPUT); 
//	set GPIO18 as output:
//		gpioSetMode(18, PI_OUTPUT);
//
// int gpioRead (unsigned gpio); // read it.
// 
// int gpioWrite(unsigned gpio, unsigned level);
// 	sets GPIO level, on or off (1 or 0)
//	also: if PWM or servo pulses are active on 
// 	the GPIO, they are switched off.
//
// gpioTick - get current microsecond tick number
// gpioTime - get current time
// gpioSleep - sleep for a time. (what unit?)
// time_sleep - sleeps for a float number of seconds.
//
//	in order to use PWM on BCM12 and BCM13, need to set gpio mode to PI_ALT0
//	in order to use PWM on BCM18, need to set gpio mode to PI_ALT5

// #define J8_8	4
// #define J8_10	15
// #define J8_11	17
// #define J8_12	18
// #define J8_13	27
// #define J8_15	22
// #define J8_32	12
// #define J8_33	13
// #define J8_36	16
// #define J8_37	26
// #define J8_38	20
// #define J8_40	21
// 
// #define PWM0_PIN	12
// #define PWM1_PIN	13
// 
// #define LMOTOR_PWM 	PWM0_PIN
// #define LMOTOR_DIR	J8_36
// #define RMOTOR_PWM	PWM1_PIN
// #define RMOTOR_DIR	J8_37
// 
// // these may or may not need to be used.
// #define LMOTOR_NSLP	
// #define RMOTOR_NSLP	

#include "raz_follower_defs.h"


void blinkGpio(int gpio){
//	blinkGpio(LMOTOR_DIR);
	for(int i = 0; i < 10; i++){
		gpioWrite(gpio, i % 2);
		time_sleep(0.5f);		
	}	
  
}
void delay(int millis);
void pwmDoubleBreather(int, int);
int initGpio();
int initGpio(){
	
	if(gpioInitialise() < 0){
		puts("couldn't initialize gpio.\n");
		return 1;
	}

	gpioSetMode(LMOTOR_DIR, PI_OUTPUT);
	gpioSetMode(RMOTOR_DIR, PI_OUTPUT);
	gpioSetMode(LMOTOR_PWM, PI_ALT0);
	gpioSetMode(RMOTOR_PWM, PI_ALT0);
	gpioSetMode(LMOTOR_NSLP, PI_OUTPUT);
	gpioSetMode(RMOTOR_NSLP, PI_OUTPUT);
	
	return 0;
}

int main(){
	// surround with silent try-catch-move-on?

	printf("hello and welcome.");

	if(initGpio() == 1){
		return 1;
	}
	
	delay(1000);
	printf("\rbye.\n");

	
	gpioTerminate();
	return 0;
}

void delay(int millis){
	time_sleep(0.001f * millis);
}

void pwmDoubleBreather(int gpioA, int gpioB){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 255; j++){
			gpioPWM(PWM0_PIN, (i % 2 == 0 ? j : 255 - j));
			gpioPWM(PWM1_PIN, (i % 2 == 1 ? j : 255 - j));
			time_sleep(0.002f);
		}
	}
}

