#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include "taskManagementWork.h"
#include<fstream>
#include <locale>
#include <codecvt>
using namespace std;


void parseHTMLTable(string htmlFileName, vector<string> taskInfo, TASK bodyData[], int taskCount) {

    setlocale(LC_ALL, "UTF-8");
    vector<string> header = { "No.", "TASK NAME", "START DATE", "END DATE", "PROGRESS", "FINISH DATE", "MANAGER"};
    ofstream writeFile;

    writeFile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t, 0x10ffff, generate_header>));
    writeFile.open(htmlFileName);

    writeFile.write("<!DOCTYPE html>\n", sizeof("<!DOCTYPE html>\n"));
    writeFile.write("<html>\n", sizeof("<html>\n"));

    string headLine = "<head>\n";
    headLine += "<meta charset = \"UTF-8\"/>\n <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n";
    headLine += "<style>\n";
    headLine += "\ttable{ border-collapse:collapse; text-align: center; width: 80 %; }\n";
    headLine += "\ttd, th{ border: 1px solid black; padding: 7px; }\n";
    headLine += "</style>\n";
    headLine += "</head>\n";
    writeFile.write(headLine.c_str(), headLine.size());

    writeFile.write("<body>\n", sizeof("<body>\n"));

    string projecNameLine = "<h2> Proejct Name : " + taskInfo[0].substr(0, taskInfo[0].size() - 4) + "</h2>\n";
    string projectPeriodLine = "<h2> Proejct Period : " + taskInfo[1] + "</h2>\n";
    string projectUserLine = "<h2> Project Participants : " + taskInfo[2] + "</h2>\n";

    writeFile.write(projecNameLine.c_str(), projecNameLine.size());
    writeFile.write(projectPeriodLine.c_str(), projectPeriodLine.size());
    writeFile.write(projectUserLine.c_str(), projectUserLine.size());

    string tableLine = " <table>\n";
    writeFile.write(tableLine.c_str(), tableLine.size());
    writeFile.write("  <tr>\n", sizeof("<tr>\n"));

    for (auto head : header) {
        string headerData = "    <th>" + head + "</th>\n";
        writeFile.write(headerData.c_str(), headerData.size());
    }

    writeFile.write("  </tr>\n", sizeof("  </tr>\n"));

    for (int i = 0; i < taskCount; i++) {
        writeFile.write("  <tr>\n", sizeof("  <tr>\n"));
        string num = to_string(i + 1);
        vector<string> rowData = {
            "    <td>" + num + "</td>\n",
            "    <td>" + bodyData[i].taskname + "</td>\n",
            "    <td>" + bodyData[i].startDate + "</td>\n"
            "    <td>" + bodyData[i].endDate + "</td>\n",
            "    <td>" + bodyData[i].finishDate + "</td>\n",
            "    <td>" + to_string(bodyData[i].progress) + "%</td>\n",
            "    <td>" + bodyData[i].manager + "</td>\n"
        };

        for (auto row : rowData) {
            writeFile.write(row.c_str(), row.size());
        }

        writeFile.write("  </tr>\n", sizeof("  </tr>\n"));
    }

    writeFile.write(" </table>\n", sizeof("</table>\n"));
    writeFile.write("</body>\n", sizeof("</body>\n"));
    writeFile.write("</html>\n", sizeof("</html>\n"));

    writeFile.close();
}