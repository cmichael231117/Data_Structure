#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
//#define MAX_STRING 100

typedef char element;
typedef struct
{
    element data[MAX_STACK_SIZE];
    int top;
} StaclType;

void init_stack(StaclType *s) { s->top = - 1; }

int is_empty(StaclType *s) { return (s->top == -1); }
int is_full(StaclType *s) { return (s->top == (MAX_STACK_SIZE - 1)); }

void push(StaclType *s, element item)
{
    if (is_full(s))
    {
        fprintf(stderr, "stack is full!\n");
        return;
    }
    else
        s->data[++(s->top)] = item;
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

int check_matching(const char *in)
{
    StaclType s;
    char ch, open_ch;
    int i, n = strlen(in);
    init_stack(&s);

    for (i = 0; i < n; i++)
    {
        ch = in[i];
        switch (ch)
        {
        case '(':
        case '[':
        case '{':
            push(&s, ch);
            break;
        case ')':
        case ']':
        case '}':
            if (is_empty(&s))
                return 0;
            else
            {
                open_ch = pop(&s);
                if ((open_ch == '(' && ch != ')') ||
                    (open_ch == '[' && ch != ']') ||
                    (open_ch == '{' && ch != '}'))
                {
                    return 0;
                }
                break;
            }
        }
    }
    if (!is_empty(&s))
        return 0;
    return 1;
}

int main()
{
    char *p = "{A[(i+1)]=0;}";
    if (check_matching(p) == 1)
        printf("%s ok\n", p);
    else
        printf("%s fail\n", p);
    return 0;
}