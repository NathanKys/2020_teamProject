#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

// 메뉴로 돌아가는 기능 추가

int pow1(int a, int b) {
	if (b == 0) return 1;
	int c;
	int d;
	d = a;
	for (c = 1;c < b;c++) {
		d = d * a;
	}
	return d;
}

bool matchEmail(const char* string) {
	regex_t state;
	const char* pattern = "^[a-zA-Z0-9_.-]*@[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*[.][a-zA-Z]{2,}$";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}

bool matchPassword(const char* string) {
	// 8~16자
	// 대소문자, 숫자 하나 이상 무조건 포함
	// 허용하는 특수문자: !@#$%^&*
	regex_t state;
	const char* pattern = "^[a-zA-Z0-9!@#$%^&\*]*$";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}

bool matchId(const char* string) {
	regex_t state;
	const char* pattern = "^[a-zA-Z0-9]*$";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}

bool matchEngName(const char* string) {
	// 한글은 최소 2자에서 최대 5자로 제한
	// 영어는 20자로 제한
	regex_t state;
	const char* pattern = "^[a-zA-Z]([a-zA-Z][[:blank:]]?)*[a-zA-Z]$";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}

bool matchNickname(const char* string) {
	regex_t state;
	const char* pattern = "^(([[:blank:]]?[a-zA-Z0-9][[:blank:]]?))*$";
	int reti;
	bool check;
	int string_size = strlen(string);
	check = matchKorean(string, string_size);

	regcomp(&state, pattern, REG_EXTENDED);
	reti = regexec(&state, string, 0, NULL, 0) ? false : true;
	if (!isCompleteKorean(string, string_size)) {
		return false;
	}
	return reti || check;
}

bool matchPhoneNumber(const char* string) {
	regex_t state;
	const char* pattern = "^01[0-9][-]?[0-9]{3,4}[-]?[0-9]{4}$";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}

bool matchBirthday(const char* string) {
	regex_t state;
	const char* pattern = "^(19|20)[0-9]{2}((0[1-9])|(1[0-2]))((0[1-9])|([1-2][0-9])|(3[0-1]))$";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}

bool matchKorean(const char* string, int n) {
	// 문자열 내에 한글이 있으면 true
	// 없으면 false
	for (int i = 0;i < n;i++) {
		if (string[i] & 0x80) return true;
	}
	return false;
}

bool kreng(const char* string, int n) {
	// 한글과 영어를 같이 쓰면 true, 아니면 false
	int a = string[0] & 0x80;

	for (int i = 1;i < n;i++) {
		if (a != (string[i] & 0x80)) {
			return true;
		}
	}
	return false;
}

bool isCompleteKorean(const char* string, int n) {
	// true면 불완전한 한글
	char temp[4] = "";
	static const char* const initial_array[] = {
	"ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ", "ㅂ", "ㅃ", "ㅅ",
	"ㅆ", "ㅇ", "ㅈ", "ㅉ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"
	};
	static const char* const medial_array[] = {
		"ㅏ", "ㅐ", "ㅑ", "ㅒ", "ㅓ", "ㅔ", "ㅕ", "ㅖ", "ㅗ", "ㅘ",
		"ㅙ", "ㅚ", "ㅛ", "ㅜ", "ㅝ", "ㅞ", "ㅟ", "ㅠ", "ㅡ", "ㅢ",
		"ㅣ"
	};
	static const char* const final_array[] = {
		  "", "ㄱ", "ㄲ", "ㄳ", "ㄴ", "ㄵ", "ㄶ", "ㄷ", "ㄹ", "ㄺ",
		"ㄻ", "ㄼ", "ㄽ", "ㄾ", "ㄿ", "ㅀ", "ㅁ", "ㅂ", "ㅄ", "ㅅ",
		"ㅆ", "ㅇ", "ㅈ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"
	};

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < sizeof(initial_array) / sizeof(char*);j++) {
			temp[0] = string[i];
			temp[1] = string[i + 1];
			if (!strcmp(temp, initial_array[j])) {
				return false;
			}
		}
		for (int j = 0;j < sizeof(medial_array) / sizeof(char*);j++) {
			temp[0] = string[i];
			temp[1] = string[i + 1];
			if (!strcmp(temp, medial_array[j])) {
				return false;
			}
		}
		for (int j = 0;j < sizeof(final_array) / sizeof(char*);j++) {
			temp[0] = string[i];
			temp[1] = string[i + 1];
			if (!strcmp(temp, final_array[j])) {
				return false;
			}
		}
	}
	return true;
}

bool isContainEng(const char* string) {
	regex_t state;
	const char* pattern = "[a-zA-Z]";

	regcomp(&state, pattern, REG_EXTENDED);
	if (!regexec(&state, string, 0, NULL, 0)) {
		return true;
	}
	else {
		return false;
	}


}

bool isOnlyNumber(const char* string) {
	regex_t state;
	const char* pattern = "^[0-9]*$";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}

// 파일체크하는 함수
bool duplicateCheck(char* _string, int option) {
	// _string: 중복 검사할 문자열
	//  option: 중복 검사할 유형
	FILE* fp;
	char temp[MAX_LINE_LENGTH];
	char ch;
	int i = 0;
	int j = 0;
	char string[EMAILADDRESS_MAXSIZE + 2] = "";

	fp = fopen("accountlist.txt", "r");
	if (fp == NULL)
	{
		printf("파일 불러오기 실패\n");
		exit(1);
	}
	while (true) {
		for (;j < option;j++) {
			while (true) {
				ch = fgetc(fp);
				if (ch == ',') {
					break;
				}
				else if (ch == EOF) {
					fclose(fp);
					return false;
				}
			}
		}
		while (true) {
			string[i] = fgetc(fp);
			if (string[i] == ',') {
				string[i] = '\0';
				i = 0;
				fgets(temp, MAX_LINE_LENGTH, fp);
				break;
			}
			else if (string[i] == EOF) {
				fclose(fp);
				return false;
			}
			i++;
		}
		//printf("%s\n", string);
		if (!strcmp(string, _string)) {
			return true;
		}
		j = 0;
	}
	fclose(fp);
	return false;
}

// 윤년체크해서 올바른 월/일 판단
bool isRightDate(const char* string) {
	int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int year, month, day;
	int index = 0;
	year = 0;
	month = 0;
	day = 0;



	for (index;index < 4;index++) {
		year += ((string[index] - '0') * pow1(10, 3 - index));
	}
	for (index;index < 6;index++) {
		month += ((string[index] - '0') * pow1(10, 5 - index));
	}

	for (index;index < 8;index++) {
		day += ((string[index] - '0') * pow1(10, 7 - index));
	}

	if (month < 1 || month>12) {
		return false;
	}

	if (day < 1 || day>31) {
		return false;
	}

	if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) {
		days[1] = 29;
	}
	if (days[month - 1] < day) {
		return false;
	}

	return true;
}

// 프로그램 실행보다 뒤의 날짜인지 판단
bool isInTheFuture(const char* string) {
	int year, month, day;
	int index = 0;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	year = 0;
	month = 0;
	day = 0;

	for (index;index < 4;index++) {
		year += ((string[index] - '0') * pow(10, 3 - index));
	}
	for (index;index < 6;index++) {
		month += ((string[index] - '0') * pow(10, 5 - index));
	}

	for (index;index < 8;index++) {
		day += ((string[index] - '0') * pow(10, 7 - index));
	}

	if (year > (tm.tm_year + 1900)) {
		return true;
	}
	else if (year == (tm.tm_year + 1900)) {
		if (month > tm.tm_mon + 1) {
			return true;
		}
		else if (month == tm.tm_mon + 1) {
			if (day > tm.tm_mday) {
				return true;
			}
		}
	}
	return false;
}

bool isContainLowerCase(const char* string) {
	regex_t state;
	const char* pattern = "[a-z]";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}

bool isContainUpperCase(const char* string) {
	regex_t state;
	const char* pattern = "[A-Z]";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}

bool isContainNumber(const char* string) {
	regex_t state;
	const char* pattern = "[0-9]";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}

bool isRepeat(const char* string, int length) {
	for (int i = 0;i < length - 2;i++) {
		if ((string[i] - string[i + 1] == 1) && (string[i + 1] - string[i + 2] == 1)) {
			return  true;
		}
		if ((string[i + 2] - string[i + 1] == 1) && (string[i + 1] - string[i] == 1)) {
			return  true;
		}
	}
	return false;
}

bool isConti(const char* string, int length) {
	for (int i = 0;i < length - 2;i++) {
		if (string[i] == string[i + 1] && string[i + 1] == string[i + 2]) { return true; }
	}
	return false;
}

int getLength(const char* string) {
	int a = strlen(string);
	int temp = 0;

	for (int i = 0;i < strlen(string);i++) {
		if (string[i] & 0x80) {
			temp++;
		}
	}
	return a - temp / 2;
}

void clearInputBuffer()
{
	// 입력 버퍼에서 문자를 계속 꺼내고 \n를 꺼내면 반복을 중단
	while (getchar() != '\n');
}

// 문자열 내의 특정 문자 제거
void Eliminate(char* string, char ch) {
	int len = strlen(string) + 1;
	for (;*string != '\0';string++, len--) {
		if (*string == ch) {
			strcpy_s(string, len, string + 1);
			string--;
		}
	}
}

// 인자로 받은 아이디의 추천 횟수 증가
void ret(char* _string) {
	// 최대 추천 횟수: 99번
	FILE* fp;
	FILE* tempfp;
	int rewindCount = 0;
	char temp[MAX_LINE_LENGTH];
	char ch;
	int i = 0;
	int j = 0;
	char string[EMAILADDRESS_MAXSIZE + 2] = "";
	int tempRet;
	char buf[10];
	char buf_temp[2] = { 0, };
	// 읽기 우선 쓰기 모드
	fp = fopen("accountlist.txt", "r+t");
	tempfp = fopen("accountlist.txt", "r");
	if (fp == NULL)
	{
		printf("파일 불러오기 실패\n");
		exit(1);
	}
	while (true) {
		while (true) {
			string[i] = fgetc(fp);
			fgetc(tempfp);
			if (string[i] == ',') { string[i] = '\0'; i = 0; break; }
			else if (string[i] == EOF) { fclose(fp);fclose(tempfp); return; }
			i++;
		}
		if (!strcmp(string, _string)) {
			// 위에서 아이디를 먼저 읽었기 때문에 -1해줘야 함.
			for (;j < RETCHECK-1;j++) {
				while (true) {
					ch = fgetc(fp);
					fgetc(tempfp);
					if (ch == ',') {
						break;
					}
					else if (ch == EOF) {
						fclose(fp);
						fclose(tempfp);
						return;
					}
				}
			}
			while (true) {
				string[i] = fgetc(fp);
				fgetc(tempfp);
				if (string[i] == ',') { string[i] = '\0'; i = 0; break; }
				else if (string[i] == EOF) { fclose(fp);fclose(tempfp); return; }
				i++;
			}
			tempRet = atoi(string);
			if (tempRet < 99 && tempRet>9) {
				tempRet += 1;
				snprintf(buf, 3, "%d", tempRet);
				fseek(fp, -3, SEEK_CUR);
				fwrite(buf, 2, 1, fp);
				fseek(fp, -3, SEEK_CUR); // 다시 원래대로 안 돌려주면 원인 모를 오류 발생

			}
			else if (tempRet < 9) {
				tempRet += 1;
				snprintf(buf, 3, "%d", tempRet);
				fseek(fp, -2, SEEK_CUR);
				fwrite(buf, 1, 1, fp);
				fseek(fp, -2, SEEK_CUR); // 다시 원래대로 안 돌려주면 원인 모를 오류 발생
			}
			else if (tempRet == 9) {

				//tempRet += 1;
				//snprintf(buf, 3, "%d", tempRet);
				//strncat(buf, ",", 1);
				//int count = 0;
				//while (true) {
				//	count++;
				//	buf_temp[0] = fgetc(fp);
				//	strncat(buf, buf_temp, 1);
				//	if (buf_temp[0] == '\n') { break; }
				//}
				////for (int k = 0;k < 10;k++) {
				////	printf("%d: %d\n", k, buf[k]);
				////}
				////printf("%s %d\n", buf, strlen(buf));
				//fseek(fp, -strlen(buf), SEEK_CUR);
				//fwrite(buf, strlen(buf), 1, fp);
				//fseek(fp, -strlen(buf), SEEK_CUR);
				fseek(fp, -2, SEEK_CUR);
				fwrite("10,", 3, 1, fp);
				fseek(fp, 2, SEEK_CUR);
				//ch = fgetc(tempfp);
				//printf("%c", ch);
				//ch = fgetc(tempfp);
				//printf("%c", ch);
				//ch = fgetc(tempfp);
				//printf("%c", ch);
				//ch = fgetc(tempfp);
				//printf("%c", ch);
				fseek(fp, -2, SEEK_CUR);
				// 10을 쓴 이후의 데이터를 tempfp에서 받아들여서 fp로 전부 복사
				while (true) {
					ch = fgetc(tempfp);
					if (feof(tempfp) != 0)
						break;
					fputc(ch, fp);
					rewindCount++;
				}
				fseek(fp, 2, SEEK_CUR);

				/*fseek(fp, -rewindCount-4, SEEK_CUR);
				fwrite("Tlqkf", 5, 1, fp);
				fseek(fp, rewindCount+4, SEEK_CUR);*/
			}

			//printf("%s의 추천횟수: %d\n", _string, tempRet);
		}
		else {
			// 아이디가 일치하지 않으면 다음 줄로 넘어감.
			fgets(temp, MAX_LINE_LENGTH, fp);
			fgets(temp, MAX_LINE_LENGTH, tempfp);
		}
		j = 0;
	}
	fclose(fp);
	fclose(tempfp);
}

// 문자열 뒤에 문자 합치기
void strAppend(char* dest, char ch) {
	char* p = dest;
	while (*p != '\0') p++;
	*p = ch;
	*(p + 1) = '\0';
}

// 제대로 입력이 되었는지 확인하는 임시 함수
void showUserInformation(Account a) {
	printf("아이디: %s\n", a.id);
	printf("비밀번호: %s\n", a.pw);
	printf("이름: %s\n", a.name);
	printf("닉네임: %s\n", a.nick);
	printf("이메일 주소: %s\n", a.email);
	printf("생년월일: %s\n", a.birth);
	printf("휴대폰 번호: %s\n", a.phone);
}

// 계정 구조체를 accountlist.txt에 저장
void writeAccount(Account user) {
	FILE* fp;
	fp = fopen("accountlist.txt", "a+");
	if (fp == NULL) {
		printf("파일지정 경로를 확인해주세요.\n");
		exit(1);
	}
	else {
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%d,%d,%d",
			user.id, user.pw, user.name, user.nick, user.email, user.birth, user.phone, user.rec, user.lock, user.changed);
		fprintf(fp, "                         \n");
		//최소 길이의 닉네임(2byte)으로 회원가입 하고, 관리자에 의해 최대 길이의 닉네임(24byte)으로 수정될 경우를 대비하여
		//이에 필요한 여유 공간을 미리 확보해둬야 함.
		//그렇지 않으면 다음 줄의 데이터를 덮어쓰게 됨.
		//24 - 2 = 22이지만 여유있게 25byte의 공간을 확보.
	}
	fclose(fp);
}

void signUp() {
	Account u1 = {0, };
	u1.lock = false;
	u1.changed = false;
	char tempPhoneNumber[PHONENUMBER_MAXSIZE + 4];
	char tempBirthNumber[BIRTHDAY_MAXSIZE + 2];
	// 아이디 입력
	while (true) {
		system("cls");
		printf("생성할 계정의 아이디를 입력합니다.");
		fgets(u1.id, ID_MAXSIZE + 2, stdin);

		u1.id[strcspn(u1.id, "\n")] = 0;

		// 메뉴로 이동
		if (u1.id[0] == '~' && strlen(u1.id) == 1) {
			printf("메뉴로 돌아갑니다.\n");
			system("pause");
			return;
		}

		if (strlen(u1.id) > ID_MAXSIZE) {
			clearInputBuffer();
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (duplicateCheck(u1.id, IDCHECK)) {
			printf("입력하신 아이디는 이미 사용 중인 아이디입니다.\n");
			system("pause");
			continue;
		}

		if (matchId(u1.id)) {
			if (getLength(u1.id) > ID_MAXSIZE || getLength(u1.id) < 6) {
				printf("글자수 범위(최소6자 ~ 최대 12자)초과입니다.\n");
				system("pause");
				continue;
			}
			else {
				printf("아이디 입력이 완료되었습니다.\n");
				system("pause");
				break;
			}
		}
		else {
			printf("올바른 문자를 입력해주세요.\n");
			system("pause");
			continue;
		}

	}

	// 비밀번호 입력
	while (true) {
		system("cls");
		printf("생성할 계정의 비밀번호를 입력합니다.");
		fgets(u1.pw, PASSWORD_MAXSIZE + 2, stdin);

		u1.pw[strcspn(u1.pw, "\n")] = 0;

		// 메뉴로 이동
		if (u1.pw[0] == '~' && strlen(u1.pw) == 1) {
			printf("메뉴로 돌아갑니다.\n");
			system("pause");
			return;
		}
		if (strlen(u1.pw) > PASSWORD_MAXSIZE) {
			clearInputBuffer();
		}

		if (matchPassword(u1.pw)) {
			if (strlen(u1.pw) < 8 || strlen(u1.pw) > 16) {
				printf("글자수 범위(최소 8자~최대 16자) 초과입니다.\n");
				system("pause");
				continue;
			}
			else {
				// 대문자 하나 이상
				// 소문자 하나 이상
				// 숫자 하나 이상
				if (!isContainUpperCase(u1.pw)) {printf("알파벳 대문자를 하나 이상 포함해야 합니다.\n");}
				if (!isContainLowerCase(u1.pw)) {printf("알파벳 소문자를 하나 이상 포함해야 합니다.\n");}
				if (!isContainNumber(u1.pw)) {printf("인도-아라비아 숫자를 하나 이상 포함해야 합니다.\n");}

				// 위의 세 조건을 모두 만족할 때
				if (isContainNumber(u1.pw) && isContainUpperCase(u1.pw) && isContainLowerCase(u1.pw)) {
					// 반복된 문자 체크
					if (isRepeat(u1.pw, strlen(u1.pw))) { 
						printf("비밀번호에 반복된 문자가 있습니다.\n"); 
						system("pause");
						continue;
					}
					// 연속된 문자 체크
					if (isConti(u1.pw, strlen(u1.pw))) {
						printf("비밀번호에 연속된 문자가 있습니다.\n");
						system("pause");
						continue;
					}

					printf("비밀번호 입력이 완료되었습니다.\n");
					system("pause");
					break;
				}
				system("pause");
				continue;
			}

		}
		else {
			printf("다음의 문자를 제외한 특수문자는 허용하지 않습니다.!@#$%^&*\n");
			system("pause");
			continue;
		}


	}

	//비밀번호 확인
	while (true) {
		system("cls");
		char checkPassword[PASSWORD_MAXSIZE + 2] = { 0, };
		printf("비밀번호 확인을 위해 다시 입력해주세요.");
		fgets(checkPassword, PASSWORD_MAXSIZE + 2, stdin);
		checkPassword[strcspn(checkPassword, "\n")] = 0;
		if (strlen(checkPassword) > PASSWORD_MAXSIZE) {
			clearInputBuffer();
		}

		// 메뉴로 이동
		if (checkPassword[0] == '~' && strlen(checkPassword) == 1) {
			printf("메뉴로 돌아갑니다.\n");
			system("pause");
			return;
		}

		/*
		   비밀번호 확인을 저장하는 변수에서 입력받지 않은 뒤의 값들은 -52로 나와서
		   checkPassword를 {0,}로 초기화해서 해결
		for (int i = 0;i < PASSWORD_MAXSIZE + 2;i++) {
			printf("\n\n비밀번호[%d]: %d\n비번확인[%d]: %d\n", i, u1.pw[i], i, checkPassword[i]);
		}
		*/


		if (!strcmp(checkPassword, u1.pw)) {
			printf("비밀번호 확인이 완료되었습니다.\n");
			system("pause");
			break;
		}
		else {
			printf("비밀번호와 일치하지 않습니다.\n");
			system("pause");
			continue;
		}
	}

	// 이름 입력
	while (true) {
		system("cls");
		printf("이름을 입력합니다.\n");
		printf("이름은 한글(최소 2자~최대 5자) 또는 영어 대소문자(최소 3자~최대 20자)로 구성됩니다.\n");
		printf("한글와 영어는 혼용하여 사용할 수 없습니다. 영어의 경우 띄어쓰기가 가능합니다.\n");
		fgets(u1.name, NAME_MAXSIZE + 2, stdin);
		u1.name[strcspn(u1.name, "\n")] = 0;

		// 메뉴로 이동
		if (u1.name[0] == '~' && strlen(u1.name) == 1) {
			printf("메뉴로 돌아갑니다.\n");
			system("pause");
			return;
		}
		if (strlen(u1.name) > NAME_MAXSIZE) {
			clearInputBuffer();
		}

		if (kreng(u1.name, strlen(u1.name))) {
			if (isContainEng(u1.name)) {
				printf("한글과 영어는 함께 사용할 수 없습니다.\n");
			}
			else {
				printf("올바른 문자를 입력해주세요.\n");
			}
			system("pause");
			continue;
		}
		if (matchKorean(u1.name, strlen(u1.name))) {
			if (!isCompleteKorean(u1.name, strlen(u1.name))) {
				printf("올바른 문자를 입력해주세요.\n");
				system("pause");
				continue;
			}
			if (getLength(u1.name) >= 2 && getLength(u1.name) <= 5) {
				printf("이름 입력이 완료되었습니다.\n");
				system("pause");
				break;
			}
			else {
				printf("한글은 공백을 포함하지 않고 2~5자를 입력해야 합니다.\n");
				system("pause");
				continue;
			}
		}
		else {
			if (matchEngName(u1.name)) {
				if (getLength(u1.name) >= 3 && getLength(u1.name) <= 20) {
					printf("이름 입력이 완료되었습니다.\n");
					system("pause");
					break;
				}
				else {
					printf("영어는 공백을 포함하여 3~20자를 입력해야 합니다.\n");
					system("pause");
					continue;
				}
			}
			else {
				printf("올바른 문자를 입력해주세요.\n");
				system("pause");
				continue;
			}
		}
	}

	// 닉네임 입력
	while (true) {
		system("cls");
		printf("생성할 계정의 닉네임을 입력합니다.\n");
		printf("닉네임에는 한글, 영어, 숫자, 띄어쓰기를 사용할 수 있습니다.(최소2자~최대12자)\n");

		fgets(u1.nick, NICKNAME_MAXSIZE + 2, stdin);
		u1.nick[strcspn(u1.nick, "\n")] = 0;

		if (u1.nick[0] == '~' && strlen(u1.nick) == 1) {
			// 메뉴로 이동
			printf("메뉴로 돌아갑니다.\n");
			system("pause");
			return;
		}
		if (strlen(u1.nick) > NICKNAME_MAXSIZE) {
			clearInputBuffer();
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (duplicateCheck(u1.nick, NICKNAMECHECK)) {
			printf("입력하신 닉네임는 이미 사용 중인 닉네임입니다.\n");
			system("pause");
			continue;
		}
		if (getLength(u1.nick) < 2 || getLength(u1.nick) > 12) {
			printf("닉네임은 한글, 영어, 숫자로 이루어진 2자~12자를 입력해야합니다.\n");
			system("pause");
			continue;
		}
		if (matchNickname(u1.nick)) {
			printf("닉네임 입력이 완료되었습니다.\n");
			system("pause");
			break;
		}
		else {
			printf("올바른 문자를 입력해주세요.\n");
			system("pause");
			continue;
		}

	}

	// 이메일 주소 입력
	while (true) {
		system("cls");
		printf("생성할 계정의 이메일 주소를 입력합니다.");

		fgets(u1.email, EMAILADDRESS_MAXSIZE + 2, stdin);
		u1.email[strcspn(u1.email, "\n")] = 0;

		// 메뉴로 이동
		if (u1.email[0] == '~' && strlen(u1.email) == 1) {
			printf("메뉴로 돌아갑니다.\n");
			system("pause");
			return;
		}
		if (strlen(u1.email) > EMAILADDRESS_MAXSIZE) {
			clearInputBuffer();
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (duplicateCheck(u1.email, EMAILCHECK)) {
			printf("이미 등록된 이메일입니다.\n");
			system("pause");
			continue;
		}

		if (getLength(u1.email) > 30) {
			printf("이메일은 30자를 초과할 수 없습니다.\n");
			system("pause");
			continue;
		}

		if (matchEmail(u1.email)) {
			printf("이메일이 등록되었습니다.\n");
			system("pause");
			break;
		}
		else {
			printf("올바른 형식의 이메일 주소를 입력해주세요.\n");
			system("pause");
			continue;
		}
	}

	//생년월일 입력
	while (true) {
		system("cls");
		printf("생성할 계정의 생년월일을 입력합니다.");

		fgets(tempBirthNumber, BIRTHDAY_MAXSIZE + 2, stdin);
		tempBirthNumber[strcspn(tempBirthNumber, "\n")] = 0;

		// 메뉴로 이동
		if (tempBirthNumber[0] == '~' && strlen(tempBirthNumber) == 1) {
			printf("메뉴로 돌아갑니다.\n");
			system("pause");
			return;
		}
		if (strlen(tempBirthNumber) > BIRTHDAY_MAXSIZE) {
			clearInputBuffer();
		}
		if (isOnlyNumber(tempBirthNumber)) {
			if (strlen(tempBirthNumber) > 8) {
				printf("글자수 범위(숫자 8자) 초과입니다.\n");
				system("pause");
				continue;
			}
			else if (strlen(tempBirthNumber) == 8) {
				if (!isRightDate(tempBirthNumber)) {
					printf("존재하지 않는 날짜입니다.\n");
					system("pause");
					continue;
				}
			}
		}
		if (matchBirthday(tempBirthNumber)) {
			// 윤년 고려해서 없는 날짜 판단
			if (isInTheFuture(tempBirthNumber)) {
				printf("잘못된 생년월일입니다.\n");
				system("pause");
				continue;
			}
			// 프로그램 실행 이후 날짜 판단
			if (!isRightDate(tempBirthNumber)) {
				printf("존재하지 않는 날짜입니다.\n");
				system("pause");
				continue;
			}
			printf("생년월일이 등록되었습니다.\n");
			strcpy_s(u1.birth, BIRTHDAY_MAXSIZE + 2, tempBirthNumber);
			system("pause");
			break;
		}
		else {
			printf("숫자로만 이루어진 8자를 입력해주세요.\n");
			system("pause");
			continue;
		}



	}

	// 휴대폰 번호 입력
	while (true) {
		system("cls");
		printf("생성할 계정의 휴대폰 번호를 입력합니다.");

		fgets(tempPhoneNumber, PHONENUMBER_MAXSIZE + 4, stdin);
		tempPhoneNumber[strcspn(tempPhoneNumber, "\n")] = 0;

		// 메뉴로 이동
		if (tempPhoneNumber[0] == '~' && strlen(tempPhoneNumber) == 1) {
			printf("메뉴로 돌아갑니다.\n");
			system("pause");
			return;
		}
		if (strlen(tempPhoneNumber) > PHONENUMBER_MAXSIZE + 2) {
			clearInputBuffer();
		}
		// fileCheck: 중복된 번호가 있는지 검사하는 함수
		if (duplicateCheck(tempPhoneNumber, PHONENUMBERCHECK)) {
			printf("입력하신 휴대폰 번호는 이미 사용 중인 번호입니다.\n");
			continue;
		}


		if (matchPhoneNumber(tempPhoneNumber)) {
			Eliminate(tempPhoneNumber, '-');
			strcpy_s(u1.phone, PHONENUMBER_MAXSIZE + 2, tempPhoneNumber);
			printf("전화번호 등록이 완료되었습니다.\n");
			system("pause");
			break;
		}
		else {
			if (isOnlyNumber(tempPhoneNumber) && strchr(tempPhoneNumber, '-') || isOnlyNumber(tempPhoneNumber)) {
				printf("전화번호는 10자리 또는 11자리로 입력해주세요.\n");
			}
			else {
				printf("올바르지 않은 문자가 포함되어 있습니다.\n");
			}
			system("pause");
			continue;
		}

	}

	// 추천인 아이디 입력
	while (true) {
		system("cls");
		// 파일에 
		char* retId = malloc(sizeof(char) * ID_MAXSIZE + 2);
		printf("추천인 아이디를 입력합니다.");
		fgets(retId, ID_MAXSIZE + 2, stdin);

		retId[strcspn(retId, "\n")] = 0;

		// 메뉴로 이동
		if (retId[0] == '~' && strlen(retId) == 1) {
			printf("메뉴로 돌아갑니다.\n");
			system("pause");
			return;
		}

		if (strlen(retId) > ID_MAXSIZE) {
			clearInputBuffer();
		}
		if (matchId(retId) && getLength(retId) >= 6 && getLength(retId) <= 12 && duplicateCheck(retId, IDCHECK)) {
			// 해당 아이디의 추천 횟수 증가
			printf("추천인 입력이 완료되었습니다.\n");
			system("pause");
			ret(retId);
			break;
		}
		break;
	}
	system("cls");
	printf("회원가입이 완료되었습니다.\n");
	//showUserInformation(u1);
	writeAccount(u1);
	system("pause");
	return;

}
