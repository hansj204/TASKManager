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
		cout << "1.TASK �߰�\t2.TASK ����\t3.TASK ����" << endl;
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
	cout << "ȯ���մϴ�. ���ο� ȸ���̶�� 0, ���� ȸ���̶�� 1�� �Է��Ͽ� �ּ��� :";
	cin >> selectUser;

	User userInfo = login(selectUser);

	cout << userInfo.id << "ȸ���� �ȳ��ϼ���" << endl;
	cout << "ȸ������ ���� ������ ";

	if (strcmp(userInfo.position.c_str(), "tl") == 0) {
		cout << "�����Դϴ�." << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << "1.���� ������Ʈ �ҷ�����\t2.���ο� ������Ʈ ����\t3. ������Ʈ ���� ��û ����" << endl;
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
		cout << "�����Դϴ�." << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << "1.���� ������Ʈ �ҷ�����\t2.������Ʈ ���� ��û" << endl;
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
	
	//cout << "-----������Ʈ ������---------------------------------------------------" << endl;

	//������Ʈ TASK ��ȸ ��¼�� ��¼��


	//while(1) {
	//	
	//	//taskLength = sizeof(task) / sizeof(TASK);

	//	

	return 0;
}