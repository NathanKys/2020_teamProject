#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SUCCESS = 1;
const int FAIL = 2;
const int LIMIT = 3;

const char *AdminID = "admin";
const char *AdminPass = "pass";

int LoginCount = 0;
int check(int id, int password);


int check(int id, int password)
{
    LoginCount++;
    if (LoginCount == LIMIT)
    {
        return LIMIT;
    }
    if (id == 0 && password == 0)
    {
        return SUCCESS;
    }
    if (id != 0 && password != 0)
    {
        return FAIL;
    }
}
int main(void)
{
    char id[12], password[16];
    char result;

    while (1)
    {
        printf("id :");
        id[12] = getchar();

        printf("password :");
        password[16] = getchar();

        int idcmp = strcmp(id, AdminID);
        int passcmp = strcmp(password, AdminPass);
        
        result = check(idcmp, passcmp);
        if (result == SUCCESS)
        {
            printf("로그인 성공\n");
            break;
        }
        if (result == FAIL)
        {
            printf("ID or PASSWORD ERROR!\n");
        }
        if (result == LIMIT)
        {
            printf("횟수초과!!!\n");
            break;
        }
    }
    return 0;
}
