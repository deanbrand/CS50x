#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char letter, int key);

int main(int argc, string argv[]) 
{
    if (argc == 2 && only_digits(argv[1]))
    {
        int k = atoi(argv[1]) % 26;
        string plain = get_string("Plaintext:  ");
        printf("ciphertext: ");
        for (int i = 0, n = strlen(plain); i < n; i++)
        {
            printf("%c", rotate(plain[i], k));
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

bool only_digits(string s)
{
    if (strlen(s) == 1)
    {
        if (isdigit(s[0]))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (isdigit(s[0]) && isdigit(s[1]))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

char rotate(char letter, int key)
{
    int shift;
    if (islower(letter))
    {
        shift = 97;
        return (letter - shift + key) % 26 + shift;
    }
    else if (isupper(letter))
    {
        shift = 65;
        return (letter - shift + key) % 26 + shift;
    }
    else
    {
        return letter;
    }
}