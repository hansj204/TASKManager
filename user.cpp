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
	cout << "���̵�: ";
	cin >> newUserId;
	cout << "��й�ȣ: ";
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
	readFile.open("user.dat");    //���� ����

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);
			char* check = strtok(tmp, " ");
			cout << check << endl;
			if (strcmp(check, user) == 0) { return true; }//������ ���� ���ڿ� �ٷ� ���.
		}
		readFile.close();    //���� �ݾ��ݴϴ�.
	}

	return false;
}
void login(int selectUser) {
	char userId[100] = "", userPw[100] = "";
	string propjectList[100];
	int i = 0, j = 0;
	if (selectUser == 0) newUser();

	cout << "\n----�α���---------------------------" << endl;
	cout << "���̵�: ";
	cin >> userId;
	cout << "��й�ȣ: ";
	cin >> userPw;

	strcat(userId, "-");
	strcat(userId, userPw);
	
	while (!checkUser(userId)) {
		cout << "���̵� ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ���." << endl;
		cout << "���̵�: ";
		cin >> userId;
		cout << "��й�ȣ: ";
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