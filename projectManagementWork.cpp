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
	int inviteType;
	string invitePermit;

	string inviteProjectName = getProjectList(userId, 1);
	char* projectName = new char[inviteProjectName.length() + 1];
	strcpy(projectName, inviteProjectName.c_str());
	projectName = strtok(projectName, ".");

	/*int findIndex = inviteProjectName.find(".");
	inviteProjectName = inviteProjectName.substr(findIndex + 1, inviteProjectName.length());*/

	cout << "1. ��� ������ ����\t2. �ʴ�" << endl;
	cin >> inviteType;

	if (inviteType == 1) {
		ifstream readFile;
		readFile.open("userWatingList.txt");

		if (readFile.is_open()) {

			while (!readFile.eof()) {
				char tmp[256];
				readFile.getline(tmp, 256);

				if (readFile.eof()) break;

				string orginData = tmp;
				if (strcmp(strtok(tmp, "-"), projectName) >= 0) {

					int findIndex = orginData.find("-");
					string name = orginData.substr(findIndex + 1, orginData.length());

					cout << "������� ������: " << name << endl;
					cout << "���� ������ Y, ������ N�� �Է����ּ���\n >> ";
					cin >> invitePermit;

					if (invitePermit == "Y") 
						insertProjectUser(projectName, name);					
				}
			}
			readFile.close();
		}
	}
	else {
		string comeUserId;
		cout << "�ʴ��� ���̵� �Է����ּ��� : ";
		cin >> comeUserId;
		insertProjectUser(projectName, comeUserId);
	}

}

void applyProjectParticipation(string userId) {
	string writeProjectName;

	cout << "������ ������Ʈ���� �Է����ּ��� : ";
	cin >> writeProjectName;

	ofstream writeFile;
	writeFile.open("userWatingList.txt", ios::app);

	//������Ʈ ��Ͽ� ���� �ÿ��� ���� �����ص��� ��
	string userWating = writeProjectName + "-" + userId + "\n";

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

void insertProjectUser(char* projectName, string name) {
	int pos = 0;

	ifstream readFile;
	readFile.open("projectList.txt");

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);

			string orginData = tmp;

			if (strcmp(projectName, strtok(tmp, "-")) == 0) {
				break;
			}
			pos += orginData.size();
		}
		readFile.close();
	}

	ofstream writeFile;
	writeFile.open("projectList.txt", ios::app);
	writeFile.seekp(3);
	writeFile.write(("," + name).c_str(), ("," + name).size());
	writeFile.close();
}
