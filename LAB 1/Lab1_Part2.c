#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stats_lib.h"
#define MAX 150

float ReadData(float nums[]);
float maximum(float nums[], int n);

void main(void)
{
    float NUMS[MAX];
    int size = 0;
    int i;
    size = ReadData(NUMS);

    printf("The data:\n");
    for (i = 0; i < size; i++)
    {
        printf("%g \n", NUMS[i]);
    }
    printf("Maximum: %g\n", maximum(NUMS,size));
    printf("Minimum: %g\n", minimum(NUMS,size));
    printf("Mean: %g\n", mean(NUMS,size));
    printf("Median: %g\n", median(NUMS,size));
    printf("Variance: %g\n", variance(NUMS,size));
    printf("standard deviation: %g\n", standard_deviation(NUMS,size));
    return 0;
}

float ReadData(float nums[])
{
    FILE *fp;
    int j = 0;
    int status = 0;

    fp = fopen("data.txt","r");
    if (fp == NULL)
    {
        printf("The file does not exist");
        exit(-1);
    }
    for (j = 0; status != EOF; j++)
    {
        status = fscanf(fp, "%f", &nums[j]);
    }
    fclose(fp);
    return (j-1);
}

