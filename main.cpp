#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>
#include "user.h"
#include "taskManagementWork.h"
#include "projectManagementWork.h"
#include <locale.h>
using namespace std;

void taskWork() {
	int selectWork;

	while (1) {
		cout << "=====================================================" << endl;
		cout << "1.TASK 추가\t2.TASK 수정\t3.TASK 정렬" << endl;
		cout << "=====================================================" << endl;
		cin >> selectWork;

		if (selectWork == -1) break;

		switch (selectWork) {

		case 1:
			addTask(task, (sizeof(task) / sizeof(TASK) - 1));
			break;
		case 2:
			updateTask(task);
			break;
		case 3:
			sortTask(task);
			break;
		default:
			break;
		}
	
	}
}

int main() {
	//TASK task[] = { {"a", "2020-10-10", "2020-10-20", 0, "-"}, {"b", "2020-11-11", "2020-12-31", 0, "-"} };
	int selectUser, selectProject, selectWork;
	
	cout << "TASKManager" << endl;
	cout << "--------------------------------------" << endl;
	cout << "환영합니다. 새로운 회원이라면 0, 기존 회원이라면 1를 입력하여 주세요 :";
	cin >> selectUser;

	User userInfo = login(selectUser);

	cout << userInfo.id << "회원님 안녕하세요" << endl;
	cout << "회원님의 현재 직급은 ";

	if (strcmp(userInfo.position.c_str(), "tl") == 0) {
		cout << "팀장입니다." << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << "1.기존 프로젝트 불러오기\t2.새로운 프로젝트 생성\t3. 프로젝트 참여 신청 수락" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << ">>";
		cin >> selectProject;

		switch (selectProject) {
			case 1:
				selectTaskList(loadProjectList(userInfo.id));
				break;
			case 2:
				break;
			case 3:
				inviteTeamPlayer(userInfo.id);
				break;
		}
		
	}else {
		cout << "팀원입니다." << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << "1.기존 프로젝트 불러오기\t2.프로젝트 참여 신청" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << ">>";
		cin >> selectProject;

		switch (selectProject) {
			case 1:
				selectTaskList(loadProjectList(userInfo.id));
				break;
			case 2:
				applyProjectParticipation(userInfo.id);
				break;
		}
	}
	
	//cout << "-----프로젝트 참여자---------------------------------------------------" << endl;

	//프로젝트 TASK 조회 어쩌구 저쩌구


	//while(1) {
	//	
	//	//taskLength = sizeof(task) / sizeof(TASK);

	//	

	return 0;
}