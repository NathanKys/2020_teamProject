#include <stdio.h>
#include "header.h"

int main () {
int number1, number2;
int login_id_num = 2;	//2는 테스트를 위한 임시값
//로그인한 아이디 번호(= 로그인한 계정이 DB 상 몇번째 줄인지. 1번부터 시작)
//이 값을 내 정보 보기 함수에서 인자로 받아, DB 상 해당 줄에 정보 출력
	do {
		number1 = menu1(1);
		switch (number1) {
		case 1:
			// 로그인 함수
			// return 값을 login_id_num에 복사
			number2 = menu1(2);
			do {
				switch (number2) {
				case 1:
					// 내정보 보기 함수
					//readAccount(login_id_num);
					
					break;
				case 2:
					// 사용자 검색 함수
					break;
				case 3:
					// 쪽지함 함수
					break;
				case 4:
					break; //로그아웃
				}
			}while (number2 != 4);
			break;
		case 2:
			// 회원가입 함수
			break;
		case 3:
			// 아이디 및 비밀번호 찾기 함수
			break;
		case 4:
			break; // 종료하기
		}
	} while (number1 != 4);
}
