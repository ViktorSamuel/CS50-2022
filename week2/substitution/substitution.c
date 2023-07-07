#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int testIn(int a, string s);

int main(int argc, string argv[])
{
    // input test
    if (testIn(argc, argv[1]))
    {
        return 1;
    }

    // plaintext
    string text = get_string("plaintext:  ");

    // ciphertext
    printf("ciphertext: ");

    // take every letter of plaintext
    for (int i = 0; text[i] != '\0'; i++)
    {
        char letter = text[i];

        // if is aplphabetical
        if (isalpha(letter))
        {
            // case-insensitive
            if (islower(letter))
            {
                // print ciphertext
                printf("%c", tolower(argv[1][(int) letter - 97]));
            }
            else
            {
                // print ciphertext
                printf("%c", toupper(argv[1][(int) letter - 65]));
            }
        }
        // is not aplhabetical
        else
        {
            printf("%c", letter);
        }

    }
    printf("\n");
}

// test input finction
int testIn(int a, string s)
{
    // just 1 argument
    if (a != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int letter = 0, j = 0;

    // take every letter of key
    for (int i = 0; s[i] != '\0'; i++)
    {
        // is alpha
        if (isalpha(s[i]))
        {
            // check if is only one time
            for (int n = 0; '\0' != s[n]; n++)
            {
                if (tolower(s[n]) == tolower(s[i]))
                {
                    letter++;
                }
            }
        }
        j++;
    }

    // key contain 26 letters
    if (letter == 26 && j == 26)
    {
        return 0;
    }
    // invalid key
    else
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
}