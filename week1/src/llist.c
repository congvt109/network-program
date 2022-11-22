#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

node *makeNode(char username[], char password[], int status) {
    node *newNode = (node*)malloc(sizeof(node));
    strcpy()newNode->username = username;
    newNode->password = password;
    newNode->status = status;
    newNode->next = NULL;
    return newNode;
}

void freeNode(node *p) {
    free(p);
}

void printNode(node *p) {
    printf("%s %s %d\n", p->username, p->password, p->status);
}

void printList(node *head) {
    node *p = head;
    while (p != NULL) {
        printNode(p);
        p = p->next;
    }
}

node* insertHead(node *head, node *newNode) {
    newNode->next = head;
    return newNode;
}

node* insertTail(node *head, node *newNode) {
    if (head == NULL) {
        head = newNode;
        return head;
    }
    node *p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
    return head;
}


node *postInsert(node *top, char username[], char password[], int status) {
	if (top == NULL)
		return makeNode(username, password, status);
	else{// top -> next = postInsert(top -> next, username, password, status);
        node *p = top;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = makeNode(username, password, status);
    }
	return top;
}

// head -> tmp1 -> tmp2 -> tmp3

node* insertAfter(node *head, node *newNode, char username[]) {
    node *p = head;
    while (p != NULL && strcmp(p->username, username) != 0) {
        p = p->next;
    }
    if (p == NULL) {
        return head;
    }
    newNode->next = p->next;
    p->next = newNode;
    return head;
}

node* insertBefore(node *head, node *newNode, char username[]) {
    if (head == NULL) {
        return newNode;
    }
    if (strcmp(head->username, username) == 0) {
        return insertHead(head, newNode);
    }
    node *p = head;
    while (p->next != NULL && strcmp(p->next->username, username) != 0) {
        p = p->next;
    }
    if (p->next == NULL) {
        return head;
    }
    newNode->next = p->next;
    p->next = newNode;
    return head;
}

node* deleteHead(node *head) {
    if (head == NULL) {
        return NULL;
    }
    node *p = head;
    head = head->next;
    freeNode(p);
    return head;
}

node* deleteTail(node *head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        freeNode(head);
        return NULL;
    }
    node *p = head;
    while (p->next->next != NULL) {
        p = p->next;
    }
    freeNode(p->next);
    p->next = NULL;
    return head;
}

node* deleteNode(node *head, char username[]) {
    if (head == NULL) {
        return NULL;
    }
    if (strcmp(head->username, username) == 0) {
        return deleteHead(head);
    }
    node *p = head;
    while (p->next != NULL && strcmp(p->next->username, username) != 0) {
        p = p->next;
    }
    if (p->next == NULL) {
        return head;
    }
    node *q = p->next;
    p->next = q->next;
    freeNode(q);
    return head;
}



node* searchName(node *head, char username[]) {
    node *p = head;
    while (p != NULL && strcmp(p->username, username) != 0) {
        p = p->next;
    }
    return p;
}

node* searchPass(node *head, char password[]) {
    node *p = head;
    while (p != NULL && strcmp(p->password, password) != 0) {
        p = p->next;
    }
    return p;
}


node* searchNamePass(node *head, char username[], char password[]) {
    node *p = head;
    while (p != NULL 
            && strcmp(p->username, username) != 0 
            && strcmp(p->password, password) != 0) {
        p = p->next;
    }
    return p;
}


node* reverse(node *head) {
    node *p = head;
    node *q = NULL;
    while (p != NULL) {
        node *r = p->next;
        p->next = q;
        q = p;
        p = r;
    }
    return q;
}

