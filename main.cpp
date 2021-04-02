#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;
vector<string> importLastYear(int year);
void createClasses(int year)
{
    string schoolYear = to_string(year) + "-" + to_string(year + 1);
    mkdir((schoolYear + "/classes").c_str());

    ifstream fin;
    ofstream fout;
    fout.open(schoolYear + "/classes" + "/classes.txt");
    string classes;
    do
    {
        cout << "class: ";
        cin >> classes;
        if (classes != "0")
        {
            mkdir((schoolYear + "/classes/" + classes).c_str());
            fout << classes << endl;
        }

    } while (classes != "0");
    fout.close();
    vector<string> lastYear = importLastYear(year);
    fout.open(schoolYear + "/classes" + "/classes.txt");
    for (int i = 0; i < lastYear.size(); i++)
    {
        mkdir((schoolYear + "/classes/" + lastYear[i]).c_str());
        fout << lastYear[i] << endl;
    }
    fout << "0";
    fout.close();
}

vector<string> importLastYear(int year)
{
    ifstream fin;
    ofstream fout;
    string lastSchoolYear = to_string(year - 1) + "-" + to_string(year);
    vector<string> lastYear;
    fout.open(lastSchoolYear + "/classes" + "/classes.txt");
    string classes;
    do
    {
        fin >> classes;
        if ((int(classes[0]) * 10 + int(classes[1])) + 4 < year)
        {
            lastYear.push_back(classes);
        }
    } while (classes != "0");
    fout.close();
    return lastYear;
}
createSemester(int year)
{
    string schoolYear = to_string(year) + "-" + to_string(year + 1);
    for (int i = 1; i < 4; i++)
    {
        cout << "semester" + to_string(i) << endl;
        mkdir((schoolYear + "/semester " + to_string(i)).c_str());
        ifstream fin;
        ofstream fout;
        fout.open(schoolYear + "/semester " + to_string(i) + "/info.txt");
        fout << schoolYear << endl;
        string s;
        cout << "start date" << endl;
        cin >> s;
        fout << s << endl;
        cout << "end date" << endl;
        cin >> s;
        fout << s << endl;
    }
}
// void importListCourses()
// {
// }
// void createCourse(int semester)
// {
// }

void createSchoolYear(int year)
{
    string schoolYear = to_string(year) + "-" + to_string(year + 1);
    mkdir(schoolYear.c_str());
    createSemester(year);
    createClasses(year);
}
int main()
{
    cout << "begin" << endl;
    int year;
    cin >> year;
    createSchoolYear(year);
}