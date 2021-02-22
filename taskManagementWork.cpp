#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
# define SWAP(x, y, temp) ( (temp)=(x), (x)=(y), (y)=(temp) )
#include <iostream>
#include <string.h>
#include<fstream>
#include <cstring>
#include "taskManagementWork.h"
#include "user.h"
#include <locale.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <ctime>
#include <experimental/filesystem>
using namespace std;

vector<string> projectInfo;
void selectTaskList(string fileName) {

	while (1) {
		int totalProject = 0;
		TASK* projectTask = new TASK[100];

		int i = 0, taskCount = 0, selectProject, projectInfoCnt = -1;
		vector<double> planProgress;

		system("cls");

		ifstream readFile;
		readFile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		readFile.open(fileName);
		projectInfo.clear();
		projectInfo.push_back(fileName);

		cout << "=========================================================================================" << endl;

		if (readFile.is_open()) {

			while (!readFile.eof()) {
				char tmp[256];
				i = 0;

				readFile.getline(tmp, 256);

				projectInfoCnt++;
				if (projectInfoCnt < 4) {
					if (projectInfoCnt == 1 || projectInfoCnt == 2) {
						if (projectInfoCnt == 1) cout << "프로젝트 기간 : " << tmp << endl;
						if (projectInfoCnt == 2) cout << "참여자 : " << tmp << endl;
						projectInfo.push_back(tmp);
					}
					continue;
				}

				string orginData = tmp;

				char* token = strtok(tmp, "||");

				while (token != NULL) {

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
					case 5:
						projectTask[taskCount].manager = token;
						break;
					}
					token = strtok(NULL, "||");
					i++;
				}

				++taskCount;
			}

			readFile.close();
		}

		double totalProgress = (totalProject == 0) ? 0 : (totalProject / (taskCount - 1));

		cout << "프로젝트 진행률 : " << totalProgress << "%" << endl;
		//cout << "계획 대비 프로젝트 진행률 : " << totalProgress << "%" << endl;
		cout << "=========================================================================================" << endl;
		cout << "=========================================================================================" << endl;
		cout << left << setw(5) << "No." << setw(15) << "TASK명" << setw(15) << "시작일" << setw(15) << "마감일" << setw(10) << "진행률" << setw(15) << "완료일" << setw(10) << "담당자" << endl;
		cout << "=========================================================================================" << endl;

		if (taskCount < 0) cout << "데이터가 없습니다." << endl;

		for (int i = 0; i < taskCount - 1; i++) {
			cout << left << setw(5) << i + 1 << setw(15) << projectTask[i].taskname << setw(15) << projectTask[i].startDate;
			cout << setw(15) << projectTask[i].endDate << setw(10) << to_string(projectTask[i].progress) + "%" << setw(15) << projectTask[i].finishDate << setw(10) << projectTask[i].manager << endl;
		}
		cout << "=========================================================================================\n" << endl;

		int selectWork;

		cout << "===================================================================" << endl;
		cout << "1.TASK 추가\t2.TASK 수정\t3.TASK 정렬\t4.검색\t5.다운로드" << endl;
		cout << "===================================================================" << endl;
		cout << "(프로젝트 작업 돌아가기를 원하면 0을 입력해 주세요.)" << endl;
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
			sortTask(fileName, projectTask, taskCount - 1);
			break;
		case 4:
			searchTask(projectTask, taskCount - 1);
			break;
		case 5:
			downloadTask(fileName, projectTask, taskCount - 1);
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
	cin.ignore();
	getline(cin, task.taskname);
	cout << "TASK 시작일을 입력하세요(YYYY-DD-MM): ";
	cin.clear();
	getline(cin, task.startDate);
	cout << "TASK 마감일을 입력하세요(YYYY-DD-MM) : ";
	cin.clear();
	getline(cin, task.endDate);
	cout << "TASK 담당자를 입력하세요 : ";
	cin.clear();
	getline(cin, task.manager);

	task.progress = 0;
	task.finishDate = '-';

	string addTaskInfo = task.taskname + "||" + task.startDate + "||" + task.endDate + "||" + to_string(task.progress) + "||" + task.finishDate + "||" + task.manager + "\n";
	writeFile.write(addTaskInfo.c_str(), addTaskInfo.size());
	writeFile.close();
}

void updateTask(string projectFileName, TASK project[], int taskRowCnt) {

	int selectUpdate, selectNo, progress;
	cout << "------------------------------------------------------------" << endl;
	cout << "1. TASK 수정\t2. TASK 진행률 업데이트" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << ">>";
	cin >> selectUpdate;

	if (selectUpdate == 1) {
		TASK task;
		string input;

		cout << "수정할 TASK의 No를 입력해주세요 :";
		cin >> selectNo;

		cout << "\n\nTASK 명을 입력하세요(수정을 원치 않는 항목이면 .을 입력) : ";
		cin.ignore();
		getline(cin, task.taskname);
		cout << "TASK 시작일을 입력하세요(수정을 원치 않는 항목이면 .을 입력): ";
		cin.clear();
		getline(cin, task.startDate);
		cout << "TASK 마감일을 입력하세요(수정을 원치 않는 항목이면 .을 입력) : ";
		cin.clear();
		getline(cin, task.endDate);
		cout << "TASK 진행률을 입력하세요(수정을 원치 않는 항목이면 .을 입력) : ";
		cin.clear();
		getline(cin, input);
		cout << "TASK 완료일을 입력하세요(수정을 원치 않는 항목이면 .을 입력) : ";
		cin.clear();
		getline(cin, task.finishDate);
		cout << "TASK 담당자를 입력하세요(수정을 원치 않는 항목이면 .을 입력) : ";
		cin.clear();
		getline(cin, task.manager);

		if (task.taskname != ".") project[selectNo - 1].taskname = task.taskname;
		if (task.startDate != ".") project[selectNo - 1].startDate = task.startDate;
		if (task.endDate != ".") project[selectNo - 1].endDate = task.endDate;
		if (input != ".") {
			project[selectNo - 1].progress = stoi(input);
			if (task.progress == 100) {
				task.finishDate = currentDateTime();
			}
		}
		if (task.finishDate != ".") project[selectNo - 1].finishDate = task.finishDate;
		if (task.manager != ".") project[selectNo - 1].manager = task.manager;
	}
	else {
		cout << "수정할 TASK의 No와 진행률을 입력해주세요 :";
		cin >> selectNo >> progress;

		project[selectNo - 1].progress = progress;

		if (project[selectNo - 1].progress == 100) {
			project[selectNo - 1].finishDate = currentDateTime();
		}
	}

	saveProject(projectFileName, project, taskRowCnt);
}


void saveProject(string projectFileName, TASK* project, int taskRowCnt) {
	ofstream writeFile;
	writeFile.open(projectFileName);

	writeFile.write("==========================================\n", 43);
	writeFile.write((projectInfo[1] + "\n").c_str(), (projectInfo[1] + "\n").size());
	writeFile.write((projectInfo[2] + "\n").c_str(), (projectInfo[2] + "\n").size());
	writeFile.write("==========================================\n", 43);

	for (int i = 0; i < taskRowCnt; i++) {
		string udpdateTaskInfo = project[i].taskname + "||" + project[i].startDate + "||" + project[i].endDate + "||" + to_string(project[i].progress) + "||" + project[i].finishDate + "||" + project[i].manager + "\n";
		writeFile.write(udpdateTaskInfo.c_str(), udpdateTaskInfo.size());
	}

	writeFile.close();
}

int returnValue(TASK array[], int index, int selectWork) {
	if (selectWork == 1) return parseDateString(array[index].startDate);
	else if (selectWork == 2) return parseDateString(array[index].endDate);
	else if (selectWork == 3) return array[index].progress;
	else if (selectWork == 4) return (array[index].finishDate.compare("-") == 0) ? 0 : parseDateString(array[index].finishDate);
}


void selectSort(TASK list[], int length, int selectWork, string selectKind) {
	int i, j, least;
	TASK temp;

	for (i = 0; i < length - 1; i++) {
		least = i;

		if (selectKind == "asc") {
			for (j = i + 1; j < length; j++) {
				if (returnValue(list, j, selectWork) < returnValue(list, least, selectWork))
					least = j;
			}
		} else {
			for (j = i + 1; j < length; j++) {
				if (returnValue(list, j, selectWork) > returnValue(list, least, selectWork))
					least = j;
			}
		}

		if (i != least) {
			temp = list[i];
			list[i] = list[least];
			list[least] = temp;
		}
	}

}

void sortTask(string fileName, TASK projectTask[], int length) {
	int selectWork = NULL;
	string selectKind;
	cout << "===================================================================================" << endl;
	cout << "1.시작일\t 2.마감일\t3.진행률\t4.완료일" << endl;
	cout << "===================================================================================" << endl;
	cout << "정렬할 항목을 입력하고 오름차순 정렬을 원하면 asc, 내림차순을 원하면 desc를 입력해주세요: ";
	cin >> selectWork >> selectKind;
	selectSort(projectTask, length, selectWork, selectKind);
	saveProject(fileName, projectTask, length );
}

void searchTask(TASK projectTask[], int taskRowCnt) {
	int searchNo;
	string searchData, temp = "", goStop;

	while (true) {
		
		cout << "=========================================================================================" << endl;
		cout << "1.TASK명\t2.시작일\t 3.마감일\t4.진행률\t5.완료일\t6.담당자" << endl;
		cout << "=========================================================================================" << endl;
		cout << "검색할 항목의 No와 검색어를 입력하세요 : ";
		cin >> searchNo >> searchData;

		system("cls");

		cout << "=============================================================================================" << endl;
		cout << left << setw(5) << "No." << setw(15) << "TASK명" << setw(15) << "시작일" << setw(15) << "마감일" << setw(10) << "진행률" << setw(15) << "완료일" << setw(10) << "담당자" << endl;
		cout << "=============================================================================================" << endl;

		for (int i = 0; i < taskRowCnt; i++) {

			if (searchNo != 4) {
				switch (searchNo) {
					case 1: temp = projectTask[i].taskname; break;
					case 2: temp = projectTask[i].startDate; break;
					case 3: temp = projectTask[i].endDate; break;
					case 5: temp = projectTask[i].finishDate; break;
					case 6: temp = projectTask[i].manager; break;
				}

				if (temp == searchData) {
					cout << left << setw(5) << i + 1 << setw(15) << projectTask[i].taskname << setw(15) << projectTask[i].startDate;
					cout << setw(15) << projectTask[i].endDate << setw(10) << to_string(projectTask[i].progress) + "%" << setw(15) << projectTask[i].finishDate << setw(10) << projectTask[i].manager << endl;
				}

			}
			else {
				if (temp == searchData) {
					cout << left << setw(5) << i + 1 << setw(15) << projectTask[i].taskname << setw(15) << projectTask[i].startDate;
					cout << setw(15) << projectTask[i].endDate << setw(10) << to_string(projectTask[i].progress) + "%" << setw(15) << projectTask[i].finishDate << setw(10) << projectTask[i].manager << endl;
				}
			}
		}
			
		cout << "=============================================================================================" << endl;

		cout << "검색한 목록 조회를 종료를 원하면 아무 키를 입력해주세요 >> ";
		cin >> goStop;
		if(goStop.compare("") != 0) break;
	}
}

namespace fs = std::experimental::filesystem::v1;

void downloadTask(string fileName, TASK projectTask[], int taskRowCnt) {
	string route;

	cout << "다운로드 받을 경로를 입력하세요 ex) C:\\Download : ";
	cin >> route;
	route = route + "\\" + currentDateTime() + "_taskList.html";

	parseHTMLTable(route, projectInfo, projectTask, taskRowCnt);
}

int parseDateString(string str) {
	str.erase(remove(str.begin(), str.end(), '-'), str.end());
	return stoi(str);
}

string timeFormat(int time) {
	return (time < 10) ? "0" + to_string(time) : to_string(time);
}

string currentDateTime() {
	time_t curr_time;
	struct tm* curr_tm;
	curr_time = time(NULL);
	curr_tm = localtime(&curr_time);
	return to_string(curr_tm->tm_year + 1900) + "-" + timeFormat(curr_tm->tm_mon + 1) + "-" + timeFormat(curr_tm->tm_mday);
}