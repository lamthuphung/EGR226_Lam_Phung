#include "stats_lib.h"
#include <math.h>

float maximum(float nums[], int n) {
    int i;
    float max = nums[0];
    for (i = 0; i < n; i++)
    {
        if (max < nums[i])
        {
            max = nums[i];
        }
    }
    return max;
}

float minimum (float nums[], int n)
{
    int i;
    float min = nums[0];
    for (i = 0; i < n; i++)
    {
        if (min > nums[i])
        {
            min = nums[i];
        }
    }
    return min;
}

float mean(float nums[], int n)
{
    int i;
    int total = 0;
    double mean;
    for (i = 0; i < n; i++)
    {
        total += nums[i];
    }
    mean = total / n;
    return mean;
}

float median(float nums[], int n)
{
    int i, j;
    int temp;
    int middle;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (nums[i] > nums[j])
            {
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }
    middle = n / 2;
    return nums[middle];
}

float variance(float nums[], int n)
{
    double total = 0;
    double average;
    double variance;
    average = mean(nums,n);

    for (int i = 0; i < n; i++)
    {
        total += pow(nums[i] - average,2);
    }
    return total/(n-1);
}

float standard_deviation(float nums[], int n)
{
    double var;
    var = variance(nums,n);
    return sqrt(var);
}


