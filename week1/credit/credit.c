#include <stdio.h>

int main(void)
{
    // define credit card number, sum and digit number tracker i
    long num, cNum;
    int i, sum = 0;

    // insert positive number
    do
    {
        printf("Number: ");
        scanf("%ld", &num);
    }
    while (num < 0);

    cNum = num;

    // check algoritm
    while (cNum != 0)
    {
        // odd digits
        if (i % 2 != 0)
        {
            int digit = (cNum % 10) * 2;
            if (digit >= 10)
            {
                while (digit != 0)
                {
                    sum += digit % 10;
                    digit /= 10;
                }
            }
            // even digits
            else
            {
                sum += digit;
            }
        }
        else
        {
            sum += cNum % 10;
        }

        cNum /= 10;
        i = i + 1;
    }
    // if card is valid
    if (sum % 10 == 0)
    {
        // visa
        if (i == 13 && num / 1000000000000 == 4)
        {
            printf("VISA\n");
        }
        else if (i == 15)
        {
            // amex
            if (num / 10000000000000 == 34 || num / 10000000000000 == 37)
            {
                printf("AMEX\n");
            }
            // inavlid
            else
            {
                printf("INVALID\n");
            }
        }
        else if (i == 16)
        {
            // MASTERCARD
            if (num / 100000000000000 >= 51 && num / 100000000000000 <= 55)
            {
                printf("MASTERCARD\n");
            }
            // visa
            else if (num / 1000000000000000 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}