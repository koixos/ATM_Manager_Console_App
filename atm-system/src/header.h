#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERS "./data/users.txt"
#define RECORDS "./data/records.txt"

struct Date {
    int month;
    int day;
    int year;
};

struct Record {
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User {
    int id;
    char name[50];
    char password[50];
};

typedef struct Date Date;
typedef struct Record Record;
typedef struct User User;

// authentication functions
void loginMenu(char[], char[]);
void registerMenu(char[], char[]);
void createNewUser(int, char[], char[]);
const char *getPassword(User);
const int getId(User);

// system function
int createNewAcc(User);
int updateAccount(User);
int removeAccount(User);
int transferAccount(User);
int checkAccount(User);
int checkAllAccounts(User);
int makeTransaction(User);