#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define candidates_MAX 9
#define voters_MAX 100


int preference [voters_MAX][candidates_MAX];

typedef struct
{
    char name[50];
    bool eliminated;
    int votes;
}
candidate;

candidate candidates[candidates_MAX];


int voters_count;
int candidates_count;

bool vote(int voter, int rank, char name[50]);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("usage: runoff[candidate...]\n");

        return 1;
    }

    candidates_count = argc - 1;
    if(candidates_count > candidates_MAX)
    {
        printf("maximum number of candidates can on be %i", candidates_count);

        return 2;
    }

    for(int i=0; i<candidates_count; i++)
    {
        strcpy(candidates[i].name, argv[i +1]);
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    printf("number of voter: ");
    scanf("%i", &voters_count);
    if(voters_count > voters_MAX)
    {
        printf("inavalid voters number");

        return 3;
    }

    for(int i =0; i<voters_count; i++)
    {
        for(int j=0; j<candidates_count; j++)
        {
            char name[50];
            printf("Rank %i: ", j+1);
            scanf("%s", name);

            if(!vote(i,j,name))
            {
                printf("invalid vote\n");

                return 4;
            }
        }
        printf("\n");
    }
    while (true)
    {
        tabulate();

        bool won = print_winner();
        if(won)
        {
            break;
        }

        int min = find_min();
        bool tie = is_tie(min);

        if(tie)
        {
            for(int i=0; i<candidates_count; i++)
            {
                if(!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }
        eliminate(min);

        for(int i=0; i<candidates_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
    
}

bool vote(int voter, int rank, char name[50])
{
    for(int i=0; i<candidates_count; i++)
    {
        if(strcmp(candidates[i].name,name) == 0)
        {
            preference[voter][rank] = i;

            return true;
        }
    }
    return false;
}
void tabulate(void)
{
    for(int i =0; i<voters_count; i++)
    {
        for(int j=0;j<candidates_count; j++)
        {
            if(!candidates[preference[i][j]].eliminated)
            {
                candidates[preference[i][j]].votes++;
                break;
            }
        }
    }
    return;
}
bool print_winner(void)
{
    int winner_votes = voters_count / 2;
    for(int i=0; i<candidates_count; i++)
    {
        if(candidates[i].votes > winner_votes)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}
int find_min(void)
{
    int least_votes = voters_count;
    for(int i =0; i<candidates_count; i++)
    {
        if(!candidates[i].eliminated && candidates[i].votes < least_votes)
        {
            least_votes = candidates[i].votes;
        }
    }
    return least_votes;
}
bool is_tie(int min)
{
    for(int i=0; i<candidates_count; i++)  
    {
        if(candidates[i].votes > min)
        {
            return false;
        }
    }
    return true;
}
void eliminate(int min)
{
    for(int i=0; i<candidates_count; i++)
    {
        if(candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}