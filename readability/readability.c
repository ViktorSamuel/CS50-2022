#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
// #include <string.h>

int main(void)
{
    // text
    string text = get_string("Text ");

    // num of:
    int sentences = 0, words = 1, letters = 0, grade = 0;

    // take every one letter
    for (int i = 0; text[i] != '\0'; i++)
    {
        // count number of sentences
        if (text[i + 1] == ' ' || text[i + 1] == '\0')
        {
            switch (text[i])
            {
                case '.':
                    sentences++;
                    break;
                case '?':
                    sentences++;
                    break;
                case '!':
                    sentences++;
                    break;
                default:
                    break;
            }
        }

        // count number of words
        if (text[i] == ' ' && text[i - 1] != ' ')
        {
            words++;
        }

        // count number of letters
        if (isalnum(text[i]))
        {
            letters++;
        }
    }

    // formula to count grade
    grade = round(0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8);

    // cases of result
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Before Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}