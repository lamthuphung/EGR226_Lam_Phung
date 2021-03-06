#include "msp.h"    //header files with declaration and macro
#include <stdio.h>  //definitions used in the program

void SysTick_Init(void);
void SysTick_Delay(uint16_t delayms);
void keypad_init(void);     //GPIO initialization
uint8_t Read_Keypad(void);  //Keypad scan
void print_key(void);   //print key pressed
uint8_t num;
int pin[4] = {-1,-1,-1,-1}; //declare array pin with the length of 4
int match[4] = {-1,-1,-1,-1};

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    printf("Hello world\n");
    SysTick_Init();
    keypad_init();  //calling initialization functions for functionality
    int pressed, read;
    while (1)
    {
        pressed = Read_Keypad();    //Call function to read keypad
        if (pressed)
            {
                print_key();
                if (num != 12 && num != 10)
                {
                    pin[3] = pin[2];
                    pin[2] = pin[1];
                    pin[1] = pin[0];
                    pin[0] = num;
                }
                else if (num == 12)
                {
                    if ((pin[0] != -1) && (pin[1] != -1) && (pin[2] != -1) && (pin[3] != -1))
                    {
                        printf("PIN accepted. Please enter the PIN again to validate\n");
                        while (read = 1)
                        {
                        pressed = Read_Keypad();
                        if (pressed)
                        {
                            print_key();
                            if (num != 12 && num != 10)
                            {
                                match[3] = match[2];
                                match[2] = match[1];
                                match[1] = match[0];
                                match[0] = num;
                            }
                            else if (num == 12)
                            {
                                if ((match[3] == pin[3]) && (match[2] == pin[2]) && (match[1] == pin[1]) && (match[0] == pin[0]))
                                {
                                    printf("PIN entered:\t\t[%d][%d][%d][%d]\n", pin[3], pin[2], pin[1], pin[0]);
                                    printf("Validation PIN entered:\t[%d][%d][%d][%d]\n", match[3], match[2], match[1], match[0]);
                                    printf("PIN match!\n");
                                    read = 0;
                                }
                                else
                                {
                                    printf("PINs do not match\n");
                                    match[0] = -1;
                                    match[1] = -1;
                                    match[2] = -1;
                                    match[3] = -1;
                                }
                            }
                        }
                        }
                    }
                    else
                    {
                        printf("Too few input\n");
                    }

                }
            }
        _delay_cycles(30000);   //10ms delay through the loop before reading keypad again
    }
    return 0;
}

void keypad_init(void)
{
    P4->SEL0 &=~ 0xFF;
    P4->SEL1 &=~ 0xFF;
    P4->DIR &=~ 0x0F;
    P4->REN |= 0x0F;    //enable pull resistor for row pins
    P4->OUT |= 0x0F;
    P4->DIR &=~ 0x70;
}

uint8_t Read_Keypad(void)
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
    if (num < 10) printf("Key [%d]\n", num);
}

void SysTick_Init(void)
{
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000005;
}

void SysTick_Delay(uint16_t delayms)
{
    SysTick->LOAD = ((delayms * 3000) - 1);
    SysTick->VAL = 0;
    while((SysTick-> CTRL & BIT(16)) == 0);
}
