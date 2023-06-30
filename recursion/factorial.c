#include <cs50.h>
#include <stdio.h>


int fact(int n);

int main(void)
{
    printf("%d\n", fact(4));
}

int fact(int n){
    //base case
    if (n == 1)
        return 1;
   // recursive case
    else
        return n * fact(n-1);
}