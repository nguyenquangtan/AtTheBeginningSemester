#include "structLibraryHeader.h"
#ifndef _CHECKER_H_
#define _CHECKER_H_

void verify(int& option, int number, int startRow, string askInput);
bool compareDate(date a, date b);
bool checkLeapYear(int year);
bool checkValidDate(date a);
void valiDate(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt, date& startDate, date& endDate);
bool checkUnduplicatedSemester(semesterNode* pHead, semester tempsmt);
bool checkTimeOrder(semesterNode* pHead, semester tempsmt);
bool checkSemesterExist(semesterNode* pHead, semester tempsmt); //thay doi default semester thi can check xem co semester do khong, vi du nhu academic staff thay doi semester 0 cua school year 0000 - 0000 thi sai roi
bool compareString_Same(string a, string b); //so sanh 2 string giong nhau khong
bool compareString_Alphabet(string a, string b); //so sanh theo thu tu alphabet
bool checkCourseInfoFulfill(courseInfo newCourse); //truoc khi tao course thi phai check xem moi thong tin da duoc dien het chua: course ID, course name...
bool checkUnduplicatedCourse(courseNode* pHead, courseInfo newCourse); //check xem course da duoc tao truoc do chua de tranh 2 course giong nhau 
bool checkFreeTeacher(courseNode* pHead, courseInfo newCourse); //khi ma add course thi can check xem giao vien co ranh khong vi co khi giao vien dang day mon khac

#endif