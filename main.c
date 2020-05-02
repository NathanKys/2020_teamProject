#include <stdio.h>
#include "header.h"

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main() {

	Account login;	//로그인한 계정의 계정 정보 저장.
	Account targetAccount;	//관리자 로그인 시 관리 대상 계정
	int login_id_num = 2;	//현재 로그인된 아이디의 DB상 순서. 1부터 시작. -1은 관리자 아이디
	//로그인한 아이디 번호(= 로그인한 계정이 DB 상 몇번째 줄인지. 1번부터 시작)
	//이 값을 내 정보 보기 함수에서 인자로 받아, DB 상 해당 줄에 정보 출력
	int nextMenu = 0;
	bool flag = 0;	//로그인 상태
	int num_account = 12;	//DB에 등록된 계정의 총 개수
	char** oldNick = (char**)malloc(sizeof(char*) * num_account);			//닉네임 변경된 계정의 기존 닉네임 목록

	bool programFlag = 1;
	do {
		switch (uiMainMenu()) {
			case 1:
				signUp();

				num_account++;	//회원가입 완료 시 계정 개수 증가
				break;

			case 2:
				// 로그인 함수 - 리턴값은 DB상 몇번째 줄에 있는 계정인지.(1부터 시작)
				// return 값을 login_id_num에 복사
				// 관리자 로그인의 경우 -1을 리턴
				flag = 1;

				if (login_id_num != -1) {	//관리자가 아닌 일반 회원 로그인일 경우

					login = readAccountInfo(login_id_num); //로그인한 계정 정보 구조체에 저장
					if (login.lock) {
						printf("잠긴 계정입니다. 서비스를 이용할 수 없습니다.\n");
						system("pause");
						system("cls");
					}
					else {
						if (login.changed) {
							printf("닉네임이 변경되었습니다.\n");
							printf("기존 닉네임: %s\n", oldNick[login_id_num - 1]);
							printf("새로운 닉네임: %s\n", login.nick);
							login.changed = 0;
							system("pause");
							system("cls");
						}
						while (flag) {
							switch (uiAfterLogin(login.nick)) {
								case 1:	// 내 정보 보기 함수
									while (uiShowMyInfo(&login) != 2) {

									}
									break;

								case 2:
									userSearch(&login, num_account);
									// 사용자 검색 함수
									break;

								case 3:
									messageBox(login.id);
									// 쪽지함 함수
									break;

								case 4:
									flag = 0;
									writeAccountInfo(login_id_num, &login);
									break; //로그아웃
							}
						}
					}
				}
				else {	//관리자 로그인
					checkSecondPw();
					for (int i = 0; i < num_account; i++) {
						oldNick[i] = (char*)malloc(sizeof(char) * (NICKNAME_MAXSIZE + 2));
					}
					while (flag) {
						flag = adminMenu(num_account, &targetAccount, oldNick);
					}

				}

				break;
			case 3:
				// 아이디 및 비밀번호 찾기 함수
				break;
			case 4:
				programFlag = 0;
				system("cls");
				break; // 종료하기
		}
	} while (programFlag);

	for (int i = 0; i < num_account; i++) {
		free(oldNick[i]);
	}

	free(oldNick);
}