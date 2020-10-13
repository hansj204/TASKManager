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
	
	cout << "---참여 프로젝트 목록---------------------------------------" << endl;
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
	
	string writeProjectName;

	cout << "참여할 프로젝트명을 입력해주세요 : ";
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
	cout << "프로젝트 명을 입력해주세요: ";
	cin >> projectName;
}
