#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void findaccount() {

    FILE* memlist;
    memlist = fopen("./accountlist.txt", "r");
    if (memlist == NULL)
    {
        printf("파일 읽기 실패\n");
        exit(1);
    }

    char c = ' ';
    char account_id[num_account][13] = { 0, }; // 배열 세로는 char account_info[num_account][12];
    char account_password[num_account][17] = { 0, };
    char account_nickname[num_account][13] = { 0, };
    char account_date[num_account][13] = { 0, };

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
            c = fgetc(memlist);
        }
    }


        char stdnickname[13];
        char stddate[9];

        /*printf("아이디를 찾으시려면 1번을, 비밀번호를 찾으시려면 2번을 입력해주세요\n");
        int n;
        scanf("%d", &n);

        switch(n)*/

        printf("닉네임을 입력하세요:");
        gets(stdnickname);

        for (int i = 0; i < num_account; i++) {
            if (strcmp(account_nickname[i], stdnickname) == 0) {
                printf("\n닉네임 일치\n");
            
                printf("\n생년월일을 입력하세요:");
                gets(stddate);


                if (strcmp(account_date[i], stddate) == 0) {
                    printf("\n생년월일 일치\n");
                    printf("아이디는 %s 입니다", account_id[i]);
                    break;
                }
                else{
                printf("입력한 정보와 부합하지 않는 생년월일입니다.");
                break;
                }
            }

            if(i==num_account-1){
                printf("존재하지 않는 닉네임입니다.");
                break;
            }
        }


        fclose(memlist);
    
}
