#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>
#include "projectManagementWork.h"
#include "taskManagementWork.h"
#include <locale.h>
#include<io.h>
#include <vector>
#include <codecvt>
#include<sstream>
#include<experimental/filesystem>
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
		cout << "(프로젝트 작업 돌아가기를 원하면 0을 입력해 주세요.)" << endl;
		cout << ">> ";
		cin >> selectProject;

		if (selectProject == 0) {
			system("cls");
			return "";
		}

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

	cout << "------------------------------------------------------------" << endl;
	cout << "1. 대기 참여자 수락\t2. 초대" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << ">>";
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
			}
			readFile.close();
		}

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
	string projectName, projectStartDate, projectEndDate;
	cout << "프로젝트 명을 입력해주세요: ";
	cin >> projectName;
	cout << "프로젝트 시작일을 입력해주세요: ";
	cin >> projectStartDate;
	cout << "프로젝트 마감일을 입력해주세요: ";
	cin >> projectEndDate;

	ofstream writeFile;
	writeFile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t, 0x10ffff, generate_header>));
	writeFile.open(projectName + ".txt");

	string projectPeriod = projectStartDate + " ~ " + projectEndDate + "\n";
	string projectLeader = userId + "(tl)" + "\n";

	writeFile.write("==========================================\n", 43);
	writeFile.write(projectPeriod.c_str(), projectPeriod.size());
	writeFile.write(projectLeader.c_str(), projectLeader.size());
	writeFile.write("==========================================\n", 43);
	writeFile.close();

	writeFile.open("projectList.txt", ios::app);
	string addProject = (_access("projectList.txt", 0) == 0) ? "\n" + projectName + "-" + userId : projectName + "-" + userId;
	writeFile.write(addProject.c_str(), addProject.size());

	writeFile.close();

}

namespace fs = std::experimental::filesystem::v1;

void deleteProject(string userId) {

	string deleteProjectName = getProjectList(userId, 1);
	string againprojectName;
	cout << "삭제를 원하는 프로젝트를 입력하여 주세요 : ";
	cin >> againprojectName;

	if (deleteProjectName.substr(0, deleteProjectName.size() - 4) == againprojectName) {

		fs::path currentPath = fs::current_path();
		fs::remove(againprojectName + ".txt");

		//파일 목록에서 제거
		vector<string> projectList;
		int i = 0, selectProject = 0;
		ifstream readFile;
		readFile.open("projectList.txt");

		if (readFile.is_open()) {

			while (!readFile.eof()) {
				char tmp[256];
				readFile.getline(tmp, 256);

				string originData = tmp;
				if (strtok(tmp, " -") != againprojectName) projectList.push_back(originData);

			}

			readFile.close();
		}

		ofstream writeFile;
		writeFile.open("projectList.txt");

		for (int i = 0; i < projectList.size(); i++) {
				writeFile.write(projectList[i].c_str(), projectList[i].size());
		}

		writeFile.close();
	}
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

	ofstream writeFile;
	writeFile.open("projectList.txt");
	writeFile.write(tempData.c_str(), tempData.size());
	writeFile.close();
}

void modifyProject(string userId) {

	string changeProjectName, projectStartDate, projectEndDate, stringBuffer, answer;
	vector<string> projectInfo;
	vector<TASK> projectTask;
	int i = 0, taskCount = 0;
	ifstream readFile;

	//프로젝트 이름 수정
	string oldProjectName = getProjectList(userId, 1);
	cout << "새 프로젝트 이름을 입력해 주세요(원치 않으면 .을 입력하여 주세요.) : " << endl;
	cin >> changeProjectName;
	if (changeProjectName != ".") rename(oldProjectName.substr(0, oldProjectName.size() - 4).c_str(), changeProjectName.c_str());


	//프로젝트 기간 수정
	string projectName = ((changeProjectName != ".") ? changeProjectName : oldProjectName);
	cout << projectName << "프로젝트 기간을 수정하시겠습니까(Y/N)?.\n" << endl;
	cin >> answer;

	cout << "프로젝트 시작일을 입력해주세요(수정을 원치 않으면 .을 입력하여 주세요) : ";
	cin >> projectStartDate;
	cout << "프로젝트 마감일을 입력해주세요(수정을 원치 않으면 .을 입력하여 주세요) : ";
	cin >> projectEndDate;

	if (answer == "Y") {
		readFile.open(oldProjectName + ".txt");
		projectInfo.clear();

		if (readFile.is_open()) {

			while (!readFile.eof()) {
				char tmp[256];
				i = 0;

				readFile.getline(tmp, 256);
				string orginData = tmp;

				if (taskCount < 4) {
					istringstream ss(orginData);
					if (taskCount == 1) {
						projectInfo.push_back(strtok(tmp, " ~ "));
					}
					if (taskCount == 2) { projectInfo.push_back(tmp); }
					continue;
				}

				char* token = strtok(tmp, "||");

				while (token != NULL) {
					switch (i) {
					case 0: projectTask[taskCount].taskname = token; break;
					case 1: projectTask[taskCount].startDate = token; break;
					case 2: projectTask[taskCount].endDate = token; break;
					case 3: projectTask[taskCount].progress = atoi(token); break;
					case 4: projectTask[taskCount].finishDate = token; break;
					case 5: projectTask[taskCount].manager = token; break;
					}
					token = strtok(NULL, "||");
					i++;
				}

				++taskCount;
			}

			readFile.close();
		}

		ofstream writeFile;
		writeFile.open(projectName + ".txt");

		string projectPeriod = projectStartDate + " ~ " + projectEndDate + "\n";

		writeFile.write("==========================================\n", 43);
		writeFile.write(projectPeriod.c_str(), projectPeriod.size());
		writeFile.write((projectInfo[1] + "\n").c_str(), (projectInfo[1] + "\n").size());
		writeFile.write("==========================================\n", 43);

		for (int i = 0; i < projectTask.size(); i++) {
			string udpdateTaskInfo = projectTask[i].taskname + "||" + projectTask[i].startDate + "||" + projectTask[i].endDate + "||" + to_string(projectTask[i].progress) + "||" + projectTask[i].finishDate + "||" + projectTask[i].manager + "\n";
			writeFile.write(udpdateTaskInfo.c_str(), udpdateTaskInfo.size());
		}

		writeFile.close();
	}
}