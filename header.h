#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "ReadAccount.h"	//���Ͽ��� ���� �о�ͼ� ����ü�� ����

#define LEFT 75
#define RIGHT 77
#define UP 72 // ����Ű �� �ƽ�Ű�ڵ�
#define DOWN 80 // ����Ű �Ʒ� �ƽ�Ű�ڵ�

void gotoxy(int x, int y);
int uiMainMenu();
int uiAfterLogin(char * nick);
int uiShowMyInfo(Account login);
