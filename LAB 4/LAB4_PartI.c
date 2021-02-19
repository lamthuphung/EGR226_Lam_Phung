#include "msp.h"

int deBounce_Press(void);

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
	//Upon startup or program reset, all LEDs should be OFF -> Assign variable "state" = 0
    int state = 0;

    P2->SEL1 &= ~7;     //Configure P2.2-P2.0 as simple I/O
    P2->SEL0 &= ~7;
    P2->DIR |= 7;       //P2.2 - P2.0 set as output

    //Reading a switch
    P1->SEL1 &= ~BIT1;  //configure P1.1 as simple I/O
    P1->SEL0 &= ~BIT1;
    P1->DIR &= ~BIT1;   //P1.1 set as output
    P1->REN |= BIT1;    //P1.1 pull resistor enabled
    P1->OUT |= BIT1;    //Pull up/down is selected by P1->OUT

    while(1)
    {
    switch (state)
    {
    case 0:
        //Upon startup or program reset, all LEDs should be OFF
        P2->OUT &= ~BIT0;
        P2->OUT &= ~BIT1;
        P2->OUT &= ~BIT2;
        if (deBounce_Press() == 1)  //Check if the button is pressed
        {
            while (deBounce_Press() == 1)   //After making sure the button was pressed, the program move to state 1.
            state = 1;
        }
        break;

    case 1: //Case 1: Red LED ON, Green LED OFF, Blue LED OFF.
        P2->OUT |= BIT0;
        P2->OUT &= ~BIT1;
        P2->OUT &= ~BIT2;
        if (deBounce_Press() == 1)  //Check if the button is pressed
        {
            while (deBounce_Press() == 1)   //After making sure the button was pressed, the program move to state 2.
            state = 2;
        }
        break;

    case 2: //Case 2: Red LED OFF, Green LED ON, Blue LED OFF.
        P2->OUT &= ~BIT0;
        P2->OUT |= BIT1;
        P2->OUT &= ~BIT2;
        if (deBounce_Press() == 1)  //Check if the button is pressed
        {
            while (deBounce_Press() == 1)   //After making sure the button was pressed, the program move to state 3.
            state = 3;
        }
        break;

    case 3: //Case 3: Red LED OFF, Green LED OFF, Blue LED ON.
        P2->OUT &= ~BIT0;
        P2->OUT &= ~BIT1;
        P2->OUT |= BIT2;
        if (deBounce_Press() == 1)  //Check if the button is pressed
        {
           while (deBounce_Press() == 1)    //After making sure the button was pressed, the program move back to state 1.
           state = 1;
        }
        break;
    }
    }
}

int deBounce_Press(void)
{
    //initialize pin value (in the beginning, the button is not pressed)
    int press;

    //Check if the button is pressed
    if ((P1->IN & BIT1) == 0)   //Equal to 0 meaning it pulled down = pressed
    {
        //wait for 15ms because of switch bounce
        _delay_cycles(15000);

        //check one more time to make sure the button is still pressed
        if ((P1->IN & BIT1) == 0)
            press = 1;
    }
    else press = 0;
    return press;    //Return 1 if the button is pressed  - return 0 if the button is not pressed
}
