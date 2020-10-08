#include <string>
using namespace std;

struct TASK{
	string taskname;
	string startDate;
	string endDate;
	int progress = 0;
	string finishDate;
};

void selectTaskList(TASK task[]);

void addTask(TASK* project, int taskLength);

void updateTask(TASK project[]);

void sortTask(TASK project[]);

int binarySearch(TASK arr[], int l, int r, int searchNo, string searchData);

void searchTask(TASK project[]);