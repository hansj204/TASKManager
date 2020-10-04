#include <iostream>
#include <string.h>
using namespace std;

struct TASK {
	string taskname;
	string startDate;
	string endDate;
	int process;
	string finishDate;
};

void addTask(TASK project[]) {
	TASK task;

	for (int i = 0; i < 1; i++) {
		cout << "TASK 명을 입력하세요 : ";
		cin >> task.taskname;
		cout << "TASK 시작일을 입력하세요(YYYY-DD-MM): ";
		cin >> task.startDate;
		cout << "TASK 마감일을 입력하세요(YYYY-DD-MM) : ";
		cin >> task.endDate;

		task.process = 0;
		task.finishDate = '-';

		project[i] = task;
	}
	//cout << task.taskname << "\t" << task.startDate << "\t" << task.endDate << "\t" << task.finishDate;
}

void sortTask(TASK project[]) {

}

void main() {
	TASK task[3];
	int selectWork;
	string projectName;

	cout << "TASKManager" << endl;

	cout << "프로젝트 명을 입력해주세요: ";
	cin >> projectName;

	cout << "=====================================================" << endl;
	cout << "1.TASK 추가\t2.TASK 정렬" << endl;
	cout << "=====================================================" << endl;
	cin >> selectWork;

	switch (selectWork) {

	case 1: 
		addTask(task); 
		break;
	case 2:
		sortTask(task);
		break;

	default:
		break;
	}

	cout << "=====================================================" << endl;
	cout << "TASK명\t시작일\t마감일\t진행률\t완료일" << endl;
	cout << "=====================================================" << endl;
	for (int i = 0; i < 1; i++) {
		cout << task[i].taskname << "\t" << task[i].startDate << "\t" << task[i].endDate << "\t" << task[i].process << "%\t" << task[i].finishDate << endl;
	}
	
}