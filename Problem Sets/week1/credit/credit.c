#include <cs50.h>
#include <stdio.h>

string check_visa(long card);
int checksum(long card);

int main(void) 
{
    long card = get_long("Card number: ");
    int n = 2;
    printf("%s", check_visa(card));
}

string check_visa(long card)
{
    if (card / 1000000000000000 % 10 != 0 && card / 10000000000000000 % 10 == 0)
    {
        if (card / 1000000000000000 % 10 == 4 && checksum(card) == 0)
        {
            return "VISA\n";
        }
        else if (card / 1000000000000000 % 10 == 5 && card / 100000000000000 % 10 > 0 && card / 100000000000000 % 10 <= 5
                 && checksum(card) == 0)
        {
            return "MASTERCARD\n";
        }
        else
        {
            return "INVALID\n";
        }
    }
    else if (card / 1000000000000 % 10 != 0 && card / 10000000000000 % 10 == 0)
    {
        if (card / 1000000000000 % 10 == 4 && checksum(card) == 0)
        {
            return "VISA\n";
        }
        else
        {
            return "INVALID\n";
        }
    }
    else if (card / 100000000000000 % 10 != 0 && card / 1000000000000000 % 10 == 0)
    {
        if (card / 100000000000000 % 10 == 3 && card / 10000000000000 % 10 == 4 ||  card / 10000000000000 % 10 == 7 && checksum(card) == 0)
        {
            return "AMEX\n";
        }
        else
        {
            return "INVALID\n";
        }
    }
    else
    {
        return "INVALID\n";
    }
}

int checksum(long num)
{
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
    }

    res = num;

    while (res >= 1)
    {
        sing += res % 10;
        res /= den;
    }

    return (sing + dub) % 10;
}