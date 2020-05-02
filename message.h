#pragma once
#define ID_MAXSIZE 12
#define TEXT_MAXSIZE 200

typedef struct Message {
	char senderId[ID_MAXSIZE + 2];
	char receiverId[ID_MAXSIZE + 2];
	bool read;
	char text[TEXT_MAXSIZE + 2];
} Message;
int countMessage(char* id);
Message* readMessage(char* id);
bool matchMessage(const char* string);
char* writeMessage();
void sendMessage(char* sender, char* receiver);
void deleteMessage(Message* m);
void showMessage(Message* m, char* id, int num);
Message* showMessageList(char* id);
void messageBox(char* id);
void readMessage(const char*)
