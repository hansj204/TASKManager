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

	newUser = newUserId + "-" + newUserPw + " " + newUserPos;

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

			string orginData = tmp;

			if (user.compare(strtok(tmp, " ")) == 0) { return orginData; }
		}
		readFile.close();
	}

	return "";
}
User login(int selectUser) {
	string user, userId, userPw;
	
	if (selectUser == 0) newUser();

	cout << "\n----�α���---------------------------" << endl;
	cout << "���̵�: ";
	cin >> userId;
	cout << "��й�ȣ: ";
	cin >> userPw;

	user += userId + "-" + userPw;
	
	string checkResult = checkUser(user);

	while (checkResult.c_str() == "") {
		cout << "���̵� ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ���." << endl;
		cout << "���̵�: ";
		cin >> userId;
		cout << "��й�ȣ: ";
		cin >> userPw;

		user += userId + "-" + userPw;
	}

	char* check = new char[checkResult.size()];
	strncpy(check, checkResult.c_str(), sizeof(check));

	User member;
	member.position = checkResult.substr(checkResult.size() - 2, 2);
	member.id = strtok(check, "-");
	
	return member;
}

//cout << tempUser << endl;

	//char* Id = strtok(check, "-");

	/*string projectList[30] = { "newProject1", "newProject2" };

	User user;
	user.id = "user";

	while (tok2 != NULL) {
		if(i == 0) user.id = strtok(tok2, ",");
		else {
			propjectList[j] = tok2;
			j++;
		}

		i++;
		cout << tok2 << endl;
		tok2 = strtok(NULL, " ");
	}

	for (int i = 0; i < 5; i++) {
		cout << i << " : "<< propjectList[i] << endl;
	}*/