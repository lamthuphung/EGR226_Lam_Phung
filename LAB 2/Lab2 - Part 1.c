/**************************************************************************************
* Author: Lam Thu Phung
* Course: EGR 226 - 905
* Date: 02/05/2021
* Project: LAB 2
* File: LAB 2 - Part 1
* Description: Resistor Analysis Tool part 2
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

void prompt(void);  //Output the table information of resistors
void calcResistorColors(int val);   //This function takes the resistance of a certain resistor and output the color-code band relate to it
int check_tool(char input_check);   //This function was used to check the validity of inputs
void getColorBands(char*, char*, char*, char*); //This function was used to collect user input of 4 characters
void calcResistance(char, char, char, char);    //This function was used to calculate the resistance of 4 input color-codes

int main()
{
    int val;    //this variable was used to check the validity of resistance
    int value;  //this variable was the digit converted from character variable "option" and used to check whether the option was 1 or 2
    char option[20];    //this variable was used to check whether user want to convert resistance to color-code or color-code to resistance
    char input[20];     //The variable that stores the resistance input
    char band1,band2,band3,band4;   //declare user input for color-code band
    int check;  //This variable was used to check whether user want to do another conversion or not
    do
    {
        prompt();   //prompt the table
        printf("Choose which resistor function you would like to perform:\n");
        printf("\t(1): Determine color-code for given resistance value\n");
        printf("\t(2): Determine resistance value from given color-code\n");
        printf("Enter a value between 1 and 2:\n");
        scanf("%c", option);
        check = check_tool(option);

        //check whether user want to do another conversion or not
        if (check == 1)
        {
            value = atoi(option);   //convert character to integer
            //check whether the option was 1 or 2
            if (value == 1)
            {
                printf("\nEnter the value of the resistor: ");
                scanf("%s", input);
                //Call check_tool function to check the validity of inputs
                check = check_tool(input);
                if (check == 1)
                {
                    val = atoi(input);
                    if (val > 0 && val < 99000000)
                    {
                        calcResistorColors(val);
                        printf("Would you like to try another resistor?\n");
                        printf("Press 1 to continue\n");
                        printf("Press 0 to exit\n");
                        scanf("%d", &check);
                    }
                    else
                    {
                        printf("Invalid value - Make sure you enter a value from 1 - 99000000 - Let's try again \n");
                        check = 1;
                    }
                }
                else if (check == 0)
                {
                    printf("Invalid value - Make sure you enter a value from 1 - 99000000 - Let's try again \n");
                    check = 1;
                }
            }
            else if (value == 2)
            {
                getColorBands(&band1, &band2, &band3,&band4);
                printf("You entered the following color-code character: %c %c %c %c\n", band1, band2, band3, band4);
                calcResistance(band1, band2, band3, band4);
                printf("Would you like to try another resistor?\n");
                        printf("Press 1 to continue\n");
                        printf("Press 0 to exit\n");
                        scanf("%d", &check);
            }
        else
        {
            printf("\n\n\nERROR: Invalid input. Please make sure you enter a value 1 or 2 \n");
            check == 1;
        }
    }
    } while (check == 1); //Check == 1 allows user to do another conversion
}

int check_tool(char input_check)    //This function was used to check the validity of inputs
{
    int a;
    if ((input_check >= 'a' && input_check <= 'z') || (input_check >= 'A' && input_check <= 'Z'))
    {
        a = 0;
    }
    else a = 1;
    return a;
}

void prompt(void)   //Output the table information of resistors
{
 printf("--------------------Resistor Codes---------------------\n");
 printf("|Character | Color     | Band 1 & 2    | Band 3    | Band 4        |\n");
 printf("| K        | Black     | 0             |*1         | +/- 1%%        |\n");
 printf("| N        | Brown     | 1             |*10        | +/- 2%%        |\n");
 printf("| R        | Red       | 2             |*100       |               |\n");
 printf("| O        | Orange    | 3             |*1,000     |               |\n");
 printf("| Y        | Yellow    | 4             |*10,000    |               |\n");
 printf("| G        | Green     | 5             |*100,000   | +/- 0.5%%      |\n");
 printf("| B        | Blue      | 6             |*1,000,000 | +/- 0.25%%     |\n");
 printf("| V        | Violet    | 7             |*10,000,000| +/- 0.1%%      |\n");
 printf("| E        | Grey      | 8             |           | +/- 0.05%%     |\n");
 printf("| W        | White     | 9             |           |               |\n");
 printf("| D        | Gold      |               |*0.1       | +/- 5%%        |\n");
 printf("| S        | Silver    |               |*0.01      | +/- 10%%       |\n");
 printf("-------------------------------------------------------\n\n");
}

void calcResistorColors(int val)    //This function takes the resistance of a certain resistor and output the color-code band relate to it
{
    int band1 = 0, band2 = 0, band3 = 0;
    int count = 0;

    //Method of convert the resistance to color-code band
    while(val % 10 == 0 && val > 99)
    {
        count = count + 1;
        val /= 10;
    }
    printf("%d\n",count);
    int s1,s2,s3;
    char bandColor[][20] = {"Black", "Brown", "Red", "Orange", "Yellow", "Green", "Blue", "Violet", "Grey", "White", "Gold", "Silver"};
    s1 = log10(val);
    s2 = pow(10, s1);
    s3 = pow(10, s1 - 1);
    band1 = val / s2;
    band2 = (val / s3) - band1 * 10;
    printf("%d %d\n",band1,band2);
    printf("%s-%s-%s", bandColor[band1], bandColor[band2], bandColor[count]);
    printf(" indicate to %d-%d-%g\n", band1, band2, pow(10,count));
}

void getColorBands(char *band1, char *band2, char *band3, char *band4)  //This function was used to collect user input of 4 characters
{
    printf("Enter the color-code character for band-1, band-2, band-3, band-4 respectively: \n");
    scanf(" %c%c%c%c", band1, band2, band3, band4);
}


void calcResistance(char band1, char band2, char band3, char band4)     //This function was used to calculate the resistance of 4 input color-codes
{
    int b1, b2, b3, b4, resistance; //b# is the number of #th band that related to the user input character

    switch (band1)
    {
    case 'K':
        b1 = 0;
        break;

    case 'N':
        b1 = 1;
        break;

    case 'R':
        b1 = 2;
        break;

    case 'O':
        b1 = 3;
        break;

    case 'Y':
        b1 = 4;
        break;

    case 'G':
        b1 = 5;
        break;

    case 'B':
        b1 = 6;
        break;

    case 'V':
        b1 = 7;
        break;

    case 'E':
        b1 = 8;
        break;

    case 'W':
        b1 = 9;
        break;

    case 'D':
        b1 = 0;
        break;

    case 'S':
        b1 = 0;
        break;
    }

    switch(band2)
    {
    case 'K':
        b2 = 0;
        break;

    case 'N':
        b2 = 1;
        break;

    case 'R':
        b2 = 2;
        break;

    case 'O':
        b2 = 3;
        break;

    case 'Y':
        b2 = 4;
        break;

    case 'G':
        b2 = 5;
        break;

    case 'B':
        b2 = 6;
        break;

    case 'V':
        b2 = 7;
        break;

    case 'E':
        b2 = 8;
        break;

    case 'W':
        b2 = 9;
        break;

    case 'D':
        b2 = 0;
        break;

    case 'S':
        b2 = 0;
        break;
    }


    switch(band3)
    {
    case 'K':
        b3 = 1;
        break;

    case 'N':
        b3 = 10;
        break;

    case 'R':
        b3 = 100;
        break;

    case 'O':
        b3 = 1000;
        break;

    case 'Y':
        b3 = 10000;
        break;

    case 'G':
        b3 = 100000;
        break;

    case 'B':
        b3 = 1000000;
        break;

    case 'V':
        b3 = 10000000;
        break;

    case 'D':
        b3 = 0.1;
        break;

    case 'S':
        b3 = 0.01;
        break;
    }

    resistance = ((b1 * 10) + b2) * b3; //Resistance calculation
    switch(band4){// determines character entered for fourth color band
        case 'K':
            printf("This resistor is [%d]Ohms with a +/- 1%% tolerance\n\n", resistance);
            break;
        case 'N':
            printf("This resistor is [%d]Ohms with a +/- 2%% tolerance\n\n", resistance);
            break;
        case 'G':
            printf("This resistor is [%d]Ohms with a +/- 0.5%% tolerance\n\n", resistance);
            break;
        case 'B':
            printf("This resistor is [%d]Ohms with a +/- 0.25%% tolerance\n\n", resistance);
            break;
        case 'V':
            printf("This resistor is [%d]Ohms with a +/- 0.1%% tolerance\n\n", resistance);
            break;
        case 'E':
            printf("This resistor is [%d]Ohms with a +/- 0.05%% tolerance\n\n", resistance);
            break;
        case 'D':
            printf("This resistor is [%d]Ohms with a +/- 5%% tolerance\n\n", resistance);
            break;
        case 'S':
            printf("This resistor is [%d]Ohms with a +/- 10%% tolerance\n\n", resistance);
            break;
    }

}
