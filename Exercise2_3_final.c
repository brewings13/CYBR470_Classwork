#include <stdio.h>

int read_byte_total(float* total_bytes)
{
    printf("Enter a size in bytes:");
    return scanf("%f", total_bytes);
}

int main()
{
    float total_bytes; 
    if (read_byte_total(&total_bytes) != 1 || total_bytes < 0)
    {
        printf("Error: size must be a non-negative number.\n");
        return 1;
    }
    float kibibytes = total_bytes / 1024; 
    int mebibytes = kibibytes / 1024;
    float remaining_kibibytes = kibibytes - (mebibytes * 1024);   
    printf("%.1f bytes = %d MiB, %.1f KiB\n", total_bytes, mebibytes, remaining_kibibytes);
    return 0; 
}
