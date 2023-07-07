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

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
//bool make_cycle(int winner, loser);
bool makes_circle(int cycle_start, int loser);

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
    // Check is name exist
    for (int z = 0; z < candidate_count; z++)
    {
        if (!strcmp(candidates[z], name))
        {
            // for each voter store his vote
            ranks[rank] = z;
            return true;
        }
    }
    // invalid vote
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    // TODO
    for (int z = 0; z < candidate_count - 1; z++)
    {
        for (int i = 1 + z; i < candidate_count; i++)
        {
            preferences[ranks[z]][ranks[i]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int z = 0; z < candidate_count; z++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (preferences[z][i] < preferences[i][z])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = z;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int stength = 0, start = 0, j = 0, i = 0;
    pair low;

    while (start < pair_count)
    {
        for (int z = 0; z < candidate_count; z++)
        {
            for (int n = 0; n < candidate_count; n++)
            {
                if (stength < preferences[z][n])
                {
                    stength = preferences[z][n];
                    i = z;
                    j = n;
                }
            }
        }

        if (stength == 0)
        {
            return;
        }

        for (int z = start; z < pair_count; z++)
        {
            if (pairs[z].winner == i && pairs[z].loser == j)
            {
                low = pairs[start];
                if (low.winner != pairs[z].winner || low.loser != pairs[z].loser)
                {
                    pairs[start] = pairs[z];
                    pairs[z] = low;
                    start++;
                    preferences[i][j] = 0;
                    stength = 0;
                }
                else
                {
                    start++;
                    preferences[i][j] = 0;
                    stength = 0;
                }
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!makes_circle(pairs[i].winner, pairs[i].loser))
        {
            // Lock the pair unless it makes a circle
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{


    int num = 0;
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                for (int z = 0; z < candidate_count; z++)
                {
                    if (locked[z][i] == true)
                    {
                        num++;
                    }
                }

                if (num == 0)
                {
                    printf("%s\n", candidates[i]);
                    return;
                }
                num = 0;
            }
        }
    }
    return;
}

// input is winner and loser
// check if my loser is winer in some previous pair
// if so then rpeat but loser change to loser of loser
bool makes_circle(int cycle_start, int loser)
{
    if (loser == cycle_start)
    {
        // If the current loser is the cycle start
        // The entry makes a circle
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // loser is winer is some of previous
        if (locked[loser][i])
        {
            // check if loser against my loser is not winner against my winner
            if (makes_circle(cycle_start, i))
            {
                // Forward progress through the circle
                return true;
            }
        }
    }
    return false;
}