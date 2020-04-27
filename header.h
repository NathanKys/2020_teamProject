#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "ReadAccount.h"	//파일에서 계정 읽어와서 구조체에 저장

#define LEFT 75
#define RIGHT 77
#define UP 72 // 방향키 위 아스키코드
#define DOWN 80 // 방향키 아래 아스키코드

void gotoxy(int x, int y);
int uiMainMenu();
int uiAfterLogin(char * nick);
int uiShowMyInfo(Account login);
