#include "LL.h"
node* head = NULL;
node* current = NULL;
int NumAccount;
account Account[100];

void printList()
{
   node *ptr = head;
   while(ptr != NULL)
	{        
      printf("%s %s %d\n", ptr->info.username, ptr->info.password, ptr->info.status);
      ptr = ptr->next;
   }
}
//Only call when first run main
void readfile(FILE *fptr){
    NumAccount = 0;
    while (!feof(fptr)){
        node* new =(struct node*) malloc(sizeof(node));
        fscanf(fptr, "%s %s %d\n", new->info.username, new->info.password, &new->info.status);
        new->next = head;
        head = new;
        NumAccount++;
    }
    //printf("NumAccount = %d\n", NumAccount);
}   

//Check username existed
node* FoundUserName(char username[64]){
    node* current = head;
    if (current->next == NULL) return NULL;
    while (strcmp(current->info.username, username) != 0){
        if (current->next == NULL) return NULL;
        else current = current->next;
    }
    return current;
}
//Check password correct
node* ValidAccount(char username[64], char password[64]){
    node* current = FoundUserName(username);
    if (current == NULL) {
        printf("Account not existed!\n");
        return NULL;
    }
    if (strcmp(current->info.password, password) != 0){
            printf("Password not correct!\n");
            return NULL;
    }
    return current;
}
//Overwrite Linked List to file
void Overwrite(){
    FILE *fptr = fopen("nguoidung.txt", "w+");
    node* current = head;
    while (current != NULL){
        fprintf(fptr, "%s %s %d\n", current->info.username, current->info.password, current->info.status);
        current = current->next;
    }
    fclose(fptr);
}

//Function 1
void Register(FILE* fptr)
{
    account info;
    printf("\tREGISTER \n");
    printf("Username: ");
    fflush(stdin);
    scanf("%s", info.username);
    if (FoundUserName(info.username) != NULL){
        do{
            printf("Account existed!\n");
            printf("Username: ");
            fflush(stdin);
            scanf("%s", info.username);
        }while(FoundUserName(info.username) != NULL);
    }
    printf("Password: ");
    fflush(stdin);
    scanf("%s", info.password);
    info.status = 2;
    node *link = (struct node*) malloc(sizeof(node));
    link->info = info;
    link->next = head;
    head = link;
    printf("Registered successfully!\n");
    Overwrite();
}

//Function 2
void Activate(){
    char code[9];
    char MSSV[9]  = "20194576";
    int LIMIT = 4;
    node* check;
    account info;

    printf("\tACTIVATE\n");
    printf("Username: ");
    fflush(stdin);
    scanf("%s", info.username);
    if (FoundUserName(info.username) == NULL){
        do{
            printf("Account does not exist!\n");
            printf("Username: ");
            fflush(stdin);
            scanf("%s", info.username);
        }while(FoundUserName(info.username) == NULL);
    }
    do{
        printf("Password: ");
        fflush(stdin);
        scanf("%s", info.password);
        check = ValidAccount(info.username, info.password);
        //If username and password both correct
        if (check != NULL){
            printf("Activation code: ");
            fflush(stdin);
            scanf("%s", code);
            if (strcmp(code, MSSV) != 0){
                do{
                    printf("Wrong activation code, you only have %d chance\n", LIMIT);
                    LIMIT--;
                    printf("Activation code: ");
                    fflush(stdin);
                    scanf("%s", code);
                }while(strcmp(code, MSSV) != 0 && LIMIT > 0);
                if (LIMIT == 0){
                    printf("Your account has been blocked!\n");
                    check->info.status = 0;
                    Overwrite();
                    return;
                }
            }
            else{
                check->info.status = 1;
                printf("You have activated successfully!\n");
                Overwrite();
                return;
            }
        }
        else printf("Wrong password!\n");
    }while(check == NULL);
}

//Function 3
void SignIn(){
    int LIMIT = 3;
    account info;
    node* check;

    printf("\tSIGN IN\n");
    printf("Username: ");
    fflush(stdin);
    scanf("%s", info.username);

    check = FoundUserName(info.username);
    if (check == NULL){
        do{
            printf("Account does not exist!\n");
            printf("Username: ");
            fflush(stdin);
            scanf("%s", info.username);
            check = FoundUserName(info.username);
        }while(check == NULL);
    }
    //check is node contain username
    printf("Password: ");
    fflush(stdin);
    scanf("%s", info.password);
    if (ValidAccount(check->info.username, info.password) == NULL){
        do{
            printf("Wrong password! You only have %d chance.\n", LIMIT);
            LIMIT--;
            printf("Password: ");
            fflush(stdin);
            scanf("%s", info.password);
        }while(ValidAccount(check->info.username, info.password) == NULL && LIMIT > 0);
        if (LIMIT == 0){
            printf("Your account has been blocked!\n");
            check->info.status = 0;
            Overwrite();
            return;
        }
    }
    printf("Sign in successfully!\n");
    check->info.status = 1;
    Overwrite();
}

//Function 4
void Search(){
    account info;
    printf("\tSEARCH\n");
    printf("Username: ");
    fflush(stdin);
    scanf("%s", info.username);

    node* check = FoundUserName(info.username);
    if (check == NULL){
        do{
            printf("Account does not exist!\n");
            printf("Username: ");
            fflush(stdin);
            scanf("%s", info.username);
            check = FoundUserName(info.username);
        }while(check == NULL);
    }
    if (check->info.status == 0)
        printf("Account blocked!\n");
    else if (check->info.status == 2)
        printf("Account not activated!\n");
    else printf("Account active!\n");
}

//Function 5
void ChangePassword(){
    account info;
    printf("\tCHANGE PASSWORD\n");
    printf("Username: ");
    fflush(stdin);
    scanf("%s", info.username);

    node* check = FoundUserName(info.username);
    if (check == NULL){
        do{
            printf("Account does not exist!\n");
            printf("Username: ");
            fflush(stdin);
            scanf("%s", info.username);
            check = FoundUserName(info.username);
        }while(check == NULL);
    }
    if (check->info.status == 0)
        printf("Error! Account blocked!\n");
    else if (check->info.status == 2)
        printf("Error! Account not sign in yet!\n");
    else {
        printf("Old password: ");
        fflush(stdin);
        scanf("%s", info.password);
        if (ValidAccount(check->info.username, info.password) == NULL){
            do{
                printf("Wrong password!\n");
                printf("Old password: ");
                fflush(stdin);
                scanf("%s", info.password);
            }while(ValidAccount(check->info.username, info.password) == NULL);
        }
        char NewPassword[20];
        printf("New password: ");
        fflush(stdin);
        scanf("%s", info.password);
        strcpy(check->info.password, info.password);
        printf("Change password successfully!\n");
        Overwrite();
    }
}

//Function 6
void SignOut(){
    account info;
    printf("\tSign Out\n");
    printf("Username: ");
    fflush(stdin);
    scanf("%s", info.username);

    node* check = FoundUserName(info.username);
    if (check == NULL){
        do{
            printf("Account does not exist!\n");
            printf("Username: ");
            fflush(stdin);
            scanf("%s", info.username);
            check = FoundUserName(info.username);
        }while(check == NULL);
    }
    if (check->info.status == 0)
        printf("Error! Account blocked!\n");
    else if (check->info.status == 2)
        printf("Error! Account not sign in yet!\n");
    else {
        printf("Sign out successfully!\n");
        check->info.status = 2;
        Overwrite();
    }
}
