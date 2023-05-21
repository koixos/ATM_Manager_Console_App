#include "header.h"

const double SAVING_INTEREST_RATE = 0.07;
const double FIXED1_INTEREST_RATE = 0.04;
const double FIXED2_INTEREST_RATE = 0.05;
const double FIXED3_INTEREST_RATE = 0.08;

int getAccountFromFile(FILE *ptr, Record *r) {
    return fscanf(
        ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
        &r->id,
        &r->userId,
		r->name,
        &r->accountNbr,
        &r->deposit.month,
        &r->deposit.day,
        &r->deposit.year,
        r->country,
        &r->phone,
        &r->amount,
        r->accountType
    ) != EOF;
}

void saveAccountToFile(FILE *ptr, User u, Record r) {
    fprintf(
        ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
        r.id,
        u.id,
        u.name,
        r.accountNbr,
        r.deposit.month,
        r.deposit.day,
        r.deposit.year,
        r.country,
        r.phone,
        r.amount,
        r.accountType
    );
}

void saveUpdatedAccountToFile(User u, Record r, int updAccNum) {
    FILE *temp = fopen("./data/temp.txt", "w");
    FILE *ptr = fopen(RECORDS, "r");

    Record tempR;
    while (getAccountFromFile(ptr, &tempR)) {
        User tempU;
        tempU.id = tempR.userId;
        strcpy(tempU.name, tempR.name);

        if (updAccNum == tempR.accountNbr) {
            tempU.id = u.id;
            strcpy(tempU.name, u.name);
            tempR.userId = u.id;
            strcpy(tempR.name, u.name);
            strcpy(tempR.country, r.country);
            tempR.phone = r.phone;
            tempR.amount = r.amount;
        }
        saveAccountToFile(temp, tempU, tempR);
    }
    fclose(ptr);
    fclose(temp);
    remove(RECORDS);
    rename("./data/temp.txt", RECORDS);
}

void removeAccountFromFile(int line) {
    FILE *temp = fopen("./data/temp.txt", "w");
    FILE *ptr = fopen(RECORDS, "r");

    Record tempR;
    int counter = 0;
    while (getAccountFromFile(ptr, &tempR)) {
        if (counter != line) {
            User tempU;
            tempU.id = tempR.userId;
            strcpy(tempU.name, tempR.name);
            saveAccountToFile(temp, tempU, tempR);
        } else {
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                tempR.accountNbr,
                tempR.deposit.day,
                tempR.deposit.month,
                tempR.deposit.year,
                tempR.country,
                tempR.phone,
                tempR.amount,
                tempR.accountType);
        }
        ++counter;
    }
    fclose(ptr);
    fclose(temp);
    remove(RECORDS);
    rename("./data/temp.txt", RECORDS);
}

int success() {
    int option;
    printf("\n✔ Success!\n\n");
    while (1) {
        printf("Enter 1 to go to the main menu and 0 to exit\n");
        scanf("%d", &option);
        system("clear");
        if (option == 1)
            return 1;
        else if (option == 0)
            return 8;
        printf("Insert a valid operation!\n");
        while (getchar() != 10);
    }
}

double calculateInterest(double deposit, double interestRate) { return deposit * interestRate / 100; }

int createNewAcc(User u) {
    FILE *pf = fopen(RECORDS, "a+");
    Record rec, cRec;
    int doesExist = 0;
    
    while (1) {
        system("clear");
        if (doesExist) {
            printf("✖ This Account already exists for this user");
            doesExist = 0;
        }
        printf("\n\n\t\t===== New record =====\n");
        printf("\n\tEnter today's date(mm/dd/yyyy): ");
        scanf("%d/%d/%d", &rec.deposit.month, &rec.deposit.day, &rec.deposit.year);
        printf("\n\tEnter the account number: ");
        scanf("%d", &rec.accountNbr);

        while (getAccountFromFile(pf, &cRec)) {
            if (strcmp(cRec.name, u.name) == 0 && cRec.accountNbr == rec.accountNbr) {   
                doesExist = 1;
                break;
            }
        }
        if (!doesExist)
            break;
    }
    printf("\n\tEnter the country: ");
    scanf("%s", rec.country);
    printf("\n\tEnter the phone number: ");
    scanf("%d", &rec.phone);
    printf("\n\tEnter amount to deposit: $");
    scanf("%lf", &rec.amount);
    printf("\n\tChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice: ");
    scanf("%s", rec.accountType);

    rec.id = cRec.id+1;
    saveAccountToFile(pf, u, rec);
    fclose(pf);
    return success();
}

int updateAccount(User u) {
    FILE *pf = fopen(RECORDS, "r");
    Record r;
    int accountNum;
    printf("Account number to be updated: ");
    scanf("%d", &accountNum);

    int doesExist = 0;
    while (getAccountFromFile(pf, &r)) {
        if (strcmp(u.name, r.name) == 0 && accountNum == r.accountNbr) {
            doesExist = 1;
            break;
        }
    }
    fclose(pf);

    if (!doesExist)
        return -1;

    int option;
    printf("1) Update phone number\n2) Update country\n\nOption: ");
    scanf("%d", &option);
    
    if (option == 1) {
        int newNum;
        printf("Enter new phone number: ");
        scanf("%d", &newNum);
        r.phone = newNum;
    } else if (option == 2) {
        char newCount[50];
        printf("Enter new country: ");
        scanf("%s", newCount);
        strcpy(r.country, newCount);
    } else {
        printf("Invalid option\n");
        return -1;
    }
    saveUpdatedAccountToFile(u, r, accountNum);
    return success();
}

int removeAccount(User u) {
    FILE *pf = fopen(RECORDS, "r");
    Record r;
    int accountNum;
    printf("Account number to be deleted: ");
    scanf("%d", &accountNum);

    int flag = 0;
    int line = 0;
    while (getAccountFromFile(pf, &r)) {
        if (strcmp(u.name, r.name) == 0 && accountNum == r.accountNbr) {
            flag = 1;
            break;
        } else {
            ++line;
        }
    }
    fclose(pf);

    if (!flag)
        return -1;

    removeAccountFromFile(line);
    return success();
}

int transferAccount(User u) {
    FILE *pf = fopen(RECORDS, "r");
    Record r;
    User _to;
    int accountNum;
    printf("Account number to be transfered: ");
    scanf("%d", &accountNum);

    int flag = 0;
    while (getAccountFromFile(pf, &r)) {
        if (strcmp(u.name, r.name) == 0 && accountNum == r.accountNbr) {
            flag = 1;
            break;
        }
    }
    fclose(pf);

    if (!flag) {
        while (getchar() != 10);
        return -1;
    }
    
    printf("\t\tTransferring Account:\n\n");
    printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
        r.accountNbr,
        r.deposit.day,
        r.deposit.month,
        r.deposit.year,
        r.country,
        r.phone,
        r.amount,
        r.accountType);

    char to[50];
    printf("Transfer to (user name):");
    scanf("%s", to);

    pf = fopen(USERS, "r");
    int userId;
    char userName[50], userPasswd[50];
    flag = 0;
    while (fscanf(pf, "%d %s %s", &userId, userName, userPasswd) != EOF) {
        if (strcmp(userName, to) == 0) {
            _to.id = userId;
            strcpy(_to.name, userName);
            strcpy(_to.password, userPasswd);
            flag = 1;
            break;
        }
    }
    fclose(pf);

    if (!flag)
        return -2;

    saveUpdatedAccountToFile(_to, r, accountNum);
    return success();
}

int checkAccount(User u) {
    FILE *pf = fopen(RECORDS, "r");
    Record r;
    int accountNum;
    printf("Account number to be checked: ");
    scanf("%d", &accountNum);

    int flag = 0;
    while (getAccountFromFile(pf, &r)) {
        if (strcmp(u.name, r.name) == 0 && accountNum == r.accountNbr) {
            flag = 1;
            break;
        }
    }
    fclose(pf);

    if (!flag)
        return -1;
    
    printf("_____________________\n");
    printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
        r.accountNbr,
        r.deposit.day,
        r.deposit.month,
        r.deposit.year,
        r.country,
        r.phone,
        r.amount,
        r.accountType);

    if (strcmp(r.accountType, "current") == 0)
        printf("You will not get interests because the account is of type current\n");
    else if (strcmp(r.accountType, "saving") == 0)
        printf("You will get %0.2f as interest on day %d of every month\n",
            calculateInterest(r.amount, SAVING_INTEREST_RATE), r.deposit.day);
    else if (strcmp(r.accountType, "fixed01") == 0)
        printf("You will get %0.2f as interest on %d/%d/%d\n",
            12*calculateInterest(r.amount, FIXED1_INTEREST_RATE), r.deposit.month, r.deposit.day, r.deposit.year+1);
    else if (strcmp(r.accountType, "fixed02") == 0)
        printf("You will get %0.2f as interest on %d/%d/%d\n",
            12*calculateInterest(r.amount, FIXED2_INTEREST_RATE), r.deposit.month, r.deposit.day, r.deposit.year+2);
    else if (strcmp(r.accountType, "fixed03") == 0)
        printf("You will get %0.2f as interest on %d/%d/%d\n",
            12*calculateInterest(r.amount, FIXED3_INTEREST_RATE), r.deposit.month, r.deposit.day, r.deposit.year+3);
    return success();
}

int checkAllAccounts(User u) {
    FILE *pf = fopen(RECORDS, "r");
    Record r;
    char userName[100];

    printf("\n\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, &r)) {
        if (strcmp(r.name, u.name) == 0) {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                r.accountNbr,
                r.deposit.day,
                r.deposit.month,
                r.deposit.year,
                r.country,
                r.phone,
                r.amount,
                r.accountType);
        }
    }
    fclose(pf);
    return success();
}
      
int makeTransaction(User u) {
    FILE *pf = fopen(RECORDS, "r");
    struct Record r;
    int accountNum;
    printf("Account number of the customer: ");
    scanf("%d", &accountNum);

    int flag = 0;
    while (getAccountFromFile(pf, &r)) {
        if (strcmp(u.name, r.name) == 0 && accountNum == r.accountNbr) {
            flag = 1;
            break;
        }
    }
    fclose(pf);

    if (!flag)
        return -1;

    if (strcmp(r.accountType, "fixed01") == 0 || strcmp(r.accountType, "fixed02") == 0 || strcmp(r.accountType, "fixed03") == 0)
        return 0;

    int choice;
    printf("Selection:\n\t1) withdraw\n\t2) deposit\n\nChoice: ");
    scanf("%d", &choice);
    
    double amount;
    if (choice == 1) {
        printf("Enter the amount to withdraw: ");
        scanf("%lf", &amount);
        if (amount > r.amount)
            return -2;
        
        r.amount -= amount;
        printf("Success on withdrawing!\n");
        saveUpdatedAccountToFile(u, r, accountNum);
        return success();
    }
    if (choice == 2) {
        printf("Enter the amount to deposit: ");
        scanf("%lf", &amount);
        r.amount += amount;
        printf("Success on deposit!\n");
        saveUpdatedAccountToFile(u, r, accountNum);
        return success();
    }
    return -3;
}