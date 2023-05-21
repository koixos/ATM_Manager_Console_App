#include "header.h"
#include <termios.h>

void loginMenu(char a[50], char passwd[50]) {
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\tBank Management System\n\t\tUser Login: ");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        return exit(1);
    }

    printf("\n\n\n\n\n\tEnter the password to login: ");
    scanf("%s", passwd);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        return exit(1);
    }
}

void registerMenu(char a[50], char pass[50]) {
    FILE *pf = fopen(USERS, "r");
    
    loginMenu(a, pass);

    int userId;
    char userName[50], userPassword[50];
    while (fscanf(pf, "%d %s %s", &userId, userName, userPassword) != EOF) {
        if (strcmp(userName, a) == 0) {
            printf("\n✖ This user already exists\n");
            exit(1);
        }
    }
    fclose(pf);

    createNewUser(userId+1, a, pass);
}

void createNewUser(int id, char name[50], char passwd[50]) {
    FILE *pf = fopen(USERS, "a+");
    fprintf(pf, "%d %s %s\n", id, name, passwd);
    fclose(pf);
}

const char *getPassword(User u) {
    FILE *pf;
    User userChecker;

    if ((pf = fopen("./data/users.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(pf, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF) {
        if (strcmp(userChecker.name, u.name) == 0) {
            fclose(pf);
            char *buff = userChecker.password;
            return buff;
        }
    }
    fclose(pf);
    return "✖ No user found";
}

const int getId(User u) {
    FILE *pf;
    User userChecker;

    if ((pf = fopen("./data/users.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(pf, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF) {
        if (strcmp(userChecker.name, u.name) == 0) {
            fclose(pf);
            return userChecker.id;
        }
    }
    fclose(pf);
    return -1;
}