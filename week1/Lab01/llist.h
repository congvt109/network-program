#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char username[50];
    char password[50];
    int status;
    int login;
    struct Node *next;
} Node;

Node *newNode(char *, char *, int);
Node *preInsert(Node *, char *, char *, int); 
Node *orderInsert(Node *, char *, char *, int);
Node *postInsert(Node *, char *, char *, int); 
Node *findNode(Node *, char *); 
Node *deleteNode(Node *, char *);
Node *deleteList(Node *); 
void saveNode(Node *, char *);
void printNode(Node *);
void printList(Node *); 
int countNodes(Node *);