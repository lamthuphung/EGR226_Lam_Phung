/*****************************************************************************************************************************
*Author:       Lam Thu Phung
*Course:       EGR 226 - 901
*Date:         March 17, 2021
*Program:      Lab 8 Part3
*File:         main.c
*Description:  This program uses TimerA module to implement PWM cycles for a DC motor. The program takes input from a keypad
               (0-100) and sets the PWM duty cycle to the inputed value. The user input is only accepted when the
               '#' character is pressed.
******************************************************************************************************************************/
#include "msp.h"
#include <stdio.h>
#include <stdint.h>
#define Delay 100 // variable tells how long to use Systick Delay
void pinAssign();//assigns necessary pins for keypad and f
void timerA(void);//function used to initialize TimerA, set period, and set duty cycle
void SysTick_Init (void);//initializes Systick timer
void SysTick_Delay (uint16_t delay);//creates 1 ms delay per input value
uint8_t read_keypad(void);//function that looks for keypad input
double dutyCycle = 50;    //set initial duty cycle to 50% (65000/2)=37500 counts
void print_key(void);
double num;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    int8_t pressed;//variable which holds value of button pressed)
    double pin_array[2]={-1,-1}; // signed integer array that stores the last 4 buttons pressed
    pinAssign();//assigns necessary pins
    timerA();//function used to initialize TimerA, set period, and set duty cycle
    SysTick_Init();
    while(1)
    {
        pressed = read_keypad(); // Call Function to read Keypad
        if (pressed)
        { // checks to see if a button was pressed
              //print_key();
              if(num != 10 && num != 12)
              { // check to see if character '*' or '#' was entered
                     print_key();
                     if (num == 11)
                     {
                          num = 0;
                     }
                     pin_array[1]= pin_array[0];//shifts all values in array to the right 1 index
                     pin_array[0]= num;//assigns most recent key pressed to array index 0
              }
              if (num == 12)
              {//if character '#' is pressed on keypad
                     print_key();
                     dutyCycle = ((pin_array[1]*10) + pin_array[0]);
                     printf("Duty cycle = %g\n", dutyCycle);
                     TIMER_A0->CCR[4] = (dutyCycle * 650); // CCR1 PWM duty cycle in 10ths of percent
              }
        }
    }
}

void timerA(void)
{
    TIMER_A0->CCR[0] = 65000 - 1; // PWM Period (# cycles of clock = (3MHz /46.2Hz) - 1)
    TIMER_A0->CCR[4] = 32500; // CCR1 PWM duty cycle
    TIMER_A0->CCTL[4] = 0xE0; // CCR1 reset/set mode 7
    TIMER_A0->CTL = 0x0214;
}

void pinAssign(void)
{
    P2->SEL0 |= 0x80;
    P2->SEL1 &= 0x80;
    P2->DIR |= 0x80; // P2.7 set TA0.1
    P4->SEL0 &=~ 0x7F; //Set pins to inputs to start
    P4->SEL1 &=~ 0x7F;
    P4->DIR  &=~ 0x7F; //setting rows as input
    P4->REN |= 0x7F; //pull resistor enabled
    P4->OUT |= 0x7F; //setting to pull up resistor
}

uint8_t read_keypad(void)
{
    uint8_t col, row;
    for (col = 0; col < 3; col++)
    {
        P4->DIR = 0x00; //Set columns to inputs
        P4->DIR |= BIT(4 + col);    //Set column 3 to output
        P4->OUT &=~ BIT(4 + col);   //Set column 3 to LOW

        SysTick_Delay(10);
        row = P4->IN & 0x0F;

        while(!(P4IN & BIT0) | !(P4IN & BIT1) | !(P4IN & BIT2) | !(P4IN & BIT3));
        if (row != 0x0F) break;     //if one of the input is low, some key is pressed
    }

    P4->DIR = 0x00; //Set Columns to inputs
    if (col == 3) return 0;

    if (row == 0x0E) num = col + 1; //key in row 0
    if (row == 0x0D) num = 3 + col + 1; //key in row 1
    if (row == 0x0B) num = 6 + col + 1; //key in row 2
    if (row == 0x07) num = 9 + col + 1; //key in row 3

    return 1;
}

void print_key(void)
{
    if (num == 12) printf("Key [#]\n");
    if (num == 11) printf("Key [0]\n");
    if (num == 10) printf("Key [*]\n");
    if (num < 10) printf("Key [%g]\n", num);
}

void SysTick_Init (void)
{ //initialization of systic timer
    SysTick -> CTRL = 0; // disable SysTick During step
    SysTick -> LOAD = 0x00FFFFFF; // max reload value
    SysTick -> VAL = 0; // any write to current clears it
    SysTick -> CTRL = 0x00000005; // enable systic, 3MHz, No Interrupts
}

void SysTick_Delay (uint16_t delay)
{ // Systick delay function
    SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
    SysTick -> VAL = 0; // any write to CVR clears it
    while ((SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}
