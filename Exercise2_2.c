
#include <stdio.h>

int read_record_number()
{
    int record_number; 
    printf("Enter the number of records:\n");
    scanf("%d", &record_number);
    return record_number;
}

int read_record_size()
{
    int record_size; 
    printf("Enter the size of one record in bytes:\n");
    scanf("%d", &record_size);
    return record_size; 
}

int calculate_total_bytes_required(int number_of_records, int record_size)
{
   int total_bytes_required = number_of_records * record_size; 
   return total_bytes_required; 
}

int main() 
{
    int number_of_records = read_record_number();
    if (number_of_records <= 0)
    {
        printf("Error: invalid input.\n");
        return 1; 
    }
    int size_of_single_record = read_record_size();
    if (size_of_single_record <= 0) 
    {
        printf("Error: invalid input.\n");
        return 1; 
    }
    int total_buffer_storage_required = calculate_total_bytes_required(number_of_records, size_of_single_record); 
    printf("Total bytes required: %d\n", total_buffer_storage_required);
    return 0; 
}