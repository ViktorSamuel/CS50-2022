#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int digits_only(string s);

int main(int argc, string argv[])
{
    if (argc != 2 || digits_only(argv[1]) == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // take original text and make space for crypted
    string text = get_string("plaintext:  ");

    // convert string into num
    int key = atoi(argv[1]), d = 0;

    printf("ciphertext: ");

    // take every letter
    for (int i = 0; text[i] != '\0'; i++)
    {
        char letter = text[i];

        // check if is alphabet
        if (isalpha(letter))
        {
            if (islower(letter))
            {
                d = 96;
            }
            else
            {
                d = 64;
            }
            letter = (char)((int) letter + key - d) % 26 + d;
        }
        printf("%c", letter);
    }
    printf("\n");
}


int digits_only(string s) //const char *s
{
    int dig = 0;
    for (int i = 1; s[i] != '\0'; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            dig++;
        }

        if (dig == i){
            return 0;
        }
    }

//     while (*s)
//     {
//         if (isdigit(*s++) == 0)
//         {
//             return 0;
//         }
//     }

    return 1;
}