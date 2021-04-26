#include "structLibraryHeader.h"
#ifndef _MENU_H_
#define _MENU_H_

void mainMenu(schoolYear defaultsc, semester defaultsmt);

void semesterMenu(schoolYear defaultsc, semester defaultsmt);
void createASemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt);
void chooseTheSchoolYear(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt);
void inputANumberOfTheSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt);
void inputAStartDateAndAEndDateOfTheSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt);
void create(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt);
void changeDefaultSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt);
void chooseSchoolYear(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt);
void chooseSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt);
void change(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt);
void courseMenu(schoolYear defaultsc, semester defaultsmt);
void addACourse(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void inputCourseID(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void inputCourseName(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void inputTeacherName(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void inputNumberOfCredits(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void inputTheMaximumNumberOfStudents(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void inputCourseSession(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number);
void inputDayOfTheWeek(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number);
void inputTime(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number);
void add(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);

void viewListOfCourse(schoolYear defaultsc, semester defaultsmt);
void viewCourses(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt);
void deleteACourse(schoolYear defaultsc, semester defaultsmt);
void viewChooseDeleteCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt);
void deleteChosenCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt);
void updateCourseInformation(schoolYear defaultsc, semester defaultsmt);
void viewChooseUpdateCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt);
void updateChosenCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void changeCourseID(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void changeCourseName(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void changeTeacherName(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void changeNumberOfCredits(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void changeTheMaximumNumberOfStudents(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);
void changeCourseSession(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number);
void changeDayOfTheWeek(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number);
void changeTime(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number);
void update(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse);

#endif