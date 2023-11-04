#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string s = get_string("Text: ");
    int numLetters = count_letters(s);
    int numWords = count_words(s);
    int numSentences = count_sentences(s);

    float L = (float) numLetters / numWords * 100.0;
    float S = (float) numSentences / numWords * 100.0;

    float res = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(res);
    if (res >= 16)
        printf("Grade 16+\n");
    else if (res < 1)
        printf("Before Grade 1\n");
    else
        printf("Grade %i\n", index);
}

int count_letters(string text)
{
    int i = 0;
    int count = 0;
    while (text[i] != '\0')
    {
        if (islower(text[i]) || isupper(text[i]))
            count++;
        i++;
    }
    return count;
}

int count_words(string text)
{
    int i = 0;
    int count = 0;
    while (text[i] != '\0')
    {
        if (text[i] == ' ')
            count++;
        i++;
    }
    count++;
    return count;
}

int count_sentences(string text)
{
    int i = 0;
    int count = 0;
    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
            count++;
        i++;
    }
    return count;
}