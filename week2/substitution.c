#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int is_invalidkey(string key);
char encrypt(char c, string key);

const int ALPHA_NUM = 26;

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    if (is_invalidkey(key))
    {
        return 1;
    }
    for (int i = 0; i < ALPHA_NUM; i++)
    {
        key[i] = tolower(key[i]);
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            printf("%c", encrypt(plaintext[i], key));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}

int is_invalidkey(string key)
{
    if (strlen(key) != ALPHA_NUM)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }

    int alpha_counts[ALPHA_NUM];
    for (int i = 0; i < ALPHA_NUM; i++)
    {
        alpha_counts[i] = 0;
    }
    for (int i = 0; i < ALPHA_NUM; i++)
    {
        if (isalpha(key[i]))
        {
            alpha_counts[tolower(key[i]) - 'a']++;
        }
        else
        {
            printf("key must only contain alphabetic characters\n");
            return 1;
        }
    }
    for (int i = 0; i < ALPHA_NUM; i++)
    {
        if (alpha_counts[i] != 1)
        {
            printf("key must not contain repeated characters\n");
            return 1;
        }
    }
    return 0;
}

char encrypt(char c, string key)
{
    if (islower(c))
    {
        return key[c - 'a'];
    }
    else
    {
        return toupper(key[c - 'A']);
    }
}
