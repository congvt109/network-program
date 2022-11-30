#include <stdio.h>
#include "./llist.h"
#include "./llist.c"

int main () {
    int menu = 0;
    node* head = NULL;

    char username[20];
    char password[20];
    int status;

    char c;
    FILE* p = fopen("userInfo.txt", "r");
    while(fscanf(p, "%s %s %d", username, password, &status) != EOF){
        // node* temp = makeNode(username, password, status);
        // head = insertTail(head, temp);
        head = postInsert(head, username, password,status);
        printf("head = ");
        printNode(head);
    }
    printf("\n");
    fclose(p);
    printList(head);

    do{
        printf("\nUSER MANAGEMENT PROGRAM\n");
        printf("==============================\n");
        printf("1. Register\n");
        printf("2. Active\n");
        printf("3. Sign in\n");
        printf("4. Search\n");
        printf("5. Change password\n");
        printf("6.Sign out\n");
        printf("Your choice (1-6, other quit)\n");

        printf("Nhap menu: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1: 
                char username1[20];
                char password1[20];
                printf("Username: ");
                scanf("%s", username1);
                printf("Password: ");
                scanf("%s", password1);
                
                if (searchName(head, username1)) {
                    printf("Account is exist");
                    break;
                }else{
                    FILE* p = fopen("userInfo.txt", "a+");
                    fprintf(p, "\n%s %s %d", username1, password1, 2);
                    node* temp = makeNode(username1, password1, 2);
                    head = insertTail(head, temp);
                    fclose(p);
                }
                printList(head);
                break;

            case 2: 
                char activeCode[10];
                int check=0;
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");   
                scanf("%s", password);
                
                if (searchName(head, username)) {
                    printf("Account is not exist");
                    break;
                }

                while (check <= 2){
                    printf("Active code: ");
                    scanf("%s", activeCode);
                    if (strcmp(activeCode, "20194496")){
                        printf("Active code is wrong\n");
                        check++;
                    }else{
                        node * temp = searchName(head, username);
                        temp->status = 1;
                        break;
                    }
                    printf("Activation code is incorrect. Account is blocked");
                    node * temp = searchName(head, username);
                    temp->status = 0;
                    break;
                }
                    
                node * temp = searchNamePass(head, username, password);
                if (temp){
                    printNode(temp);
                }else {
                    printf("Account is not exist");
                }
                break;
            case 3:     
                char signInName[20];
                char signInPass[20];
                int checkPass = 0;
                
                printf("Username: ");
                fflush(stdin);
                scanf("%s", signInName);

                node* temp2 = searchName(head, signInName);
                if(temp2 == NULL){
                    printf("Cannot find user name");
                }
                
                while (checkPass <= 3){
                    printf("Password: ");
                    scanf("%s", signInPass);
                    if(searchPass(head, signInPass) == NULL){
                        printf("Password is incorrect");
                        checkPass++;
                    }else{
                        
                        break;
                    }
                    printf("Password enter more 3 times. Blocking...");
                    node* tmpBlock = searchName(head, signInName);
                    tmpBlock->status = 0;
                    break;
                }                   
                //todo: change status in file 
                break;

            case 4: 
                //search account
                char searchName[20];
                char searchPass[20];
                printf("Username: ");
                fflush(stdin);
                scanf("%s", searchName);
                printf("Password: ");
                fflush(stdin);
                scanf("%s", searchPass);
                node* search = searchNamePass(head, searchName, searchPass);
                if(search != NULL){
                    if (search->status == 0){
                        printf("Account is not active");
                    }else if (search->status == 1){
                        printf("Account is active");
                    }else{
                        printf("Account is blocked");
                    }
                }else{
                    printf("Cannot find the account");
                }
                break;
            case 5: 
                printf("case 5\n");
                break;
            case 6: 
                printf("case 6\n");
                break;
        }
    }while( menu >= 1 && menu <= 6);
}