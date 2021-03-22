#include "msp.h"
#include "string.h"
#include <stdio.h>

void SysTick_Init(void);
void LCD_Pins(void);
void LCD_init(void);
void pushNibble (uint8_t nibble);
void pushByte (uint8_t byte);
void commandWrite(uint8_t command);
void dataWrite(float data);
void PulseEnablePin(void);
void delay_ms(unsigned ms);
void delay_micro(uint32_t microsecond);
void printString(char* string);
void gotoLine(uint8_t line);

void main(void)
{
        SysTick_Init();
        LCD_Pins();
        LCD_init();
        gotoLine(1);
        printString("Lam");
        gotoLine(2);
        printString("Phung");
        gotoLine(3);
        printString("EGR");
        gotoLine(4);
        printString("226");

        while(1);
}

void SysTick_Init(void)
{   //initialization of Systick timer
    SysTick -> CTRL = 0;    //disable SysTick During step
    SysTick -> LOAD = 0x00FFFFFF;   //max reload value
    SysTick -> VAL = 0;     //any write to current clears it
    SysTick -> CTRL = 0x00000005;   //enable Systick, 3MHz, No Interrupts
}



void LCD_Pins(void)
{
    P6->SEL0 &= ~BIT1;  //6.1 set as output is the E pin
    P6->SEL1 &= ~BIT1;
    P6->DIR |= BIT1;

    P6->SEL0 &= ~BIT0;  //6.0 set as output is the RS pin
    P6->SEL1 &= ~BIT0;
    P6->DIR |= BIT0;

    P4->SEL0 &= ~0xF0;  //setting pins 4.4,4.5,4.6,4.7 output
    P4->SEL1 &= ~0xF0;
    P4->DIR |= 0xF0;
    P4->OUT &= ~0xF0;   //set to low
}



void LCD_init(void)
{
    commandWrite(0x03);
    delay_ms(100);
    commandWrite(0x03);  //Reset Sequence from flowchart in lab handout
    delay_ms(200);
    commandWrite(0x03);
    delay_ms(100);

    commandWrite(0x02); //4 bit mode
    delay_micro(100);
    commandWrite(0x02);
    delay_micro(100);

    commandWrite(0x08);  //2 lines 5x7
    delay_micro(100);

    commandWrite(0x0F); //Display on, cursor ON, blinking
    delay_micro(100);

    commandWrite(0x01); //Clear display, move cursor to home
    delay_micro(100);

    commandWrite(0x06); //Increment cursor
    delay_micro(10);
}

void pushNibble (uint8_t nibble)
{
    P4OUT &= ~0xF0;  // clearing Data pins (P4.4-P4.7)
    P4OUT |= (nibble & 0x0F) << 4;
    PulseEnablePin();  //pulsing Enable so the LCD read new data
}

void pushByte (uint8_t byte)
{
    pushNibble((byte & 0xF0) >>4);
    pushNibble(byte & 0x0F);
    delay_ms(100);
}



void commandWrite(uint8_t command)
{
    P6->OUT &= ~BIT0;  //RS is set to 0
    pushByte(command);
}

void dataWrite(float data)
{
    P6->OUT |= BIT0;   //RS is set to 1
    pushByte(data);
}

void PulseEnablePin(void)
{
    P6->OUT |= BIT1; //E is set to high
    delay_micro(100); //delay for 10 microseconds
    P6->OUT &= ~BIT1; //E is set back to low
}



void delay_ms(unsigned ms)
{
    SysTick->LOAD = (ms*3000-1);
    SysTick->VAL = 34334;  //any write to CVR clears it
    SysTick->CTRL |= BIT0;
    while((SysTick->CTRL&BIT(16))==0);
}



void delay_micro(uint32_t microsecond)
{
    SysTick->LOAD = (microsecond*3-1);
    SysTick->VAL = 0;   //any write to CVR clears it
    SysTick->CTRL |= BIT0;
    while((SysTick->CTRL&BIT(16))==0);
}

void printString(char* string)
{
    int i;  //indexing value
    //this for loop will cycle through any sting entered
    // and print values to the screen.
    for(i = 0;i < strlen(string); i++)
    {
        dataWrite(string[i]);
    }
}

void gotoLine(uint8_t line) {
    if(line == 1) {
        commandWrite(0x80);     //set DDRAM address to first line
    } else if(line == 2) {
        commandWrite(0xC0);     //set DDRAM address to second line
    } else if(line == 3) {
        commandWrite(0x90);     //set DDRAM address to third line
    } else if(line == 4) {
        commandWrite(0xD0);     //set DDRAM address to forth line
    }
}



