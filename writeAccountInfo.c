// 계정 구조체를 accountlist.txt에 저장
void writeAccountInfo(Account user) {
	FILE* fp;
	fp = fopen("accountlist.txt", "a+");
	if (fp == NULL) {
		printf("파일지정 경로를 확인해주세요.\n");
		exit(1);
	}
	else {
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%d,%d,%d\n",
			user.name, user.pw, user.name, user.nick, user.email, user.birth, user.phone, user.rec, user.lock, user.admin);
		printf("위의 정보를 저장하였습니다.\n");
	}
	fclose(fp);
}
