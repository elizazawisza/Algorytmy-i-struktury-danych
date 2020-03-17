// Eliza Zawisza
// 244967

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Struct which represent single node of linked list.
typedef struct Node {
    int value;
    struct Node* next;
} Node;


//Struct which represent Linked List.
typedef struct LinkedList {
    Node* head;
    Node* tail;
    int size;
} LinkedList;


//Function which check whether the linked list is empty or not. 
int isEmpty (LinkedList* list) {
    if (list -> size == 0) {
        return 1;
    } else {
        return 0;
    }
}

//Function which create linked list.
LinkedList* createList () {
    LinkedList* list = malloc (sizeof (LinkedList));
    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;
    return list;
}

//Function which initiate the linked list.
void initList (LinkedList* list, int value) {
    Node* newNode = malloc (sizeof (Node));
    newNode -> value = value;
    newNode -> next = NULL;
    list -> head = newNode;
    list -> tail = newNode;
    list -> size = 1;
}

//Function which add single node with given value to the linked list. Eventually init new Linked list if the linked list is empty.
void push (LinkedList* list, int value) {
    if (isEmpty (list) == 1) {
        initList (list, value);
        return;
    }

    Node* newNode = malloc (sizeof (Node));
    newNode -> value = value;
    newNode -> next = NULL;
    list -> head -> next = newNode;
    list -> head = newNode;
    list -> size++;
}

//Function which remove element at given index from linked list. 
int pop (LinkedList* list, int index) {
    if (index >= list -> size) {
        return 0;
    }

    Node* tmp = list -> tail;
    Node* prev = NULL;

    if (index == 0) {
        list -> tail = list -> tail -> next;
    } else {
        for (int i = 1; i <= index; i++) {
            prev = tmp;
            tmp = tmp -> next;
        }
        prev -> next = tmp -> next;
    }
    free (tmp);
    list -> size--;
    return 1;
}

//Function which find element at given index of linked list and return its value.
int find (LinkedList* list, int index) {
    if (index >= list -> size) {
        return -1;
    }
    
    Node* current = list -> tail;
    for (int i = 1; i <= index; i++) {
        current = current -> next;
    }
    return current -> value;
}

//Function which print the linked list. 
void print (LinkedList* list) {
    if (isEmpty (list) == 1) {
        printf ("List is empty!\n");
        return;
    }
    
    Node* current = list -> tail;
    while (current != NULL) {
        printf ("%d ~~> ", current -> value);
        current = current -> next;
    }
    printf ("(null)\n");
}

//Function which merge two linked lists into one. 
LinkedList* megre (LinkedList* list1, LinkedList* list2) {
    LinkedList* merged = createList();
    Node* current = list1 -> tail;

    while (current != NULL) {
        push (merged, current -> value);
        current = current -> next;
    }

    current = list2 -> tail;

    while (current != NULL) {
        push (merged, current -> value);
        current = current -> next;
    }

    return merged;
}

int main () {
    LinkedList* list1 = createList();
    push (list1, 23);
    print (list1);
    push (list1, 10);
    print (list1);
    push (list1, 19);
    print (list1);
    printf ("%d\n", find(list1, 0));
    pop(list1, 0);
    push (list1, 48);
    push (list1, 73);
    print (list1);

    LinkedList* list2 = createList();
    push (list2, 9);
    push (list2, 41);
    push (list2, 37);

    LinkedList* merged = megre (list1, list2);
    print (merged);

// TIME EXPERIMENTS

    int value;
    int index;
    double executionTime;
    clock_t start;
    clock_t end;

    LinkedList* test = createList ();

    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        value = rand() % 3158;
        push (test, value);
    }

    index = rand() % test -> size - 1;
    
    int n = 10000;

    start = clock();
    for (int i = 0; i < n; i++) {
        find (test, index);
    }
    end = clock();

    executionTime = ((double)(end - start))/CLOCKS_PER_SEC;
    printf ("Checking element %d lasts %f \n", index, executionTime);



    int* randomIndex = malloc (n * sizeof (int));

    for (int i = 0; i < n; i++) {
        randomIndex[i] = rand() % (test -> size);
    }

    start = clock();
    for (int i = 0; i < n; i++) {
        find (test, randomIndex[i]);
    }
    end = clock();

    executionTime = ((double)(end - start))/CLOCKS_PER_SEC;
    printf ("Checking random elements lasts %f\n", executionTime);

    free (randomIndex);
    return 0;
}