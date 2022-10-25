#include <stdio.h>
#include "llist.c"

int main()
{
    FILE *f = fopen("account.txt", "r");
    if (f == NULL)
    {
        printf("Error: Cannot open file account.txt!\n");
        return 0;
    }
    char username[50], password[50];
    int status;
    Node *head = NULL;
    while (fscanf(f, "%s %s %d\n", username, password, &status) != EOF)
    {
        head = postInsert(head, username, password, status);
    }
    fclose(f);

    int menu;
    do
    {
        printf("\nUSER MANAGEMENT PROGRAM\n");
        printf("-----------------------------------\n");
        printf("1. Register\n");
        printf("2. Activate\n");
        printf("3. Sign in\n");
        printf("4. Search\n");
        printf("5. Change password\n");
        printf("6. Sign out\n");
        printf("Your menu (1-6, other to quit): ");

        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            printf("Username: ");
            scanf("%s", username);

            if (findNode(head, username) == NULL)
            {
                printf("Password: ");
                scanf("%s", password);
                head = postInsert(head, username, password, 2);
                f = fopen("account.txt", "a");
                fprintf(f, "%s %s %d\n", username, password, 2);
                fclose(f);
                printf("Successful registration. Activation required.\n");
            }
            else
                printf("Account existed!\n");
            break;
        case 2:
            // active code : 20194496
            char actCode[] = "20194496";
            printf("Username: ");
            scanf("%s", username);
            Node *p = findNode(head, username);
            if (p != NULL)
            {
                printf("Password: ");
                scanf("%s", password);
                if (strcmp(p->password, password) == 0)
                {
                    if (p->status == 0)
                    {
                        printf("Account is blocked!\n");
                        break;
                    }
                    else if (p->status == 1)
                    {
                        printf("Account is activated\n");
                        break;
                    }
                    printf("Account is not activated\n");

                    char activationCode[20];
                    int checkCode = 0;
                    while (checkCode < 4)
                    {
                        printf("Code : ");
                        fflush(stdin);
                        scanf("%s", activationCode);
                        if (strcmp(activationCode, actCode) == 0)
                        {
                            p->status = 1;
                            printListToFile(head, "account.txt");
                            printf("Account is active!\n");
                            break;
                        }
                        else
                        {
                            checkCode++;
                        }
                    }
                    if (checkCode == 4)
                    {
                        p->status = 0;
                        printListToFile(head, "account.txt");
                        printf("Activation code is incorrect. Account is blocked\n");
                        break;
                    }
                }
                else
                    printf("Password incorrect\n");
            }
            else
                printf("Cannot find account\n");
            break;
        case 3:
            printf("Username: ");
            scanf("%s", username);
            int checkPassword = 0;
            Node *tmp = findNode(head, username);
            if (tmp != NULL)
            {
                if (tmp->status == 0)
                {
                    printf("Account is blocked\n");
                    break;
                }
                while (checkPassword < 3)
                {
                    printf("Password: ");
                    scanf("%s", password);
                    if (strcmp(tmp->password, password) != 0)
                    {
                        printf("Password was wrong\n");
                        checkPassword++;
                    }
                    else
                    {
                        if (tmp->status == 0)
                        {
                            printf("Account is blocked!\n");
                            break;
                        }
                        else
                        {
                            tmp->login = 1;
                            printf("Hello %s\n", tmp->username);
                            break;
                        }
                    }
                }
                if (checkPassword == 3)
                {
                    // wrong password
                    printf("Password is incorrect. Account is blocked\n");
                    tmp->status = 0;
                    printListToFile(head, "account.txt");
                    break;
                }
            }
            else
            {
                printf("Cannot find account\n");
            }
            break;
        case 4:
            printf("Username: ");
            scanf("%s", username);
            Node *temp = findNode(head, username);
            if (temp != NULL)
            {
                if (temp->login == 0)
                {
                    printf("Not login yet!\n");
                    break;
                }
                if (temp->status == 0)
                {
                    printf("Account is blocked!\n");
                    break;
                }
                else if (temp->status == 1)
                {
                    printf("Account is active!\n");
                    break;
                }
                else
                {
                    printf("Account is inactive!\n");
                    break;
                }
            }
            else
            {
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
            if (point != NULL)
            {
                if (point->login == 0)
                {
                    printf("Account is not sign in\n");
                    break;
                }
                while (checkPass <= 3)
                {
                    printf("Password: ");
                    fflush(stdin);
                    scanf("%s", password);
                    if (strcmp(tmp->password, password) != 0)
                    {
                        printf("Current password is incorrect. Please try again\n");
                        checkPass++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (checkPass == 3)
                { // wrong password
                    printf("Enter pass more 3 times\n");
                    break;
                }
                else
                {
                    printf("New password: ");
                    fflush(stdin);
                    scanf("%s", newPassword);
                    strcpy(point->password, newPassword);
                    printListToFile(head, "account.txt");
                }
            }
            else
            {
                printf("Username is not found!\n");
            }
            break;
        case 6:
            // Sign out
            printf("Username: ");
            fflush(stdin);
            scanf("%s", username);
            Node *pointer = findNode(head, username);
            if (pointer != NULL)
            {
                if (pointer->login == 0)
                {
                    printf("Account is not sign in\n");
                    break;
                }
                else
                {
                    pointer->login = 0;
                    printf("Goodbye %s!\n", pointer->username);
                }
            }
            else
            {
                printf("Cannot find account\n");
            }
            break;
        default:
            break;
        }
    } while (menu > 0 && menu <= 6);

    return 0;
}