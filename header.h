#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <regex.h> // 정규식 라이브러리
#include <string.h>
#include <time.h>
#include <conio.h>

#include "ReadAccount.h"	//파일에서 계정 읽어와서 구조체에 저장

#define LEFT 75
#define RIGHT 77
#define UP 72 // 방향키 위 아스키코드
#define DOWN 80 // 방향키 아래 아스키코드
#define MAX_LINE_LENGTH 130

enum { IDCHECK = 0, NICKNAMECHECK = 3, EMAILCHECK = 4, PHONENUMBERCHECK = 6, RETCHECK = 7 };

void gotoxy(int x, int y);
int uiMainMenu();
int uiAfterLogin(char* nick);
int uiShowMyInfo(Account* login);

// 내 정보 수정 관련 함수
int checkPW(char* pw);
void selectEdit(Account* login);
void editPW(char* pw);
void editName(char* name);
void editNick(char* nick);
void editEmail(char* email);
void editBirth(int* birth);
void editPhone(int* phone);

// 관리자 기능 관련 함수
void checkSecondPw();
bool adminMenu(int num_account, Account* targetAccount);
void readAccountInfo2(int startline, Account* a);
void showAllAccountInfo(int pageNum, int num_account);
int selectAccountToManage();
int selectManageFunction();
void changeNick(char* nick);
void changeLock(char* id, bool* lock);

// 회원가입 관련 함수
int pow(int, int);
bool matchEmail(const char*);
bool matchPassword(const char*);
bool matchId(const char*);
bool matchEngName(const char*);
bool matchNickname(const char*);
bool matchPhoneNumber(const char*);
bool matchBirthday(const char*);
bool matchKorean(const char*, int);
bool kreng(const char*, int n);
bool isCompleteKorean(const char*, int);
bool isContainEng(const char*);
bool isOnlyNumber(const char*);
bool duplicateCheck(char*, int);
bool isRightDate(const char*);
bool isInTheFuture(const char*);
bool isContainLowerCase(const char*);
bool isContainUpperCase(const char*);
bool isContainNumber(const char*);
bool isRepeat(const char*, int);
bool isConti(const char*, int);
int getLength(const char*);
void Eliminate(char*, char);
void ret(char*);
void strAppend(char*, char);
void clearInputBuffer();
void showUserInformation(Account);
void writeAccount(Account);
void signUp(Account);

void writeAccountInfo(int, Account*);
