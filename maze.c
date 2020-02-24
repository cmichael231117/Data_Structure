#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 6

#define MAX_STACK_SIZE 100

typedef struct
{
    short r;
    short c;
} element;

typedef struct
{
    element data[MAX_STACK_SIZE];
    int top;
} StaclType;

char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'}};

element here = {1, 0}, entry = {1, 0};

void init_stack(StaclType *s) { s->top = -1; }

int is_empty(StaclType *s) { return (s->top == -1); }
int is_full(StaclType *s) { return (s->top == (MAX_STACK_SIZE - 1)); }

void push1(StaclType *s, element item)
{
    if (is_full(s))
    {
        fprintf(stderr, "stack is full!\n");
        return;
    }
    else
        s->data[++(s->top)] = item;
}

void push_loc(StaclType *s, int r, int c)
{
    if (r < 0 || c < 0)
        return;
    if (maze[r][c] != '1' && maze[r][c] != '.')
    {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push1(s, tmp);
    }
}

element pop(StaclType *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "stack is empty!\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];
}

element peek(StaclType *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "stack is empty!\n");
        exit(1);
    }
    else
        return s->data[(s->top)];
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++)
    {
        for (int c = 0; c < MAZE_SIZE; c++)
        {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main()
{
    int r, c;
    StaclType s;

    init_stack(&s);
    here = entry;
    while (maze[here.r][here.c] != 'x')
    {
        r = here.r;
        c = here.c;
        maze[r][c] = '.';
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        if (is_empty(&s))
        {
            printf("Fail\n");
            return 0;
        }
        else
        {
            here = pop(&s);
        }
        printf("Succeed\n");
        return 0;
    }
}