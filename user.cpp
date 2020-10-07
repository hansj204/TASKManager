#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>

struct User{
	char *id;
	//string projectList[100];
};

using namespace std;

void newUser() {
	ofstream writeFile;
	writeFile.open("user.dat");
	char newUserId[100] = "", newUserPw[100] = "";
	cout << "아이디: ";
	cin >> newUserId;
	cout << "비밀번호: ";
	cin >> newUserPw;

	strcat(newUserId, "-");
	strcat(newUserId, newUserPw);
	strcat(newUserId, " ");
	strcat(newUserId, "newProject");
	strcat(newUserId, " ");
	strcat(newUserId, "newProject");
	strcat(newUserId, " ");
	strcat(newUserId, "newProject");

	string newUser = newUserId;
	writeFile.write(newUser.c_str(), newUser.size());
	writeFile.close();
}

bool checkUser(char* user) {
	ifstream readFile;
	readFile.open("user.dat");    //파일 열기

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);
			char* check = strtok(tmp, " ");
			cout << check << endl;
			if (strcmp(check, user) == 0) { return true; }//지금은 읽은 문자열 바로 출력.
		}
		readFile.close();    //파일 닫아줍니다.
	}

	return false;
}
void login(int selectUser) {
	char userId[100] = "", userPw[100] = "";
	string propjectList[100];
	int i = 0, j = 0;
	if (selectUser == 0) newUser();

	cout << "\n----로그인---------------------------" << endl;
	cout << "아이디: ";
	cin >> userId;
	cout << "비밀번호: ";
	cin >> userPw;

	strcat(userId, "-");
	strcat(userId, userPw);
	
	while (!checkUser(userId)) {
		cout << "아이디나 비밀번호가 틀렸습니다. 다시 입력해주세요." << endl;
		cout << "아이디: ";
		cin >> userId;
		cout << "비밀번호: ";
		cin >> userPw;

		strcat(userId, "-");
		strcat(userId, userPw);
	}

	char* tok2 = strtok(userId, "-");
	
	User user;
	
	while (tok2 != NULL) {
		if(i == 0) user.id = tok2;
		else {
			propjectList[j] = tok2;
			j++;
		}

		i++;
		cout << tok2 << endl;
		tok2 = strtok(NULL, " ");
	}

	for (int i = 0; i < 2; i++) {
		cout << i << " : "<< propjectList[i] << endl;
	}

	/*strcpy(user.projectList, propjectList);*/
}