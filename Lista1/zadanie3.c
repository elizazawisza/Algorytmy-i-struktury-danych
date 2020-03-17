// Eliza Zawisza
// 244967

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Struct which represent single node of list.
typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

//Struct which represent List.
typedef struct List {
    int size;
    Node* head;
} List;


//Function which check whether the list is empty or not. 
int isEmpty (List* list) {
    if (list -> size == 0) {
        return 1;
    } else {
        return 0;
    }
}


//Function which create list.
List* createList () {
    List* list = malloc (sizeof (List));
    list -> head = NULL;
    list -> size = 0;
    return list;
}

//Function which initiate the list.
void initList (List* list, int value) {
    Node* newNode = malloc (sizeof (Node));
    newNode -> value = value;
    newNode -> next = newNode;
    newNode -> prev = newNode;
    list -> head = newNode;
    list -> size = 1;
}


//Function which add single node with given value to the list. Eventually init new Linked list if the linked list is empty.
void push (List* list, int value) {
    if (isEmpty (list) == 1) {
        initList (list, value);
        return;
    }

    Node* newNode = malloc (sizeof (Node));
    newNode -> value = value;
    newNode -> prev = list -> head -> prev;
    newNode -> next = list -> head;
    list -> head -> prev -> next = newNode;
    list -> head -> prev = newNode;
    list -> size++;
}

//Function which remove element at given index from list. 
int pop (List* list, int index) {
    if (index >= list -> size) {
        return 0;
    }

    Node* current = list -> head;;

    if (index == 0) {
        current -> next -> prev = current -> prev;
        current -> prev -> next = current -> next;
        list -> head = current -> next;
        free (current);
        list -> size--;
        return 1;
    }

    if (index < list -> size / 2) {
        for (int i = 1; i <= index; i++) {
            current = current -> next;
        }
    } else {
        int start = list -> size - 1;

        for (int i = start; i >= index; i--) {
            current = current -> prev;
        }
    }

    current -> next -> prev = current -> prev;
    current -> prev -> next = current -> next;
    list -> size--;
    free (current);
    return 1;
}

//Function which find element at given index of list and return its value.
int find (List* list, int index) {
    if (index >= list -> size) {
        return -1;
    }

    Node* current = list -> head;

    if (index < list -> size / 2) {
        for (int i = 1; i <= index; i++) {
            current = current -> next;
        }
    } else {
        int start = list -> size - 1;

        for (int i = start; i >= index; i--) {
            current = current -> prev;
        }
    }

    return current -> value;
}

//Function which print the list. 
void print (List* list) {
    if (isEmpty (list) == 1) {
        printf ("List is empty!\n");
        return;
    }

    Node* current = list -> head;
    int end = list -> size;

    printf ("(~~) ");
    for (int i = 0; i < end; i++) {
        printf ("%d ~~> ", current -> value);
        current = current -> next;
    }

    printf ("%d (~~)\n", list -> head -> value);
}

//Function which merge two lists into one. 
List* megre (List* list1, List* list2) {
    List* merged = createList ();

    Node* current = list1 -> head;
    int end = list1 -> size;

    for (int i = 0; i < end; i++) {
        push (merged, current -> value);
        current = current -> next;
    }

    current = list2 -> head;
    end = list2 -> size;

    for (int i = 0; i < end; i++) {
        push (merged, current -> value);
        current = current -> next;
    }

    return merged;
}

int main () {
    List* list1 = createList();
    push (list1, 20);
    print (list1);
    push (list1, 21);
    print (list1);
    push (list1, 22);
    print (list1);
    push (list1, 45);
    print (list1);
    push (list1, 17);
    print (list1);
    push (list1, 18);
    print (list1);
    printf ("%d\n", find(list1, 1));
    printf ("%d\n", find(list1, 4));
    pop(list1, 0);
    print (list1);

    List* list2 = createList ();
    push (list2, 198);
    push (list2, 36);
    push (list2, 59);
    push (list2, 16);
    push (list2, 29);

    List* merged = megre (list1, list2);
    print (merged);

// TIME EXPERIMENTS
    
    int value;
    int index;
    double executionTime;
    clock_t start;
    clock_t end;

    List* test = createList ();

    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        value = rand() % 4325;
        push (test, value);
    }

    index = rand() % test -> size - 1;
    
    int n = 20000;

    start = clock();
    for (int i = 0; i < n; i++) {
        find (test, index);
    }
    end = clock();

    executionTime = ((double)(end - start))/CLOCKS_PER_SEC;
    printf ("Checking element %d everytime lasts %f \n", index, executionTime);



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
    printf ("Checking random elements lasts %f15.\n", executionTime);

    free (randomIndex);
    return 0;
}