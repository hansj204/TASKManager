#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>
#include "user.h"
using namespace std;

void newUser() {
	string newUser, newUserId, newUserPw, newUserPos;
	ofstream writeFile;
	writeFile.open("user.txt", ios::app);
	
	cout << "아이디: ";
	cin >> newUserId;
	cout << "비밀번호: ";
	cin >> newUserPw;
	cout << "팀장은 tl, 팀원은 tp를 입력해주세요";
	cin >> newUserPos;

	newUser = newUserId + "-" + newUserPw + " " + newUserPos + "\n";

	writeFile.write(newUser.c_str(), newUser.size());
	writeFile.close();
}

string checkUser(string user) {
	ifstream readFile;
	readFile.open("user.txt"); 

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);

			if (readFile.eof()) break;

			string orginData = tmp;

			if (user.compare(strtok(tmp, " ")) == 0) { return orginData; }
		}
		readFile.close();
	}

	return "";
}
User login(int selectUser) {
	string user, userId, userPw, checkResult;
	
	if (selectUser == 0) newUser();

	cout << "\n----로그인---------------------------" << endl;

	do {
		cout << "아이디: ";
		cin >> userId;
		cout << "비밀번호: ";
		cin >> userPw;

		user = userId + "-" + userPw;
		checkResult = checkUser(user);

		if(checkResult == "") 
			cout << "\n아이디나 비밀번호가 틀렸습니다. 다시 입력해주세요." << endl;

	} while (checkResult == "");

	char* check = new char[checkResult.size()];
	strncpy(check, checkResult.c_str(), sizeof(check));

	User member;
	member.position = checkResult.substr(checkResult.size() - 2, 2);
	member.id = strtok(check, "-");

	delete[] check;

	system("cls");
	
	return member;
}