#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>
#include "taskManagementWork.h"
#include "user.h"
#include <locale.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

void selectTaskList(string fileName) {

	while (1) {
		int totalProject = 0;
		TASK *projectTask = new TASK[100];
		int i = 0, taskCount = 0, selectProject;

		setlocale(LC_ALL, "ko-KR");

		ifstream readFile;
		readFile.open(fileName);

		if (readFile.is_open()) {

			while (!readFile.eof()) {
				char tmp[256];
				i = 0;

				readFile.getline(tmp, 256);
				string orginData = tmp;

				char* token = strtok(tmp, " ");

				while (token != NULL){

					switch (i) {
						case 0:
							projectTask[taskCount].taskname = token;
							break;
						case 1:
							projectTask[taskCount].startDate = token;
							break;
						case 2:
							projectTask[taskCount].endDate = token;
							break;
						case 3:
							projectTask[taskCount].progress = atoi(token);
							totalProject += atoi(token);
							break;
						case 4:
							projectTask[taskCount].finishDate = token;
							break;
					}

					token = strtok(NULL, " ");
					i++;
				}

				++taskCount;
			}

			readFile.close();
		}

		double totalProgress = (totalProject == 0)? 0 : (totalProject / (double)(taskCount - 1));

		cout << "=======================================================================" << endl;
		cout << "������Ʈ ����� : " << totalProgress << "%" << endl;
		cout << "=======================================================================" << endl;
		cout << left << setw(5) << "No." << setw(15) << "TASK��" << setw(15) << "������" << setw(15) << "������" << setw(10) << "�����" << setw(10) << "�Ϸ���" << endl;
		cout << "=======================================================================" << endl;
		for (int i = 0; i < taskCount - 1; i++) {
			cout << left << setw(5) << i + 1 << setw(15) << projectTask[i].taskname << setw(15) << projectTask[i].startDate << setw(15) << projectTask[i].endDate << setw(10) << to_string(projectTask[i].progress) + "%" <<  setw(10) << projectTask[i].finishDate << endl;
		}
		cout << "=======================================================================\n" << endl;

		int selectWork = NULL;
		string selectKind;

		cout << "===================================================================" << endl;
		cout << "1.TASK �߰�\t2.TASK ����\t3.TASK ����\t4.�˻�\t5.�ٿ�ε�" << endl;
		cout << "===================================================================" << endl;
		cout << "(������Ʈ �۾� ���ư��⸦ ���ϸ� 0�� �Է��� �ּ���.)" << endl;
		cout << ">> ";
		cin >> selectWork;

		if (selectWork == 0) {
			system("cls");
			break;
		}

		switch (selectWork) {

		case 1:
			addTask(fileName);
			break;
		case 2:
			updateTask(fileName, projectTask, taskCount - 1);
			break;
		case 3:
			cout << "=====================================================" << endl;
			cout << "1.No.\t2.TASK��\t3.������\t 4.������\t5.�����\t6.�Ϸ���" << endl;
			cout << "=====================================================" << endl;
			cout << "������ �׸��� �Է��ϰ� �������� ������ ���ϸ� asc, ���������� ���ϸ� desc�� �Է����ּ���: ";
			cin >> selectWork >> selectKind;
			sortTask(projectTask, 0, taskCount-2, selectWork, selectKind);
			saveProject(fileName, projectTask, taskCount - 1);
			break;
		case 4:
			searchTask(projectTask, taskCount - 1);
			break;
		case 5: 
			downloadTask();
			break;
		default:
			break;
		}

	}
}

void addTask(string projectFileName) {
	ofstream writeFile;
	writeFile.open(projectFileName, ios::app);

	TASK task;

	cout << "TASK ���� �Է��ϼ��� : ";
	cin >> task.taskname;
	cout << "TASK �������� �Է��ϼ���(YYYY-DD-MM): ";
	cin >> task.startDate;
	cout << "TASK �������� �Է��ϼ���(YYYY-DD-MM) : ";
	cin >> task.endDate;

	task.progress = 0;
	task.finishDate = '-';

	string addTaskInfo = task.taskname + " " + task.startDate + " " + task.endDate + " " + to_string(task.progress) + " " + task.finishDate + "\n";

	writeFile.write(addTaskInfo.c_str(), addTaskInfo.size());
	writeFile.close();
}

void updateTask(string projectFileName, TASK project[], int taskRowCnt) {

	int selectUpdate, selectNo, progress;
	
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
		if (task.progress != -1) {
			project[selectNo - 1].progress = task.progress;
			if (task.progress == 100) {
				task.finishDate = "2020-12-12";
			}
		}
		if (task.finishDate != ".") project[selectNo - 1].finishDate = task.finishDate;
	}
	else {
		cout << "������ TASK�� No�� ������� �Է����ּ��� :";
		cin >> selectNo >> progress;

		project[selectNo - 1].progress = progress;
	}

	ofstream writeFile;
	writeFile.open(projectFileName);

	for (int i = 0; i < taskRowCnt; i++) {
		string udpdateTaskInfo = project[i].taskname + " " + project[i].startDate + " " + project[i].endDate + " " + to_string(project[i].progress) + " " + project[i].finishDate + "\n";
		writeFile.write(udpdateTaskInfo.c_str(), udpdateTaskInfo.size());
	}

	writeFile.close();

}


void saveProject(string projectFileName, TASK* projectTask, int taskRowCnt) {
	ofstream writeFile;
	writeFile.open(projectFileName);


	for (int i = 0; i < taskRowCnt; i++) {
		string udpdateTaskInfo = projectTask[i].taskname + " " + projectTask[i].startDate + " " + projectTask[i].endDate + " " + to_string(projectTask[i].progress) + " " + projectTask[i].finishDate + "\n";
		writeFile.write(udpdateTaskInfo.c_str(), udpdateTaskInfo.size());
	}

	writeFile.close();
}


void swap(TASK* a, TASK* b) {
	TASK temp = *a;
	*a = *b;
	*b = temp;
}

void sortTask(TASK* list, int left, int right, int selectWork, string selectKind) {
	if (left >= right)
		return;
	int pivot = left;
	int start = left + 1;
	int end = right;
	
	string pivotList;
	string startList;
	string endList;
	
	while (start <= end) {
		
		if (selectWork == 2) {
			pivotList = list[pivot].taskname;
			startList = list[start].taskname;
			endList = list[end].progress;
		}

		if (selectKind == "asc") {
			while (pivotList >= startList && start <= right)
				start++;
			while (pivotList <= endList && end > left)
				end--;
		} else  {
			while (pivotList <= startList && start <= right)
				start++;
			while (pivotList >= endList && end > left)
				end--;
		}
		

		if (start > end)
			swap(list[pivot], list[end]);
		else
			swap(list[start], list[end]);
	}

	sortTask(list, start, end - 1, selectWork, selectKind);
	sortTask(list, end + 1, right, selectWork, selectKind);
	
}


int Max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

bool BoyerMooreSearch(const char* txt, const char* pat) {
	int lengTxt = strlen(txt);
	int lengPat = strlen(pat);
	int badchar[256] = { -1, }; 
	for (int i = 0; i < lengPat; i++)
		badchar[(int)pat[i]] = i;
	int s = 0, j; 
	while (s < lengTxt - lengPat)
	{
		j = lengPat - 1;
		while (j >= 0 && txt[s + j] == pat[j])
			j--; 
		if (j < 0) {
			return true;
		} else {
			return false;
		}
	}
}

void searchTask(TASK projectTask[], int taskRowCnt) {
	int searchNo, goStop = -1;
	string searchData, temp = "";

	while (true) {

		cout << "=====================================================" << endl;
		cout << "1.No.\t2.TASK��\t3.������\t 4.������\t5.�����\t6.�Ϸ���" << endl;
		cout << "=====================================================" << endl;
		cout << "�˻��� �׸��� No�� �˻�� �Է��ϼ��� : ";
		cin >> searchNo >> searchData;

		if (searchNo != 5) {
			cout << "=======================================================================" << endl;
			cout << left << setw(5) << "No." << setw(15) << "TASK��" << setw(15) << "������" << setw(15) << "������" << setw(10) << "�����" << setw(10) << "�Ϸ���" << endl;
			cout << "=======================================================================" << endl;
			for (int i = 0; i < taskRowCnt - 1; i++) {
				switch (searchNo) {
				case 1:
					temp = i + 1;
					break;
				case 2:
					temp = projectTask[i].taskname;
					break;
				case 3:
					temp = projectTask[i].startDate;
					break;
				case 4:
					temp = projectTask[i].endDate;
					break;
				case 6:
					temp = projectTask[i].finishDate;
					break;
				}

				cout << i << endl;
				cout << temp << endl;
				cout << searchData << endl;

				if (temp.find(searchData))
					cout << left << setw(5) << i + 1 << setw(15) << projectTask[i].taskname << setw(15) << projectTask[i].startDate << setw(15) << projectTask[i].endDate << setw(10) << to_string(projectTask[i].progress) + "%" << setw(10) << projectTask[i].finishDate << endl;
			}
			cout << "=======================================================================\n" << endl;
		}
		cin.clear();
		cout << "�˻� ���Ḧ ���ϸ� 0�� �Է����ּ��� >> ";
		cout << goStop;
		if (goStop == 0) break;
	}
}

void downloadTask() {
	namespace fs = std::experimental::filesystem::v1;
	string route;

	cout << "�ٿ�ε� ���� ��θ� �Է��ϼ��� ex) C:\\Download : ";
	cin >> route;

	ofstream writeFile;
	writeFile.open(route + "/new.txt");

	cout << route + "\\/new.txt" << endl;
}