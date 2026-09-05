#include <stdio.h>

void print_network_indicators(void)
{
    printf("IP address, domain name"); 
}

void print_host_indicators(void)
{
    printf("file hash, registry key");
}

int main()
{
    print_host_indicators();
    printf("\n");
    print_network_indicators();
    printf("\n"); 
    print_network_indicators();
    printf(", "); 
    print_host_indicators();
    printf("\n");
}