#include <stdio.h>
#include <stdlib.h>


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
    FILE *jpg;

    while (eof == 0)
    {
        // Read block of 512 bytes and simultaeously check for EOF
        if (fread(block, 1, 512, rawdata) < 512)
        {
            printf("This is the end.\n");
            eof = 1;
        }

        // Check beginning of block for JPG header
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            printf("Found %i!\n", counter);
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

        // fwrite(block, 1, 512, jpg);

        if (eof == 1)
        {
            fclose(jpg);
        }

    }

    fclose(rawdata);

}