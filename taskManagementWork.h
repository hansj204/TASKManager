#include <string>
using namespace std;

struct TASK{
	string taskname;
	string startDate;
	string endDate;
	int progress = 0;
	string finishDate;
};

void selectTaskList(string fileName);

void addTask(string projectFileName);

void updateTask(string projectFileName, TASK project[], int taskRowCnt);

void sortTask(TASK* arr, int left, int right, int selectWork, string selectKind);

int binarySearch(TASK arr[], int l, int r, int searchNo, string searchData);

void searchTask(TASK project[], int taskRowCnt);

void downloadTask();

void saveProject(string projectFileName, TASK* projectTask, int taskRowCnt);

int parseDateString(string str);
int currentDateTime();
