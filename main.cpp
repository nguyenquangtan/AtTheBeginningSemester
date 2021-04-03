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
void displayLogin();
// void displaySignUp();
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
    fin.open(lastSchoolYear + "/classes" + "/classes.txt");
    string classes;
    do
    {
        fin >> classes;
        if ((int(classes[0]) * 10 + int(classes[1])) + 4 < year)
        {
            lastYear.push_back(classes);
        }
    } while (classes != "0");
    fin.close();
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
bool checkStaffOrStudent(string tk)
{
    ifstream fin;
    ofstream fout;
    fin.open("User/user.txt");
    string user;
    bool check;
    while (true)
    {
        fin >> user;
        fin >> check;

        if (user == tk)
        {
            return check;
            break;
        }
    }
    fin.close();
}
void parsePass(string &pass)
{
    for (int i = 0; i < pass.length(); i++)
    {
        pass[i] = char(int(pass[i]) - 123);
    }
}
void login(string tk)
{
    ifstream fin;
    ofstream fout;
    string passwordData, passwordUser;
    while (true)
    {
        if (checkStaffOrStudent(tk) == 1)
        {
            cout << "staff" << endl;
            fin.open("User/staff/" + tk + "/" + tk + ".txt");
        }
        else if (checkStaffOrStudent(tk) == 0)
        {
            cout << "student" << endl;
            fin.open("User/student/" + tk + "/" + tk + ".txt");
        }
        fin >> passwordData;
        cout << "pass: ";
        cin >> passwordUser;
        parsePass(passwordData);
        if (passwordData == passwordUser)
        {
            cout << "login sucess";
            break;
        }
        fin.close();
    }
}
void enPass(string &pass)
{
    for (int i = 0; i < pass.length(); i++)
    {
        pass[i] = char(int(pass[i]) + 123);
    }
}
void changePass(string tk)
{
    ifstream fin;
    ofstream fout;
    string dir;
    if (checkStaffOrStudent(tk) == 1)
    {
        dir = "User/staff";
    }
    else if (checkStaffOrStudent(tk) == 0)
    {
        dir = "User/student";
    }
    fout.open(dir + "/" + tk + "/" + tk + ".txt");
    string password;
    cout << "pass? : ";
    cin >> password;
    enPass(password);
    fout << password;
    fout.close();
    displayLogin();
}
void viewProfile()
{
}
void createProfile(string dir, string tk, string choose)
{
    ifstream fin;
    ofstream fout;
    fout.open(dir + "/" + tk + "/" + "info.txt");
    fout << choose;
    //nhập info j đó dô cho acc đó
    fout.close();
}
void signUp()
{
    string tk;
    cout << "tk? : ";
    cin >> tk;
    string choose;
    cout << "staff/student? : ";
    cin >> choose;
    string password;
    cout << "pass? : ";
    cin >> password;
    ifstream fin;
    ofstream fout;
    mkdir("User");
    mkdir("User/staff");
    mkdir("User/student");
    string dir;
    fout.open("User/user.txt", ios::app);
    if (choose == "staff")
    {
        fout << tk << endl
             << 1 << endl;
        dir = "User/staff";
    }
    else if (choose == "student")
    {
        fout << tk << endl
             << 0 << endl;
        dir = "User/student";
    }
    fout.close();
    mkdir((dir + "/" + tk).c_str());
    fout.open(dir + "/" + tk + "/" + tk + ".txt");
    enPass(password);
    fout << password;
    cout << "end";
    fout.close();
    createProfile(dir, tk, choose);
}
void displayBegin()
{
    cout << "Login/Sign up" << endl;
    string s;
    cin >> s;
    if (s == "Login")
    {
        displayLogin();
    }
    else if (s == "Sign up")
    {
        signUp();
    }
}
void displayStaff()
{
    cout << "Staff" << endl;
}
void displayStudent()
{
    cout << "Student" << endl;
}
void displayLogin()
{
    string tk;
    cout << "user: ";
    cin >> tk;
    login(tk);
    cout << endl;
    cout << "View profile/Change Password/Logout/Next" << endl;
    int s;
    cin >> s;
    if (s == 1)
    {
        viewProfile();
    }
    else if (s == 2)
    {
        changePass(tk);
    }
    else if (s == 3)
    {
        return;
    }
    else if (s == 4)
    {
        if (checkStaffOrStudent(tk))
        {
            displayStaff();
        }
        else
        {
            displayStudent();
        }
    }
}

int main()
{
    cout << "begin" << endl;
    // int year;
    // cin >> year;
    // createSchoolYear(year);
    // signUp();
    displayBegin();
};