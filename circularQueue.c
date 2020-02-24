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
} QueueType;

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(QueueType *q)
{
    q->rear = 0;
    q->front = 0;
}

int is_full(QueueType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}

void queue_print(QueueType *q)
{
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
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

void enqueue(QueueType *q, int item)
{
    if (is_full(q))
    {
        error("queue is full.");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType *q)
{
    if (is_empty(q))
    {
        error("queue is empty.");
        return -1;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element peek(QueueType *q)
{
    if (is_empty(q))
    {
        error("queue is empty.");
        return -1;
    }
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main()
{
    int element;
    QueueType q;
    init_queue(&q);

    srand(time(NULL));
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
    }

    return 0;
}