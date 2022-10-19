#include <stdio.h>
int main () {
    int menu = 0;
    do{
        printf("USER MANAGEMENT PROGRAM\n");
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
                printf("case 1\n");
                break;
            case 2: 
                printf("case 2\n");
                break;
            case 3: 
                printf("case 3\n");
                break;
            case 4: 
                printf("case 4\n");
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