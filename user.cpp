#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>
#include "user.h"
using namespace std;

void newUser() {
	char newUserId[30] = "", newUserPw[30] = "", newUserPos[5] = "";
	
	ofstream writeFile;
	writeFile.open("user.txt", ios::app);
	
	cout << "���̵�: ";
	cin >> newUserId;
	cout << "��й�ȣ: ";
	cin >> newUserPw;
	cout << "������ tl, ������ tp�� �Է����ּ���";
	cin >> newUserPos;

	strcat(newUserId, "-");
	strcat(newUserId, newUserPw);
	strcat(newUserId, " ");
	strcat(newUserId, newUserPos);
	strcat(newUserId, "\n");

	string newUser = newUserId;
	writeFile.write(newUser.c_str(), newUser.size());
	writeFile.close();
}

string checkUser(char* user) {
	ifstream readFile;
	readFile.open("user.txt"); 

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);

			string orginData = tmp;

			char* check = strtok(tmp, " ");

			cout << "check : " << check << endl;

			if (strcmp(check, user) == 0) { return orginData; }//������ ���� ���ڿ� �ٷ� ���.
		}
		readFile.close();    //���� �ݾ��ݴϴ�.
	}

	return "";
}
User login(int selectUser) {
	char userId[50] = "", userPw[50] = "";
	
	if (selectUser == 0) newUser();

	cout << "\n----�α���---------------------------" << endl;
	cout << "���̵�: ";
	cin >> userId;
	cout << "��й�ȣ: ";
	cin >> userPw;

	strcat(userId, "-");
	strcat(userId, userPw);
	
	string checkResult = checkUser(userId);

	while (checkResult.c_str() == "") {
		cout << "���̵� ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ���." << endl;
		cout << "���̵�: ";
		cin >> userId;
		cout << "��й�ȣ: ";
		cin >> userPw;

		strcat(userId, "-");
		strcat(userId, userPw);
	}

	char* check = new char[checkResult.size()];
	strncpy(check, checkResult.c_str(), sizeof(check));

	User user;
	user.position = checkResult.substr(checkResult.size() - 2, 2);
	user.id = strtok(check, "-");
	

	return user;
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