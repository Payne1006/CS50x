/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;
#define MEMBLOCK 512

int main(int argc, char* argv[])
{
    // Verify correct execution of program
    if (argc != 1)
    {
        printf("Invalid Execution: ./recover\n");
        return 1;
    }
    
    // Open Memory card for analysis
    FILE* memcard = fopen("card.raw", "r");
    if (memcard == NULL)
    {
        printf("Memory allocation error \n");
        return 2;
    }
    
    // Create storage for 512 bytes of read memory
    BYTE buffer[MEMBLOCK]; 
    
     // Create outfile, set to NULL for safety
    FILE* jpeg; 
    jpeg = NULL;
    
    // Counter to assign number to outfile prefix
    int counter = 0;
    
    // Assign jpeg to file
    char filename[8];
    
    // Iterate through input looking for .jpg files
    while(fread(buffer, sizeof(MEMBLOCK), 1, memcard) == 1)
    {
        // Check for .jpg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // Close current file, if one exists
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }
            
            // Name file for writing
            sprintf(filename, "%03d.jpg", counter);
            
            // Open file for writing, update counter, write file
            jpeg = fopen(filename, "w");
            counter++;
            fwrite(&buffer, sizeof(MEMBLOCK), 1, jpeg);
        }
        // Data is part of .jpg, write data
        else if (counter != 0)
        {
            fwrite(buffer, sizeof(MEMBLOCK), 1, jpeg);
        }
        //  Data is not part of .jpg, read only
        else
        {
            fread(buffer, sizeof(MEMBLOCK), 1, memcard);
        }
    }
    
    // Clean up yo' mess
    fclose(jpeg);
    fclose(memcard);
    
    // Have a nice day
    return 0;
