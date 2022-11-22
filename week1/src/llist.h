// How to write single linked list library

#ifndef _LLIST_H
#define _LLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char username[20];
    char password[20];
    int status;
    struct node *next;
} node;

node* makeNode(char *username, char *password, int status);
void freeNode(node *p);
void printNode(node *p);
void printList(node *head);
node* insertHead(node *head, node *newNode);
node* insertTail(node *head, node *newNode);
node* insertAfter(node *head, node *newNode, char *username);
node* insertBefore(node *head, node *newNode, char *username);
node* deleteHead(node *head);
node* deleteTail(node *head);
node* deleteNode(node *head, char *username);
node* search(node *head, char *username);
node* reverse(node *head);

#endif
