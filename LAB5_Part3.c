/**************************************************************************************
* Author: Lam Thu Phung
* Course: EGR 226 - 905
* Date: 02/26/2021
* Project: LAB 5
* File: LAB 5 - Part 3
* Description: Reverse the order
**************************************************************************************/

#include "msp.h"

int deBounce_Press_Forward(void);
int deBounce_Press_Backward(void);
void SysTick_Init(void);
void SysTick_delay(uint16_t delayms);
void setupButton(void);
void setupLed(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    //Upon startup or program reset, all LEDs should be OFF -> Assign variable "state" = 0
    int state = 0;

    setupButton();
    setupLed();
    SysTick_Init(); //SysTick initialization

    while(1)
    {
    switch (state)
    {
    case 0:
        //Upon startup or program reset, all LEDs should be OFF
        SysTick_delay(100);
        P4->OUT &= ~BIT0;
        P4->OUT &= ~BIT1;
        P4->OUT &= ~BIT2;
        if (deBounce_Press_Forward() == 1)  //Check if the button is pressed
        {
            SysTick_delay(50);
            if (deBounce_Press_Forward() == 1)   //After making sure the button was pressed, the program move forward to state 1.
            state = 1;
        }
        else if (deBounce_Press_Backward() == 1)  //Check if the button is pressed
        {
            SysTick_delay(50);
            if (deBounce_Press_Backward() == 1)   //After making sure the button was pressed, the program move backward to state 3.
            state = 3;
        }
        break;

    case 1: //Case 1: Green LED ON, Yellow LED OFF, Red LED OFF.
        SysTick_delay(100);
        P4->OUT |= BIT0;
        P4->OUT &= ~BIT1;
        P4->OUT &= ~BIT2;
        if (deBounce_Press_Forward() == 1)  //Check if the button is pressed
        {
            SysTick_delay(50);
            if (deBounce_Press_Forward() == 1)   //After making sure the button was pressed, the program move to state 2.
            state = 2;
        }
        else if (deBounce_Press_Backward() == 1)  //Check if the button is pressed
        {
            SysTick_delay(50);
            if (deBounce_Press_Backward() == 1)   //After making sure the button was pressed, the program move backward to state 3.
            state = 3;
        }
        break;

    case 2: //Case 2: Green LED OFF, Yellow LED ON, Red LED OFF.
        SysTick_delay(100);
        P4->OUT &= ~BIT0;
        P4->OUT |= BIT1;
        P4->OUT &= ~BIT2;
        if (deBounce_Press_Forward() == 1)  //Check if the button is pressed
        {
            SysTick_delay(50);
            if (deBounce_Press_Forward() == 1)   //After making sure the button was pressed, the program move to state 3.
            state = 3;
        }
        else if (deBounce_Press_Backward() == 1)  //Check if the button is pressed
        {
            SysTick_delay(50);
            if (deBounce_Press_Backward() == 1)   //After making sure the button was pressed, the program move backward to state 3.
            state = 1;
        }
        break;

    case 3: //Case 3: Green LED OFF, Yellow LED OFF, Red LED ON.
        SysTick_delay(100);
        P4->OUT &= ~BIT0;
        P4->OUT &= ~BIT1;
        P4->OUT |= BIT2;
        if (deBounce_Press_Forward() == 1)  //Check if the button is pressed
        {
            SysTick_delay(50);
            if (deBounce_Press_Forward() == 1)    //After making sure the button was pressed, the program move back to state 1.
           state = 1;
        }
        else if (deBounce_Press_Backward() == 1)  //Check if the button is pressed
        {
            SysTick_delay(50);
            if (deBounce_Press_Backward() == 1)   //After making sure the button was pressed, the program move backward to state 3.
            state = 2;
        }
        break;
    }
    }
}

int deBounce_Press_Forward(void)
{
    //initialize pin value (in the beginning, the button is not pressed)
    int press;

    //Check if the button is pressed
    if ((P3->IN & BIT7) == 0)   //Equal to 0 meaning it pulled down = pressed
    {
        //wait for 15ms because of switch bounce
        SysTick_delay(15);

        //check one more time to make sure the button is still pressed
        if ((P3->IN & BIT7) == 0)
            press = 1;
    }
    else press = 0;
    return press;    //Return 1 if the button is pressed  - return 0 if the button is not pressed
}

int deBounce_Press_Backward(void)
{
    //initialize pin value (in the beginning, the button is not pressed)
    int press;

    //Check if the button is pressed
    if ((P3->IN & BIT6) == 0)   //Equal to 0 meaning it pulled down = pressed
    {
        //wait for 15ms because of switch bounce
        SysTick_delay(15);

        //check one more time to make sure the button is still pressed
        if ((P3->IN & BIT6) == 0)
            press = 1;
    }
    else press = 0;
    return press;    //Return 1 if the button is pressed  - return 0 if the button is not pressed
}

void SysTick_Init(void)
{   //initialization of systic timer
    SysTick -> CTRL = 0;    //disable SysTick During step
    SysTick -> LOAD = 0x00FFFFFF;   //max reload value
    SysTick -> VAL = 0;     //any write to current clears it
    SysTick -> CTRL = 0x00000005;   //enable systic, 3MHz, No Interrupts
}

void SysTick_delay(uint16_t delayms)
{
    SysTick -> LOAD = ((delayms * 3000) - 1);  //delay for 1msecond per delay
    SysTick -> VAL = 0; //any write to CVR clears it
    while ((SysTick -> CTRL & 0x00010000) == 0);    //wait for flag to be SET
}

void setupButton(void)
{
    //Reading a button switch going forward
    P3->SEL1 &= ~BIT7;  //configure P3.7 as simple I/O
    P3->SEL0 &= ~BIT7;
    P3->DIR &= ~BIT7;   //P3.7 set as output
    P3->REN |= BIT7;    //P3.7 pull resistor enabled
    P3->OUT |= BIT7;    //Pull up/down is selected by P3->OUT

    //Reading a button switch going forward
    P3->SEL1 &= ~BIT6;  //configure P3.6 as simple I/O
    P3->SEL0 &= ~BIT6;
    P3->DIR &= ~BIT6;   //P3.6 set as output
    P3->REN |= BIT6;    //P3.6 pull resistor enabled
    P3->OUT |= BIT6;    //Pull up/down is selected by P3->OUT
}

void setupLed(void)
{
    P4->SEL1 &= ~BIT0;     //Configure P4.0 for green led
    P4->SEL0 &= ~BIT0;
    P4->DIR |= BIT0;       //P4.0 set as output
    P4->OUT &= ~BIT0;

    P4->SEL1 &= ~BIT1;     //Configure P4.1 for yellow led
    P4->SEL0 &= ~BIT1;
    P4->DIR |= BIT1;       //P4.1 set as output
    P4->OUT &= ~BIT1;

    P4->SEL1 &= ~BIT2;     //Configure P4.2 for red led
    P4->SEL0 &= ~BIT2;
    P4->DIR |= BIT2;       //P4.2 set as output
    P4->OUT &= ~BIT2;
}
