#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 20

typedef int element;
typedef struct
{
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} DequeType;

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_deque(DequeType *q)
{
    q->rear = 0;
    q->front = 0;
}

int is_full(DequeType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(DequeType *q)
{
    return (q->front == q->rear);
}

void queue_print(DequeType *q)
{
    printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
    if (!is_empty(q))
    {
        int i = q->front;
        do
        {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            printf("%d | ", q->data[i]);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}

void add_rear(DequeType *q, element item)
{
    if (is_full(q))
    {
        error("queue is full.");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

void add_front(DequeType *q, element item)
{
    if (is_full(q))
    {
        error("queue is full.");
        return;
    }
    q->data[q->front] = item;
    q->front = (q->front - 1+MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_front(DequeType *q)
{
    if (is_empty(q))
    {
        error("queue is empty.");
        return -1;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element delete_rear(DequeType *q)
{
    int prev=q->rear;
    if (is_empty(q))
    {
        error("queue is empty.");
        return -1;
    }
    q->rear = (q->rear - 1+MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return q->data[prev];
}

element get_front(DequeType *q)
{
    if (is_empty(q))
    {
        error("queue is empty.");
        return -1;
    }
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
element get_rear(DequeType *q)
{
    if (is_empty(q))
    {
        error("queue is empty.");
        return -1;
    }
    return q->data[q->rear];
}

int main()
{
    int element;
    DequeType q;
    init_deque(&q);
    
    /*srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        if (rand() % 10 == 0)
        {
            enqueue(&q, rand() % 100);
            queue_print(&q);
        }
        if (rand() % 10 == 0)
        {
            int data = dequeue(&q);
            queue_print(&q);
        }
    }*/

    return 0;
}