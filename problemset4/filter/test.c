#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef uint8_t  BYTE;

int main(void)
{
    BYTE tmp[3] = {54, 67, 91};

    int sum = 0;

    int average = 0;

    for (int i = 0; i < 3; i++)
    {
        printf("tmp[%i] = %i\n", i, tmp[i]);
        sum = sum + tmp[i];
    }

    int check = -1554;

    printf("%i\n", tmp[check]);

    average = round((float) sum / 3);

    printf("Sum: %i -- Average: %i\n", sum, average);
}