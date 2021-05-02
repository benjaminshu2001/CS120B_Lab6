/*	Author: Benjamin Shu
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Link to Demo: https://www.youtube.com/watch?v=hiUQfTYpmkw
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"
enum States {Start, Begin, Wait, Inc, IncDepressed, Dec, DecDepressed, Reset, IncHold, DecHold} State;

unsigned char count = 0;
void Tick_Counter() {
    switch(State) {
        case Start:
            State = Wait;
            break;
        case Begin:
            State = Wait;
            break;
        case Wait:
            if((~PINA & 0x03) == 0x03) {
                State = Reset;
            }
            else if((~PINA & 0x01) == 0x01) {
                State = Inc;
            }
            else if((~PINA & 0x02) == 0x02) {
                State = Dec;
            }
            else {
                State = Wait;
            }
            break;
        case Inc:
			if(count >= 0x0A) {
				count = 0;
			}
			State = IncDepressed;
            break;
		case IncHold:
			if((~PINA & 0x03) == 0x01) {
				State = Inc;
			}
			else {
				State = Wait;
			}
            break;

        case IncDepressed:
            if((~PINA & 0x01) == 0x01) {
				count++;
				State = IncDepressed;
				if(count >= 0x0A) {
					State = Inc;
				}
			}
			else {
				State = IncHold;
			}
			break;
        case Dec:
            if(count >= 0x0A) {
				count = 0;
			}
			State = DecDepressed;
            break;
		case DecHold:
			if((~PINA & 0x02) == 0x02) {
				State = DecHold;
			}
			else {
				State = Wait;
			}
			break;
        case DecDepressed:
            if((~PINA & 0x03) == 0x02) {
                count++;
				State = DecDepressed;
				if(count >= 0x0A) {
					State = Dec;
				}
            }
			else {
				State = DecHold;
			}
            break;
        case Reset:
            if((~PINA & 0x03) == 0x03) {
                State = Reset;
            }
            else {
                State = Wait;
            }
            break;
        default:
            State = Start;
            break;
    }
    switch(State) {
        case Start:
            PORTB = 0x07;
            break;
        case Begin:     
            PORTB = 0x07;
            break;
        case Wait:
			count = 0;
            break;
        case Inc:
            if(PORTB < 0x09) {
                PORTB = PORTB + 1;
            }
            break;
		case IncHold:
			break;
        case IncDepressed:
            break;
        case Dec:
            if(PORTB > 0x00) {
                PORTB = PORTB - 1;
            }
            break;
		case DecHold:
			break;
        case DecDepressed:
            break;
        case Reset:
            PORTB = 0x00;
            break;
        default:
            PORTB = 0x07;
            break;
    }              
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
	TimerSet(100);
	TimerOn();
	State = Start;
    while (1) {
		Tick_Counter();
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
