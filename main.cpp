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
		cout << "TASK ���� �Է��ϼ��� : ";
		cin >> task.taskname;
		cout << "TASK �������� �Է��ϼ���(YYYY-DD-MM): ";
		cin >> task.startDate;
		cout << "TASK �������� �Է��ϼ���(YYYY-DD-MM) : ";
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

	cout << "������Ʈ ���� �Է����ּ���: ";
	cin >> projectName;

	cout << "=====================================================" << endl;
	cout << "1.TASK �߰�\t2.TASK ����" << endl;
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
	cout << "TASK��\t������\t������\t�����\t�Ϸ���" << endl;
	cout << "=====================================================" << endl;
	for (int i = 0; i < 1; i++) {
		cout << task[i].taskname << "\t" << task[i].startDate << "\t" << task[i].endDate << "\t" << task[i].process << "%\t" << task[i].finishDate << endl;
	}
	
}