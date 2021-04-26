#ifndef _COURSE_H_
#define _COURSE_H_
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <direct.h>
#include <iomanip>
using namespace std;

struct schoolYear {
	int startYear;
	int endYear;
};

struct schoolYearNode {
	schoolYear sc; //sc = school year viet tat
	schoolYearNode* pNext;
};

struct date {
	int day;
	int month;
	int year;
};

struct semester {
	int number;
	date startDate;
	date endDate;
};

struct semesterNode {
	semester smt; // smt = semester viet tat
	semesterNode* pNext;
};

struct schedule {
	int hour;
	int minute;
};

struct courseSession {
	string dayOfWeek;
	schedule time;
};

struct courseInfo {
	string ID;
	string name;
	string teacher;
	int credit;
	int student = 50;
	courseSession session[2];
};

struct courseNode {
	courseInfo course;
	courseNode* pNext;
};

struct courseDNode {
	courseInfo course;
	courseDNode* pNext, *pPre;
};

void goToXY(SHORT posX, SHORT posY);



void verify(int& option, int number, int startRow); //////////////////////////////////////////////////////////////////////
void mainMenu(schoolYear defaultsc, semester defaultsmt);////////////////////////////////////////////////////////////
int convertStringToInt(string a);
void loadSchoolYear(ifstream& fin, schoolYearNode*& pHead, string path); //////////////////////////////////////////////////
void deleteSchoolYear(schoolYearNode*& pHead); ////////////////////////////////////////////////////////////////////////////
void changeDefaultSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt); ////////////////////////////////
void chooseSchoolYear(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt); ////////////////////////////////////
date convertStringToDate(string a);
void loadSemester(ifstream& fin, semesterNode*& pHead, string path);/////////////////////////////////////////////////////////////////////
void deleteSemester(semesterNode*& pHead);/////////////////////////////////////////////////////////////////////////////////////////////////
void chooseSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt); ///////////////////////////////////////
bool checkSemesterExist(semesterNode* pHead, semester a); //////////////////////////////////////////////////
void change(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt); /////////////////////////////////
void courseMenu(schoolYear& defaultsc, semester& defaultsmt); ////////////////////////////////////////
void addACourse(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse); /////////////////////////////////////////////
void inputCourseID(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse); /////////////////////////////////////////
void inputCourseName(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse); ///////////////////////////////////////////
void inputTeacherName(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse); //////////////////////////////////////////
void inputNumberOfCredits(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse); //////////////////////////////////////
void inputTheMaximumNumberOfStudents(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse); ////////////////////////////////////
void inputCourseSession(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int number); //////////////////////////////////////
void inputDayOfTheWeek(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int number); /////////////////////////////////////
void inputTime(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int number); /////////////////////////////////////////////
schedule convertStringToSchedule(string a);
void loadCourse(ifstream& fin, courseNode*& pHead, string path); //////////////////////////////////////////////////
void deleteCourse(courseNode*& pHead); //////////////////////////////////////////////////////////////////////////////
void addCourse(courseNode*& pHead, courseInfo newCourse); ///////////////////////////////////////////////////////////
void saveCourse(ofstream& fout, courseNode* pHead, string path);/////////////////////////////////////////////////////
bool compareString_Same(string a, string b); ///////////////////////////////////////////////////////////////////////
bool compareString_Alphabet(string a, string b); ////////////////////////////////////////////////////////////////
bool checkUnduplicatedCourse(courseNode* pHead, courseInfo newCourse); ///////////////////////////////////////////
bool checkFreeTeacher(courseNode* pHead, courseInfo newCourse); ////////////////////////////////////////////////////
void add(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);////////////////////////////////////////
void loadDCourse(ifstream& fin, courseDNode*& pHead, string path);///////////////////////////////////////////////
void deleteDCourse(courseDNode*& pHead);///////////////////////////////////////////////////////////////////////////////
void saveDCourse(ofstream& fout, courseDNode* pHead, string path);////////////////////////////////////////////////////








void viewListOfCourse(schoolYear& defaultsc, semester& defaultsmt);
void viewCourses(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt);
void deleteACourse(schoolYear& defaultsc, semester& defaultsmt);
void viewChooseDeleteCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt);
void deleteChosenCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt);
void updateCourseInformation(schoolYear& defaultsc, semester& defaultsmt);
void viewChooseUpdateCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt);
void updateChosenCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo newCourse);
void changeCourseID(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);
void changeCourseName(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);
void changeTeacherName(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);
void changeNumberOfCredits(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);
void changeTheMaximumNumberOfStudents(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo newCourse);
//void changeCourseSession(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo newCourse, int number);
//void changeDayOfTheWeek(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo newCourse, int number);
//void changeTime(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo newCourse, int number);

#endif 
