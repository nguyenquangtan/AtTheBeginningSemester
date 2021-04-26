#include "checkerHeader.h"
#include "menuHeader.h"
#include "utilityHeader.h"

void verify(int& option, int number, int startRow, string askInput) {
	while (option < 1 || option > number) {
		goToXY(0, number + startRow);
		for (int i = 0; i <= number + startRow + 1; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, number + startRow);
		cout << askInput << option;
		goToXY(0, number + startRow + 1);
		for (int i = 0; i <= number + startRow + 1; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, number + startRow + 1);
		cout << "Invalid! Try again: ";
		cin >> option;
	}
}

bool compareDate(date a, date b) { //nếu ngày a lớn hơn ngày b thì trả về true
	if (a.year > b.year)
		return true;
	if (a.year == b.year && a.month > b.month)
		return true;
	if (a.year == b.year && a.month == b.month && a.day > b.day)
		return true;
	return false;
}

bool checkLeapYear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return true;
	return false;
}

bool checkValidDate(date a) {
	if (a.day > 0 && a.day < 30 && a.month == 2 && checkLeapYear(a.year) == true)
		return true;
	if (a.day > 0 && a.day < 29 && a.month == 2 && checkLeapYear(a.year) == false)
		return true;
	if (a.day > 0 && a.day < 32 && (a.month == 1 || a.month == 3 || a.month == 5 || a.month == 7 || a.month == 8 || a.month == 10 || a.month == 12))
		return true;
	if (a.day > 0 && a.day < 31 && (a.month == 4 || a.month == 6 || a.month == 9 || a.month == 11))
		return true;
	return false;
}

void valiDate(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt, date& startDate, date& endDate) {
	while (checkValidDate(startDate) == false || checkValidDate(endDate) == false || compareDate(endDate, startDate) == false) {
		goToXY(0, 4);
		for (int i = 0; i <= 6; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 4);
		cout << "Input a start date of the semester (dd/mm/yyyy): " << setw(2) << setfill('0') << startDate.day << " " << setw(2) << setfill('0') << startDate.month << " " << setw(4) << setfill('0') << startDate.year << "\n";
		cout << "Input a end date of the semester (dd/mm/yyyy): " << setw(2) << setfill('0') << endDate.day << " " << setw(2) << setfill('0') << endDate.month << " " << setw(4) << setfill('0') << endDate.year;
		goToXY(0, 6);
		for (int i = 0; i <= 6; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 6);
		cout << "Invalid! Try again! Start date: ";
		cin >> startDate.day;
		switch (startDate.day) {
		case 0:
			createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
			break;
		default:
			cin >> startDate.month;
			switch (startDate.month) {
			case 0:
				createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
				break;
			default:
				cin >> startDate.year;
				switch (startDate.year) {
				case 0:
					createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
					break;
				default:
					cout << "                    End date: ";
					cin >> endDate.day;
					switch (endDate.day) {
					case 0:
						createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
						break;
					default:
						cin >> endDate.month;
						switch (endDate.month) {
						case 0:
							createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
							break;
						default:
							cin >> endDate.year;
							switch (endDate.year) {
							case 0:
								createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
								break;
							}
						}
					}
				}
			}
		}
	}
	return;
}

bool checkUnduplicatedSemester(semesterNode* pHead, semester tempsmt) {
	if (pHead == nullptr) return true;
	semesterNode* pCur = pHead;
	while (pCur != nullptr && tempsmt.number != pCur->smt.number)
		pCur = pCur->pNext;
	if (pCur != nullptr) return false;
	return true;
}

bool checkTimeOrder(semesterNode* pHead, semester tempsmt) {
	if (pHead == nullptr) return true;
	if (tempsmt.number < pHead->smt.number && compareDate(pHead->smt.startDate, tempsmt.endDate) == true) return true;
	semesterNode* pCur = pHead;
	while (pCur->pNext != nullptr && tempsmt.number > pCur->pNext->smt.number)
		pCur = pCur->pNext;
	if (pCur->pNext != nullptr && compareDate(tempsmt.startDate, pCur->smt.endDate) == true && compareDate(pCur->pNext->smt.startDate, tempsmt.endDate) == true)
		return true;
	if (pCur->pNext == nullptr && compareDate(tempsmt.startDate, pCur->smt.endDate) == true) return true;
	return false;
}

bool checkSemesterExist(semesterNode* pHead, semester tempsmt) {
	if (pHead == nullptr) return false;
	semesterNode* pCur = pHead;
	while (pCur != nullptr && pCur->smt.number != tempsmt.number)
		pCur = pCur->pNext;
	if (pCur != nullptr) return true;
	return false;
}

bool compareString_Same(string a, string b) {
	if (a.size() != b.size()) return false;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] >= 'A' && a[i] <= 'Z')
			a[i] += 32;
		if (b[i] >= 'A' && b[i] <= 'Z')
			b[i] += 32;
		if (a[i] != b[i])
			return false;
	}
	return true;
}

bool compareString_Alphabet(string a, string b) {
	for (int i = 0; i < a.size(); i++)
		if (a[i] >= 'A' && a[i] <= 'Z')
			a[i] += 32;
	for (int j = 0; j < b.size(); j++)
		if (b[j] >= 'A' && b[j] <= 'Z')
			b[j] += 32;
	if (a < b) return false;
	return true;
}

bool checkCourseInfoFulfill(courseInfo newCourse) {
	if (newCourse.ID == "0" || newCourse.ID == "\n" || newCourse.name == "0" || newCourse.name == "\n" || newCourse.teacher == "0" || newCourse.teacher == "\n" ||
		newCourse.credit == 0 || newCourse.session[0].dayOfWeek == "0" || newCourse.session[0].dayOfWeek == "\n" || newCourse.session[0].time.hour == 0 || newCourse.session[0].time.minute == 0 ||
		newCourse.session[1].dayOfWeek == "0" || newCourse.session[1].dayOfWeek == "\n" || newCourse.session[1].time.hour == 0 || newCourse.session[1].time.minute == 0) return false;
	return true;
}

bool checkUnduplicatedCourse(courseNode* pHead, courseInfo newCourse) {
	if (pHead == nullptr) return true;
	courseNode* pCur = pHead;
	while (pCur != nullptr) {
		if (compareString_Same(pCur->course.ID, newCourse.ID) == true && compareString_Same(pCur->course.name, newCourse.name) == true
			&& compareString_Same(pCur->course.teacher, newCourse.teacher) == true && pCur->course.credit == newCourse.credit
			&& pCur->course.student == newCourse.student && compareString_Same(pCur->course.session[0].dayOfWeek, newCourse.session[0].dayOfWeek) == true
			&& pCur->course.session[0].time.hour == newCourse.session[0].time.hour && compareString_Same(pCur->course.session[1].dayOfWeek, newCourse.session[1].dayOfWeek) == true
			&& pCur->course.session[1].time.hour == newCourse.session[1].time.hour) return false;
		pCur = pCur->pNext;
	}
	return true;
}

bool checkFreeTeacher(courseNode* pHead, courseInfo newCourse) {
	if (pHead == nullptr) return true;
	courseNode* pCur = pHead;
	while (pCur != nullptr) {
		if (compareString_Same(pCur->course.teacher, newCourse.teacher) == true && ((compareString_Same(pCur->course.session[0].dayOfWeek, newCourse.session[0].dayOfWeek) == true
			&& pCur->course.session[0].time.hour == newCourse.session[0].time.hour) || (compareString_Same(pCur->course.session[1].dayOfWeek, newCourse.session[1].dayOfWeek) == true
				&& pCur->course.session[1].time.hour == newCourse.session[1].time.hour))) return false;
		pCur = pCur->pNext;
	}
	return true;
}