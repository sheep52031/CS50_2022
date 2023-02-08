#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Check for voter vote is who, and update the get of vote.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate winner;

    // Very important that you need to initialize when you create instance.
    // Otherwise,the instance content will random.
    winner.votes = 0;
    winner.name = " ";

    // Filter out the highest voter
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > winner.votes)
        {
            winner = candidates[i];
        }
    }

    // Double check those candidates has same votes for highest?
    // If true than print them (they are tie), if false just print a winner.
    for (int j = 0 ; j < candidate_count; j++)
    {
        if (candidates[j].votes == winner.votes)
        {
            printf("%s\n", candidates[j].name);
        }
    }
    return;
}

