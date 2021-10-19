#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


float colemanliau(float l, float w, float s); // Calculates the Coleman-Liau formula


int main(void)
{
    string text = get_string("Text: ");

    int length = strlen(text);
    int letters = 0;
    int words = 1;
    int sentences = 0;

    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]) != 0) // Alphabetical letter?
        {
            letters++;
        }
        else if (text[i] == 32) // Or space?
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?') // Or punctuation
        {
            sentences++;
        }
    }

    float cl = colemanliau(letters, words, sentences);

    if (cl < 1)
    {
        printf("Before Grade 1\n");
    }
    else if ((int) round(cl) >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(cl));
    }
}


float colemanliau(float l, float w, float s) // Calculates the Coleman-Liau formula and returns unrounded value
{
    float L = 100 * l / w;
    float S = 100 * s / w;
    return 0.0588 * L - 0.296 * S - 15.8;
}