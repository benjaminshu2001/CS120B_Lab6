/*	Author: Benjamin Shu
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Link to Demo: https://www.youtube.com/watch?v=n27OcaQxdAE
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum Light_States {Start, Wait, Light1, Wait1, Light2, Wait2, Light3, Wait3, Wait4, Wait5} State;

void TckLight() {
	switch(State) {
		case Start:
			State = Wait;
			break;
		case Wait:
			if((~PINA & 0x01) == 0x01) {
				State = Wait;
			}
			else {
				State = Light1;
			}
			break;
		case Light1:
			if((~PINA & 0x01) == 0x01) { //turns on light, moves when 300 ms passes
				State = Light1;
			}
			else {
				State = Wait1;
			}
			break;
		case Wait1:
			if((~PINA & 0x01) == 0x01) { //if pressed, stay, else go to next light
				State = Wait1;
			}
			else {
				State = Light2;
			}
			break;
		case Light2:
			if((~PINA & 0x01) == 0x01) {
				State = Wait2;
			}
			else {
				State = Light3;
			}
			break;
		case Wait2:
			if((~PINA & 0x01) == 0x01) {
				State = Wait2;
			}
			else {
				State = Light3;
			}
			break;
		case Light3:
			if((~PINA & 0x01) == 0x01) {
				State = Wait3;
			}
			else {
				State = Wait4;
			}
			break;
		case Wait3:
			if((~PINA & 0x01) == 0x01) {
				State = Wait3;
			}
			else {
				State = Wait4;
			}
			break;
		case Wait4:
			if((~PINA & 0x01) == 0x01) {
				State = Wait4;
			}
			else {
				State = Wait5;
			}
			break;
		case Wait5:
			if((~PINA & 0x01) == 0x01) {
				State = Wait5;
			}
			else {
				State = Light1;
			}
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
		case Wait1:
			PORTB = 0x01;
			break;
		case Light2:
			PORTB = 0x02;
			break;
		case Wait2:
			PORTB = 0x02;
			break;
		case Light3:
			PORTB = 0x04;
			break;
		case Wait3:
			PORTB = 0x04;
			break;
		case Wait4:
			PORTB = 0x02;
			break;
		case Wait5:
			PORTB = 0x02;
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
	TimerSet(300);
	TimerOn();
	State = Start;
    while (1) {
		TckLight();
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
