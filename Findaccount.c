#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int interfaceFindAccount() {
    int triangle;
    char ch;
    system("cls");
    gotoxy(32, 10);
    printf("-------------------------------------------------\n");
    gotoxy(32, 11);
    printf("|\t\t\t\t\t\t|\n");
    gotoxy(32, 12);
    printf("|\t -------------------------------  \t|\n");
    gotoxy(32, 13);
    printf("|\t-            Find ID            - \t|\n");
    gotoxy(32, 14);
    printf("|\t -------------------------------  \t|\n");
    gotoxy(32, 15);
    printf("|\t\t\t\t\t\t|\n");
    gotoxy(32, 16);
    printf("|\t -------------------------------  \t|\n");
    gotoxy(32, 17);
    printf("|\t-         Find Password         - \t|\n");
    gotoxy(32, 18);
    printf("|\t -------------------------------  \t|\n");
    gotoxy(32, 19);
    printf("|\t\t\t\t\t\t|\n");
    gotoxy(32, 20);
    printf("--------------------------------------------------\n");


    triangle = 13;
    gotoxy(37, triangle);
    printf("▶");
    while (1)
    {
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                switch (ch)
                {
                case UP:
                    if (triangle > 13)
                    {
                        gotoxy(37, triangle);
                        printf(" ");
                        triangle = triangle - 4;
                        gotoxy(37, triangle);
                        printf("▶");
                    }
                    break;
                case DOWN:
                    if (triangle < 17)
                    {
                        gotoxy(37, triangle);
                        printf(" ");
                        triangle = triangle + 4;
                        gotoxy(37, triangle);
                        printf("▶");
                    }
                    break;
                }
            }
            if (ch == 13)
                break;
        }
    }
    if (triangle == 13)
        return 1;
    if (triangle == 17)
        return 2;
}

void findaccount(int num_account) {

    FILE* memlist;
    memlist = fopen("./accountlist.txt", "r");
    if (memlist == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    char c = ' ';
    char** account_id = malloc(sizeof(char*) * num_account);
    char** account_password = malloc(sizeof(char*) * num_account);
    char** account_nickname = malloc(sizeof(char*) * num_account);
    char** account_date = malloc(sizeof(char*) * num_account);

    for (int i = 0; i < num_account; i++) {
        account_id[i] = (char*)malloc(sizeof(char) * 50);
    }
    for (int i = 0; i < num_account; i++) {
        account_password[i] = (char*)malloc(sizeof(char) * 50);
    }
    for (int i = 0; i < num_account; i++) {
        account_nickname[i] = (char*)malloc(sizeof(char) * 50);
    }
    for (int i = 0; i < num_account; i++) {
        account_date[i] = (char*)malloc(sizeof(char) * 50);
    }

    //char account_id[num_account][13] = { 0, }; // 배열 세로는 char account_info[num_account][12];
    //char account_password[num_account][17] = { 0, };
    //char account_nickname[num_account][13] = { 0, };
    //char account_date[num_account][13] = { 0, };

    int j;
    for (j = 0; j < num_account; j++) {   //j<??? 로 수정

        int i = 0;
        while (1) {
            c = fgetc(memlist);
            if (c == ',') {
                account_id[j][i] = NULL;
                break;
            }
            account_id[j][i++] = c; //나중에 알려줄 아이디 값
        }
        i = 0;
        while (1) {
            c = fgetc(memlist);
            if (c == ',') {
                account_password[j][i] = NULL;
                break;
            }
            account_password[j][i++] = c;   //나중에 알려줄 비밀번호
        }
        while (fgetc(memlist) != ',') {

        }
        i = 0;
        while (1) {
            c = fgetc(memlist);
            if (c == ',') {
                account_nickname[j][i] = NULL;
                break;
            }
            account_nickname[j][i++] = c;

        }
        while (fgetc(memlist) != ',') {

        }
        i = 0;
        while (1) {
            c = fgetc(memlist);
            if (c == ',') {
                account_date[j][i] = NULL;
                break;
            }
            account_date[j][i++] = c;
        }


        while (fgetc(memlist) != '\n') {

        }
    }


    char stdid[13];
    char stdnickname[13];
    char stddate[9];

    int n = interfaceFindAccount();
  
    int count = 0;

    switch (n) {
    case 1:
    {
        while (count == 0) {
            system("cls");
            printf("Nickname:");
            gets(stdnickname);

            if (strcmp(stdnickname, "~") == 0) {
                count++;
                break;
            }

            int i;
            for (int i = 0; i < num_account; i++) {
                if (strcmp(account_nickname[i], stdnickname) == 0) {
                date: system("cls");
                    printf("Date of Birth:");
                    gets(stddate);

                    if (strcmp(stddate, "~") == 0) {
                        count++;
                        break;
                    }

                    if (strcmp(account_date[i], stddate) == 0) {
                        printf("Your Id is \'%s\' \n", account_id[i]);
                        count++;
                        system("pause");
                        break;
                    }
                    else {
                        printf("Wrong date of birth\n");
                        system("pause");
                        goto date;
                    }
                }
                else if (i == (num_account - 1)) {
                    printf("Inexistent nickname\n");
                    system("pause");
                }

            }

        }
    }
    case 2:
    {
        while (count == 0) {
            system("cls");
            printf("ID:");
            gets(stdid);

            if (strcmp(stdid, "~") == 0) {
                count++;
                break;
            }

            int i;
            for (i = 0; i < num_account; i++) {
                if (strcmp(account_id[i], stdid) == 0) {
                pass_nick: system("cls");
                    printf("Nickname:");
                    gets(stdnickname);

                    if (strcmp(stdnickname, "~") == 0) {
                        count++;
                        break;
                    }

                    if (strcmp(account_nickname[i], stdnickname) == 0) {
                    pass_date: system("cls");
                        printf("Date of Birth:");
                        gets(stddate);

                        if (strcmp(stddate, "~") == 0) {
                            count++;
                            break;
                        }

                        if (strcmp(account_date[i], stddate) == 0) {
                            system("cls");
                            printf("Password is \'%s\' \n", account_password[i]);
                            count++;
                            system("pause");
                            break;
                        }
                        else {
                            printf("Wrong date of birth\n");
                            system("pause");
                            goto pass_date;
                        }
                    }
                    else {
                        printf("Wrong nickname\n");
                        system("pause");
                        goto pass_nick;
                    }
                }
                else if (i == (num_account - 1)) {
                    printf("Inexistent id\n");
                    system("pause");
                    break;
                }
            }
        }
    }
    }
    for (int i = 0; i < num_account; i++)
        free(account_date[i]);
    free(account_date);
    for (int i = 0; i < num_account; i++)
        free(account_nickname[i]);
    free(account_nickname);
    for (int i = 0; i < num_account; i++)
        free(account_password[i]);
    free(account_password);
    for (int i = 0; i < num_account; i++)
        free(account_id[i]);
    free(account_id);
    fclose(memlist);
}
