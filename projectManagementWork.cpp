#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>
#include "projectManagementWork.h"
#include <locale.h>
using namespace std;

string loadProjectList(string userId) {

	string projectList[50];
	int i = 0, selectProject;
	
	ifstream readFile;
	readFile.open("projectList.txt");

	if (readFile.is_open()) {
		
		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);

			string orginData = tmp;

			if (orginData.find(userId) >= 0) {
				projectList[i] = strtok(tmp, "-");
				i++;
			}
		}

		readFile.close(); 
	}
	
	cout << "---���� ������Ʈ ���---------------------------------------" << endl;
	for (int j = 0; j < i; j++) {
		cout << j+1 << "." << projectList[j] << endl;
	}
	cout << "------------------------------------------------------------" << endl;
	
	cout << ">>";
	cin >> selectProject;

	return projectList[selectProject - 1] + ".txt";
}

void projectUser(char  projectName[]) {
	string projectList[50];

	ifstream readFile;
	readFile.open("projectList.txt");    //���� ����

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);

			string orginData = tmp;

			char* projectName = strtok(tmp, "-");

			//if (strcmp(check, user) == 0) { return check; }//������ ���� ���ڿ� �ٷ� ���.
		}
		readFile.close();    //���� �ݾ��ݴϴ�.
	}
}

void inviteTeamPlayer(string userId) {
	
	string writeProjectName;

	cout << "������ ������Ʈ���� �Է����ּ��� : ";
	cin >> writeProjectName;

	fstream readFile;
	readFile.open("projectList.txt");

	if (readFile.is_open()) {

		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);

			string orginData = tmp;

			cout << orginData.find(writeProjectName);

			if (orginData.find(writeProjectName) >= 0) {
				 strcpy(tmp, ",");
				 strcpy(tmp, userId.c_str());
				 readFile.write(tmp, sizeof(tmp));
			}
		}
		readFile.close();
	}
}

void applyProjectParticipation(string userId) {

}

void createdNewProject() {
	char projectName[256] = "";
	cout << "������Ʈ ���� �Է����ּ���: ";
	cin >> projectName;
}
