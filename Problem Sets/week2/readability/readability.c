#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float Coleman_Liau(float L, float W, float S);

int main(void) 
{
    string input = get_string("Text: ");

    float L = count_letters(input);
    float W = count_words(input);
    float S = count_sentences(input);

    float index = Coleman_Liau(L, W, S);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letters(string text)
{
    int let = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            let += 1;
        }
    }

    return let;
}

int count_words(string text)
{
    int wor;

    if (strlen(text) > 0)
    {
        wor = 1;
    }
    else
    {
        wor = 0;
    }

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            wor += 1;
        }
    }

    return wor;
}

int count_sentences(string text)
{
    int sen = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sen += 1;
        }
    }

    return sen;
}

float Coleman_Liau(float L, float W, float S)
{
    float l = L / W * 100;
    float s = S / W * 100;
    float index = 0.0588 * l - 0.296 * s - 15.8;
    return index;
}