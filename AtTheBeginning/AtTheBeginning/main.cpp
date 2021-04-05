#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>
using namespace std;

struct schoolYear {
	int startYear;
	int endYear;
};

struct schoolYearNode {
	schoolYear sc;
	schoolYearNode* pNext;
};

struct date {
	int day;
	int month;
	int year;
};

struct semester {
	int number; //xác định học kì thứ bao nhiêu, vd: học kì 1
	date startDate;
	date endDate;
};

struct semesterNode {
	semester sem;
	semesterNode* pNext;
};

void goToXY(SHORT posX, SHORT posY);
void loadSchoolYear(ifstream& f, string path, schoolYearNode*& pHead);
void loadSemester(ifstream& f, string path, semesterNode*& pHead);
void createASemester(semesterNode*& pHead);
schoolYear chooseTheSchoolYear(schoolYearNode* pHead);

int main()
{
	ifstream ifs;
	int status;
	schoolYearNode* pHead1 = nullptr;
	semesterNode* pHead2 = nullptr;
	string path = "Data\\schoolyear.txt";
	loadSchoolYear(ifs, path, pHead1);
	schoolYear answer = chooseTheSchoolYear(pHead1);
	path = "Data\\" + to_string(answer.startYear) + "-" + to_string(answer.endYear) + "\\semester.txt";
	loadSemester(ifs, path, pHead2);
	path = "Data\\" + to_string(answer.startYear) + "-" + to_string(answer.endYear) + "Semester3";
	status = _mkdir("Data\\2020-2021\\Semester3");
	return 0;
}

void goToXY(SHORT posX, SHORT posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}

schoolYear chooseTheSchoolYear(schoolYearNode* pHead) {
	int i = 0, choice;
	schoolYear answer;
	schoolYearNode* pCur = pHead;
	while (pCur != nullptr) {
		i++;
		cout << i << ". " << pCur->sc.startYear << "-" << pCur->sc.endYear << "\n";
		pCur = pCur->pNext;
	}
	cout << "Please input an option: ";
	cin >> choice;
	while (choice < 1 && choice > i) {
		goToXY(i, 0);
		cout << "Invalid! Please input an option again: ";
		cin >> choice;
	}
	pCur = pHead;
	for (int i = 0; i < choice - 1; i++)
		pCur = pCur->pNext;
	answer.startYear = pCur->sc.startYear;
	answer.endYear = pCur->sc.endYear;
	return answer;
}

void loadSchoolYear(ifstream& f, string path, schoolYearNode* &pHead) {
	f.open(path);
	if (!f.is_open()) {
		cout << "Can not open file\n";
	}
	else {
		schoolYearNode* pCur = nullptr;
		int start, end;
		f >> start;
		while (start != 0) {
			f >> end;
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
			f >> start;
		}
		f.close();
	}
	return;
}

void loadSemester(ifstream& f, string path, semesterNode*& pHead) {
	f.open(path);
	if (!f.is_open()) {
		cout << "Can not open file\n";
	}
	else {
		semesterNode* pCur = nullptr;
		int num;
		date start;
		date end;
		f >> num;
		while (num != 0) {
			f >> start.day;
			f >> start.month;
			f >> start.year;
			f >> end.day;
			f >> end.month;
			f >> end.year;
			if (pHead == nullptr) {
				pHead = new semesterNode;
				pCur = pHead;
			}
			else {
				pCur->pNext = new semesterNode;
				pCur = pCur->pNext;
			}
			pCur->sem.number = num;
			pCur->sem.startDate.day = start.day;
			pCur->sem.startDate.month = start.month;
			pCur->sem.startDate.year = start.year;
			pCur->sem.endDate.day = end.day;
			pCur->sem.endDate.month = end.month;
			pCur->sem.endDate.year = end.year;
			pCur->pNext = nullptr;
			f >> num;
		}
		f.close();
	}
	return;
}

/*void createASemester(semesterNode*& pHead) {
	semester newsem;
	cout << "Please input a semester: ";
	cin >> newsem.number;

}*/