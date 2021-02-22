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
	cout << "ȯ���մϴ�. ���ο� ȸ���̶�� 0, ���� ȸ���̶�� 1�� �Է��Ͽ� �ּ��� :";
	cin >> selectUser;

	userInfo = login(selectUser);

	cout << userInfo.id << "ȸ���� �ȳ��ϼ���" << endl;
	cout << "ȸ������ ���� ������ ";

	if (strcmp(userInfo.position.c_str(), "tl") == 0)
		cout << "�����Դϴ�." << endl;
	else
		cout << "�����Դϴ�." << endl;

	while (1) {

		if (strcmp(userInfo.position.c_str(), "tl") == 0) {
			cout << "-----------------------------------------------------------------------------------------------------------" << endl;
			cout << "1.���� ������Ʈ �ҷ�����\t2.���ο� ������Ʈ ����\t 3. ������Ʈ ����\t 4. ������Ʈ ���� ��û ����" << endl;
			cout << "-----------------------------------------------------------------------------------------------------------" << endl;
			cout << "(������Ʈ ���Ḧ ���ϸ� 0�� �Է��� �ּ���.)" << endl;
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
			cout << "1.���� ������Ʈ �ҷ�����\t2.������Ʈ ���� ��û" << endl;
			cout << "------------------------------------------------------------------------" << endl;
			cout << "(������Ʈ ���Ḧ ���ϸ� 0�� �Է��� �ּ���.)" << endl;
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