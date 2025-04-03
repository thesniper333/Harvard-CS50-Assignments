#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();


        for (int i = 0; i < candidate_count; i++)
        {
            printf("%s  %i\n", candidates[i].name, candidates[i].votes);
        }
        // Check if election has been won
        bool won = print_winner();



        if (won)
        {
            printf("%s\n", candidates[candidate_count - 1].name);

            break;
        }


        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;

}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int counter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {

            preferences[voter][rank] = i;
            counter += 1;
            break;
        }
    }
    if (counter == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated != false)
            {
            }
            else
            {
                candidates[preferences[i][j]].votes += 1;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int j = 0;
    int temp_vote;
    string temp_candidate;
    bool temp_bool;

    while (j < (candidate_count - 1))
    {
        for (int i = 0; i < candidate_count - 1; i++)
        {
            temp_vote = candidates[i].votes;
            temp_candidate = candidates[i].name;
            temp_bool = candidates[i].eliminated;
            if (candidates[i].votes >= candidates[i + 1].votes)
            {

                candidates[i].votes = candidates[i + 1].votes;
                candidates[i].name = candidates[i + 1].name;
                candidates[i].eliminated = candidates[i + 1].eliminated;
                candidates[i + 1].votes = temp_vote;
                candidates[i + 1].name = temp_candidate;
                candidates[i + 1].eliminated = temp_bool;
            }
        }
        j++;
    }
    if (candidates[candidate_count - 1].votes > (0.5 * voter_count))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int i = 0;
    for (i; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            break;
        }
    }
    return candidates[i].votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int counter = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes != min)
            {
                counter += 1;
            }
        }
    }
    if (counter == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
                candidates[i].votes = 0;
            }
            else
            {
                return;
            }
        }
    }
}
