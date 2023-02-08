#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};


int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

// Compute and return score for string
int compute_score(string word)
{

    int j = 0;
    int k = 0;
    int score[30];
    int total = 0;

    // Initialization array score[]
    for (int i = 0; i < 30 ; i++)
    {
        score[i] = 0;
    }

    // Distinguish lower or upper and found the points
    while (word[j] != '\0')
    {
        if (islower(word[j]))
        {
            score[j] = POINTS[(int) word[j] - 97];
        }
        else if (isupper(word[j]))
        {
            score[j] = POINTS[(int) word[j] - 65];
        }
        else
        {
            score[j] = 0;
        }
        j++;
    }

    // Calculate all points
    while (score[k] != '\0')
    {
        total += score[k];
        k++;
    }

    return total;
}
