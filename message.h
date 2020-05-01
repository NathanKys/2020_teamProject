#pragma once
#define ID_MAXSIZE 12
#define text_MAXSIZE 200

typedef struct Message {
	char senderId[ID_MAXSIZE + 2];
	char receiverId[ID_MAXSIZE + 2];
	bool read;
	char text[text_MAXSIZE + 2];
} Message;
