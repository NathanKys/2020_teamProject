#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE* memlist;
    memlist = fopen("./accountlist.txt", "r");
    if (memlist == NULL)
    {
        printf("파일 읽기 실패\n");
        exit(1);
    }

    char c = ' ';
    char account_id[num_account][13] = { 0, }; // 배열 세로는 char account_id[num_account][12];
    char account_password[100][17] = { 0, };

    int j;
    for (j = 0; j < num_account; j++) {   // for(j=0;j<num_account;j++)
 
        int i = 0;
            while (1) {
            c = fgetc(memlist);
            if (c == ',') {
                account_id[j][i] = NULL;
                break;
            }
                account_id[j][i++] = c;
            }
            i = 0;
            while (1) {
                c = fgetc(memlist);
                if (c == ',') {
                    account_password[j][i] = NULL;
                    break;
                }
                account_password[j][i++] = c;
            }
            while (fgetc(memlist) != '\n') {

            }
    }
    
    char stdid[13];
    char stdpassword[17];

    printf("아이디를 입력하세요:");
    gets(stdid);
    
    for (int i = 0; i < num_account; i++) {       //i<num_account 로 수정
        if (strcmp(account_id[i], stdid) == 0) {
            printf("\n아이디 일치\n");

            printf("\n비밀번호를 입력하세요:");
            gets(stdpassword);


            if (strcmp(account_password[i], stdpassword) == 0) {
                printf("\n비밀번호 일치\n");
                break;
            }
            else
                printf("비밀번호가 틀립니다.");
            break;
        }

        if (i == 1)
            printf("존재하지 않는 아이디 입니다");
    }
    
    
    

    fclose(memlist);
}
