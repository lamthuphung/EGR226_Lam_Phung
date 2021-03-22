/*****************************************************************************************************************************
*Author:       Lam Thu Phung
*Course:       EGR 226 - 901
*Date:         March 17, 2021
*Program:      Lab 8 Part2
*File:         main.c
*Description:  This program uses TimerA module to implement PWM cycles for a DC motor.
******************************************************************************************************************************/

#include "msp.h"
void pinAssign();
void timerA(void);
double dutyCycle = 40;  //set initial duty cycle to 40%

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    pinAssign();
    timerA();
    while(1)
    {
        TIMER_A0->CCR[4] = (dutyCycle * 650); // CCR1 PWM duty cycle in 10ths of percent
    }
}

void timerA(void)
{
    TIMER_A0->CCR[0] = 65000 - 1; // PWM Period (# cycles of clock = (3MHz /60Hz) - 1)
    TIMER_A0->CCR[4] = 32500; // CCR1 PWM duty cycle
    TIMER_A0->CCTL[4] = 0xE0; // CCR1 reset/set mode 7
    TIMER_A0->CTL = 0x0214;
}

void pinAssign(void)
{
    P2->SEL0 |= BIT7;
    P2->SEL1 &= BIT7;
    P2->DIR |= BIT7; // P2.7 set TA0.1
}
