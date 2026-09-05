#include <stdio.h>

int read_byte_total()
{
    float total_bytes; 
    printf("Enter a size in bytes:");
    scanf("%f", &total_bytes);
    return total_bytes; 
}

int compute_kibibyte_total()
{
    float kibibyte_total = read_byte_total() / 1024; 
    return kibibyte_total; 
}

int compute_mibibyte_total()
{
    float initial_mibibyte_total = compute_kibibyte_total() / 1024; 
    return initial_mibibyte_total; 
}

int compute_kibibyte_remainder()
{
    float kibibyte_multiplier = compute_mibibyte_total() - floor(compute_mibibyte_total); 
    float kibibyte_remainder = kibibyte_multiplier * 102.4; 
    return kibibyte_remainder;
}

int main()
{



}