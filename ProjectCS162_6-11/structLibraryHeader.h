#ifndef _STRUCTLIBRARY_H_
#define _STRUCTLIBRARY_H_
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

struct schoolYearNode { //singly linked list cho school year
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

struct semesterNode { //singly linked list cho semester
	semester smt; //smt = semester viet tat
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
	int student = 50; //mac dinh so luong sinh vien la 50
	courseSession session[2];
};

struct courseNode { //singly linked list cho course
	courseInfo course;
	courseNode* pNext;
};

struct courseDNode { //doubly linked list cho course
	courseInfo course;
	courseDNode* pNext, * pPre;
};

#endif