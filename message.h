#pragma once
#define ID_MAXSIZE 12
#define TEXT_MAXSIZE 200

typedef struct Message {
	char receiverId[ID_MAXSIZE + 2];
	char senderId[ID_MAXSIZE + 2];
	bool read;
	char text[TEXT_MAXSIZE + 2];
} Message;
int countMessage(char* id);
Message* readMessageFile(char* id, int count);
bool matchMessage(const char* string);
char* writeMessage();
void sendMessage(char* sender, char* receiver);
void showMessage(Message* m, char* id, int count, int index);
Message* showMessageList(char* id);
int findLine(char* id, int count, int flag);
void deleteMessage(char* id, int count, int index);
void readMessage(char* id, int count, int index);
void messageBox(char* id);
