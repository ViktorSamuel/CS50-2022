#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int size = 0;
    // load size
    do
    {
        size = get_int("Size: ");
    }
    while (size < 1 || size > 8);

    // draw triangel
    for (int i = 1; i <= size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (j + i < size)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}