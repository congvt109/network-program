#include "llist.h"

Node *newNode(char *username, char *password, int status) {
	Node *newNode = (Node *) malloc (sizeof(Node));
    strcpy(newNode->username, username);
    strcpy(newNode->password, password);
    newNode->status = status;
    newNode->login = 0;
	newNode -> next = NULL;
	return newNode;
}

Node *preInsert(Node *head, char *username, char *password, int status) {
	Node *preNode = newNode(username, password, status);						
	preNode -> next = head;						
	return preNode;
}

Node *postInsert(Node *head, char *username, char *password, int status) {
	if (head == NULL)
		return newNode(username, password, status);
	else
		head -> next = postInsert(head -> next, username, password, status);
	return head;
}

Node *findNode(Node *head, char *username) {
	Node *p = head;
	while (p != NULL) {
		if (strcmp(p->username, username) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

Node *findAccount(Node*head, char *username, char *password) {
    Node *p = head;
    while (p!= NULL) {
        if (strcmp(p->username, username) == 0
            && strcmp(p->password, password) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}


Node *deleteNode(Node *head, char *username) {
	Node *tmp;
	if (head != NULL) {
		if (head -> username == username) {	
			tmp = head -> next;
			free(head);
			head = tmp;
		}
		else{
			head -> next = deleteNode(head -> next, username);
        }
	}
	return head;
}

Node *deleteList(Node *head) {
	if (head != NULL) {				/* if not reached end of the list... */
		deleteList(head -> next);	/* ...move on */
		free(head);				/* delete the node */
	}
	else 
		return NULL;
}

void printNode(Node *p) {
	if (p != NULL) {
		printf("%s %s %d\n", p -> username, p -> password, p -> status);
	}

}

void printListToFile(Node *head, char *filename) {
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	Node *p = head;
	while (p != NULL) {
		fprintf(f, "%s %s %d\n", p -> username, p -> password, p -> status);
		p = p -> next;
	}
	fclose(f);
}

void printList(Node *head) {
	if (head != NULL) {
		printf("%s %s %d\n", head -> username, head -> password, head -> status);
		printList(head -> next);
	}
}


int countNodes(Node *head) {
    if (head == NULL)
        return 0;
    else
        return 1 + countNodes(head -> next);
}
