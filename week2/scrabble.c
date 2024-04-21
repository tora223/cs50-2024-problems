#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int scores[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 4, 10};

int get_score(string word);

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = get_score(word1);
    int score2 = get_score(word2);

    if (score1 > score2) {
        printf("Player 1 wins!\n");
    } else if (score1 < score2) {
        printf("Player 2 wins!\n");
    } else {
        printf("Tie!\n");
    }
    return 0;
}

int get_score(string word)
{
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char letter = tolower(word[i]);

        if ('a' <= letter && letter <= 'z') {
            score += scores[tolower(word[i]) - 'a'];
        }   
    }
    return score;
}