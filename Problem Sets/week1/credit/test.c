#include <stdio.h>

int main(void)
{
    long num = 4003600000000014;
    long num10 = num * 10;
    long den = 100;
    long res = num10;

    int dub = 0;
    int sing = 0;

    while (res >= 10)
    {
        res /= den;

        if (2 * (res % 10) >= 10)
        {
            dub += 2 * (res % 10) / 10 % 10;
            dub += 2 * (res % 10) % 10;
        }
        else if (2 * (res % 10) != 0)
        {
            dub += 2 * (res % 10);
        }

        printf("%li\n", res % 10);
    }

    res = num;
    printf("\n");

    while (res >= 1)
    {
        printf("%li\n", res % 10);
        sing += res % 10;
        res /= den;
    }

    printf("\n%i\n", sing);
    printf("\n%i\n", dub);
    printf("\n%i\n", sing + dub);

}