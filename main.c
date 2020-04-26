//#include <stdio.h>
#include "header.h"

int main () {
int number1, number2;
	do {
		number1 = menu1(1);
		switch (number1) {
		case 1:
			// 로그인 함수
			number2 = menu1(2);
			switch (number2) {
			case 1:
				// 내정보 보기 함수
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
