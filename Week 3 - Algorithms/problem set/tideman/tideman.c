#include <cs50.h>
#include <stdio.h>
#include <strings.h>

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
bool check_cycle(int w, int l);
void merge_sort_arrays(pair pairs_array[], int left_index, int middle_index, int right_index);
void merge_recursion(pair pairs_array[], int left_index, int right_index);
void bubble_sort(void);


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
    for (int i = 0; i < candidate_count; i++)
    {
        // check whether input matches candidate name case insensitive
        if (strcasecmp(name, candidates[i]) == 0)
        {
            // stores voters candidate choice at their rank preference
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // increments preferences[][] to represent the number of voters who prefer candidate ith over candidate jth
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // checks whether ith candidate has more voters who prefer ith over jth the candidate
            if (preferences[i][j] > preferences[j][i])
            {
                // create pair, add to pairs array, increment pair count by 1
                pair placeholder = {.winner = i, .loser = j};
                pairs[pair_count] = placeholder;
                pair_count += 1;
            }
        }
    }
    return;
}

void merge_sort_arrays(pair pairs_array[], int left_index, int middle_index, int right_index)
{
    int left_length = middle_index - left_index + 1;
    int right_length = right_index - middle_index;

    pair temp_left[left_length];
    pair temp_right[right_length];
    // copy left side of pair array to temp left array
    for (int i = 0; i < left_length; i++)
    {
        temp_left[i] = pairs_array[left_index + i];
    }
    // copy right side of pairs array to temp right array
    for (int i = 0; i < right_length; i++)
    {
        temp_right[i] = pairs_array[middle_index + i + 1];
    }

    int i, j, k;
    // i current pos of left array
    // j current pos of right array
    // k index of this array

    for (i = 0, j = 0, k = left_index; k <= right_index; k++)
    {
        int sum1 = preferences[temp_left[i].winner][temp_left[i].loser] - preferences[temp_left[i].loser][temp_left[i].winner];
        int sum2 = preferences[temp_right[j].winner][temp_right[j].loser] - preferences[temp_right[j].loser][temp_right[j].winner];
        // check whether reached end of left array or right and sum
        if ((i < left_length) && (j >= right_length || sum2 <= sum1))
        {
            pairs_array[k] = temp_left[i];
            i++;
        }
        else
        {
            pairs_array[k] = temp_right[j];
            j++;
        }
    }
    return;
}

void merge_recursion(pair pairs_array[], int left_index, int right_index)
{
    if (left_index < right_index)
    {
        int middle_index = left_index + (right_index - left_index) / 2;
        // index for left side
        merge_recursion(pairs_array, left_index, middle_index);
        // index for right side
        merge_recursion(pairs_array, middle_index + 1, right_index);
        // merge
        merge_sort_arrays(pairs_array, left_index, middle_index, right_index);
    }
    return;
}

void bubble_sort(void)
{
    bool sorted = true;
    pair temp;

    // bubble sort to order pairs array in decreasing order
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 1; j < pair_count - i; j++)
        {
            // pair jth - 1 winner to loser vote difference
            int sum1 = preferences[pairs[j - 1].winner][pairs[j - 1].loser] - preferences[pairs[j - 1].loser][pairs[j - 1].winner];
            // pair jth winner to loser vote difference
            int sum2 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];

            if (sum1 < sum2)
            {
                temp = pairs[j];
                pairs[j] = pairs[j - 1];
                pairs[j - 1] = temp;
                sorted = false;
            }
        }
        // no swaps mean array sorted
        if (sorted)
        {
            break;
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //todo fix merge sort
    //bubble_sort();
    merge_recursion(pairs, 0, pair_count - 1);
    return;
}

bool check_cycle(int w, int l)
{
    // returned back to winner i.e a cycle
    if (w == l)
    {
        return true;
    }
    // iterates over loser row for true values
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[l][i] == true)
        {
            // recursive call see if its possible to get back to pos in winner row
            if (check_cycle(w, i) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (check_cycle(winner, loser) == false)
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // row
    for (int i = 0; i < candidate_count; i++)
    {
        // col
        for (int j = 0; j < candidate_count; j++)
        {
            // check the row for each candidate in jth column for true values
            if (locked[j][i] == true)
            {
                break;
            }
            // prints winning candidate after iterating over each candidate row in jth column and not finding any true values i.e. finding source of election
            else if (j == candidate_count - 1)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }
}