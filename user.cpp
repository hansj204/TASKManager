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
	
	cout << "���̵�: ";
	cin >> newUserId;
	cout << "��й�ȣ: ";
	cin >> newUserPw;
	cout << "������ tl, ������ tp�� �Է����ּ���";
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

	cout << "\n----�α���---------------------------" << endl;

	do {
		cout << "���̵�: ";
		cin >> userId;
		cout << "��й�ȣ: ";
		cin >> userPw;

		user = userId + "-" + userPw;
		checkResult = checkUser(user);

		if(checkResult == "") 
			cout << "\n���̵� ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ���." << endl;

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