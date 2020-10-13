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
	cout << left << setw(5) << "No." << setw(15) << "TASK명" << setw(15) << "시작일" << setw(15) << "마감일" << setw(10) << "진행률" << setw(10) << "완료일" << endl;
	cout << "=======================================================================" << endl;
	for (int i = 0; i < 1; i++) {
		cout << left << setw(5) << i + 1 << setw(15) << task.taskname << setw(15) << task.startDate << setw(15) << task.endDate << setw(10) << to_string(task.progress) + "%" <<  setw(10) << task.finishDate << endl;
	}
	cout << "=======================================================================\n" << endl;

	int selectWork;

	while (1) {
		cout << "=====================================================" << endl;
		cout << "1.TASK 추가\t2.TASK 수정\t3.TASK 정렬" << endl;
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

	cout << "TASK 명을 입력하세요 : ";
	cin >> task.taskname;
	cout << "TASK 시작일을 입력하세요(YYYY-DD-MM): ";
	cin >> task.startDate;
	cout << "TASK 마감일을 입력하세요(YYYY-DD-MM) : ";
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

	system("cls");
}

void sortTask(TASK project[]) {
	//sort(project, project + 2);
}

int binarySearch(TASK arr[], int l, int r, int searchNo, string searchData) { // 매개변수 : 배열이름, 배열 시작 인덱스, 배열 끝 인덱스, 찾으려는 값

	if (r >= l) {

		int mid = l + (r - l) / 2; // 중간 값 선택
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

		if (temp == searchData) return mid; // 비교하여 찾는 값이라면 해당 인덱스 반환


		if (temp > searchData) return binarySearch(arr, l, mid - 1, searchNo, searchData); // 찾으려는 값보다 크다면 좌측 배열 탐색


		return binarySearch(arr, mid + 1, r, searchNo, searchData); // 우측 배열 탐색

	}

	return -1;  // 찾으려는 값이 없다면 -1 반환

}

void searchTask(TASK project[]) {
	int searchNo;
	string searchData;

	cout << "=====================================================" << endl;
	cout << "1.No.\t2.TASK명\t3.시작일\t 4.마감일\t5.진행률\t6.완료일" << endl;
	cout << "=====================================================" << endl;
	cout << "검색할 항목의 No와 검색어를 입력하세요 : ";
	cin >> searchNo >> searchData;

	binarySearch(project, 0, 1, searchNo, searchData);
}