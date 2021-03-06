﻿#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <regex.h> // 정규식 라이브러리
#include <string.h>
#include <time.h>
#include <conio.h>

#include "ReadAccount.h"	//파일에서 계정 읽어와서 구조체에 저장
#include "message.h"

#define LEFT 75
#define RIGHT 77
#define UP 72 // 방향키 위 아스키코드
#define DOWN 80 // 방향키 아래 아스키코드
#define MAX_LINE_LENGTH 220
// 한 계정당 가능한 최소 데이터 길이(51byte)
// 한 계정당 가능한 최대 데이터 길이(120byte)
// 최소 길이로 회원가입하고, 그 계정의 닉네임이 관리자에 의해 최대 길이로 수정될 경우
// 2byte짜리 닉네임 -> 24byte짜리 닉네임(최대 한글 12자)
// 따라서, 최소 길이로 회원가입해도, DB 상에서 이에 필요한 여유 공간은 22byte 이상 빈칸으로 처리해둬야 함.
// -> 120 byte + 22byte의 여유있는 값으로 150 설정

enum { IDCHECK = 0, NICKNAMECHECK = 3, EMAILCHECK = 4, PHONENUMBERCHECK = 6, RETCHECK = 7 };

// 계정 개수 구하는 함수
int readAccountNum();

void gotoxy(int x, int y);
int uiMainMenu();
int uiAfterLogin(char* nick);
int uiShowMyInfo(Account* login, int login_id_num);

// 로그인 함수
int loginFunction(int* num_account);

// 내 정보 수정 관련 함수
int checkPW(char* pw);
void selectEdit(Account* login, int login_id_num);
void editPW(char* pw);
void editName(char* name);
void editNick(char* nick);
void editEmail(char* email);
void editBirth(int* birth);
void editPhone(int* phone);
void writeAccountInfo(int, Account*);
void recordHistory(char*, char*, int);
//문자열 형태(비밀번호 등)의 내 정보 수정 시 수정 이전의 정보 breakdown 파일로 출력
//최고 관리자에 의해 닉네임 수정 시에도 이 함수 사용
void writeBreakdownChar(int num, char* id, char* info);
//숫자 형태(휴대폰 번호 등)의 내 정보 수정 시
void writeBreakdownInt(int num, char* id, int* info);


// 관리자 기능 관련 함수
void checkSecondPw();
bool checkSubAdmin(Account* targetAccount, int login_id_num);
void subAdminMenu(int num_account, Account* targetAccount, int login_id_num, char* my_id);
bool adminMenu(int num_account, Account* targetAccount);
void readAccountInfo2(int startline, Account* a);
void showAllAccountInfo(int pageNum, int num_account);
int selectAccountToManage(int num_account, int pageNum, int endPage);
int selectManageFunction(bool subAdmin);
int selectManageFunctionSub(bool subAdmin);
void changeNick(char* nick);
void changeLock(char* id, bool* lock);
void changeNickSub(char* nick, Account* targetAccount, int login_id_num);
void changeLockSub(char* id, bool* lock, Account* targetAccount, int login_id_num);
//보조 관리자가 다른 사용자 닉네임 수정 시 수정내역과 자신의 아이디 출력하는 함수
void writeNickSub(int num, char* target_id, char* oldNick, char* my_id);


// 회원가입 관련 함수
int pow1(int, int);
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
int signUp();

void showAllAccountInfo2(int pageNum, int num_account);
int selectAccountToShow(int num_account, int pageNum, int endPage);
int accountInfo_Menu(Account* a);
void userSearch(Account* login, int num_account);

//int writeMessage(Account tt,char *s_Nickname);
//
void findaccount(int num_account);
void uiOldInfo(Account* login);
