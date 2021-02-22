#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include "user.h"
#include "taskManagementWork.h"
#include "projectManagementWork.h"
#include <locale.h>
using namespace std;

static User userInfo;

int main() {
	int selectUser, selectProject, selectWork;
	string fileName;

	cout << "TASKManager" << endl;
	cout << "--------------------------------------" << endl;
	cout << "환영합니다. 새로운 회원이라면 0, 기존 회원이라면 1를 입력하여 주세요 :";
	cin >> selectUser;

	userInfo = login(selectUser);

	cout << userInfo.id << "회원님 안녕하세요" << endl;
	cout << "회원님의 현재 직급은 ";

	if (strcmp(userInfo.position.c_str(), "tl") == 0)
		cout << "팀장입니다." << endl;
	else
		cout << "팀원입니다." << endl;

	while (1) {

		if (strcmp(userInfo.position.c_str(), "tl") == 0) {
			cout << "-----------------------------------------------------------------------------------------------------------" << endl;
			cout << "1.기존 프로젝트 불러오기\t2.새로운 프로젝트 생성\t 3. 프로젝트 삭제\t 4. 프로젝트 참여 신청 수락" << endl;
			cout << "-----------------------------------------------------------------------------------------------------------" << endl;
			cout << "(프로젝트 종료를 원하면 0을 입력해 주세요.)" << endl;
			cout << ">>";
			cin >> selectProject;

			if (selectProject == 0) break;

			switch (selectProject) {
			case 1:
				 fileName = loadProjectList(userInfo.id);
				if(fileName != "") selectTaskList(fileName);
				break;
			case 2:
				createNewProject(userInfo.id);
				break;
			case 3:
				deleteProject(userInfo.id);
				break;
			case 4:
				inviteTeamPlayer(userInfo.id);
				break;
			}

		}
		else {
			cout << "------------------------------------------------------------------------" << endl;
			cout << "1.기존 프로젝트 불러오기\t2.프로젝트 참여 신청" << endl;
			cout << "------------------------------------------------------------------------" << endl;
			cout << "(프로젝트 종료를 원하면 0을 입력해 주세요.)" << endl;
			cout << ">>";
			cin >> selectProject;

			if (selectProject == 0) break;

			switch (selectProject) {
			case 1:
				selectTaskList(loadProjectList(userInfo.id));
				break;
			case 2:
				applyProjectParticipation(userInfo.id);
				break;
			}
		}
	}

	return 0;
}