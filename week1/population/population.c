#include <stdio.h>

// prompt for user input until value is not bigger than min 
int get_int_input(char *s, int min)
{
    int n = 0;
    do
    {
        printf("%s: ", s);
        scanf("%d", &n);
    }
    while (n < min);
}

int main(void)
{
    // Prompt for start size
    int startSize = get_int_input("Start size: ", 9);
    // Prompt for end size
    int endSize = get_int_input("End size: ", startSize);
    // Calculate number of years until we reach threshold
    int years = 0;
    while (startSize < endSize)
    {
        years++;
        startSize = startSize + startSize / 3 - startSize / 4;
    }
    // Print number of years
    printf("Years: %i\n", years);

    return 0;
}