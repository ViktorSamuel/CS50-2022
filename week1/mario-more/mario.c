#include <stdio.h>

int main(void)
{
    // define and load positive size from 1 to 8
    int size = 0;
    do
    {
        printf("Size: ");
        scanf("%d", &size);
    }
    while (size < 1 || size > 8);

    // draw the triangel
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

        printf("  ");

        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}