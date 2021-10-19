#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

// Check if key present and nothing else?

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }


// Check key length equals 26

    int key_length = strlen(argv[1]);

    if (key_length != 26)
    {
        printf("Key must be 26 letters, no more, no less.\n");
        return 1;
    }


// Check for letters only

    for (int i = 0; i < 26; i++)
    {
        if (!((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z')))
        {
            printf("Key must be alphabetical letters only and is not case-sensitive.\n");
            return 2;
        }
    }


// Check for complete alphabet and create upper case key

    char check[26] = {0}; // Important to assign all 26 values, otherwise non-zero value might appear in array.

    for (int i = 0; i < 26; i++)
    {
        int p = toupper(argv[1][i]) - 65;
        if (check[p] == 0)
        {
            check[p] = 1;
        }
        else
        {
            printf("Key must contain each letter of the alphabet only once.\n");
            return 3;
        }
    }


// Read message and encrypt

    string plain = get_string("plaintext: ");
    int msg_length = strlen(plain);
    char cipher[msg_length];

    for (int i = 0; i < msg_length; i++)
    {
        if (!((plain[i] >= 'a' && plain[i] <= 'z') || (plain[i] >= 'A' && plain[i] <= 'Z')))
        {
            cipher[i] = plain[i];
        }
        else if (plain[i] >= 'A' && plain[i] <= 'Z')
        {
            cipher[i] = toupper(argv[1][plain[i] - 65]);
        }
        else
        {
            cipher[i] = tolower(argv[1][plain[i] - 97]);
        }
    }


// Print ciphertext

    printf("ciphertext: ");
    for (int i = 0; i < msg_length; i++)
    {
        printf("%c", cipher[i]);
    }
    printf("\n");


}

