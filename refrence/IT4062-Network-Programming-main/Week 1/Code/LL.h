#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//File function
void getfile();
void readfile(FILE *fptr);
void printList();
void Register(FILE* fptr);
void Overwrite();

//LinkedList function
typedef struct account{
    char username[64];
    char password[64];
    int status;
} account;
typedef struct node{
    account info;
    struct node* next;
} node;

node* FoundUsername(char username[64]);
node* ValidAccount(char username[64], char password[64]);
void Activate();
void SignIn();
void Search();
void ChangePassword();
void SignOut();