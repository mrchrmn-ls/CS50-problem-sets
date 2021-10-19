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

    while (number == 512)
    {
        number = fread(block, 1, 512, rawdata);
        printf("Number: %i\n", number);

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

        if (jpg != NULL && number == 512)
        {
            //printf("Writing %i, %i\n", counter-1, block[0]);
            fwrite(block, 1, 512, jpg);
        }

    }

    if (jpg != NULL)
    {
            //printf("Writing final block %i, %i\n", counter-1, block[0]);
            printf("Final: %i\n", number);
            fwrite(block, 1, number, jpg);
    }

    fclose(jpg);
    fclose(rawdata);

}