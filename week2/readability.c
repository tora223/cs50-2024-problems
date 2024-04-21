#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int is_letter(char c);
int is_space(char c);
int is_end(char c);
void print_grade(int index);

int main(void)
{
    string text = get_string("Text: ");
    int letters = 0, words = 0, sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (is_letter(text[i]))
        {
            letters++;
        }
        else if (is_end(text[i]))
        {
            sentences++;
        }
        else if (is_space(text[i]))
        {
            words++;
        }
    }
    if (words > 0)
    {
        words++;
    }

    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);
    print_grade(index);
    return 0;
}

int is_letter(char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

int is_space(char c)
{
    return c == ' ';
}

int is_end(char c)
{
    return c == '!' || c == '?' || c == '.';
}

void print_grade(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
