#include <string>
using namespace std;

struct TASK{
	string taskname;
	string startDate;
	string endDate;
	int progress = 0;
	string finishDate;
	string manager;
};

void selectTaskList(string fileName);

void addTask(string projectFileName);

void updateTask(string projectFileName, TASK project[], int taskRowCnt);

void sortTask(string fileName, TASK projectTask[], int length);

void searchTask(TASK project[], int taskRowCnt);

void downloadTask(string projectFileName);

void saveProject(string projectFileName, TASK* projectTask, int taskRowCnt);

int parseDateString(string str);
int currentDateTime();
