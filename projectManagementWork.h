#include <string>
using namespace std;

string loadProjectList(string userId);

void projectUser(char projectName[]);

void inviteTeamPlayer(string userId);

void applyProjectParticipation (string userId);

void createNewProject(string userId);

void deleteProject(string userId);

void insertProjectUser(char* projectName, string name);