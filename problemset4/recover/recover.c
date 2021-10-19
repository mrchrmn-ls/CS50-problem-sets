#include <stdio.h>
#include <stdlib.h>

FILE *jpg;

int main(int argc, char *argv[])
{

    // Check for filename
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }


    // Open file and check whether it worked
    FILE *rawdata = fopen(argv[1], "r");
    if (rawdata == NULL)
    {
        printf("Something went wrong trying to open the file.\n");
        return 1;
    }


    // Initialize helpful variables
    int eof = 0;
    unsigned char block[512];
    int counter = 0;
    int number = 512;

    // Repeat for full blocks of 512 bytes
    while (number == 512)
    {

        // Get number of read items
        number = fread(block, 1, 512, rawdata);

        // Check first four bytes of block for JPG header
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            printf("Found %i!\n", counter + 1);
            // Check for first image
            if (counter == 0)
            {
                char filename[8];
                sprintf(filename, "%03i.jpg", counter);
                jpg = fopen(filename, "a");
                counter++;
            }
            else
            {
                fclose(jpg);
                char filename[8];
                sprintf(filename, "%03i.jpg", counter);
                jpg = fopen(filename, "a");
                counter++;
            }
        }

        // Write full block of 512 bytes but only if jpg is open
        if (jpg != NULL && number == 512)
        {
            fwrite(block, 1, 512, jpg);
        }

    }

    // Write remaining bytes if jpg is open
    if (jpg != NULL)
    {
        fwrite(block, 1, number, jpg);
    }

    fclose(jpg);
    fclose(rawdata);

}