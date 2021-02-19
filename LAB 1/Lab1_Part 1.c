/**************************************************************************************
* Author: Lam Thu Phung
* Course: EGR 226 - 905
* Date: 01/22/2021
* Project: LAB 1
* File: LAB 1 - Part 1
* Description: Resistor Analysis Tool
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

void prompt(void);
void calcResistorColors(int val);
int check_tool(char input_check);

int main()
{
    int val;
    char input[20];
    int check;
    do
    {
        prompt();
        printf("\nEnter the value of the resistor: ");
        scanf("%s", input);
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
    } while (check == 1);
}

int check_tool(char input_check)
{
    int a;
    if ((input_check >= 'a' && input_check <= 'z') || (input_check >= 'A' && input_check <= 'Z'))
    {
        a = 0;
    }
    else a = 1;
    return a;
}

void prompt(void)
{
 printf("---------------Resistor Codes---------------\n");
 printf("|Character| Color  | Band 1 & 2 | Band 3     |\n");
 printf("| K       | Black  |     0      |*1          |\n");
 printf("| N       | Brown  |     1      |*10         |\n");
 printf("| R       | Red    |     2      |*100        |\n");
 printf("| O       | Orange |     3      |*1,000      |\n");
 printf("| Y       | Yellow |     4      |*10,000     |\n");
 printf("| G       | Green  |     5      |*100,000    |\n");
 printf("| B       | Blue   |     6      |*1,000,000  |\n");
 printf("| V       | Violet |     7      |*10,000,000 |\n");
 printf("| E       | Grey   |     8      |            |\n");
 printf("| W       | White  |     9      |            |\n");
 printf("| D       | Gold   |            |            |\n");
 printf("| S       | Silver |            |            |\n");
 printf("---------------------------------------------\n\n");
}

void calcResistorColors(int val)
{
    int band1 = 0, band2 = 0, band3 = 0;
    int count = 0;
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
