#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


float colemanliau(float l, float w, float s);
void printgrade(float g);


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
        else if (text[i] == 32) // Space?
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?') // Punctuation
        {
            sentences++;
        }
    }

    float cl = colemanliau(letters, words, sentences);

    printf("Length: %i\n", length);
    printf("Letters: %i\n", letters);
    printf("Words: %i\n", words);
    printf("Sentences: %i\n", sentences);
    printf("Coleman-Liau: %f\n", cl);

    printgrade(cl);

}


float colemanliau(float l, float w, float s)
{
    float L = 100 * l / w;
    printf("L: %f    ---   ", L);
    float S = 100 * s / w;
    printf("S: %f\n", S);
    return 0.0588 * L - 0.296 * S - 15.8;
}

void printgrade(float g)
{
    if (g < 1)
    {
        printf("Before Grade 1\n");
    }
    else if ((int) round(g) >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(g));
    }
}