#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "ReadAccount.h"

#define UP 72 // 방향키 위 아스키코드
#define DOWN 80 // 방향키 아래 아스키코드

void gotoxy(int x, int y);
int menu1(int k);
