#include "header.h"


int pow(int a, int b) {
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

// 미완성
bool matchPassword(const char* string) {
	// 8~16자
	// 대소문자, 숫자 하나 이상 무조건 포함
	// 허용하는 특수문자?
	regex_t state;
	const char* pattern = "[A-Z]{1,}[a-z]{1,}[0-9]{1,}";

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

// 임시로 파일체크하는 함수
bool fileCheck() {
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
		year += ((string[index] - '0') * pow(10, 3 - index));
	}
	for (index;index < 6;index++) {
		month += ((string[index] - '0') * pow(10, 5 - index));
	}

	for (index;index < 8;index++) {
		day += ((string[index] - '0') * pow(10, 7 - index));
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

	if (year > (tm.tm_year+1900)) {
		return true;
	}
	else if (year == (tm.tm_year+1900)) {
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

void signUp(Account u1) {
	u1.admin = false;
	u1.lock = false;


	// 아이디 입력
	while (true) {
		printf("생성할 계정의 아이디를 입력합니다.");
		fgets(u1.id, ID_MAXSIZE + 2, stdin);

		u1.id[strcspn(u1.id, "\n")] = 0;

		// 메뉴로 이동
		if (u1.id[0] == '~') {
			exit(1);
		}

		if (strlen(u1.id) > ID_MAXSIZE) {
			clearInputBuffer();
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (fileCheck(u1.id)) {
			printf("입력하신 아이디는 이미 사용 중인 아이디입니다.\n");
			continue;
		}

		if (matchId(u1.id)) {
			if (getLength(u1.id) > ID_MAXSIZE || getLength(u1.id) < 6) {
				printf("글자수 범위(최소6자 ~ 최대 12자)초과입니다.\n");
				continue;
			}
			else {
				printf("아이디 입력이 완료되었습니다.\n");
				break;
			}
		}
		else {
			printf("올바른 문자를 입력해주세요.\n");
		}

	}
	// 비밀번호 입력 (미완성)
	/*

	while (true) {
		break;
	}
	*/
	// 비밀번호 확인 (미완성)
	/*while (true) {
		char checkPassword[PASSWORD_MAXSIZE];
		fgets(checkPassword, PASSWORD_MAXSIZE + 2, stdin);
		if (strlen(checkPassword) > PASSWORD_MAXSIZE) {
			clearInputBuffer();
		}

		// 메뉴로 이동
		if (checkPassword[0] == '~') {
			exit();
		}

		if (u1.pw != checkPassword) {
			printf("비밀번호를 다시 확인해주세요!\n");
			continue;
		}
		else {
			printf("비밀번호 확인이 완료되었습니다.\n");
		}
	}*/

	// 이름 입력
	while (true) {
		printf("이름을 입력합니다.");
		fgets(u1.name, NAME_MAXSIZE + 2, stdin);
		u1.name[strcspn(u1.name, "\n")] = 0;

		// 메뉴로 이동
		if (u1.name[0] == '~') {
			exit(1);
		}
		if (strlen(u1.name) > NAME_MAXSIZE) {
			clearInputBuffer();
		}

		if (kreng(u1.name, strlen(u1.name))) {
			if (isContainEng(u1.name)) {
				printf("한글과 영어는 함께 사용할 수 없습니다.\n");
				continue;
			}
			else {
				printf("올바른 문자를 입력해주세요.\n");
				continue;
			}

		}
		if (matchKorean(u1.name, strlen(u1.name))) {
			if (!isCompleteKorean(u1.name, strlen(u1.name))) {
				printf("올바른 문자를 입력해주세요.\n");
				continue;
			}
			if (getLength(u1.name) >= 2 && getLength(u1.name) <= 5) {
				printf("이름 입력이 완료되었습니다.\n");
				break;
			}
			else {
				printf("한글은 공백을 포함하지 않고 2~5자를 입력해야 합니다.\n");
				continue;
			}
		}
		else {
			if (matchEngName(u1.name)) {
				if (getLength(u1.name) >= 3 && getLength(u1.name) <= 20) {
					printf("이름 입력이 완료되었습니다.\n");
					break;
				}
				else {
					printf("영어는 공백을 포함하여 3~20자를 입력해야 합니다.\n");
					continue;
				}
			}
			else {
				printf("올바른 문자를 입력해주세요.\n");
			}
		}
	}

	// 닉네임 입력
	while (true) {
		printf("생성할 계정의 닉네임을 입력합니다.\n");
		printf("닉네임에는 한글, 영어, 숫자, 띄어쓰기를 사용할 수 있습니다.\n");

		fgets(u1.nick, NICKNAME_MAXSIZE + 2, stdin);
		u1.nick[strcspn(u1.nick, "\n")] = 0;

		if (u1.nick[0] == '~') {
			// 메뉴로 이동
			exit(1);
		}
		if (strlen(u1.nick) > NICKNAME_MAXSIZE) {
			clearInputBuffer();
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (fileCheck(u1.nick)) {
			printf("입력하신 닉네임는 이미 사용 중인 아이디입니다.\n");
			continue;
		}
		if (getLength(u1.nick) < 2 || getLength(u1.nick) > 12) {
			printf("닉네임은 한글, 영어, 숫자로 이루어진 2자~12자를 입력해야합니다.\n");
			continue;
		}
		if (matchNickname(u1.nick)) {
			printf("닉네임 입력이 완료되었습니다.\n");
			break;
		}
		else {
			printf("올바른 문자를 입력해주세요.\n");
			continue;
		}

	}

	// 이메일 주소 입력
	while (true) {
		printf("생성할 계정의 이메일 주소를 입력합니다.");

		fgets(u1.email, EMAILADDRESS_MAXSIZE + 2, stdin);
		u1.email[strcspn(u1.email, "\n")] = 0;

		// 메뉴로 이동
		if (u1.email[0] == '~') {
			exit(1);
		}
		if (strlen(u1.email) > EMAILADDRESS_MAXSIZE) {
			clearInputBuffer();
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (fileCheck(u1.email)) {
			printf("이미 등록된 이메일입니다.\n");
			continue;
		}

		if (getLength(u1.email) > 30) {
			printf("이메일은 30자를 초과할 수 없습니다.\n");
			continue;
		}

		if (matchEmail(u1.email)) {
			printf("이메일이 등록되었습니다.\n");
			break;
		}
		else {
			printf("올바른 형식의 이메일 주소를 입력해주세요.\n");
			continue;
		}
	}
	// 생년월일 입력
	while (true) {
		printf("생성할 계정의 생년월일을 입력합니다.");

		fgets(u1.birth, BIRTHDAY_MAXSIZE + 2, stdin);
		u1.birth[strcspn(u1.birth, "\n")] = 0;

		// 메뉴로 이동
		if (u1.birth[0] == '~') {
			exit(1);
		}
		if (strlen(u1.birth) > BIRTHDAY_MAXSIZE) {
			clearInputBuffer();
		}
		if (isOnlyNumber(u1.birth)) {
			if (strlen(u1.birth)>8) {
				printf("글자수 범위(숫자 8자) 초과입니다.\n");
				continue;
			}
			else if (strlen(u1.birth) == 8) {
				if (!isRightDate(u1.birth)) {
					printf("존재하지 않는 날짜입니다.\n");
					continue;
				}
			}
		}
		if (matchBirthday(u1.birth)) {
			// 윤년 고려해서 없는 날짜 판단
			if (isInTheFuture(u1.birth)) {
				printf("잘못된 생년월일입니다.\n");
				continue;
			}
			// 프로그램 실행 이후 날짜 판단
			if (!isRightDate(u1.birth)) {
				printf("존재하지 않는 날짜입니다.\n");
				continue;
			}
			printf("생년월일이 등록되었습니다.\n");
			break;
		}
		else {
			
			printf("숫자로만 이루어진 8자를 입력해주세요.\n");
			continue;
		}



	}

	// 휴대폰 번호 입력
	while (true) {
		printf("생성할 계정의 휴대폰 번호를 입력합니다.");

		fgets(u1.phone, PHONENUMBER_MAXSIZE + 2, stdin);
		u1.phone[strcspn(u1.phone, "\n")] = 0;

		// 메뉴로 이동
		if (u1.phone[0] == '~') {
			exit(1);
		}
		if (strlen(u1.phone) > PHONENUMBER_MAXSIZE) {
			clearInputBuffer();
		}
	}

	// 추천인 아이디 입력
	while (true) {
		// 파일에 
		char* retId = malloc(sizeof(char)*ID_MAXSIZE+2);
		printf("추천인 아이디를 입력합니다.");
		fgets(retId, ID_MAXSIZE + 2, stdin);

		retId[strcspn(retId, "\n")] = 0;

		// 메뉴로 이동
		if (retId[0] == '~') {
			exit(1);
		}

		if (strlen(retId) > ID_MAXSIZE) {
			clearInputBuffer();
		}
		if (matchId(retId)&& getLength(retId) >= 6 && getLength(retId) <= 12&& fileCheck(retId)) {
			// 해당 아이디의 추천 횟수 증가
			break;
		}
		break;
	}

	printf("회원가입이 완료되었습니다.");
	showUserInformation(u1);
	// 파일에 구조체 쓰기
	// 초기 메뉴로 이동

}
