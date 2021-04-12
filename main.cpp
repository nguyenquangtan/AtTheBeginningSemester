#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <direct.h>
#include <iomanip>
#include <ios>
#include <limits>
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
	int maxtudent;
	courseSession session[2];
};

struct courseNode {
	courseInfo course;
	courseNode* pNext;
};

void goToXY(SHORT posX, SHORT posY);
void mainMenu(schoolYear& defaultsc, semester& defaultsmt);
void validateOption(int& option, int number);
void semesterMenu(schoolYear& defaultsc, semester& defaultsmt);
void createASemester(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt);
void chooseTheSchoolYear(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt);
void inputANumberOfTheSemester(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt);
void inputAStartDateAndAEndDateOfTheSemester(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt);
void loadSchoolYear(ifstream& fin, schoolYearNode*& pHead, string path);
void validateDates(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt, date& start, date& end);
bool compareDates(date a, date b);
bool checkValidDate(date a);
bool checkLeapYear(int year);
void loadSemester(ifstream& fin, semesterNode*& pHead, string path);
bool checkUnduplicated(semesterNode* pHead, semester tempsmt);
bool checkTimeOrder(semesterNode* pHead, semester tempsmt);
void saveSemester(ofstream& fout, semesterNode* pHead, string path);
void deleteSemester(semesterNode*& pHead);
void create(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt);
void insertSemester(semesterNode*& pHead, semester tempsmt);
void deleteSchoolYear(schoolYearNode*& pHead);
void courseMenu(schoolYear& defaultsc, semester& defaultsmt);
void addACourse(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);
void inputCourseID(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);
void inputCourseName(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);
void inputTeacherName(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);
void inputCredit(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);
void inputStudent(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);
void inputCourseSession(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int n);
void inputDayOfTheWeek(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int n);
void inputTime(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int n);
void loadCourse(ifstream& fin, courseNode*& pHead, string path);
void insertCourse(courseNode*& pHead, courseInfo newCourse);
void saveCourse(ofstream& fout, courseNode* pHead, string path);
void deleteCourse(courseNode*& pHead);
bool compareStrings(string a, string b);
bool checkUnduplicatedCourse(courseNode* pHead, courseInfo newCourse);
void add(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse);

int main()
{
	schoolYear defaultsc; //sc = school year viet tat
	semester defaultsmt; // smt = semester viet tat
	defaultsc.startYear = 0;
	defaultsc.endYear = 0;
	defaultsmt.number = 0;
	defaultsmt.startDate.day = 0;
	defaultsmt.startDate.month = 0;
	defaultsmt.startDate.year = 0;
	defaultsmt.endDate.day = 0;
	defaultsmt.endDate.month = 0;
	defaultsmt.endDate.year = 0;
	mainMenu(defaultsc, defaultsmt);
	return 0;
}

void goToXY(SHORT posX, SHORT posY) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;
	SetConsoleCursorPosition(hStdout, Position);
}

void mainMenu(schoolYear& defaultsc, semester& defaultsmt) {
	system("cls");
	int option;
	cout << "Your default school year is currently set to: " << defaultsc.startYear << "-" << defaultsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << defaultsmt.number << "\n";
	cout << "1. Semester\n";
	cout << "2. Course Registration Session\n";
	cout << "3. Course\n";
	cout << "4. Change default\n";
	cout << "5. Exit\n";
	cout << "Input your option: ";
	cin >> option;
	validateOption(option, 5);
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
		cout << "Temporarily closed\n";
		break;
	default:
		cout << "And it's the end!\n";
		return;
	}
}

void validateOption(int& option, int number) { //ví dụ menu 1. Facebook 2. Instagram mà user nhập vô option là 3 thì hàm này 
	while (option < 1 || option > number) {    //bắt user phải nhập lại cho đến khi đúng option
		/* để in lại cho đẹp 
		ví dụ Input your option: 
		1
		thì sẽ in lại thành Input your option: 1*/
		goToXY(0, number + 2);
		for (int i = 0; i <= number + 3; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, number + 2);
		cout << "Input your option: " << option;
		// bắt đầu kêu user nhập lại cho đúng và nếu nhập không đẹp thì cũng in lại cho đẹp
		goToXY(0, number + 3);
		for (int i = 0; i <= number + 3; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, number + 3);
		cout << "Invalid! Try again: ";
		cin >> option;
	}
}

void semesterMenu(schoolYear& defaultsc, semester& defaultsmt) {
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
	cout << "Your default school year is currently set to: " << defaultsc.startYear << "-" << defaultsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << defaultsmt.number << "\n";
	cout << "1. Create a semester\n";
	cout << "2. Edit a semester\n";
	cout << "3. Delete a semester\n";
	cout << "4. Back\n";
	cout << "Input your option: ";
	cin >> option;
	validateOption(option, 4);
	switch (option) {
	case 1:
		createASemester(defaultsc, defaultsmt , tempsc, tempsmt);
		break;
	case 2:
		cout << "Temporarily closed\n";
		break;
	case 3:
		cout << "Temporarily closed\n";
		break;
	default:
		mainMenu(defaultsc, defaultsmt);
		return;
	}
}

void createASemester(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt) {
	system("cls");
	int option;
	cout << "Your default school year is currently set to: " << tempsc.startYear << "-" << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << tempsmt.number << "\n";
	////////////////////////////////////////////////////////////////////////////
	//cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << " " << setw(2) << setfill('0') << tempsmt.startDate.month << " " << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
	//cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << " " << setw(2) << setfill('0') << tempsmt.endDate.month << " " << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
	cout << "1. Choose the school year\n";
	cout << "2. Input a number of the semester\n";
	cout << "3. Input a start date and a end date of the semester\n";
	cout << "4. Create\n";
	cout << "5. Back\n";
	cout << "Input your option: ";
	cin >> option;
	validateOption(option, 5);
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
		return;
	}
}

void loadSchoolYear(ifstream& fin, schoolYearNode*& pHead, string path) { //hàm này tạo linked list các năm học đã được tạo
	fin.open(path);
	if (!fin.is_open()) {
		cout << "Can not open file\n"; //hỏi lại team có cần kiểm tra trường hợp chưa tạo năm học
	}
	else {
		schoolYearNode* pCur = nullptr;
		int start, end;
		fin >> start;
		while (start != 0) {
			fin >> end;
			if (pHead == nullptr) {
				pHead = new schoolYearNode;
				pCur = pHead;
			}
			else {
				pCur->pNext = new schoolYearNode;
				pCur = pCur->pNext;
			}
			pCur->sc.startYear = start;
			pCur->sc.endYear = end;
			pCur->pNext = nullptr;
			fin >> start;
		}
		fin.close();
	}
}


void chooseTheSchoolYear(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt) {
	system("cls");
	int i = 0, option;
	string path = "Data/schoolyear.txt";
	ifstream fin;
	schoolYearNode* pHead = nullptr;
	loadSchoolYear(fin, pHead, path);
	schoolYearNode* pCur = pHead; //nhớ hỏi lại cái trường hợp ở trên
	cout << "Your default school year is currently set to: " << tempsc.startYear << "-" << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << tempsmt.number << "\n";
	//cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << " " << setw(2) << setfill('0') << tempsmt.startDate.month << " " << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
	//cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << " " << setw(2) << setfill('0') << tempsmt.endDate.month << " " << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
	//in ra các năm học đã được tạo
	while (pCur != nullptr) {
		cout << ++i << ". " << pCur->sc.startYear << "-" << pCur->sc.endYear << "\n";
		pCur = pCur->pNext;
	}
	cout << ++i << ". Back\n";
	//người dùng chọn một trong các năm học đã được hiển thị để tạo semester trong năm học đó hoặc quay lại menu trước
	cout << "Input your option: ";
	cin >> option;
	validateOption(option, i);

	if (option == i) {
		deleteSchoolYear(pHead);
		createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
	}
	else {
		pCur = pHead;
		for (int j = 0; j < option - 1; j++)
			pCur = pCur->pNext;
		tempsc = pCur->sc; //startyear
		//tempsc.endYear = pCur->sc.endYear;
		deleteSchoolYear(pHead);
		chooseTheSchoolYear(defaultsc, defaultsmt, tempsc, tempsmt);
	}
}

void inputANumberOfTheSemester(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt) {
	system("cls");
	int option;
	cout << "Your default school year is currently set to: " << tempsc.startYear << "-" << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << tempsmt.number << "\n";
	//cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << " " << setw(2) << setfill('0') << tempsmt.startDate.month << " " << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
	//cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << " " << setw(2) << setfill('0') << tempsmt.endDate.month << " " << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
	cout << "0. Back\n";
	cout << "Input a number of the semester or 0 to back: "; //này là kết hợp cho user nhập vô muốn tạo semester 1 hay 2 hay 3 hoặc 0 để thoát
	cin >> option;
	//validateOption nhưng do option có 0 nên phải ghi riêng
	while (option < 0 || option > 3) {
		goToXY(0, 3);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 3);
		cout << "Input a number of the semester or 0 to back: " << option;
		goToXY(0, 4);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 4);
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
		return;
	}
}

void inputAStartDateAndAEndDateOfTheSemester(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt) {
	system("cls");
	date start, end;
	cout << "Your default school year is currently set to: " << tempsc.startYear << "-" << tempsc.endYear << "\n";
	cout << "Your default semester is currently set to: " << tempsmt.number << "\n";
	//cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << " " << setw(2) << setfill('0') << tempsmt.startDate.month << " " << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
	//cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << " " << setw(2) << setfill('0') << tempsmt.endDate.month << " " << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
	cout << "Input a start date of the semester or 0 to back (dd/mm/yyyy): ";
	cin >> start.day;
	// chỗ này là cho người dùng nhập ngày start và end nhưng bất kể khi nào người dùng nhập 0 thì back về menu trước
	switch (start.day) {
	case 0:
		createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
		break;
	default:
		cin >> start.month;
		switch (start.month) {
		case 0:
			createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
			break;
		default:
			cin >> start.year;
			switch (start.year) {
			case 0:
				createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
				break;
			default:
				cout << "Input a end date of the semester or 0 to back (dd/mm/yyyy): ";
				cin >> end.day;
				switch (end.day) {
				case 0:
					createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
					break;
				default:
					cin >> end.month;
					switch (end.month) {
					case 0:
						createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
						break;
					default:
						cin >> end.year;
						switch (end.year) {
						case 0:
							createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
							break;
						default:
							validateDates(defaultsc, defaultsmt, tempsc, tempsmt, start, end);
							tempsmt.startDate = start;
							tempsmt.endDate = end;
							inputAStartDateAndAEndDateOfTheSemester(defaultsc, defaultsmt, tempsc, tempsmt);
							return;
						}
					}
				}
			}
		}
	}
}


bool compareDates(date a, date b) { //nếu ngày a lớn hơn ngày b thì trả về true
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
//chức năng cũng giống như validateOption
void validateDates(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt, date& start, date& end) {
	while (checkValidDate(start) == false || checkValidDate(end) == false || compareDates(end, start) == false) {
		goToXY(0, 2);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 2);
		cout << "Input a start date of the semester (dd/mm/yyyy): " << setw(2) << setfill('0') << start.day << " " << setw(2) << setfill('0') << start.month << " " << setw(4) << setfill('0') << start.year << "\n";
		cout << "Input a end date of the semester (dd/mm/yyyy): " << setw(2) << setfill('0') << end.day << " " << setw(2) << setfill('0') << end.month << " " << setw(4) << setfill('0') << end.year;
		goToXY(0, 4);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 4);
		cout << "Invalid! Try again! Start date: ";
		cin >> start.day;
		switch (start.day) {
		case 0:
			createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
			break;
		default:
			cin >> start.month;
			switch (start.month) {
			case 0:
				createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
				break;
			default:
				cin >> start.year;
				switch (start.year) {
				case 0:
					createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
					break;
				default:
					cout << "                    End date: ";
					cin >> end.day;
					switch (end.day) {
					case 0:
						createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
						break;
					default:
						cin >> end.month;
						switch (end.month) {
						case 0:
							createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
							break;
						default:
							cin >> end.year;
							switch (end.year) {
							case 0:
								createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
								break;
							default:
								return;
							}
						}
					}
				}
			}
		}
	}
}

void create(schoolYear& defaultsc, semester& defaultsmt, schoolYear& tempsc, semester& tempsmt) {
	system("cls");
	int option;
	string path = "Data/" + to_string(tempsc.startYear) + "-" + to_string(tempsc.endYear) + "/semester.txt";
	ifstream fin;
	ofstream fout;
	semesterNode* pHead = nullptr;
	if (tempsc.startYear != 0 && tempsc.endYear != 0) {
		loadSemester(fin, pHead, path);
	}
	//
	if (checkUnduplicated(pHead, tempsmt) == false || checkTimeOrder(pHead, tempsmt) == false || tempsmt.startDate.year < tempsc.startYear || tempsmt.endDate.year > tempsc.endYear || tempsc.startYear == 0 || tempsc.endYear == 0 || tempsmt.number == 0 || tempsmt.startDate.day == 0 || tempsmt.startDate.month == 0 || tempsmt.startDate.year == 0 || tempsmt.endDate.day == 0 || tempsmt.endDate.month == 0 || tempsmt.endDate.year == 0) {
		deleteSemester(pHead);
		cout << "There is missing or invalid information to create a semester!\n";
		cout << "Please check again the information of semester which you would like to create and go back to fix it\n";
		cout << "Semester: " << tempsmt.number << "\n";
		cout << "Belong to school year: " << tempsc.startYear << "-" << tempsc.endYear << "\n";
		cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << " " << setw(2) << setfill('0') << tempsmt.startDate.month << " " << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
		cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << " " << setw(2) << setfill('0') << tempsmt.endDate.month << " " << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
		cout << "0. Back\n";
		cout << "Input 0: ";
		cin >> option;
		while (option != 0) {
			goToXY(0, 7);
			for (int i = 0; i <= 7; i++) {
				cout << "                                                                                                                  \n";
			}
			goToXY(0, 7);
			cout << "Input 0: " << option;
			goToXY(0, 8);
			for (int i = 0; i <= 7; i++) {
				cout << "                                                                                                                  \n";
			}
			goToXY(0, 8);
			cout << "Invalid! Try again: ";
			cin >> option;
		}
		createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
		return;
	}
	else {
		path = "Data/" + to_string(tempsc.startYear) + "-" + to_string(tempsc.endYear) + "/Semester" + to_string(tempsmt.number);
		int newSemester = _mkdir(path.c_str());
		cout << "Semester: " << tempsmt.number << "\n";
		cout << "Belong to school year: " << tempsc.startYear << "-" << tempsc.endYear << "\n";
		cout << "Start day: " << setw(2) << setfill('0') << tempsmt.startDate.day << " " << setw(2) << setfill('0') << tempsmt.startDate.month << " " << setw(4) << setfill('0') << tempsmt.startDate.year << "\n";
		cout << "End day: " << setw(2) << setfill('0') << tempsmt.endDate.day << " " << setw(2) << setfill('0') << tempsmt.endDate.month << " " << setw(4) << setfill('0') << tempsmt.endDate.year << "\n";
		if (newSemester == 0) {
			defaultsc = tempsc;
			defaultsmt = tempsmt;
			path = "Data/" + to_string(tempsc.startYear) + "-" + to_string(tempsc.endYear) + "/semester.txt";
			insertSemester(pHead, tempsmt);
			saveSemester(fout, pHead, path);
			deleteSemester(pHead);
			cout << "Has been created successfully!\n";
			cout << "0. Back\n";
			cout << "Input your option: ";
			cin >> option;
			while (option != 0) {
				goToXY(0, 6);
				for (int i = 0; i <= 7; i++) {
					cout << "                                                                                                                  \n";
				}
				goToXY(0, 6);
				cout << "Input 0: " << option;
				goToXY(0, 7);
				for (int i = 0; i <= 7; i++) {
					cout << "                                                                                                                  \n";
				}
				goToXY(0, 7);
				cout << "Invalid! Try again: ";
				cin >> option;
			}
			tempsc.startYear = 0;
			tempsc.endYear = 0;
			tempsmt.number = 0;
			tempsmt.startDate.day = 0;
			tempsmt.startDate.month = 0;
			tempsmt.startDate.year = 0;
			tempsmt.endDate.day = 0;
			tempsmt.endDate.month = 0;
			tempsmt.endDate.year = 0;
			createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
			return;
		}
		else {
			deleteSemester(pHead);
			cout << "Failed to create!\n";
			cout << "1. Try again\n";
			cout << "2. Back\n";
			cout << "Input your option: ";
			cin >> option;
			while (option < 1 || option > 2) {
				goToXY(0, 7);
				for (int i = 0; i <= 7; i++) {
					cout << "                                                                                                                  \n";
				}
				goToXY(0, 7);
				cout << "Input your option: " << option;
				goToXY(0, 8);
				for (int i = 0; i <= 7; i++) {
					cout << "                                                                                                                  \n";
				}
				goToXY(0, 8);
				cout << "Invalid! Try again: ";
				cin >> option;
			}
			switch (option) {
			case 1:
				create(defaultsc, defaultsmt, tempsc, tempsmt);
				break;
			default:
				createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
				return;
			}
		}
	}
}

void loadSemester(ifstream& fin, semesterNode*& pHead, string path) {
	fin.open(path);
	if (!fin.is_open()) {
		return;
	}
	else {
		semesterNode* pCur = nullptr;
		int num;
		date start;
		date end;
		fin >> num;
		while (num != 0) {
			fin >> start.day;
			fin >> start.month;
			fin >> start.year;
			fin >> end.day;
			fin >> end.month;
			fin >> end.year;
			if (pHead == nullptr) {
				pHead = new semesterNode;
				pCur = pHead;
			}
			else {
				pCur->pNext = new semesterNode;
				pCur = pCur->pNext;
			}
			pCur->smt.number = num;
			pCur->smt.startDate = start;
			//pCur->smt.startDate.month = start.month;
			//pCur->smt.startDate.year = start.year;
			pCur->smt.endDate = end;
			//pCur->smt.endDate.month = end.month;
			//pCur->smt.endDate.year = end.year;
			pCur->pNext = nullptr;
			fin >> num;
		}
		fin.close();
	}
}

bool checkUnduplicated(semesterNode* pHead, semester tempsmt) {
	if (pHead == nullptr) return true;
	semesterNode* pCur = pHead;
	while (pCur != nullptr && tempsmt.number != pCur->smt.number)
		pCur = pCur->pNext;
	if (pCur != nullptr) return false;
	return true;
}

bool checkTimeOrder(semesterNode* pHead, semester tempsmt) {
	if (pHead == nullptr) return true;
	if (tempsmt.number < pHead->smt.number && compareDates(pHead->smt.startDate, tempsmt.endDate) == true) return true;
	semesterNode* pCur = pHead;

	while (pCur -> pNext != nullptr && tempsmt.number > pCur->pNext->smt.number)
		pCur = pCur->pNext;
	if (pCur->pNext != nullptr && compareDates(tempsmt.startDate, pCur->smt.endDate) == true && compareDates(pCur->pNext->smt.startDate, tempsmt.endDate) == true)
		return true;
	if (pCur -> pNext == nullptr && compareDates(tempsmt.startDate, pCur->smt.endDate) == true) return true;
	return false;
}

void saveSemester(ofstream& fout, semesterNode* pHead, string path) {
	fout.open(path);
	if (!fout.is_open()) {
		cout << "cannot open\n";
	}
	else {
		if (pHead == nullptr) {
			fout << "0";
			return;
		}
		semesterNode* pCur = pHead;
		while (pCur != nullptr) {
			fout << pCur->smt.number << " " << setw(2) << setfill('0') << pCur->smt.startDate.day << " " << setw(2) << setfill('0') << pCur->smt.startDate.month << " " << pCur->smt.startDate.year << " " << setw(2) << setfill('0') << pCur->smt.endDate.day << " " << setw(2) << setfill('0') << pCur->smt.endDate.month << " " << pCur->smt.endDate.year << "\n";
			pCur = pCur->pNext;
		}
		fout << "0";
		fout.close();
	}
}

void deleteSemester(semesterNode*& pHead) {
	semesterNode* pCur = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pCur;
		pCur = pHead;
	}
}

void insertSemester(semesterNode*& pHead, semester tempsmt) {
	semesterNode* pIns = nullptr;
	if (pHead == nullptr || (pHead != nullptr && tempsmt.number < pHead->smt.number)) {
		pIns = new semesterNode;
		pIns->smt = tempsmt;
		pIns->pNext = nullptr;
		pHead = pIns;
		return;
	}
	semesterNode* pCur = pHead;
	while (pCur->pNext != nullptr && tempsmt.number > pCur->pNext->smt.number)
		pCur = pCur->pNext;
	pIns = new semesterNode;
	pIns->smt = tempsmt;
	pIns->pNext = pCur->pNext;
	pCur->pNext = pIns;
}

void deleteSchoolYear(schoolYearNode*& pHead) {
	schoolYearNode* pDel = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pDel;
		pDel = pHead;
	}
}

void courseMenu(schoolYear& defaultsc, semester& defaultsmt) {
	system("cls");
	int option;
	cout << "Your default semester is currently set to: " << defaultsmt.number << ". School year: " << defaultsc.startYear << "-" << defaultsc.endYear << "\n";
	if (defaultsmt.number == 0 || defaultsc.startYear == 0 || defaultsc.endYear == 0) {
		cout << "Please create a semester or change the default semester to continue!\n";
		cout << "1. Create a semester\n";
		cout << "2. Main Menu\n";
		cout << "Input your option: ";
		cin >> option;
		validateOption(option, 2);
		switch (option) {
		case 1:
			schoolYear tempsc = defaultsc;
			semester tempsmt = defaultsmt;
			createASemester(defaultsc, defaultsmt, tempsc, tempsmt);
			break;
		default:
			mainMenu(defaultsc, defaultsmt);
			return;
		}
	}
	else {
		courseInfo newCourse;
		newCourse.ID = "0";
		newCourse.name = "0";
		newCourse.teacher = "0";
		newCourse.credit = 0;
		newCourse.maxtudent = 0;
		newCourse.session[0].dayOfWeek = "0";
		newCourse.session[0].time.hour = 0;
		newCourse.session[0].time.minute = 0;
		newCourse.session[1].dayOfWeek = "0";
		newCourse.session[1].time.hour = 0;
		newCourse.session[1].time.minute = 0;
		cout << "All the below actions will be perfome on the default semester!\n";
		cout << "1. Add a course\n";
		cout << "2. Update course information\n";
		cout << "3. Delete a course\n";
		cout << "4. View list of course\n";
		cout << "5. Back\n";
		cout << "Input your option: ";
		cin >> option;
		validateOption(option, 5);
		switch (option) {
		case 1:
			addACourse(defaultsc, defaultsmt, newCourse);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4: 
			break;
		default:
			mainMenu(defaultsc, defaultsmt);
			return;
		}
	}
}

void addACourse(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	int option;
	cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
	cout << "Credit: " << newCourse.credit << " Student: " << newCourse.maxtudent;
	cout << " Session 1: " << newCourse.session[0].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute;
	cout << " Session 2: " << newCourse.session[1].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "1. Input course ID\n";
	cout << "2. Input course name\n";
	cout << "3. Input teacher name\n";
	cout << "4. Input number of credits\n";
	cout << "5. Input the maximum number of students in the course\n";
	cout << "6. Input course session 1\n";
	cout << "7. Input course session 2\n";
	cout << "8. Add a course\n";
	cout << "9. Back\n";
	cout << "Input your option: ";
	cin >> option;
	validateOption(option, 9);
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
		inputCredit(defaultsc, defaultsmt, newCourse);
		break;
	case 5:
		inputStudent(defaultsc, defaultsmt, newCourse);
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
	cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
	cout << "Credit: " << newCourse.credit << " Student: " << newCourse.maxtudent;
	cout << " Session 1: " << newCourse.session[0].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute;
	cout << " Session 2: " << newCourse.session[1].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "0. Back\n";
	cout << "Input course ID or 0 to back: ";
	cin.ignore(100, '\n');
	getline(cin, option);
	if (option.size() == 1 && option[0] == '0') {
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
	newCourse.ID = option;
	inputCourseID(defaultsc, defaultsmt, newCourse);
}

void inputCourseName(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	string option;
	cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
	cout << "Credit: " << newCourse.credit << " Student: " << newCourse.maxtudent;
	cout << " Session 1: " << newCourse.session[0].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute;
	cout << " Session 2: " << newCourse.session[1].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "0. Back\n";
	cout << "Input course name or 0 to back: ";
	cin.ignore(100, '\n');
	getline(cin, option);
	if (option.size() == 1 && option[0] == '0') {
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
	newCourse.name = option;
	inputCourseName(defaultsc, defaultsmt, newCourse);
}

void inputTeacherName(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	string option;
	cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
	cout << "Credit: " << newCourse.credit << " Student: " << newCourse.maxtudent;
	cout << " Session 1: " << newCourse.session[0].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute;
	cout << " Session 2: " << newCourse.session[1].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "0. Back\n";
	cout << "Input teacher name or 0 to back: ";
	cin.ignore(100, '\n');
	getline(cin, option);
	if (option.size() == 1 && option[0] == '0') {
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
	newCourse.teacher = option;
	inputTeacherName(defaultsc, defaultsmt, newCourse);
}

void inputCredit(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	int option;
	cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
	cout << "Credit: " << newCourse.credit << " Student: " << newCourse.maxtudent;
	cout << " Session 1: " << newCourse.session[0].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute;
	cout << " Session 2: " << newCourse.session[1].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "0. Back\n";
	cout << "Input number of credits or 0 to back: ";
	cin >> option;
	while (option < 0) {
		goToXY(0, 3);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 3);
		cout << "Input number of credits or 0 to back: " << option;
		goToXY(0, 4);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 4);
		cout << "Invalid! Try again: ";
		cin >> option;
	}
	switch (option) {
	case 0: 
		addACourse(defaultsc, defaultsmt, newCourse);
		break;
	default:
		newCourse.credit = option;
		inputCredit(defaultsc, defaultsmt, newCourse);
		return;
	}
}

void inputStudent(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	int option;
	cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
	cout << "Credit: " << newCourse.credit << " Student: " << newCourse.maxtudent;
	cout << " Session 1: " << newCourse.session[0].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute;
	cout << " Session 2: " << newCourse.session[1].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "0. Back\n";
	cout << "Input the maximum number of students in the course or 0 to back: ";
	cin >> option;
	while (option < 0) {
		goToXY(0, 3);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 3);
		cout << "Input the maximum number of students in the course or 0 to back: " << option;
		goToXY(0, 4);
		for (int i = 0; i <= 7; i++) {
			cout << "                                                                                                                  \n";
		}
		goToXY(0, 4);
		cout << "Invalid! Try again: ";
		cin >> option;
	}
	switch (option) {
	case 0:
		addACourse(defaultsc, defaultsmt, newCourse);
		break;
	default:
		newCourse.maxtudent = option;
		inputStudent(defaultsc, defaultsmt, newCourse);
		return;
	}
}

void inputCourseSession(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int n) {
	system("cls");
	int option;
	cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
	cout << "Credit: " << newCourse.credit << " Student: " << newCourse.maxtudent;
	cout << " Session 1: " << newCourse.session[0].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute;
	cout << " Session 2: " << newCourse.session[1].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "1. Input day of the week\n";
	cout << "2. Input time\n";
	cout << "3. Back\n";
	cout << "Input your option: ";
	cin >> option;
	validateOption(option, 3);
	switch (option) {
	case 1:
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, n);
		break;
	case 2:
		inputTime(defaultsc, defaultsmt, newCourse, n);
		break;
	default:
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
}

void inputDayOfTheWeek(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int n) {
	system("cls");
	int option;
	cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
	cout << "Credit: " << newCourse.credit << " Student: " << newCourse.maxtudent;
	cout << " Session 1: " << newCourse.session[0].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute;
	cout << " Session 2: " << newCourse.session[1].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
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
	validateOption(option, 8);
	switch (option) {
	case 1:
		newCourse.session[n].dayOfWeek = "MON";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, n);
		break;
	case 2:
		newCourse.session[n].dayOfWeek = "TUE";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, n);
		break;
	case 3:
		newCourse.session[n].dayOfWeek = "WED";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, n);
		break;
	case 4:
		newCourse.session[n].dayOfWeek = "THU";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, n);
		break;
	case 5:
		newCourse.session[n].dayOfWeek = "FRI";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, n);
		break;
	case 6:
		newCourse.session[n].dayOfWeek = "SAT";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, n);
		break;
	case 7:
		newCourse.session[n].dayOfWeek = "SUN";
		inputDayOfTheWeek(defaultsc, defaultsmt, newCourse, n);
		break;
	default:
		inputCourseSession(defaultsc, defaultsmt, newCourse, n);
		return;
	}
}

void inputTime(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse, int n) {
	system("cls");
	int option;
	cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
	cout << "Credit: " << newCourse.credit << " Student: " << newCourse.maxtudent;
	cout << " Session 1: " << newCourse.session[0].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute;
	cout << " Session 2: " << newCourse.session[1].dayOfWeek << " " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
	cout << "1. S1(07:30)\n";
	cout << "2. S2(9:30)\n";
	cout << "3. S3(13:30)\n";
	cout << "4. S4(15:30)\n";
	cout << "5. Back\n";
	cout << "Input your option: ";
	cin >> option;
	validateOption(option, 5);
	switch (option) {
	case 1:
		newCourse.session[n].time.hour = 7;
		newCourse.session[n].time.minute = 30;
		inputTime(defaultsc, defaultsmt, newCourse, n);
		break;
	case 2:
		newCourse.session[n].time.hour = 9;
		newCourse.session[n].time.minute = 30;
		inputTime(defaultsc, defaultsmt, newCourse, n);
		break;
	case 3:
		newCourse.session[n].time.hour = 13;
		newCourse.session[n].time.minute = 30;
		inputTime(defaultsc, defaultsmt, newCourse, n);
		break;
	case 4:
		newCourse.session[n].time.hour = 15;
		newCourse.session[n].time.minute = 30;
		inputTime(defaultsc, defaultsmt, newCourse, n);
		break;
	default:
		inputCourseSession(defaultsc, defaultsmt, newCourse, n);
		return;
	}
}

void loadCourse(ifstream& fin, courseNode*& pHead, string path) {
	fin.open(path);
	if (!fin.is_open()) {
		pHead = nullptr;
	}
	else {
		courseNode* pCur = nullptr;
		string ID;
		string name;
		string teacher;
		int credit;
		int student;
		courseSession session[2];
		getline(fin, ID);
		while (!(ID.size() == 1 && ID[0] == '0')) {
			getline(fin, name);
			getline(fin, teacher);
			fin >> credit;
			fin >> student;
			getline(fin, session[0].dayOfWeek);
			fin >> session[0].time.hour;
			fin >> session[0].time.minute;
			getline(fin, session[1].dayOfWeek);
			fin >> session[1].time.hour;
			fin >> session[1].time.minute;
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
			pCur->course.credit = credit;
			pCur->course.maxtudent = student;
			pCur->course.session[0].dayOfWeek = session[0].dayOfWeek;
			pCur->course.session[0].time.hour = session[0].time.hour;
			pCur->course.session[0].time.minute = session[0].time.minute;
			pCur->course.session[1].dayOfWeek = session[1].dayOfWeek;
			pCur->course.session[1].time.hour = session[1].time.hour;
			pCur->course.session[1].time.minute = session[1].time.hour;
			pCur->pNext = nullptr;
			getline(fin, ID);
		}
		fin.close();
	}
}

void insertCourse(courseNode*& pHead, courseInfo newCourse) {
	courseNode* pIns = nullptr;
	if (pHead == nullptr) {
		pIns = new courseNode;
		pIns->course = newCourse;
		pIns->pNext = nullptr;
		pHead = pIns;
		return;
	}
	courseNode* pCur = pHead;
	while (pCur->pNext != nullptr)
		pCur = pCur->pNext;
	pIns = new courseNode;
	pIns->course = newCourse;
	pIns->pNext = pCur->pNext;
	pCur->pNext = pIns;
}

void saveCourse(ofstream& fout, courseNode* pHead, string path) {
	fout.open(path);
	if (!fout.is_open()) {
		cout << "cannot open\n";
	}
	else {
		if (pHead == nullptr) {
			fout << "0";
			return;
		}
		courseNode* pCur = pHead;
		while (pCur != nullptr) {
			fout << pCur->course.ID << "\n" << pCur->course.name << "\n" << pCur->course.teacher << "\n" << pCur->course.credit << "\n" << pCur -> course.maxtudent << "\n";
			fout << pCur->course.session[0].dayOfWeek << "\n";
			fout << setw(2) << setfill('0') << pCur->course.session[0].time.hour << " " << setw(2) << setfill('0') << pCur ->course.session[0].time.minute << "\n";
			fout << pCur->course.session[1].dayOfWeek << "\n";
			fout << setw(2) << setfill('0') << pCur->course.session[1].time.hour << " " << setw(2) << setfill('0') << pCur->course.session[1].time.minute << "\n";
			pCur = pCur->pNext;
		}
		fout << "0";
		fout.close();
	}
}

void deleteCourse(courseNode*& pHead) {
	courseNode* pCur = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pCur;
		pCur = pHead;
	}
}

bool compareStrings(string a, string b) {
	if (a.size() != b.size())
		return false;
	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}

bool checkUnduplicatedCourse(courseNode* pHead, courseInfo newCourse) {
	if (pHead == nullptr) return true;
	courseNode* pCur = pHead;
	while (pCur != nullptr) {
		if (compareStrings(pCur->course.ID, newCourse.ID) == true && compareStrings(pCur->course.name, newCourse.name) == true && compareStrings(pCur->course.teacher, newCourse.teacher) == true && pCur->course.credit == newCourse.credit && pCur->course.maxtudent == newCourse.maxtudent && compareStrings(pCur->course.session[0].dayOfWeek, newCourse.session[0].dayOfWeek) == true && pCur->course.session[0].time.hour == newCourse.session[0].time.hour && pCur->course.session[0].time.minute == newCourse.session[0].time.minute && compareStrings(pCur->course.session[1].dayOfWeek, newCourse.session[1].dayOfWeek) == true && pCur->course.session[1].time.hour == newCourse.session[1].time.hour && pCur->course.session[1].time.minute == newCourse.session[1].time.minute)
			return false;
		pCur = pCur->pNext;
	}
	return true;
}

void add(schoolYear& defaultsc, semester& defaultsmt, courseInfo& newCourse) {
	system("cls");
	int option;
	string path = "Data/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.txt";
	ifstream fin;
	ofstream fout;
	courseNode* pHead = nullptr;
	loadCourse(fin, pHead, path);
	if (checkUnduplicatedCourse(pHead, newCourse) == false || (newCourse.ID.size() == 1 && newCourse.ID[0] == '0') || (newCourse.name.size() == 1 && newCourse.name[0] == '0') || (newCourse.teacher.size() == 1 && newCourse.teacher[0] == '0') || (newCourse.session[0].dayOfWeek.size() == 1 && newCourse.session[0].dayOfWeek[0] == '0') || (newCourse.session[1].dayOfWeek.size() == 1 && newCourse.session[1].dayOfWeek[0] == '0') || newCourse.credit == 0 || newCourse.maxtudent == 0 || newCourse.session[0].time.hour == 0 || newCourse.session[0].time.minute == 0 || newCourse.session[1].time.hour == 0 || newCourse.session[1].time.minute == 0) {
		deleteCourse(pHead);
		cout << "There is missing or invalid information to create a course!\n";
		cout << "Please check again the information of semester which you would like to create and go back to fix it\n";
		cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
		cout << "Credit: " << newCourse.credit << "\tStudent: " << newCourse.maxtudent << "\n";
		cout << " Session 1: " << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
		cout << " Session 2: " << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
		cout << "0. Back\n";
		cout << "Input 0: ";
		cin >> option;
		while (option != 0) {
			goToXY(0, 7);
			for (int i = 0; i <= 7; i++) {
				cout << "                                                                                                                  \n";
			}
			goToXY(0, 7);
			cout << "Input 0: " << option;
			goToXY(0, 8);
			for (int i = 0; i <= 7; i++) {
				cout << "                                                                                                                  \n";
			}
			goToXY(0, 8);
			cout << "Invalid! Try again: ";
			cin >> option;
		}
		addACourse(defaultsc, defaultsmt, newCourse);
		return;
	}
	else {
		path = "Data/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/" + newCourse.ID;
		int newCourseFolder = _mkdir(path.c_str());
		cout << "Course ID: " << newCourse.ID << "\tName: " << newCourse.name << "\tTeacher: " << newCourse.teacher << "\n";
		cout << "Credit: " << newCourse.credit << "\tStudent: " << newCourse.maxtudent << "\n";
		cout << " Session 1: " << newCourse.session[0].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[0].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[0].time.minute << "\n";
		cout << " Session 2: " << newCourse.session[1].dayOfWeek << " - " << setw(2) << setfill('0') << newCourse.session[1].time.hour << ":" << setw(2) << setfill('0') << newCourse.session[1].time.minute << "\n";
		if (newCourseFolder == 0) {
			path = "Data/" + to_string(defaultsc.startYear) + "-" + to_string(defaultsc.endYear) + "/Semester" + to_string(defaultsmt.number) + "/course.txt";
			insertCourse(pHead, newCourse);
			saveCourse(fout, pHead, path);
			deleteCourse(pHead);
			cout << "Has been created successfully!\n";
			cout << "0. Back\n";
			cout << "Input your option: ";
			cin >> option;
			while (option != 0) {
				goToXY(0, 6);
				for (int i = 0; i <= 7; i++) {
					cout << "                                                                                                                  \n";
				}
				goToXY(0, 6);
				cout << "Input 0: " << option;
				goToXY(0, 7);
				for (int i = 0; i <= 7; i++) {
					cout << "                                                                                                                  \n";
				}
				goToXY(0, 7);
				cout << "Invalid! Try again: ";
				cin >> option;
			}
			newCourse.ID = "0";
			newCourse.name = "0";
			newCourse.teacher = "0";
			newCourse.credit = 0;
			newCourse.maxtudent = 0;
			newCourse.session[0].dayOfWeek = "0";
			newCourse.session[0].time.hour = 0;
			newCourse.session[0].time.minute = 0;
			newCourse.session[1].dayOfWeek = "0";
			newCourse.session[1].time.hour = 0;
			newCourse.session[1].time.minute = 0;
			addACourse(defaultsc, defaultsmt, newCourse);
			return;
		}
		else {
			deleteCourse(pHead);
			cout << "Failed to create!\n";
			cout << "1. Try again\n";
			cout << "2. Back\n";
			cout << "Input your option: ";
			cin >> option;
			while (option < 1 || option > 2) {
				goToXY(0, 7);
				for (int i = 0; i <= 7; i++) {
					cout << "                                                                                                                  \n";
				}
				goToXY(0, 7);
				cout << "Input your option: " << option;
				goToXY(0, 8);
				for (int i = 0; i <= 7; i++) {
					cout << "                                                                                                                  \n";
				}
				goToXY(0, 8);
				cout << "Invalid! Try again: ";
				cin >> option;
			}
			switch (option) {
			case 1:
				add(defaultsc, defaultsmt, newCourse);
				break;
			default:
				addACourse(defaultsc, defaultsmt, newCourse);
				return;
			}
		}
	}
}