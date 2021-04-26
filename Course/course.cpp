#include "header.h"

void goToXY(SHORT posX, SHORT posY) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;
	SetConsoleCursorPosition(hStdout, Position);
}

//string
void verify(int& option, int number, int startRow) { 
	while (option < 1 || option > number) {    
		goToXY(0, number + startRow);
		for (int i = 0; i <= number + startRow + 1; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, number + startRow);
		cout << "Input your option: " << option;
		goToXY(0, number + startRow + 1);
		for (int i = 0; i <= number + startRow + 1; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, number + startRow + 1);
		cout << "Invalid! Try again: ";
		cin >> option;
	}
}

void mainMenu(schoolYear defaultsc, semester defaultsmt) {
	system("cls");
	int option;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << defaultsc.startYear << "-" << setw(4) << setfill('0') << defaultsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << defaultsmt.number << "\n";
	cout << "1. Semester\n";
	cout << "2. Course Registration Session\n";
	cout << "3. Course\n";
	cout << "4. Change default semester\n";
	cout << "5. Exit\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 5, 2); /////////////////////////////////////////////////////////////////////////
	switch (option) {
	case 1:
		cout << "Temporarily closed\n";
		break;
	case 2:
		cout << "Temporarily closed\n";
		break;
	case 3:
		courseMenu(defaultsc, defaultsmt);
		break;
	case 4:
		schoolYear tempsc = defaultsc; 
		semester tempsmt = defaultsmt;
		changeDefaultSemester(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	default:
		cout << "And it's the end!\n";
	}
	return;
}

int convertStringToInt(string a) {
	int result = 0;
	for (int i = 0; i < a.size(); i++) {
		result *= 10;
		result += int(a[i] - '0');
	}
	return result;
}

void loadSchoolYear(ifstream& fin, schoolYearNode*& pHead, string path) {
	fin.open(path);
	if (!fin.is_open()) { ///////////////////////////////////////////////
		return;
	}
	string startYear, endYear;
	schoolYearNode* pCur = nullptr;
	while (!fin.eof()) {
		getline(fin, startYear, ',');
		getline(fin, endYear);
		if (pHead == nullptr) {
			pHead = new schoolYearNode;
			pCur = pHead;
		}
		else {
			pCur->pNext = new schoolYearNode;
			pCur = pCur->pNext;
		}
		pCur->sc.startYear = convertStringToInt(startYear);
		pCur ->sc.endYear = convertStringToInt(endYear);
		pCur->pNext = nullptr;
	}
	fin.close();
}

void deleteSchoolYear(schoolYearNode*& pHead) {
	schoolYearNode* pCur = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pCur;
		pCur = pHead;
	}
}

void changeDefaultSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	int option;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	cout << "1. Choose school year\n";
	cout << "2. Choose semester\n";
	cout << "3. Change\n";
	cout << "4. Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 4, 2); ////////////////////////////////////////////////////////////////////////////////////////
	switch (option) {
	case 1:
		chooseSchoolYear(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	case 2:
		chooseSemester(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	case 3:
		change(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	default:
		mainMenu(defaultsc, defaultsmt);
	}
	return;
}

void chooseSchoolYear(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	int option, i = 0;
	string path = "Data/schoolyear.csv";
	ifstream fin;
	schoolYearNode* pHead = nullptr;
	loadSchoolYear(fin, pHead, path); // neu ma chua tao cai school year nao thi sao?
	schoolYearNode* pCur = pHead;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	while (pCur != nullptr) {
		cout << ++i << ". " << setw(4) << setfill('0') << pCur->sc.startYear << "-" << setw(4) << setfill('0') << pCur->sc.endYear << "\n";
		pCur = pCur->pNext;
	}
	cout << ++i << ". Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, i, 2); /////////////////////////////////////////////////
	if (option == i) {
		changeDefaultSemester(defaultsc, defaultsmt, tempsc, tempsmt);
		return;
	}
	pCur = pHead;
	for (int i = 0; i < option - 1; i++)
		pCur = pCur->pNext;
	tempsc = pCur->sc;
	deleteSchoolYear(pHead);
	chooseSchoolYear(defaultsc, defaultsmt, tempsc, tempsmt);
	return;
}

date convertStringToDate(string a) {
	date result;
	result.day = 0;
	result.month = 0;
	result.year = 0;
	for (int i = 0; i < 2; i++) {
		result.day *= 10;
		result.day += int(a[i] - '0');
	}
	for (int i = 2; i < 4; i++) {
		result.month *= 10;
		result.month += int(a[i] - '0');
	}
	for (int i = 4; i < 8; i++) {
		result.year *= 10;
		result.year += int(a[i] - '0');
	}
	return result;
}

void loadSemester(ifstream& fin, semesterNode*& pHead, string path) {
	fin.open(path);
	if (!fin.is_open()) {
		return;
	}
	string number, startDate, endDate;
	semesterNode* pCur = nullptr;
	while (!fin.eof()) {
		getline(fin, number, ',');
		getline(fin, startDate, ',');
		getline(fin, endDate);
		if (pHead == nullptr) {
			pHead = new semesterNode;
			pCur = pHead;
		}
		else {
			pCur->pNext = new semesterNode;
			pCur = pCur->pNext;
		}
		pCur->smt.number = convertStringToInt(number);
		pCur->smt.startDate = convertStringToDate(startDate);
		pCur->smt.endDate = convertStringToDate(endDate);
		pCur->pNext = nullptr;
	}
	fin.close();
}

void deleteSemester(semesterNode*& pHead) {
	semesterNode* pCur = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pCur;
		pCur = pHead;
	}
}

void chooseSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	int option, i = 0;
	string path = "Data/" + to_string(tempsc.startYear) + "-" + to_string(tempsc.endYear) + "/semester.csv";
	ifstream fin;
	semesterNode* pHead = nullptr;
	loadSemester(fin, pHead, path);
	semesterNode* pCur = pHead;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	if (pHead == nullptr) {
		cout << "Create a semester for the current default school year or choose another school year to continue!\n";
		cout << "1. Create a semester\n";
		cout << "2. Choose school year\n";
		cout << "3. Back\n";
		cout << "Input your option: ";
		cin >> option;
		verify(option, 3, 3);
		switch (option) {
		case 1:
			cout << "Temporarily closed\n";
			break;
		case 2:
			chooseSchoolYear(defaultsc, defaultsmt, tempsc, tempsmt);
			break;
		default:
			changeDefaultSemester(defaultsc, defaultsmt, tempsc, tempsmt);
		}
		return;
	}
	while (pCur != nullptr) {
		cout << ++i << ". Semester " << setw(2) << setfill('0') << pCur->smt.number << "\n";
		pCur = pCur->pNext;
	}
	cout << ++i << ". Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, i, 2);
	if (option == i) {
		changeDefaultSemester(defaultsc, defaultsmt, tempsc, tempsmt);
		return;
	}
	pCur = pHead;
	for (int i = 0; i < option - 1; i++)
		pCur = pCur->pNext;
	tempsmt = pCur->smt;
	deleteSemester(pHead);
	chooseSemester(defaultsc, defaultsmt, tempsc, tempsmt);
	return;
}

bool checkSemesterExist(semesterNode* pHead, semester a) {
	if (pHead == nullptr) return false;
	semesterNode* pCur = pHead;
	while (pCur != nullptr && pCur->smt.number != a.number)
		pCur = pCur->pNext;
	if (pCur != nullptr) return true;
	return false;
}

void change(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	int option;
	string path = "Data/" + to_string(tempsc.startYear) + "-" + to_string(tempsc.endYear) + "/semester.csv";
	ifstream fin;
	semesterNode* pHead = nullptr;
	loadSemester(fin, pHead, path);
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	if (pHead == nullptr || (pHead != nullptr && checkSemesterExist(pHead, tempsmt) == false)) {
		cout << "Create a semester for the current default school year or go back to choose another school year or semester to continue!\n";
		cout << "1. Create a semester\n";
		cout << "2. Back\n";
		cout << "Input your option: ";
		cin >> option;
		verify(option, 2, 3);
		switch (option) {
		case 1:
			cout << "Temporarily closed\n";
			break;
		default:
			changeDefaultSemester(defaultsc, defaultsmt, tempsc, tempsmt);
		}
		return;
	}
	defaultsc = tempsc;
	defaultsmt = tempsmt;
	cout << "Change default semester successfully!\n";
	cout << "1. Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 1, 3);
	deleteSemester(pHead);
	changeDefaultSemester(defaultsc, defaultsmt, tempsc, tempsmt);
	return;
}

void courseMenu(schoolYear& defaultsc, semester& defaultsmt) {
	system("cls");
	int option;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << defaultsc.startYear << "-" << setw(4) << setfill('0') << defaultsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << defaultsmt.number << "\n";
	if (defaultsmt.number == 0 || defaultsc.startYear == 0 || defaultsc.endYear == 0) {
		cout << "Create a semester or change default semester to continue!\n";
		cout << "1. Create a semester\n";
		cout << "2. Change default semester\n";
		cout << "Input your option: ";
		cin >> option;
		verify(option, 2, 3);
		switch (option) {
		case 1:
			cout << "Temporarily closed\n";
			break;
		default:
			schoolYear tempsc = defaultsc;
			semester tempsmt = defaultsmt;
			changeDefaultSemester(defaultsc, defaultsmt, tempsc, tempsmt);
		}
		return;
	}
	courseInfo newCourse;
	newCourse.ID = "0";
	newCourse.name = "0";
	newCourse.teacher = "0";
	newCourse.credit = 0;
	newCourse.session[0].dayOfWeek = "0";
	newCourse.session[0].time.hour = 0;
	newCourse.session[0].time.minute = 0;
	newCourse.session[1].dayOfWeek = "0";
	newCourse.session[1].time.hour = 0;
	newCourse.session[1].time.minute = 0;
	cout << "1. Add a course\n";
	cout << "2. View list of course\n";
	cout << "3. Update course information\n";
	cout << "4. Delete a course\n";
	cout << "5. Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 5, 2);
	switch (option) {
	case 1:
		addACourse(defaultsc, defaultsmt, newCourse);
		break;
	case 2:
		viewListOfCourse(defaultsc, defaultsmt);
		break;
	case 3:
		updateCourseInformation(defaultsc, defaultsmt);
		break;
	case 4:
		deleteACourse(defaultsc, defaultsmt);
		break;
	default:
		mainMenu(defaultsc, defaultsmt);
		return;
	}
}

void addACourse(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	int option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "1. Input course ID\n";
	cout << "2. Input course name\n";
	cout << "3. Input teacher name\n";
	cout << "4. Input number of credits\n";
	cout << "5. Input the maximum number of students\n";
	cout << "6. Input course session 1\n";
	cout << "7. Input course session 2\n";
	cout << "8. Add\n";
	cout << "9. Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 9, 7);
	switch (option) {
	case 1:
		inputCourseID(defaultsc, defaultsmt, newCourse);
		break;
	case 2:
		inputCourseName(defaultsc, defaultsmt, newCourse);
		break;
	case 3:
		inputTeacherName(defaultsc, defaultsmt, newCourse);
		break;
	case 4:
		inputNumberOfCredits(defaultsc, defaultsmt, newCourse);
		break;
	case 5:
		inputTheMaximumNumberOfStudents(defaultsc, defaultsmt, newCourse);
		break;
	case 6:
		inputCourseSession(defaultsc, defaultsmt, newCourse, 0);
		break;
	case 7:
		inputCourseSession(defaultsc, defaultsmt, newCourse, 1);
		break;
	case 8:
		add(defaultsc, defaultsmt, newCourse);
		break;
	default:
		courseMenu(defaultsc, defaultsmt);
		return;
	}
}

void inputCourseID(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	string option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "Input course ID or 1 to Back: ";
	cin.ignore(100, '\n');
	getline(cin, option);
	if (option.size() == 1 && option[0] == '1') {
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
	newCourse.ID = option;
	inputCourseID(defaultsc, defaultsmt, newCourse);
}

void inputCourseName(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	string option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "Input course name or 1 to Back: ";
	cin.ignore(100, '\n');
	getline(cin, option);
	cout << option;
	if (option.size() == 1 && option[0] == '1') {
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
	newCourse.name = option;
	inputCourseName(defaultsc, defaultsmt, newCourse);
}

void inputTeacherName(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	string option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "Input teacher name or 1 to Back: ";
	cin.ignore(100, '\n');
	getline(cin, option);
	if (option.size() == 1 && option[0] == '1') {
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
	newCourse.teacher = option;
	inputTeacherName(defaultsc, defaultsmt, newCourse);
}

void inputNumberOfCredits(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	int option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "Input number of credits or 0 to Back: ";
	cin >> option;
	while (option < 0) {
		goToXY(0, 7);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 7);
		cout << "Input number of credits or 0 to Back: " << option;
		goToXY(0, 8);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 8);
		cout << "Invalid! Try again: ";
		cin >> option;
	}
	switch (option) {
	case 0:
		addACourse(defaultsc, defaultsmt, newCourse);
		break;
	default:
		newCourse.credit = option;
		inputNumberOfCredits(defaultsc, defaultsmt, newCourse);
		return;
	}
}

void inputTheMaximumNumberOfStudents(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	int option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "Input the maximum number of students or 0 to Back: ";
	cin >> option;
	while (option < 0) {
		goToXY(0, 7);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 7);
		cout << "Input the maximum number of students or 0 to Back: " << option;
		goToXY(0, 8);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 8);
		cout << "Invalid! Try again: ";
		cin >> option;
	}
	switch (option) {
	case 0:
		addACourse(defaultsc, defaultsmt, newCourse);
		break;
	default:
		newCourse.student = option;
		inputTheMaximumNumberOfStudents(defaultsc, defaultsmt, newCourse);
		return;
	}
}

void inputCourseSession(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int number) {
	system("cls");
	int option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "1. Input day of the week\n";
	cout << "2. Input time\n";
	cout << "3. Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 3, 7);
	switch (option) {
	case 1:
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, number);
		break;
	case 2:
		inputTime(defaultsc, defaultsmt, newCourse, number);
		break;
	default:
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
}

void inputDayOfTheWeek(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int number) {
	system("cls");
	int option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "1. MON\n";
	cout << "2. TUE\n";
	cout << "3. WED\n";
	cout << "4. THU\n";
	cout << "5. FRI\n";
	cout << "6. SAT\n";
	cout << "7. SUN\n";
	cout << "8. Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 8, 7);
	switch (option) {
	case 1:
		newCourse.session[number].dayOfWeek = "MON";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, number);
		break;
	case 2:
		newCourse.session[number].dayOfWeek = "TUE";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, number);
		break;
	case 3:
		newCourse.session[number].dayOfWeek = "WED";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, number);
		break;
	case 4:
		newCourse.session[number].dayOfWeek = "THU";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, number);
		break;
	case 5:
		newCourse.session[number].dayOfWeek = "FRI";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, number);
		break;
	case 6:
		newCourse.session[number].dayOfWeek = "SAT";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, number);
		break;
	case 7:
		newCourse.session[number].dayOfWeek = "SUN";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, number);
		break;
	default:
		inputCourseSession(defaultsc, defaultsmt, newCourse, number);
		return;
	}
}

void inputTime(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int number) {
	system("cls");
	int option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "1. S1(07:30)\n";
	cout << "2. S2(9:30)\n";
	cout << "3. S3(13:30)\n";
	cout << "4. S4(15:30)\n";
	cout << "5. Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 5, 7);
	switch (option) {
	case 1:
		newCourse.session[number].time.hour = 7;
		newCourse.session[number].time.minute = 30;
		inputTime(defaultsc, defaultsmt, newCourse, number);
		break;
	case 2:
		newCourse.session[number].time.hour = 9;
		newCourse.session[number].time.minute = 30;
		inputTime(defaultsc, defaultsmt, newCourse, number);
		break;
	case 3:
		newCourse.session[number].time.hour = 13;
		newCourse.session[number].time.minute = 30;
		inputTime(defaultsc, defaultsmt, newCourse, number);
		break;
	case 4:
		newCourse.session[number].time.hour = 15;
		newCourse.session[number].time.minute = 30;
		inputTime(defaultsc, defaultsmt, newCourse, number);
		break;
	default:
		inputCourseSession(defaultsc, defaultsmt, newCourse, number);
		return;
	}
}

schedule convertStringToSchedule(string a) {
	schedule result;
	result.hour = 0;
	result.minute = 0;
	for (int i = 0; i < 2; i++) {
		result.hour *= 10;
		result.hour += int(a[i] - '0');
	}
	for (int i = 2; i < 4; i++) {
		result.minute *= 10;
		result.minute += int(a[i] - '0');
	}
	return result;
}

void loadCourse(ifstream& fin, courseNode*& pHead, string path) {
	fin.open(path);
	if (!fin.is_open()) {
		return;
	}
	string ID,name,teacher,credit,student,dayOfWeek[2], time[2];
	courseNode* pCur = nullptr;
	while (!fin.eof()) {
		getline(fin, ID, ',');
		getline(fin, name, ',');
		getline(fin, teacher, ',');
		getline(fin, credit, ',');
		getline(fin, student, ',');
		getline(fin, dayOfWeek[0], ',');
		getline(fin, time[0], ',');
		getline(fin, dayOfWeek[1], ',');
		getline(fin, time[1]);
		if (pHead == nullptr) {
			pHead = new courseNode;
			pCur = pHead;
		}
		else {
			pCur->pNext = new courseNode;
			pCur = pCur->pNext;
		}
		pCur->course.ID = ID;
		pCur->course.name = name;
		pCur->course.teacher = teacher;
		pCur->course.credit = convertStringToInt(credit);
		pCur->course.student = convertStringToInt(student);
		pCur->course.session[0].dayOfWeek = dayOfWeek[0];
		pCur->course.session[0].time = convertStringToSchedule(time[0]);
		pCur->course.session[1].dayOfWeek = dayOfWeek[1];
		pCur->course.session[1].time = convertStringToSchedule(time[1]);
		pCur->pNext = nullptr;
	}
	fin.close();
}

void deleteCourse(courseNode*& pHead) {
	courseNode* pCur = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pCur;
		pCur = pHead;
	}
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

void addCourse(courseNode*& pHead, courseInfo newCourse) {
	courseNode* pIns = nullptr;
	if (pHead == nullptr) {
		pIns = new courseNode;
		pIns->course = newCourse;
		pIns->pNext = nullptr;
		pHead = pIns;
		return;
	}
	courseNode* pCur = pHead;
	while (pCur->pNext != nullptr && compareString_Alphabet(pCur->pNext->course.ID, newCourse.ID) == false)
		pCur = pCur->pNext;
	pIns = new courseNode;
	pIns->course = newCourse;
	pIns->pNext = pCur->pNext;
	pCur->pNext = pIns;
}

void saveCourse(ofstream& fout, courseNode* pHead, string path) {
	fout.open(path);
	if (!fout.is_open()) {
		return; ////////////////////////////////////////////////////////////
	}
	if (pHead == nullptr) return;
	courseNode* pCur = pHead;
	while (pCur != nullptr) {
		fout << pCur->course.ID << ',' << pCur->course.name << ',' << pCur->course.teacher << ',' << pCur->course.credit << ',' << pCur->course.student << ',';
		fout << pCur->course.session[0].dayOfWeek << ',';
		fout << setw(2) << setfill('0') << pCur->course.session[0].time.hour << setw(2) << setfill('0') << pCur->course.session[0].time.minute << ',';
		fout << pCur->course.session[1].dayOfWeek << ',';
		fout << setw(2) << setfill('0') << pCur->course.session[1].time.hour << setw(2) << setfill('0') << pCur->course.session[1].time.minute;
		if (pCur->pNext != nullptr)
			fout << "\n";
		pCur = pCur->pNext;
	}
	fout.close();
}

//check CS162 folder created, nhieu lop co the hoc cung 1 mon, check inf0da dien het chua

void add(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	int option;
	string path = "Data/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	ifstream fin;
	ofstream fout;
	courseNode* pHead = nullptr;
	loadCourse(fin, pHead, path);
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	if (checkUnduplicatedCourse(pHead, newCourse) == false || checkFreeTeacher(pHead, newCourse) == false) {
		cout << "Has not been successfully created!\n";
		cout << "Course has already been created before or teacher is not free! Change course information to continue!\n";
		cout << "Input 1 to Back: ";
		cin >> option;
		verify(option, 1, 8);
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
	path = "Data/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/" + newCourse.ID;
	int newCourseFolder = _mkdir(path.c_str());
	if (newCourseFolder != 0) {
		deleteCourse(pHead);
		cout << "Has not been successfully created!\n";
		cout << "Cannot create new course folder!\n";
		cout << "1. Try again\n";
		cout << "2. Back\n";
		cout << "Input your option: ";
		cin >> option;
		verify(option, 2, 9);
		switch (option) {
		case 1:
			add(defaultsc, defaultsmt, newCourse);
			break;
		default:
			addACourse(defaultsc, defaultsmt, newCourse);
		}
		return;
	}
	path = "Data/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	addCourse(pHead, newCourse);
	saveCourse(fout, pHead, path);
	deleteCourse(pHead);
	cout << "Has been successfully created!\n";
	cout << "Input 1 to Back: ";
	cin >> option;
	verify(option, 1, 7);
	addACourse(defaultsc, defaultsmt, newCourse);
}

void loadDCourse(ifstream& fin, courseDNode*& pHead, string path) {
	fin.open(path);
	if (!fin.is_open()) {
		return;
	}
	string ID, name, teacher, credit, student, dayOfWeek[2], time[2];
	courseDNode* pCur = nullptr;
	while (!fin.eof()) {
		getline(fin, ID, ',');
		getline(fin, name, ',');
		getline(fin, teacher, ',');
		getline(fin, credit, ',');
		getline(fin, student, ',');
		getline(fin, dayOfWeek[0], ',');
		getline(fin, time[0], ',');
		getline(fin, dayOfWeek[1], ',');
		getline(fin, time[1]);
		if (pHead == nullptr) {
			pHead = new courseDNode;
			pCur = pHead;
			pCur->pPre = nullptr;
		}
		else {
			pCur->pNext = new courseDNode;
			pCur->pNext->pPre = pCur;
			pCur = pCur->pNext;
		}
		pCur->course.ID = ID;
		pCur->course.name = name;
		pCur->course.teacher = teacher;
		pCur->course.credit = convertStringToInt(credit);
		pCur->course.student = convertStringToInt(student);
		pCur->course.session[0].dayOfWeek = dayOfWeek[0];
		pCur->course.session[0].time = convertStringToSchedule(time[0]);
		pCur->course.session[1].dayOfWeek = dayOfWeek[1];
		pCur->course.session[1].time = convertStringToSchedule(time[1]);
		pCur->pNext = nullptr;
	}
	fin.close();
}

void deleteDCourse(courseDNode*& pHead) {
	courseDNode* pCur = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pCur;
		pCur = pHead;
	}
}

void saveDCourse(ofstream& fout, courseDNode* pHead, string path) {
	fout.open(path);
	if (!fout.is_open()) {
		return; ////////////////////////////////////////////////////////////
	}
	if (pHead == nullptr) return;
	courseDNode* pCur = pHead;
	while (pCur != nullptr) {
		fout << pCur->course.ID << ',' << pCur->course.name << ',' << pCur->course.teacher << ',' << pCur->course.credit << ',' << pCur->course.student << ',';
		fout << pCur->course.session[0].dayOfWeek << ',';
		fout << setw(2) << setfill('0') << pCur->course.session[0].time.hour << setw(2) << setfill('0') << pCur->course.session[0].time.minute << ',';
		fout << pCur->course.session[1].dayOfWeek << ',';
		fout << setw(2) << setfill('0') << pCur->course.session[1].time.hour << setw(2) << setfill('0') << pCur->course.session[1].time.minute;
		if (pCur->pNext != nullptr)
			fout << "\n";
		pCur = pCur->pNext;
	}
	fout.close();
}

void viewListOfCourse(schoolYear& defaultsc, semester& defaultsmt) {
	string path = "Data/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	ifstream fin;
	courseDNode* pHead = nullptr;
	loadDCourse(fin, pHead, path);
	courseDNode* pCur = pHead;
	viewCourses(pHead, pCur, defaultsc, defaultsmt);
}

void viewCourses(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt) {
	system("cls");
	int option, i = 0;
	if (pCur == nullptr) { /////////////////////////////////////////////
		cout << "None of courses have been created\n";
		cout << "Input 1 to Back: ";
		cin >> option;
		verify(option, 1, 0);
		deleteDCourse(pHead);
		courseMenu(defaultsc, defaultsmt);
		return;
	}
	cout << "Course ID: " << pCur->course.ID << "\n";
	cout << "Course name: " << pCur->course.name << "\n";
	cout << "Teacher name: " << pCur->course.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << pCur->course.credit << "\tMaximum number of students: " << pCur->course.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << pCur->course.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << pCur->course.session[0].time.hour << ":" << setw(2) << setfill('0') << pCur->course.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << pCur->course.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << pCur->course.session[1].time.hour << ":" << setw(2) << setfill('0') << pCur->course.session[1].time.minute << "\n";
	if (pCur ->pNext != nullptr)
		cout << ++i << ". Next\n";
	if (pCur -> pPre != nullptr)
		cout << ++i << ". Previous\n";
	cout << ++i << ". Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, i, 6);
	switch (option) {
		case 1:
		{
			if (pCur->pNext == nullptr && pCur->pPre == nullptr) {
				deleteDCourse(pHead);
				courseMenu(defaultsc, defaultsmt);
			}

			if (pCur->pNext == nullptr)
				viewCourses(pHead, pCur->pPre, defaultsc, defaultsmt);

			viewCourses(pHead, pCur->pNext, defaultsc, defaultsmt);
			break;
		}
		case 2:
		{
			if (pCur->pNext == nullptr || pCur->pPre == nullptr) {
				deleteDCourse(pHead);
				courseMenu(defaultsc, defaultsmt);
			}

			viewCourses(pHead, pCur->pPre, defaultsc, defaultsmt);
			break;
		}
		default:
		{
			deleteDCourse(pHead);
			courseMenu(defaultsc, defaultsmt);
		}
	}
	return;
}

void deleteACourse(schoolYear& defaultsc, semester& defaultsmt) {
	string path = "Data/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	ifstream fin;
	courseDNode* pHead = nullptr;
	loadDCourse(fin, pHead, path);
	courseDNode* pCur = pHead;
	viewChooseDeleteCourse(pHead, pCur, defaultsc, defaultsmt);
}

void viewChooseDeleteCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt) {
	system("cls");
	int option, i = 0;
	if (pCur == nullptr) { /////////////////////////////////////////////
		cout << "None of courses have been created\n";
		cout << "Input 1 to Back: ";
		cin >> option;
		verify(option, 1, 0);
		deleteDCourse(pHead);
		courseMenu(defaultsc, defaultsmt);
		return;
	}
	cout << "Course ID: " << pCur->course.ID << "\n";
	cout << "Course name: " << pCur->course.name << "\n";
	cout << "Teacher name: " << pCur->course.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << pCur->course.credit << "\tMaximum number of students: " << pCur->course.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << pCur->course.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << pCur->course.session[0].time.hour << ":" << setw(2) << setfill('0') << pCur->course.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << pCur->course.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << pCur->course.session[1].time.hour << ":" << setw(2) << setfill('0') << pCur->course.session[1].time.minute << "\n";
	if (pCur->pNext != nullptr)
		cout << ++i << ". Next\n";
	if (pCur->pPre != nullptr)
		cout << ++i << ". Previous\n";
	cout << ++i << ". Delete\n";
	cout << ++i << ". Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, i, 6);
	switch (option) {
		case 1:
		{
			if (pCur->pNext == nullptr && pCur->pPre == nullptr)
				deleteChosenCourse(pHead, pCur, defaultsc, defaultsmt);

			else if (pCur->pNext == nullptr) {
				//pCur = pCur->pPre;
				viewChooseDeleteCourse(pHead, pCur->pPre, defaultsc, defaultsmt);
			}

			else {
				//pCur = pCur->pNext;
				viewChooseDeleteCourse(pHead, pCur->pNext, defaultsc, defaultsmt);
			}

			break;
		}
		case 2:
		{
			if (pCur->pNext == nullptr && pCur->pPre == nullptr) {
				deleteDCourse(pHead);
				courseMenu(defaultsc, defaultsmt);
			}

			else if (pCur->pNext == nullptr || pCur->pPre == nullptr)
				deleteChosenCourse(pHead, pCur, defaultsc, defaultsmt);

			else {
				//pCur = pCur->pPre;
				viewChooseDeleteCourse(pHead, pCur->pPre, defaultsc, defaultsmt);
			}

			break;
		}
		case 3:
		{
			if (pCur->pNext == nullptr || pCur->pPre == nullptr) {
				deleteDCourse(pHead);
				courseMenu(defaultsc, defaultsmt);
			}

			else
				deleteChosenCourse(pHead, pCur, defaultsc, defaultsmt);

			break;
		}
		default:
		{
			deleteDCourse(pHead);
			courseMenu(defaultsc, defaultsmt);
		}
	}
	return;
}

void deleteChosenCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt) {
	string path = "Data/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	courseDNode* pDel = pCur;
	ofstream fout;
	if (pCur->pNext == nullptr)
		pCur = pCur->pPre;
	else
		pCur = pCur->pNext;
	if (pDel == pHead) {
		pHead = pHead->pNext;
		if (pDel->pNext != nullptr)
			pHead->pPre = nullptr;
	}
	else {
		pDel->pPre->pNext = pDel->pNext;
		if (pDel -> pNext != nullptr)
			pDel->pPre->pNext->pPre = pDel->pPre;
	}
	delete pDel;
	saveDCourse(fout, pHead, path);
	viewChooseDeleteCourse(pHead, pCur, defaultsc, defaultsmt);
}

void updateCourseInformation(schoolYear& defaultsc, semester& defaultsmt) {
	string path = "Data/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	ifstream fin;
	courseDNode* pHead = nullptr;
	loadDCourse(fin, pHead, path);
	courseDNode* pCur = pHead;
	viewChooseUpdateCourse(pHead, pCur, defaultsc, defaultsmt);
}

void viewChooseUpdateCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt) {
	system("cls");
	int option, i = 0;
	if (pCur == nullptr) { //////////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "None of courses have been created\n";
		cout << "Input 1 to Back: ";
		cin >> option;
		verify(option, 1, 0);
		deleteDCourse(pHead);
		courseMenu(defaultsc, defaultsmt);
		return;
	}
	cout << "Course ID: " << pCur->course.ID << "\n";
	cout << "Course name: " << pCur->course.name << "\n";
	cout << "Teacher name: " << pCur->course.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << pCur->course.credit << "\tMaximum number of students: " << pCur->course.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << pCur->course.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << pCur->course.session[0].time.hour << ":" << setw(2) << setfill('0') << pCur->course.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << pCur->course.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << pCur->course.session[1].time.hour << ":" << setw(2) << setfill('0') << pCur->course.session[1].time.minute << "\n";
	if (pCur->pNext != nullptr)
		cout << ++i << ". Next\n";
	if (pCur->pPre != nullptr)
		cout << ++i << ". Previous\n";
	cout << ++i << ". Update\n";
	cout << ++i << ". Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, i, 6);
	switch (option) {
		case 1:
		{
			if (pCur->pNext == nullptr && pCur->pPre == nullptr) {
				courseInfo newCourse;
				newCourse = pCur->course;
				updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
			}

			else if (pCur->pNext == nullptr) {
				//pCur = pCur->pPre;
				viewChooseUpdateCourse(pHead, pCur->pPre, defaultsc, defaultsmt);
			}

			else {
				//pCur = pCur->pNext;
				viewChooseUpdateCourse(pHead, pCur->pNext, defaultsc, defaultsmt);
			}

			break;
		}
		case 2:
		{
			if (pCur->pNext == nullptr && pCur->pPre == nullptr) {
				deleteDCourse(pHead);
				courseMenu(defaultsc, defaultsmt);
			}

			else if (pCur->pNext == nullptr || pCur->pPre == nullptr) {
				courseInfo newCourse;
				newCourse = pCur->course;
				updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
			}

			else {
				//pCur = pCur->pPre;
				viewChooseUpdateCourse(pHead, pCur->pPre, defaultsc, defaultsmt);
			}

			break;
		}
		case 3:
		{
			if (pCur->pNext == nullptr || pCur->pPre == nullptr) {
				deleteDCourse(pHead);
				courseMenu(defaultsc, defaultsmt);
			}

			else {
				courseInfo newCourse;
				newCourse = pCur->course;
				updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
			}

			break;
		}
		default:
		{
			deleteDCourse(pHead);
			courseMenu(defaultsc, defaultsmt);
		}
	}
	return;
}

void updateChosenCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo newCourse) {
	system("cls");
	int option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "1. Change course ID\n";
	cout << "2. Change course name\n";
	cout << "3. Change teacher name\n";
	cout << "4. Change number of credits\n";
	cout << "5. Change the maximum number of students\n";
	cout << "6. Change course session 1\n";
	cout << "7. Change course session 2\n";
	cout << "8. Update\n";
	cout << "9. Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 9, 7);
	switch (option) {
	case 1:

		changeCourseID(pHead, pCur, defaultsc, defaultsmt, newCourse);
		break;
	case 2:
		changeCourseName(pHead, pCur, defaultsc, defaultsmt, newCourse);
		break;
	case 3:
		changeTeacherName(pHead, pCur, defaultsc, defaultsmt, newCourse);
		break;
	case 4:
		changeNumberOfCredits(pHead, pCur, defaultsc, defaultsmt, newCourse);
		break;
	case 5:
		changeTheMaximumNumberOfStudents(pHead, pCur, defaultsc, defaultsmt, newCourse);
		break;
	case 6:
		//changeCourseSession(pHead, pCur, defaultsc, defaultsmt, newCourse, 0);
		break;
	case 7:
	{
		//changeCourseSession(pHead, pCur, defaultsc, defaultsmt, newCourse, 1);
		break;
	}
	case 8:
		//update(defaultsc, defaultsmt, newCourse);
		break;
	default:
		viewChooseUpdateCourse(pHead, pCur, defaultsc, defaultsmt);
		return;
	}
}

void changeCourseID(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	string option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "Change course ID or 1 to Back: ";
	cin.ignore(100, '\n');
	getline(cin, option);
	if (option.size() == 1 && option[0] == '1') {
		updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
		return;
	}
	newCourse.ID = option;
	changeCourseID(pHead, pCur, defaultsc, defaultsmt, newCourse);
}

void changeCourseName(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	string option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "Change course name or 1 to Back: ";
	cin.ignore(100, '\n');
	getline(cin, option);
	cout << option;
	if (option.size() == 1 && option[0] == '1') {
		updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
		return;
	}
	newCourse.name = option;
	changeCourseName(pHead, pCur, defaultsc, defaultsmt, newCourse);
}

void changeTeacherName(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	string option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "Change teacher name or 1 to Back: ";
	cin.ignore(100, '\n');
	getline(cin, option);
	if (option.size() == 1 && option[0] == '1') {
		updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
		return;
	}
	newCourse.teacher = option;
	changeTeacherName(pHead, pCur, defaultsc, defaultsmt, newCourse);
}

void changeNumberOfCredits(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	int option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "Change number of credits or 0 to Back: ";
	cin >> option;
	while (option < 0) {
		goToXY(0, 7);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 7);
		cout << "Input number of credits or 0 to Back: " << option;
		goToXY(0, 8);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 8);
		cout << "Invalid! Try again: ";
		cin >> option;
	}
	switch (option) {
	case 0:
		updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
		break;
	default:
		newCourse.credit = option;
		changeNumberOfCredits(pHead, pCur, defaultsc, defaultsmt, newCourse);
		return;
	}
}

void changeTheMaximumNumberOfStudents(courseDNode*& pHead, courseDNode* pCur, schoolYear& defaultsc, semester& defaultsmt, courseInfo newCourse) {
	system("cls");
	int option;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "Change the maximum number of students or 0 to Back: ";
	cin >> option;
	while (option < 0) {
		goToXY(0, 7);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 7);
		cout << "Input the maximum number of students or 0 to Back: " << option;
		goToXY(0, 8);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 8);
		cout << "Invalid! Try again: ";
		cin >> option;
	}
	switch (option) {
	case 0:
		updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
		break;
	default:
		newCourse.student = option;
		changeTheMaximumNumberOfStudents(pHead, pCur, defaultsc, defaultsmt, newCourse);
		return;
	}
}


