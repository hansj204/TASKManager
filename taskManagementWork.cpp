#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>
#include "taskManagementWork.h"
using namespace std;

void selectTaskList(TASK task[]) {
	cout << "=====================================================" << endl;
	cout << "No.\tTASK명\t시작일\t마감일\t진행률\t완료일" << endl;
	cout << "=====================================================" << endl;
	for (int i = 0; i < 2; i++) {
		cout << i + 1 << "\t" << task[i].taskname << "\t" << task[i].startDate << "\t" << task[i].endDate << "\t" << task[i].progress << "%\t" << task[i].finishDate << endl;
	}
	cout << "=====================================================\n" << endl;
}

void addTask(TASK* project, int taskLength) {
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
	system("cls");
	cout << taskLength << endl;

	//cout << task.taskname << "\t" << task.startDate << "\t" << task.endDate << "\t" << task.finishDate;
}

void updateTask(TASK project[]) {

	int selectUpdate, selectNo, progress;
	selectTaskList(project);

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