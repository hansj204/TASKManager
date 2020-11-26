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

		double totalProgress = (totalProject == 0)? 0 : totalProject / (taskCount - 1);

		cout << "=======================================================================" << endl;
		cout << "프로젝트 진행률 : " << totalProgress << endl;
		cout << "=======================================================================" << endl;
		cout << left << setw(5) << "No." << setw(15) << "TASK명" << setw(15) << "시작일" << setw(15) << "마감일" << setw(10) << "진행률" << setw(10) << "완료일" << endl;
		cout << "=======================================================================" << endl;
		for (int i = 0; i < taskCount - 1; i++) {
			cout << left << setw(5) << i + 1 << setw(15) << projectTask[i].taskname << setw(15) << projectTask[i].startDate << setw(15) << projectTask[i].endDate << setw(10) << to_string(projectTask[i].progress) + "%" <<  setw(10) << projectTask[i].finishDate << endl;
		}
		cout << "=======================================================================\n" << endl;

		int selectWork;
		string selectKind;

		cout << "=====================================================" << endl;
		cout << "1.TASK 추가\t2.TASK 수정\t3.TASK 정렬\t4. 검색\t5. 다운로드" << endl;
		cout << "=====================================================" << endl;
		cout << ">> ";
		cin >> selectWork;

		if (selectWork == -1) break;

		switch (selectWork) {

		case 1:
			addTask(fileName);
			break;
		case 2:
			updateTask(fileName, projectTask, taskCount - 1);
			break;
		case 3:
			cout << "오름차순 정렬을 원하면 asc, 내림차순을 원하면 desc를 입력해주세요" << endl;
			cin >> selectKind;
			sortTask(projectTask, 0, taskCount-2, selectKind);
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

	cout << "TASK 명을 입력하세요 : ";
	cin >> task.taskname;
	cout << "TASK 시작일을 입력하세요(YYYY-DD-MM): ";
	cin >> task.startDate;
	cout << "TASK 마감일을 입력하세요(YYYY-DD-MM) : ";
	cin >> task.endDate;

	task.progress = 0;
	task.finishDate = '-';

	string addTaskInfo = task.taskname + " " + task.startDate + " " + task.endDate + " " + to_string(task.progress) + " " + task.finishDate + "\n";

	writeFile.write(addTaskInfo.c_str(), addTaskInfo.size());
	writeFile.close();
}

void updateTask(string projectFileName, TASK project[], int taskRowCnt) {

	int selectUpdate, selectNo, progress;
	
	cout << "1. TASK 수정\t2. TASK 진행률 업데이트" << endl;
	cin >> selectUpdate;

	if (selectUpdate == 1) {
		TASK task;

		cout << "수정할 TASK의 No를 입력해주세요 :";
		cin >> selectNo;

		cout << "\n\nTASK 명을 입력하세요(수정을 원치 않는 항목이면 .을 입력) : ";
		cin >> task.taskname;
		cout << "TASK 시작일을 입력하세요(수정을 원치 않는 항목이면 .을 입력): ";
		cin >> task.startDate;
		cout << "TASK 마감일을 입력하세요(수정을 원치 않는 항목이면 .을 입력) : ";
		cin >> task.endDate;
		cout << "TASK 진행률을 입력하세요(수정을 원치 않는 항목이면 -1을 입력) : ";
		cin >> task.progress;
		cout << "TASK 완료일을 입력하세요(수정을 원치 않는 항목이면 .을 입력) : ";
		cin >> task.finishDate;

		if (task.taskname != ".") project[selectNo - 1].taskname = task.taskname;
		if (task.startDate != ".") project[selectNo - 1].startDate = task.startDate;
		if (task.endDate != ".") project[selectNo - 1].endDate = task.endDate;
		if (task.progress != -1) project[selectNo - 1].progress = task.progress;
		if (task.finishDate != ".") project[selectNo - 1].finishDate = task.finishDate;
	}
	else {
		cout << "수정할 TASK의 No와 진행률을 입력해주세요 :";
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

void sortTask(TASK* list, int left, int right, string selectKind) {


	if (left >= right)
		return;
	int pivot = left;
	int start = left + 1;
	int end = right;

	while (start <= end) {
		
		if (selectKind == "asc") {
			while (list[pivot].progress >= list[start].progress && start <= right)
				start++;
			while (list[pivot].progress <= list[end].progress && end > left)
				end--;
		} else  {
			while (list[pivot].progress <= list[start].progress && start <= right)
				start++;
			while (list[pivot].progress >= list[end].progress && end > left)
				end--;
		}
		

		if (start > end)
			swap(list[pivot], list[end]);
		else
			swap(list[start], list[end]);
	}

	sortTask(list, start, end - 1, selectKind);
	sortTask(list, end + 1, right, selectKind);
	
}

void searchTask(TASK projectTask[], int taskRowCnt) {
	int searchNo;
	string searchData, temp;

	while (true) {

		system("cls");
		cout << "=====================================================" << endl;
		cout << "1.No.\t2.TASK명\t3.시작일\t 4.마감일\t5.진행률\t6.완료일" << endl;
		cout << "=====================================================" << endl;
		cout << "검색할 항목의 No와 검색어를 입력하세요 : ";
		cin >> searchNo >> searchData;

		if (searchNo != 5) {
			cout << "=======================================================================" << endl;
			cout << left << setw(5) << "No." << setw(15) << "TASK명" << setw(15) << "시작일" << setw(15) << "마감일" << setw(10) << "진행률" << setw(10) << "완료일" << endl;
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

				if (temp.find(searchData))
					cout << left << setw(5) << i + 1 << setw(15) << projectTask[i].taskname << setw(15) << projectTask[i].startDate << setw(15) << projectTask[i].endDate << setw(10) << to_string(projectTask[i].progress) + "%" << setw(10) << projectTask[i].finishDate << endl;
			}
			cout << "=======================================================================\n" << endl;
		}

		cout << "검색 종료를 원하면 0을 입력해주세요 >> ";
		cout << searchNo;
		if (searchNo == 0) break;
	}
}

void downloadTask() {
	string route;

	cout << "다운로드 받을 경로를 입력하세요 ex) C:\\Download : ";
	cin >> route;

	ofstream writeFile;
	writeFile.open(route + "\\/new.txt");

	cout << route + "\\/new.txt" << endl;

	ifstream readFile;
	readFile.open("new.txt");

	if (readFile.is_open()) {

		while (!readFile.eof()) {
			char tmp[256];
			readFile.getline(tmp, 256);
			cout << tmp << endl;
			writeFile.write(tmp, sizeof(tmp));
		}
		writeFile.close();
		readFile.close();
	}	
}