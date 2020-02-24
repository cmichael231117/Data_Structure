#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType
{
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[])
{
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++)
    {
        if (distance[i] < min && !found[i])
        {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void print_status(GraphType *g)
{
    static int step = 1;
    printf("STEP %d: ", step++);
    printf("distance: ");
    for (int i = 0; i < g->n; i++)
    {
        if (distance[i] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }
    printf("\n");
    printf(" found: ");
    for (int i = 0; i < g->n; i++)
        printf("%2d ", found[i]);
    printf("\n\n");
}

void shortest_path(GraphType *g, int start)
{
    int i, u, w;
    for (i = 0; i < g->n; i++)
    {
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
    }
    found[start] = TRUE;
    distance[start] = 0;
    for (i = 0; i < g->n; i++)
    {
        print_status(g);
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        for (w = 0; w < g->n; w++)
            if (!found[w])
                if (distance[u] + g->weight[u][w] < distance[w])
                    distance[w] = distance[u] + g->weight[u][w];
    }
}

int main(void)
{
    GraphType g = {
        7,
        {{0, 29, INF, INF, INF, 10, INF},
         {29, 0, 16, INF, INF, INF, 15},
         {INF, 16, 0, 12, INF, INF, INF},
         {INF, INF, 12, 0, 22, INF, 18},
         {INF, INF, INF, 22, 0, 27, 25},
         {10, INF, INF, INF, 27, 0, INF},
         {INF, 15, INF, 18, 25, INF, 0}}};
    shortest_path(&g, 0);
    return 0;
}