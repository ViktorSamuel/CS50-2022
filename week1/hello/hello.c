#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char name[100];
    printf("What's your name? ");
    fgets(name, sizeof(name), stdin);
    printf("hello, %s\n", name);
    return 0;
}
