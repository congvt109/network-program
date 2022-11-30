#include "LL.h"

void Function(int choice, FILE* fptr){
    switch(choice){
        case 1:
            Register(fptr);
            break;
        case 2:
            Activate();
            break;
        case 3:
            SignIn();
            break;
        case 4:
            Search();
            break;
        case 5:
            ChangePassword();
            break;
        case 6:
            SignOut();
            break;

    }
}
int Menu(int* choice, FILE* fptr){
    printf("-------------------------\n");
    printf("USER MANAGEMENT PROGRAM\n");
    printf("-------------------------\n");
    printf("1. Register\n");
    printf("2. Activate\n");
    printf("3. Sign in\n");
    printf("4. Search\n");
    printf("5. Change password\n");
    printf("6. Sign out\n");
    printf("Your choice (1-6, other to quit): ");
    scanf("%d", choice);
    if (*choice > 6 || *choice < 1)
        printf("Program exit!...\n");
    else
        Function(*choice, fptr);
}
int main(){
    FILE *fptr = fopen("nguoidung.txt", "r+");
    printf("File opened!\n");
    readfile(fptr);
    fclose(fptr);
    int choice;
    do{
        Menu(&choice, fptr);
    }while(choice >= 1 && choice <= 6);
}