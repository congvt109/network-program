#include <stdio.h>
#include "llist.c"

int main() {
    FILE *f = fopen("account.txt", "r");
    if (f == NULL) {
        printf("Error: Cannot open file account.txt!\n");
        return 0;
    }
    char username[50], password[50];
    int status;
    Node *head = NULL;
    while (fscanf(f, "%s %s %d\n", username, password, &status) != EOF) {
        head = postInsert(head, username, password, status);
    }
    fclose(f);
    
    int choice;
    do {
        printf("\nUSER MANAGEMENT PROGRAM\n");
        printf("-----------------------------------\n");
        printf("1. Register\n");
        printf("2. Activate\n");
        printf("3. Sign in\n");
        printf("4. Search\n");
        printf("5. Change password\n");
        printf("6. Sign out\n");
        printf("Your choice (1-6, other to quit): ");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            printList(head);
            break; 
        case 1:
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);
            if (findNode(head, username) == NULL) {
                head = postInsert(head, username, password, 2);
                f = fopen("account.txt", "a");
                fprintf(f, "%s %s %d\n", username, password, 2);
                fclose(f);
                printf("Register successfully!\n");
            }
            else
                printf("Username is existed!\n");
            break;
        case 2:
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);
            Node *p = findNode(head, username);
            if (p != NULL) {
                if (strcmp(p->password, password) == 0) {
                    if (p->status == 0)
                        printf("Account is blocked!\n");
                    else if (p->status == 1) {
                        printf("Tai khoan dang hoat dong!\n");
                    } else {
                        int activationCode;
                        printf("Activation code: ");
                        scanf("%d", &activationCode);
                        if (activationCode == 20194496) {
                            p->status = 1;
                            printListToFile(head, "account.txt"); 
                            printf("Account is active!\n");
                        } else {
                            int i;
                            for (i = 0; i < 3; i++) {
                                printf("Wrong activation code! Please try again: ");
                                scanf("%d", &activationCode);
                                if (activationCode == 20194496) {
                                    p->status = 1;   
                                    printListToFile(head, "account.txt");                    
                                    printf("Account is active!\n");
                                    break;
                                }
                            }
                            if (i == 3) {
                                p->status = 0;
                                printListToFile(head, "account.txt"); 
                                printf("Account is blocked!\n");
                            }
                        }
                    }
                }
                else
                    printf("Incorrect password!\n");
            }
            else
                printf("Username is not existed!\n");
            break;
        case 3:
            printf("Username: ");
            scanf("%s", username);
            int checkPassword = 0;
            Node* tmp = findNode(head, username);
            if (tmp != NULL){
                while (checkPassword <= 3){
                    printf("Password: ");
                    scanf("%s", password);
                    if (strcmp(tmp->password, password) != 0){
                        printf("Password was wrong\n");
                        checkPassword++;
                    }else{
                        if(tmp->status == 0){
                            printf("Account is blocked!\n");
                        }else if(tmp->status == 1){
                            printf("Account is active!\n");
                        }else{
                            printf("Account is inactive!\n");
                        }
                        break;
                    }
                }

                if (checkPassword != 3){    //eight passwords
                    tmp->login = 1;
                    printf("Hello %s\n", tmp->username);
                    break;
                }else{      //wrong password
                    printf("Enter pass more 3 times. Account is blocked\n");
                    tmp->status = 0;
                    printListToFile(head, "account.txt"); 
                }

            }else{
                printf("Username is not found!\n");
            }
            break;
        case 4:
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);
            Node *temp = findNode(head, username);
            if (temp != NULL ){
                if (temp->login == 0 ){
                    printf("Not login yet!\n");
                    break;
                }
                if(temp->status == 0){
                    printf("Account is blocked!\n");
                }else if(temp->status == 1){
                    printf("Account is active!\n");
                }else{
                    printf("Account is inactive!\n");
                }
            }else {
                printf("Username is not found!\n");
            }
            break;
        case 5:
            // Change password
            int checkPass = 0;
            char newPassword[20];
            printf("Username: ");
            scanf("%s", username);
            Node *point = findNode(head, username);
            if (point != NULL ){
                if (point->login == 0 ){
                    printf("Not login yet!\n");
                    break;
                }
                while (checkPass <= 3){
                    printf("Old Password: ");
                    scanf("%s", password);
                    if (strcmp(tmp->password, password) != 0){
                        printf("Old password was wrong\n");
                        checkPass++;
                    }
                }

                if (checkPass == 3){      //wrong password
                    printf("Enter pass more 3 times\n");
                    break;
                }else{
                    printf("New password: ");
                    scanf("%s", newPassword);
                    strcpy(point->password, newPassword);
                    printListToFile(head, "account.txt"); 
                }                
            }else {
                printf("Username is not found!\n");
            }
            break;
        case 6:
            // Sign out
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);
            Node *pointer = findAccount(head, username, password);
            if (pointer != NULL ){
                if(pointer->login == 0){
                    printf("Not login yet!\n");
                    break;
                }else{
                    pointer->login = 0;
                    printf("Goodbye %s!\n", pointer->username);
                }
            }else {
                printf("Username is not found!\n");
            }
            break;
        default:
            break;
        }
    } while (choice >= 0 && choice <= 6);
    
    return 0;
}