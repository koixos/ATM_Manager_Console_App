#include "header.h"
#include <stdio.h>
#include <stdlib.h>

// clear STDIN buff
void clear() { while(getchar() != 10); }

void mainMenu(User u) {
    int r = 0;
    system("clear");
    while (!r) {
        int option;
        printf("\n\n\t\t======= ATM =======\n");
        printf("\n\t-->> Feel free to choose one of the options below <<--\n");
        printf("\n\t[1]- Create a new account\n");
        printf("\n\t[2]- Update account information\n");
        printf("\n\t[3]- Check accounts\n");
        printf("\n\t[4]- Check list of owned account\n");
        printf("\n\t[5]- Make Transaction\n");
        printf("\n\t[6]- Remove existing account\n");
        printf("\n\t[7]- Transfer ownership\n");
        printf("\n\t[8]- Exit\n");
        scanf("%d", &option);

        system("clear");
        int flag;
        switch (option) {
            case 1:
                if (createNewAcc(u) == 8)
                    r = 1;
                break;
            case 2:
                flag = updateAccount(u);
                if (flag == 8)
                    r = 1;
                else if (flag == -1)
                    printf("No account found!\n");
                break;
            case 3:
                flag = checkAccount(u);
                if (flag == 8)
                    r = 1;
                else if (flag == -1)
                    printf("No account found!\n");
                break;
            case 4:
                if (checkAllAccounts(u) == 8)
                    r = 1;
                break;
            case 5:
                flag = makeTransaction(u);
                if (flag == 8)
                    r = 1;
                else if (flag == -1)
                    printf("No account found!\n");
                else if (flag == 0)
                    printf("You cannot deposit or withdraw cash in fixed accounts!\n");
                else if (flag == -2)
                    printf("The amount to withdraw is superior than your available balance!");
                else if (flag == -3)
                    printf("Invalid option");
                break;
            case 6:
                flag = removeAccount(u);
                if (flag == 8)
                    r = 1;
                else if (flag == -1)
                    printf("No account found!\n");
                break;
            case 7:
                flag = transferAccount(u);
                if (flag == 8)
                    r = 1;
                else if (flag == -1)
                    printf("No account found!\n");
                else if (flag == -2)
                    printf("No user found!\n");
                break;
            case 8:
                r = 1;
                break;
            default:
                printf("Invalid operation!\n");
                clear();
                break;
        }
    }
    
};

void initMenu(User *u) {
    int r = 0;
    system("clear");
    printf("\n\n\t======= ATM =======\n");
    printf("\n\t-->> Feel free to login / register :\n");
    printf("\n\t[1]- login\n");
    printf("\n\t[2]- register\n");
    printf("\n\t[3]- exit\n");
    while (!r) {
        int option;
        scanf("%d", &option);
        switch (option) {
            case 1:
                loginMenu(u->name, u->password);

                if (strcmp(u->password, getPassword(*u)) == 0) {
                    printf("\n\nPassword Match!");
                    u->id = getId(*u);
                } else {
                    printf("\nWrong password!! or User Name\n");
                    exit(1);
                }
                r = 1;
                break;
            case 2:
                registerMenu(u->name, u->password);
                u->id = getId(*u);
                r = 1;
                break;
            case 3:
                exit(1);
                break;
            default:
                printf("Insert a valid operation!\n");
                clear();
                break;
        }
    }
};

int main() {
    User u;
    initMenu(&u);
    mainMenu(u);
    return 0;
}