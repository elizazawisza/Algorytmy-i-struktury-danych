// Eliza Zawisza
// 244967

#include <stdio.h>
#include <stdlib.h>

//Struct which represent single node of queue.
typedef struct Node {
    int value;
    struct Node* prev;
} Node;

//Struct which represent queue.
typedef struct Queue {
    Node* head;
    Node* tail;
    int size;
} Queue;

//Function which create queue.
Queue* createQueue () {
    Queue* queue = malloc (sizeof (Queue));
    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> size = 0;
    return queue;
}

//Function which check whether the queue is empty or not. 
int isEmpty (Queue* queue) {
    if (queue -> size == 0) {
        return 1;
    } else {
        return 0;
    }
}

//Function which initiate the queue.
void initQueue (Queue* queue, int value) {
    Node* node = malloc (sizeof (Node));
    node -> value = value;
    node -> prev = NULL;
    queue -> head = node;
    queue -> tail = node;
    queue -> size = 1;
}


//Function which add single node with given value to the queue. Eventually init new Queue if the queue is empty.
void enqueue (Queue* queue, int value) {

    if (isEmpty(queue) == 1) {
        initQueue (queue, value);
        return; 
    }

    Node* newNode = malloc (sizeof (Node));

    newNode -> value = value;
    newNode -> prev = NULL;
    queue -> tail -> prev = newNode;
    queue -> tail = newNode;
    queue -> size++;
}


//Function which remove first element from queue. 
int dequeue (Queue* queue) {
    if (isEmpty(queue) == 1) {
        return 0;
    }

    Node* temp = queue -> head -> prev;
    free (queue -> head);
    queue -> head = temp;
    queue -> size--;
    return 1;
}

//Function which print the queue. 
void print (Queue* queue) {
    if (isEmpty(queue) == 1) {
        printf("Queue is empty!\n");
        return;
    }
    Node* temp;
    temp = queue -> head;
    while (temp != NULL) {
        printf ("%d <~~ ", temp -> value);
        temp = temp -> prev;
    }
    printf ("(null)\n");
}

int main () {
    Queue* queue = createQueue();
    enqueue (queue, 11);
    enqueue (queue, 57);
    enqueue (queue, 68);
    enqueue (queue, 19);
    print(queue);
    dequeue (queue);
    print(queue);
    dequeue (queue);
    print(queue);
    dequeue (queue);
    print(queue);
    dequeue (queue);
    print(queue);
    enqueue(queue, 33);
    print(queue);
    return 0;
}