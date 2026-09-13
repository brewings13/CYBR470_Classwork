#include <stdio.h> 

int main() 
{
    int currentDataSetSize = 0; 
    int monthlyGrowthRateEntered = 0; 
    float monthlyGrowthRateAsPercentage = 0.0;
    int numberOfMonths = 0; 
    float projectedSize = 0.0; 

    printf("Enter the current data set size in GiB: \n"); 
    scanf("%d", &currentDataSetSize); 
    printf("Enter the monthly growth rate as a percentage: \n"); 
    scanf("%d", &monthlyGrowthRateEntered); 
    monthlyGrowthRateAsPercentage = monthlyGrowthRateEntered / 100.0; 
    printf("Enter the number of months: \n"); 
    scanf("%d", &numberOfMonths);

    projectedSize = currentDataSetSize * ( 1 + (monthlyGrowthRateAsPercentage * numberOfMonths)); 

    printf("Projected size: %.2f GiB\n", projectedSize);

    return 0; 
}