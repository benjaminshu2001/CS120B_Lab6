/*	Author: Benjamin Shu
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Link to Demo: https://www.youtube.com/watch?v=tr0Z50LHVu8
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum Light_States {Start, Wait, Light1, Light2, Light3} State;

void TckLight() {
	switch(State) {
		case Start:
			State = Wait;
			break;
		case Wait:
			State = Light1;
			break;
		case Light1:
			State = Light2;
			break;
		case Light2:
			State = Light3;
			break;
		case Light3:
			State = Light1;
			break;
	}
	switch(State) {
		case Start:
			break;
		case Wait:
			break;
		case Light1:
			PORTB = 0x01;
			break;
		case Light2:
			PORTB = 0x02;
			break;
		case Light3:
			PORTB = 0x04;
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
	TimerSet(1000);
	TimerOn();
	State = Start;
    while (1) {
		TckLight();
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
