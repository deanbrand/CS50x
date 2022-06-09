#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool full(string key);
string replace(string plain, string key);

string ab = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, string argv[])
{
    if (argc == 2 && full(argv[1]))
    {
        if (strlen(argv[1]) == 26)
        {
            string plain = get_string("plaintext:  ");
            printf("ciphertext: %s\n", replace(plain, argv[1]));
            return 0;
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Invalid key.\n");
        return 1;
    }
}

bool full(string key)
{
    // Assuming the key is 26 letters, as verified in main, we want to confirm that each letter is used exactly once.
    int count = 0, high = 0;
    // string ab = "";
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        count = 0;
        for (int j = 0; j < n; j++)
        {
            if (isupper(key[j]) || islower(key[j]))
            {
                char c = tolower(key[j]);
                if (c == ab[i])
                {
                    count++;
                    if (count > high)
                    {
                        high = count;
                    }
                }
            }
            else
            {
                return false;
            }
        }
    }
    if (high > 0 && high < 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string replace(string plain, string key)
{
    // Assuming the key is valid, this function goes through every character and replaces it by the appropriate cipher.
    string cipher = plain;
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (tolower(plain[i]) == ab[j])
            {
                if (islower(cipher[i]))
                {
                    cipher[i] = tolower(key[j]);
                    break;
                }
                else
                {
                    cipher[i] = toupper(key[j]);
                    break;
                }
                // cipher[i] = key[j];
            }
        }
    }

    return cipher;
}