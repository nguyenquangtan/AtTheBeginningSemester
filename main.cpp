// đọc thấy thiếu chức năng j thì ns t để t suy nghĩ đặt nó ở đâu
// ns chung này là cơ bản rồi, add từng chức năng vào như là đọc file csv rồi đọc dữ liệu từ data nữa là xong
// các phần create coi như là ổn
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
    // sau chỗ này sẽ tạo các folder student
    // vd sv Trương Đức Thắng sẽ có folder là Trương Đức Thắng hay folder mssv j đó
    // trong đó chứa file info.txt và file scoreboard
    // Và tạo thêm file scoreBoard chung cho cả lớp nữa
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
createCourse(int year, int semester)
{
    string schoolYear = to_string(year) + "-" + to_string(year + 1);
    ifstream fin;
    ofstream fout;
    fout.open(schoolYear + "/semester" + to_string(semester) + "/courses.txt");
    string s;
    do
    {
        cin >> s;
        if (s != "0")
        {
            fout << s;
        }

    } while (s != "0");
    fout.close();
    //sau chỗ này tạo các file course.txt
    // vd như là có môn calculas 2 thì sẽ ra file calculas 2.txt
    // và trong file đó sẽ chứa các thông tin của môn học đó
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