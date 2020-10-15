#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include "user.h"
#include "taskManagementWork.h"
#include "projectManagementWork.h"
#include <locale.h>
using namespace std;

int main() {
	int selectUser, selectProject, selectWork;
	
	cout << "TASKManager" << endl;
	cout << "--------------------------------------" << endl;
	cout << "ȯ���մϴ�. ���ο� ȸ���̶�� 0, ���� ȸ���̶�� 1�� �Է��Ͽ� �ּ��� :";
	cin >> selectUser;

	User userInfo = login(selectUser);

	cout << userInfo.id << "ȸ���� �ȳ��ϼ���" << endl;
	cout << "ȸ������ ���� ������ ";

	while (1) {


		if (strcmp(userInfo.position.c_str(), "tl") == 0) {
			cout << "�����Դϴ�." << endl;
			cout << "------------------------------------------------------------------------" << endl;
			cout << "1.���� ������Ʈ �ҷ�����\t2.���ο� ������Ʈ ����\t3. ������Ʈ ���� ��û ����" << endl;
			cout << "------------------------------------------------------------------------" << endl;
			cout << ">>";
			cin >> selectProject;

			if (selectProject == -1) break;

			switch (selectProject) {
			case 1:
				selectTaskList(loadProjectList(userInfo.id));
				break;
			case 2:
				createNewProject();
				break;
			case 3:
				inviteTeamPlayer(userInfo.id);
				break;
			}

		}
		else {
			cout << "�����Դϴ�." << endl;
			cout << "------------------------------------------------------------------------" << endl;
			cout << "1.���� ������Ʈ �ҷ�����\t2.������Ʈ ���� ��û" << endl;
			cout << "------------------------------------------------------------------------" << endl;
			cout << ">>";
			cin >> selectProject;

			if (selectProject == -1) break;

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