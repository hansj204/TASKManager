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
		cout << "---참여 프로젝트 목록---------------------------------------" << endl;
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

void inviteTeamPlayer(string userId) {
	int inviteType;
	string invitePermit;

	string inviteProjectName = getProjectList(userId, 1);
	char* projectName = new char[inviteProjectName.length() + 1];
	strcpy(projectName, inviteProjectName.c_str());
	projectName = strtok(projectName, ".");


	cout << "1. 대기 참여자 수락\t2. 초대" << endl;
	cin >> inviteType;

	if (inviteType == 1) {
		string tempData;
		ifstream readFile;
		readFile.open("userWatingList.txt");

		if (readFile.is_open()) {

			while (!readFile.eof()) {
				char tmp[256];
				readFile.getline(tmp, 256);

				if (readFile.eof()) break;

				string originData = tmp;
				if (strcmp(strtok(tmp, "-"), projectName) >= 0) {

					string userName = originData;
					int findIndex = userName.find("-");
					string name = userName.substr(findIndex + 1, userName.length());

					cout << "대기중인 참여자: " << name << endl;
					cout << "참여 수락은 Y, 거절은 N을 입력해주세요\n >> ";
					cin >> invitePermit;

					if (invitePermit == "Y") {
						insertProjectUser(projectName, name);
						continue;
					}
				}

				tempData = tempData + originData;
				cout << tempData << endl;
			}
			readFile.close();
		}

		cout << tempData << endl;

		ofstream writeFile;
		writeFile.open("userWatingList.txt");
		writeFile.write(tempData.c_str(), tempData.size());
		writeFile.close();

	}
	else {
		string comeUserId;
		cout << "초대할 아이디를 입력해주세요 : ";
		cin >> comeUserId;
		insertProjectUser(projectName, comeUserId);
	}

}

void applyProjectParticipation(string userId) {
	string writeProjectName;

	cout << "참여할 프로젝트명을 입력해주세요 : ";
	cin >> writeProjectName;

	ofstream writeFile;
	writeFile.open("userWatingList.txt", ios::app);

	//프로젝트 목록에 있을 시에만 저장 가능해도록 함
	string userWating = writeProjectName + "-" + userId + "\n";

	writeFile.write(userWating.c_str(), userWating.size());
	writeFile.close();
}

void createNewProject(string userId) {
	string projectName;
	cout << "프로젝트 명을 입력해주세요: ";
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
	string tempData;
	ifstream readFile;
	readFile.open("projectList.txt");

	if (readFile.is_open()) {
		while (!readFile.eof()) {

			if (readFile.eof()) break;

			char tmp[256];
			readFile.getline(tmp, 256);

			string orginData = tmp;

			if (strcmp(projectName, strtok(tmp, "-")) == 0) 
				orginData = orginData + "," + name;
			
			tempData += "\n" + orginData;
		}
		readFile.close();
	}

	int findIndex = tempData.find_last_of("\n");
	tempData = tempData.substr(1, tempData.size());

	cout << tempData << endl;

	ofstream writeFile;
	writeFile.open("projectList.txt");
	writeFile.write(tempData.c_str(), tempData.size());
	writeFile.close();
}
