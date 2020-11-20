#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>
#include "projectManagementWork.h"
#include <locale.h>
#include<io.h>
using namespace std;


string getProjectList(string userId, int workNum = 0) {
	string projectList[10];
	int i = 0, selectProject = 0;
	ifstream readFile;
	readFile.open("projectList.txt");

	if (readFile.is_open()) {

		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);

			string originData = tmp;

			int findIndex = originData.find("-");
			originData = originData.substr(findIndex+1, originData.length());

			if (originData.find(userId) <= originData.length()) {
				projectList[i] = strtok(tmp, " -");
				i++;
			}
		}

		readFile.close();
	}

	if (workNum == 1) {
		cout << "---���� ������Ʈ ���---------------------------------------" << endl;
		for (int j = 0; j < i; j++) {
			cout << j + 1 << "." << projectList[j] << endl;
		}
		cout << "------------------------------------------------------------" << endl;

		cout << ">>";
		cin >> selectProject;

		return projectList[selectProject - 1] + ".txt";
	}
	return "";
}

string loadProjectList(string userId) {
	return getProjectList(userId, 1);	
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

	string comeUserId;
	cout << "�ʴ��� ���̵� �Է����ּ��� : ";
	cin >> comeUserId;

	
	ifstream readFile;
//	writeFile.open("projectList.txt");
	readFile.open("projectList.txt");

	if (readFile.is_open()) {

		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);

			string orginData = tmp;

			cout << orginData << endl;

			if (orginData.find("new") >= 0) {
				 strcat(tmp, ",");
				 strcat(tmp, comeUserId.c_str());

				 //istringstream readFile(tmp);
				 string buffer;


				cout << tmp << endl;

				 //readFile.write(tmp, sizeof(tmp));
			}
		}
		readFile.close();
		//writeFile.close();
	}
}

void applyProjectParticipation(string userId) {
	string writeProjectName;

	cout << "������ ������Ʈ���� �Է����ּ��� : ";
	cin >> writeProjectName;

	ofstream writeFile;
	writeFile.open("userWatingList.txt", ios::app);

	//������Ʈ ��Ͽ� ���� �ÿ��� ���� �����ص��� ��
	string userWating = writeProjectName + "-" + userId;

	writeFile.write(userWating.c_str(), userWating.size());
	writeFile.close();
}

void createNewProject(string userId) {
	string projectName;
	cout << "������Ʈ ���� �Է����ּ���: ";
	cin >> projectName;

	ofstream writeFile;
	writeFile.open(projectName + ".txt");
	writeFile.close();

	writeFile.open("projectList.txt", ios::app);
	
	string addProject = (_access("projectList.txt", 0) == 0)? "\n" + projectName + "-" + userId : projectName + "-" + userId;

	writeFile.write(addProject.c_str(), addProject.size());
	writeFile.close();
}
