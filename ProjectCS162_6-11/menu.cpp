#include "menuHeader.h"
#include "checkerHeader.h"
#include "linkedListHeader.h"
#include "utilityHeader.h"

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
	verify(option, 5, 2, "Input your option: ");
	switch (option) {
	case 1:
		semesterMenu(defaultsc, defaultsmt);
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

void semesterMenu(schoolYear defaultsc, semester defaultsmt) {
	system("cls");
	int option;
	schoolYear tempsc;
	semester tempsmt;
	tempsc.startYear = 0;
	tempsc.endYear = 0;
	tempsmt.number = 0;
	tempsmt.startDate.day = 0;
	tempsmt.startDate.month = 0;
	tempsmt.startDate.year = 0;
	tempsmt.endDate.day = 0;
	tempsmt.endDate.month = 0;
	tempsmt.endDate.year = 0;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << defaultsc.startYear << "-" << setw(4) << setfill('0') << defaultsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << defaultsmt.number << "\n";
	cout << "1. Create a semester\n";
	cout << "2. Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 2, 2, "Input your option: ");
	switch (option) {
	case 1:
		createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	default:
		mainMenu(defaultsc, defaultsmt);
	}
	return;
}

void createASemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	int option;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << "/" << setw(2) << setfill('0') << tempsmt.startDate.month << "/" << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
	cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << "/" << setw(2) << setfill('0') << tempsmt.endDate.month << "/" << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
	cout << "1. Choose the school year\n";
	cout << "2. Input a number of the semester\n";
	cout << "3. Input a start date and a end date of the semester\n";
	cout << "4. Create\n";
	cout << "5. Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, 5, 4, "Input your option: ");
	switch (option) {
	case 1:
		chooseTheSchoolYear(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	case 2:
		inputANumberOfTheSemester(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	case 3:
		inputAStartDateAndAEndDateOfTheSemester(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	case 4:
		create(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	default:
		semesterMenu(defaultsc, defaultsmt);
	}
	return;
}

void chooseTheSchoolYear(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	int option, i = 0;
	string path = "Data/School/schoolYear.csv";
	ifstream fin;
	schoolYearNode* pHead = nullptr;
	loadSchoolYear(fin, pHead, path); // neu ma chua tao cai school year nao thi sao?
	schoolYearNode* pCur = pHead;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << " " << setw(2) << setfill('0') << tempsmt.startDate.month << " " << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
	cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << " " << setw(2) << setfill('0') << tempsmt.endDate.month << " " << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
	while (pCur != nullptr) {
		cout << ++i << ". " << setw(4) << setfill('0') << pCur->sc.startYear << "-" << setw(4) << setfill('0') << pCur->sc.endYear << "\n";
		pCur = pCur->pNext;
	}
	cout << ++i << ". Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, i, 4, "Input your option: "); /////////////////////////////////////////////////
	if (option == i) {
		deleteSchoolYear(pHead);
		createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
		return;
	}
	pCur = pHead;
	for (int j = 0; j < option - 1; j++)
		pCur = pCur->pNext;
	tempsc = pCur->sc;
	deleteSchoolYear(pHead);
	chooseTheSchoolYear(defaultsc, defaultsmt, tempsc, tempsmt);
}

void inputANumberOfTheSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	int option;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << " " << setw(2) << setfill('0') << tempsmt.startDate.month << " " << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
	cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << " " << setw(2) << setfill('0') << tempsmt.endDate.month << " " << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
	cout << "Input a number of the semester or 0 to Back: "; 
	cin >> option;
	while (option < 0 || option > 3) {
		goToXY(0, 4);
		for (int i = 0; i <= 5; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 4);
		cout << "Input a number of the semester or 0 to Back: " << option;
		goToXY(0, 5);
		for (int i = 0; i <= 5; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 5);
		cout << "Invalid! Try again: ";
		cin >> option;
	}
	switch (option) {
	case 0:
		createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	default:
		tempsmt.number = option;
		inputANumberOfTheSemester(defaultsc, defaultsmt, tempsc, tempsmt);
	}
	return;
}

void inputAStartDateAndAEndDateOfTheSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	date startDate, endDate;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << " " << setw(2) << setfill('0') << tempsmt.startDate.month << " " << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
	cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << " " << setw(2) << setfill('0') << tempsmt.endDate.month << " " << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
	cout << "Input a start date of the semester or 0 to Back (dd/mm/yyyy): ";
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
				cout << "Input a end date of the semester or 0 to Back (dd/mm/yyyy): ";
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
						default:
							valiDate(defaultsc, defaultsmt, tempsc, tempsmt, startDate, endDate);
							tempsmt.startDate = startDate;
							tempsmt.endDate = endDate;
							inputAStartDateAndAEndDateOfTheSemester(defaultsc, defaultsmt, tempsc, tempsmt);
						}
					}
				}
			}
		}
	}
	return;
}

void create(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	int option;
	string path = "Data/School/" + to_string(tempsc.startYear) + "-" + to_string(tempsc.endYear) + "/semester.csv";
	ifstream fin;
	ofstream fout;
	semesterNode* pHead = nullptr;
	loadSemester(fin, pHead, path);
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << " " << setw(2) << setfill('0') << tempsmt.startDate.month << " " << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
	cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << " " << setw(2) << setfill('0') << tempsmt.endDate.month << " " << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
	if (pHead == nullptr) { //////////////////////////////////////////////////////////////////////////////////////////////////////////////
		deleteSemester(pHead);
		cout << "Create a school year or choose the school year to continue\n";
		cout << "1. Choose the school year\n";
		cout << "2. Back\n";
		cout << "Input your option: ";
		cin >> option;
		verify(option, 2, 5, "Input your option: ");
		switch (option) {
		case 1:
			chooseTheSchoolYear(defaultsc, defaultsmt, tempsc, tempsmt);
			break;
		default:
			createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
		}
		return;
	}
	if (checkUnduplicatedSemester(pHead, tempsmt) == false || checkTimeOrder(pHead, tempsmt) == false || tempsmt.startDate.year < tempsc.startYear || tempsmt.endDate.year > tempsc.endYear || tempsc.startYear == 0 || tempsc.endYear == 0 || tempsmt.number == 0 || tempsmt.startDate.day == 0 || tempsmt.startDate.month == 0 || tempsmt.startDate.year == 0 || tempsmt.endDate.day == 0 || tempsmt.endDate.month == 0 || tempsmt.endDate.year == 0) {
		deleteSemester(pHead);
		cout << "Check and fix potential faults: \n";
		cout << "1. Semester is duplicated\n";
		cout << "2. Time order is not logical\n";
		cout << "3. Semester information is not fulfilled\n";
		cout << "Input 1 to Back: ";
		cin >> option;
		verify(option, 1, 7, "Input 1 to Back: ");
		createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
		return;
	}
	path = "Data/School/" + to_string(tempsc.startYear) + "-" + to_string(tempsc.endYear) + "/Semester" + to_string(tempsmt.number);
	int newSemesterFolder = _mkdir(path.c_str());
	if (newSemesterFolder != 0) {
		deleteSemester(pHead);
		cout << "Has not been successfully created!\n";
		cout << "Cannot create new course folder!\n";
		cout << "1. Try again\n";
		cout << "2. Back\n";
		cout << "Input your option: ";
		cin >> option;
		verify(option, 2, 6, "Input your option: ");
		switch (option) {
		case 1:
			create(defaultsc, defaultsmt, tempsc, tempsmt);
			break;
		default:
			createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
		}
		return;
	}
	defaultsc = tempsc;
	defaultsmt = tempsmt;
	tempsc.startYear = 0;
	tempsc.endYear = 0;
	tempsmt.number = 0;
	tempsmt.startDate.day = 0;
	tempsmt.startDate.month = 0;
	tempsmt.startDate.year = 0;
	tempsmt.endDate.day = 0;
	tempsmt.endDate.month = 0;
	tempsmt.endDate.year = 0;
	path = "Data/School/" + to_string(tempsc.startYear) + "-" + to_string(tempsc.endYear) + "/semester.csv";
	insertSemester(pHead, tempsmt);
	saveSemester(fout, pHead, path);
	deleteSemester(pHead);
	cout << "Has been created successfully!\n";
	cout << "Input 1 to Back: ";
	cin >> option;
	verify(option, 1, 4, "Input 1 to Back: ");
	createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
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
	verify(option, 4, 2, "Input your option: "); 
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
	string path = "Data/School/schoolYear.csv";
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
	verify(option, i, 2, "Input your option: ");
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
}

void chooseSemester(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	int option, i = 0;
	string path = "Data/School/" + to_string(tempsc.startYear) + "-" + to_string(tempsc.endYear) + "/semester.csv";
	ifstream fin;
	semesterNode* pHead = nullptr;
	loadSemester(fin, pHead, path);
	semesterNode* pCur = pHead;
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	if (pHead == nullptr) {
		cout << "Create a semester or choose school year to continue!\n";
		cout << "1. Create a semester\n";
		cout << "2. Choose school year\n";
		cout << "3. Back\n";
		cout << "Input your option: ";
		cin >> option;
		verify(option, 3, 3, "Input your option: ");
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
	verify(option, i, 2, "Input your option: ");
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
}

void change(schoolYear defaultsc, semester defaultsmt, schoolYear tempsc, semester tempsmt) {
	system("cls");
	int option;
	string path = "Data/School/" + to_string(tempsc.startYear) + "-" + to_string(tempsc.endYear) + "/semester.csv";
	ifstream fin;
	semesterNode* pHead = nullptr;
	loadSemester(fin, pHead, path);
	cout << "Your default school year is currently set to: " << setw(4) << setfill('0') << tempsc.startYear << "-" << setw(4) << setfill('0') << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << setw(2) << setfill('0') << tempsmt.number << "\n";
	if (pHead == nullptr || checkSemesterExist(pHead, tempsmt) == false) {
		cout << "Semester is not existed! Create a semester or choose school year or choose semester to continue!\n";
		cout << "1. Create a semester\n";
		cout << "2. Choose school year\n";
		cout << "3. Choose semester\n";
		cout << "4. Back\n";
		cout << "Input your option: ";
		cin >> option;
		verify(option, 4, 3, "Input your option: ");
		switch (option) {
		case 1:
			cout << "Temporarily closed\n"; ////////////////////////////////////////////////////////////////////////////
			break;
		case 2:
			chooseSchoolYear(defaultsc, defaultsmt, tempsc, tempsmt);
			break;
		case 3:
			chooseSemester(defaultsc, defaultsmt, tempsc, tempsmt);
			break;
		default:
			changeDefaultSemester(defaultsc, defaultsmt, tempsc, tempsmt);
		}
		return;
	}
	defaultsc = tempsc;
	defaultsmt = tempsmt;
	cout << "Change default semester successfully!\n";
	cout << "Input 1 to Back: ";
	cin >> option;
	verify(option, 1, 2, "Input 1 to Back: ");
	deleteSemester(pHead);
	changeDefaultSemester(defaultsc, defaultsmt, tempsc, tempsmt);
}

void courseMenu(schoolYear defaultsc, semester defaultsmt) {
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
		verify(option, 2, 3, "Input your option: ");
		switch (option) {
		case 1:
			cout << "Temporarily closed\n"; ///////////////////////////////////////////////////////////////////////////
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
	verify(option, 5, 2, "Input your option: ");
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
	}
	return;
}

void addACourse(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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
	verify(option, 9, 7, "Input your option: ");
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
	}
	return;
}

void inputCourseID(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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

void inputCourseName(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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

void inputTeacherName(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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

void inputNumberOfCredits(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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
		for (int i = 0; i <= 8; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 7);
		cout << "Input number of credits or 0 to Back: " << option;
		goToXY(0, 8);
		for (int i = 0; i <= 8; i++) {
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
	}
	return;
}

void inputTheMaximumNumberOfStudents(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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
		for (int i = 0; i <= 8; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 7);
		cout << "Input the maximum number of students or 0 to Back: " << option;
		goToXY(0, 8);
		for (int i = 0; i <= 8; i++) {
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
	}
	return;
}

void inputCourseSession(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number) {
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
	verify(option, 3, 7, "Input your option: ");
	switch (option) {
	case 1:
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, number);
		break;
	case 2:
		inputTime(defaultsc, defaultsmt, newCourse, number);
		break;
	default:
		addACourse(defaultsc, defaultsmt, newCourse);
	}
	return;
}

void inputDayOfTheWeek(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number) {
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
	verify(option, 8, 7, "Input your option: ");
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
	}
	return;
}

void inputTime(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number) {
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
	verify(option, 5, 7, "Input your option: ");
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
	}
	return;
}

//check CS162 folder created, nhieu lop co the hoc cung 1 mon

void add(schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
	system("cls");
	int option;
	string path = "Data/School/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
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
	if (checkCourseInfoFulfill(newCourse) == false || checkUnduplicatedCourse(pHead, newCourse) == false || checkFreeTeacher(pHead, newCourse) == false) {
		cout << "Has not been successfully created!\n";
		cout << "Course information is not fulfilled or course is duplicated or teacher is not free! Change course information to continue!\n";
		cout << "Input 1 to Back: ";
		cin >> option;
		verify(option, 1, 8, "Input 1 to Back: ");
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
	path = "Data/School/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/" + newCourse.ID;
	int newCourseFolder = _mkdir(path.c_str());
	if (newCourseFolder != 0) {
		deleteCourse(pHead);
		cout << "Has not been successfully created!\n";
		cout << "Cannot create new course folder!\n";
		cout << "1. Try again\n";
		cout << "2. Back\n";
		cout << "Input your option: ";
		cin >> option;
		verify(option, 2, 9, "Input your option: ");
		switch (option) {
		case 1:
			add(defaultsc, defaultsmt, newCourse);
			break;
		default:
			addACourse(defaultsc, defaultsmt, newCourse);
		}
		return;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////check point
	newCourse.ID = "0";
	newCourse.name = "0";
	newCourse.teacher = "0";
	newCourse.credit = 0;
	newCourse.student = 50;
	newCourse.session[0].dayOfWeek = "0";
	newCourse.session[0].time.hour = 0;
	newCourse.session[0].time.minute = 0;
	newCourse.session[1].dayOfWeek = "0";
	newCourse.session[1].time.hour = 0;
	newCourse.session[1].time.minute = 0;
	path = "Data/School/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	addCourse(pHead, newCourse);
	saveCourse(fout, pHead, path);
	deleteCourse(pHead);
	cout << "Has been successfully created!\n";
	cout << "Input 1 to Back: ";
	cin >> option;
	verify(option, 1, 7, "Input 1 to Back: ");
	addACourse(defaultsc, defaultsmt, newCourse);
}

void viewListOfCourse(schoolYear defaultsc, semester defaultsmt) {
	string path = "Data/School/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	ifstream fin;
	courseDNode* pHead = nullptr;
	loadDCourse(fin, pHead, path);
	courseDNode* pCur = pHead;
	viewCourses(pHead, pCur, defaultsc, defaultsmt);
}

void viewCourses(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt) {
	system("cls");
	int option, i = 0;
	if (pCur == nullptr) { /////////////////////////////////////////////
		cout << "None of courses have been created\n";
		cout << "Input 1 to Back: ";
		cin >> option;
		verify(option, 1, 0, "Input 1 to Back: ");
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
	cout << ++i << ". Back\n";
	cout << "Input your option: ";
	cin >> option;
	verify(option, i, 6, "Input your option: ");
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

void deleteACourse(schoolYear defaultsc, semester defaultsmt) {
	string path = "Data/School/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	ifstream fin;
	courseDNode* pHead = nullptr;
	loadDCourse(fin, pHead, path);
	courseDNode* pCur = pHead;
	viewChooseDeleteCourse(pHead, pCur, defaultsc, defaultsmt);
}

void viewChooseDeleteCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt) {
	system("cls");
	int option, i = 0;
	if (pCur == nullptr) { /////////////////////////////////////////////
		cout << "None of courses have been created\n";
		cout << "Input 1 to Back: ";
		cin >> option;
		verify(option, 1, 0, "Input 1 to Back: ");
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
	verify(option, i, 6, "Input your option: ");
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

void deleteChosenCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt) {
	string path = "Data/School/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
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
		if (pDel->pNext != nullptr)
			pDel->pPre->pNext->pPre = pDel->pPre;
	}
	delete pDel;
	saveDCourse(fout, pHead, path);
	viewChooseDeleteCourse(pHead, pCur, defaultsc, defaultsmt);
}

void updateCourseInformation(schoolYear defaultsc, semester defaultsmt) {
	string path = "Data/School/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	ifstream fin;
	courseDNode* pHead = nullptr;
	loadDCourse(fin, pHead, path);
	courseDNode* pCur = pHead;
	viewChooseUpdateCourse(pHead, pCur, defaultsc, defaultsmt);
}

void viewChooseUpdateCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt) {
	system("cls");
	int option, i = 0;
	if (pCur == nullptr) { //////////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "None of courses have been created\n";
		cout << "Input 1 to Back: ";
		cin >> option;
		verify(option, 1, 0, "Input 1 to Back: ");
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
	verify(option, i, 6, "Input your option: ");
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

void updateChosenCourse(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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
	verify(option, 9, 7, "Input your option: ");
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
		changeCourseSession(pHead, pCur, defaultsc, defaultsmt, newCourse, 0);
		break;
	case 7:
	{
		changeCourseSession(pHead, pCur, defaultsc, defaultsmt, newCourse, 1);
		break;
	}
	case 8:
		update(pHead, pCur, defaultsc, defaultsmt, newCourse);
		break;
	default:
		viewChooseUpdateCourse(pHead, pCur, defaultsc, defaultsmt);
	}
	return;
}

void changeCourseID(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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

void changeCourseName(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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

void changeTeacherName(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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

void changeNumberOfCredits(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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
		for (int i = 0; i <= 8; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 7);
		cout << "Change number of credits or 0 to Back: " << option;
		goToXY(0, 8);
		for (int i = 0; i <= 8; i++) {
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
	}
	return;
}

void changeTheMaximumNumberOfStudents(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
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
		for (int i = 0; i <= 8; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 7);
		cout << "Change the maximum number of students or 0 to Back: " << option;
		goToXY(0, 8);
		for (int i = 0; i <= 8; i++) {
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
	}
	return;
}

void changeCourseSession(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number) {
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
	verify(option, 3, 7, "Input your option: ");
	switch (option) {
	case 1:
		changeDayOfTheWeek(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	case 2:
		changeTime(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	default:
		updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
	}
	return;
}

void changeDayOfTheWeek(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number) {
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
	verify(option, 8, 7, "Input your option: ");
	switch (option) {
	case 1:
		newCourse.session[number].dayOfWeek = "MON";
		changeDayOfTheWeek(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	case 2:
		newCourse.session[number].dayOfWeek = "TUE";
		changeDayOfTheWeek(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	case 3:
		newCourse.session[number].dayOfWeek = "WED";
		changeDayOfTheWeek(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	case 4:
		newCourse.session[number].dayOfWeek = "THU";
		changeDayOfTheWeek(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	case 5:
		newCourse.session[number].dayOfWeek = "FRI";
		changeDayOfTheWeek(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	case 6:
		newCourse.session[number].dayOfWeek = "SAT";
		changeDayOfTheWeek(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	case 7:
		newCourse.session[number].dayOfWeek = "SUN";
		changeDayOfTheWeek(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	default:
		changeCourseSession(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
	}
	return;
}

void changeTime(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse, int number) {
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
	verify(option, 5, 7, "Input your option: ");
	switch (option) {
	case 1:
		newCourse.session[number].time.hour = 7;
		newCourse.session[number].time.minute = 30;
		changeTime(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	case 2:
		newCourse.session[number].time.hour = 9;
		newCourse.session[number].time.minute = 30;
		changeTime(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	case 3:
		newCourse.session[number].time.hour = 13;
		newCourse.session[number].time.minute = 30;
		changeTime(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	case 4:
		newCourse.session[number].time.hour = 15;
		newCourse.session[number].time.minute = 30;
		changeTime(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
		break;
	default:
		changeCourseSession(pHead, pCur, defaultsc, defaultsmt, newCourse, number);
	}
	return;
}

//
void update(courseDNode*& pHead, courseDNode* pCur, schoolYear defaultsc, semester defaultsmt, courseInfo newCourse) {
	system("cls");
	int option;
	string path = "Data/School/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.csv";
	courseDNode* pDel = pCur;
	ofstream fout;
	cout << "Your default course is currently set to:\n";
	cout << "Course ID: " << newCourse.ID << "\n";
	cout << "Course name: " << newCourse.name << "\n";
	cout << "Teacher name: " << newCourse.teacher << "\n";
	cout << "Number of credits: " << setw(2) << setfill('0') << newCourse.credit << "\tMaximum number of students: " << newCourse.student << "\n";
	cout << "Course session 1: " << setw(3) << setfill('0') << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
	cout << "Course session 2: " << setw(3) << setfill('0') << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	/*if (checkCourseInfoFulfill(newCourse) == false || checkUnduplicatedCourse(pHead, newCourse) == false || checkFreeTeacher(pHead, newCourse) == false) {
		cout << "Has not been successfully updated!\n";
		cout << "Course information is not fulfilled or course is duplicated or teacher is not free! Change course information to continue!\n";
		cout << "Input 1 to Back: ";
		cin >> option;
		verify(option, 1, 8, "Input 1 to Back: ");
		updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
		return;
	}*/
	pCur->course = newCourse;
	saveDCourse(fout, pHead, path);
	cout << "Has been successfully updated!\n";
	cout << "Input 1 to Back: ";
	cin >> option;
	verify(option, 1, 7, "Input 1 to Back: ");
	updateChosenCourse(pHead, pCur, defaultsc, defaultsmt, newCourse);
}

