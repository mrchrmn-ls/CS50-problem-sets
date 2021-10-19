#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
bool loop;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_for_loop(int target, int origin);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}



// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int i=0;

    // Find candidate matching name and if found update voter's ranks array with candidate's index.
    while (i < candidate_count)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
        i++;
    }

    return false;
}



// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Go from first rank to second to last rank
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // Go from following rank to last rank
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Update preferences with rank entries at specific counts
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}



// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    // Compare each candidate ...
    for (int i = 0; i < candidate_count; i++)
    {
        // ... with all other candidates that haven't been compared with candidate i
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences [j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}



// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int pair_strength[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        pair_strength[i] = preferences[pairs[i].winner][pairs[i].loser];
    }

    int swap_count = -1;
    int temp;

    while (swap_count != 0)
    {
        swap_count = 0;

        for (int i = 0; i < pair_count - 1; i++)
        {
            if (pair_strength[i] < pair_strength[i + 1])
            {
                // Swap strength array elements
                temp = pair_strength[i];
                pair_strength[i] = pair_strength[i + 1];
                pair_strength[i + 1] = temp;

                // Swap pairs array elements
                temp = pairs[i].winner;
                pairs[i].winner = pairs[i + 1].winner;
                pairs[i + 1].winner = temp;

                temp = pairs[i].loser;
                pairs[i].loser = pairs[i + 1].loser;
                pairs[i + 1].loser = temp;

                swap_count++;
            }
        }
    }

    /* HELPER - print pair strengths again, hopefully sorted */
    for (int i = 0; i < pair_count; i++)
    {
        printf("Pair %i (%s over %s) strength: %i\n", i, candidates[pairs[i].winner], candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser]);
    }

    return;
}



// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{


    // Go through all pairs in decending order of strength to lock edges
    for (int i = 0; i < pair_count; i++)
    {
        loop = false;

        if (check_for_loop(pairs[i].loser, pairs[i].winner) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    // HELPER - print lock matrix
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i  ", locked[i][j]);
        }
        printf("\n");
    }

    return;
}



// Check for a loop from loser to winner, backtracking via recursion
bool check_for_loop(int from, int winner)
{

    for (int i = 0; i < candidate_count; i++)
    {
        if (loop == false && locked[i][winner] == true && i != from)
        {
            check_for_loop(i, winner);
        }
        else if (loop == false && locked[i][winner] == true && i == from)
        {
            loop = true;
        }
    }

    if (loop == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}



// Print the winner of the election
void print_winner(void)
{

    // This is the the sum of arrows pointing at each candidate
    int candidate_arrows[candidate_count];

    // Populate candidate_edges
    for (int i = 0; i < candidate_count; i++)
    {
        candidate_arrows[i] = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            candidate_arrows[i] = candidate_arrows[i] + locked[j][i];
        }
    }

    // Find and print candidates with least edges
    int winner = 0;

    for (int i = 1; i < candidate_count; i++)
    {
        if (candidate_arrows[i] < candidate_arrows[winner])
        {
            winner = i;
        }
    }

    printf("%s\n", candidates[winner]);

    return;
}

