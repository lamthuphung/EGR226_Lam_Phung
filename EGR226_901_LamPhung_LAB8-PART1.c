/******************************************************************************************************************
*Author:       Lam Thu Phung
*Course:       EGR 226 - 901
*Date:         March 17, 2021
*Program:      Lab 8 - Part 1
*File:         main.c
*Description:  This program uses the Systick timer to implement PWM on P2.7. PWM is implemented by turning the
*              motor on and off for a set amount of time.
******************************************************************************************************************/
#include "msp.h"
void SysTick_Init(void);    //initializes Systick timer
void motorControl(double duty);//initializes function that controls motor speed
void pinAssign();//assigns P2.7 to output
double h, l, dutyCycle;//initializing variable

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    pinAssign();
    SysTick_Init();
    dutyCycle = 40; //duty cycle variable
    while(1)
    {
        motorControl(dutyCycle);    //calling function that controls motor speed
    }
}

void SysTick_Init (void)    //initialization of SysTick timer
{
    SysTick -> CTRL = 0; // disable SysTick During step
    SysTick -> LOAD = 0x00FFFFFF; // max reload value
    SysTick -> VAL = 0; // any write to current clears it
    SysTick -> CTRL = 0x00000005; // enable SysTick, 3MHz, No Interrupts
}

void motorControl(double duty)  // SysTick delay function
{
            l = (100 - duty) / 5.0;// calculating off time
            h = duty / 5.0;//calculating on time
            P2->OUT |= BIT7;//setting P2.7 to high
            SysTick -> LOAD = ((h * 3000) - 1); //delay for 1 msecond per delay value
            SysTick -> VAL = 0; // any write to CVR clears it
            while ((SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
            P2->OUT &=~ BIT7;//setting P2.7 to low
            SysTick -> LOAD = ((l * 3000) - 1); //delay for 1 msecond per delay value
            SysTick -> VAL = 0; // any write to CVR clears it
            while ((SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}

void pinAssign(void)
{
    P2->SEL0 &=~ BIT7; //Set P2.7 to input to start
    P2->SEL1 &=~ BIT7;
    P2->DIR  |= BIT7; //setting as output
}
