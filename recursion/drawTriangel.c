#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void)
{
    draw(4);
}

void draw(int n){
    //base case
    if (n <= 0)
        return;

    // recursive case
    draw(n - 1);

    for (int i = 0; i < n; i++)
        printf("#");

     printf("\n");
}