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
#define MAX_LINE_LENGTH 150
// 한 계정당 가능한 최소 데이터 길이(51byte)
// 한 계정당 가능한 최대 데이터 길이(120byte)
// 최소 길이로 회원가입하고, 그 계정의 닉네임이 관리자에 의해 최대 길이로 수정될 경우
// 2byte짜리 닉네임 -> 24byte짜리 닉네임(최대 한글 12자)
// 따라서, 최소 길이로 회원가입해도, DB 상에서 이에 필요한 여유 공간은 22byte 이상 빈칸으로 처리해둬야 함.
// -> 120 byte + 22byte의 여유있는 값으로 150 설정

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
void changeNick(char* nick, bool* changed);
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
void showAllAccountInfo2(int pageNum, int num_account);
int selectAccountToShow();
int accountInfo_Menu(Account* a);
void userSearch(Account* login, int num_account);
