#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>
#include "taskManagementWork.h"
#include <locale.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

void selectTaskList(string fileName) {
	TASK task;

	setlocale(LC_ALL, "ko-KR");

	cout << fileName << endl;

	string projectList[50];
	int i = 0, selectProject;

	ifstream readFile;
	readFile.open(fileName);

	if (readFile.is_open()) {

		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);

			string orginData = tmp;

			char* token = strtok(tmp, " ");

			while (token != NULL){
				if(i == 0)		 task.taskname = token;
				else if (i == 1) task.startDate = token;
				else if (i == 2) task.endDate = token;
				else if (i == 3) task.progress = atoi(token);
				else if (i == 4) task.finishDate = token;
				token = strtok(NULL, " ");
				i++;
			}

		}

		readFile.close();
	}

	cout << "=======================================================================" << endl;
	cout << left << setw(5) << "No." << setw(15) << "TASK��" << setw(15) << "������" << setw(15) << "������" << setw(10) << "�����" << setw(10) << "�Ϸ���" << endl;
	cout << "=======================================================================" << endl;
	for (int i = 0; i < 1; i++) {
		cout << left << setw(5) << i + 1 << setw(15) << task.taskname << setw(15) << task.startDate << setw(15) << task.endDate << setw(10) << to_string(task.progress) + "%" <<  setw(10) << task.finishDate << endl;
	}
	cout << "=======================================================================\n" << endl;

	int selectWork;

	while (1) {
		cout << "=====================================================" << endl;
		cout << "1.TASK �߰�\t2.TASK ����\t3.TASK ����" << endl;
		cout << "=====================================================" << endl;
		cin >> selectWork;

		if (selectWork == -1) break;

		switch (selectWork) {

		case 1:
			addTask(task);
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}

	}
}

void addTask(TASK project) {
	TASK task;

	cout << "TASK ���� �Է��ϼ��� : ";
	cin >> task.taskname;
	cout << "TASK �������� �Է��ϼ���(YYYY-DD-MM): ";
	cin >> task.startDate;
	cout << "TASK �������� �Է��ϼ���(YYYY-DD-MM) : ";
	cin >> task.endDate;

	task.progress = 0;
	task.finishDate = '-';

	//project[sizeof(project) - 1] = task;
	//system("cls");
	cout << taskLength << endl;

	//cout << task.taskname << "\t" << task.startDate << "\t" << task.endDate << "\t" << task.finishDate;
}

void updateTask(TASK project[]) {

	int selectUpdate, selectNo, progress;
	//selectTaskList(project);

	cout << "1. TASK ����\t2. TASK ����� ������Ʈ" << endl;
	cin >> selectUpdate;

	if (selectUpdate == 1) {
		TASK task;

		cout << "������ TASK�� No�� �Է����ּ��� :";
		cin >> selectNo;

		cout << "\n\nTASK ���� �Է��ϼ���(������ ��ġ �ʴ� �׸��̸� .�� �Է�) : ";
		cin >> task.taskname;
		cout << "TASK �������� �Է��ϼ���(������ ��ġ �ʴ� �׸��̸� .�� �Է�): ";
		cin >> task.startDate;
		cout << "TASK �������� �Է��ϼ���(������ ��ġ �ʴ� �׸��̸� .�� �Է�) : ";
		cin >> task.endDate;
		cout << "TASK ������� �Է��ϼ���(������ ��ġ �ʴ� �׸��̸� -1�� �Է�) : ";
		cin >> task.progress;
		cout << "TASK �Ϸ����� �Է��ϼ���(������ ��ġ �ʴ� �׸��̸� .�� �Է�) : ";
		cin >> task.finishDate;

		if (task.taskname != ".") project[selectNo - 1].taskname = task.taskname;
		if (task.startDate != ".") project[selectNo - 1].startDate = task.startDate;
		if (task.endDate != ".") project[selectNo - 1].endDate = task.endDate;
		if (task.progress != -1) project[selectNo - 1].progress = task.progress;
		if (task.finishDate != ".") project[selectNo - 1].finishDate = task.finishDate;
	}
	else {
		cout << "������ TASK�� No�� ������� �Է����ּ��� :";
		cin >> selectNo >> progress;

		project[selectNo - 1].progress = progress;
	}

	system("cls");
}

void sortTask(TASK project[]) {
	//sort(project, project + 2);
}

int binarySearch(TASK arr[], int l, int r, int searchNo, string searchData) { // �Ű����� : �迭�̸�, �迭 ���� �ε���, �迭 �� �ε���, ã������ ��

	if (r >= l) {

		int mid = l + (r - l) / 2; // �߰� �� ����
		string temp;

		switch (searchNo) {
		case 1:
			temp = mid + 1;
			break;
		case 2:
			temp = arr[mid].taskname;
			break;
		case 3:
			temp = arr[mid].startDate;
			break;
		case 4:
			temp = arr[mid].endDate;
			break;
		case 5:
			temp = arr[mid].finishDate;
			break;
		}

		if (temp == searchData) return mid; // ���Ͽ� ã�� ���̶�� �ش� �ε��� ��ȯ


		if (temp > searchData) return binarySearch(arr, l, mid - 1, searchNo, searchData); // ã������ ������ ũ�ٸ� ���� �迭 Ž��


		return binarySearch(arr, mid + 1, r, searchNo, searchData); // ���� �迭 Ž��

	}

	return -1;  // ã������ ���� ���ٸ� -1 ��ȯ

}

void searchTask(TASK project[]) {
	int searchNo;
	string searchData;

	cout << "=====================================================" << endl;
	cout << "1.No.\t2.TASK��\t3.������\t 4.������\t5.�����\t6.�Ϸ���" << endl;
	cout << "=====================================================" << endl;
	cout << "�˻��� �׸��� No�� �˻�� �Է��ϼ��� : ";
	cin >> searchNo >> searchData;

	binarySearch(project, 0, 1, searchNo, searchData);
}