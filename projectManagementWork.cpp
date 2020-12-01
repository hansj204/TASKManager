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

void projectUser(char  projectName[]) {
	string projectList[50];

	ifstream readFile;
	readFile.open("projectList.txt");    //파일 열기

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);

			string orginData = tmp;

			char* projectName = strtok(tmp, "-");

			//if (strcmp(check, user) == 0) { return check; }//지금은 읽은 문자열 바로 출력.
		}
		readFile.close();    //파일 닫아줍니다.
	}
}

void inviteTeamPlayer(string userId) {
	int inviteType;

	char *inviteProjectName = strcpy(inviteProjectName, getProjectList(userId, 1).c_str());
	cout << inviteProjectName << endl;
	strtok(inviteProjectName, ".");

	/*int findIndex = inviteProjectName.find(".");
	inviteProjectName = inviteProjectName.substr(findIndex + 1, inviteProjectName.length());*/

	cout << inviteProjectName << endl;

	cout << "1. 대기 참여자 수락\t2. 초대" << endl;
	cin >> inviteType;

	if (inviteType == 1) {
		ifstream readFile;
		//	writeFile.open("projectList.txt");
		readFile.open("userWatingList.txt");

		if (readFile.is_open()) {

			while (!readFile.eof()) {
				char tmp[256];
				readFile.getline(tmp, 256);

				if (readFile.eof()) break;

				string orginData = tmp;
				cout << orginData.find(inviteProjectName) << endl;

				if (orginData.find(inviteProjectName) >= 0) {
					cout << tmp << endl;


					//istringstream readFile(tmp);



					//readFile.write(tmp, sizeof(tmp));
				}
			}
			readFile.close();
			//writeFile.close();
		}
	}
	else {
		string comeUserId;
		cout << "초대할 아이디를 입력해주세요 : ";
		cin >> comeUserId;
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
