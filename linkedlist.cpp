#include "checkerHeader.h"
#include "linkedListHeader.h"
#include "utilityHeader.h"

void loadSchoolYear(ifstream& fin, schoolYearNode*& pHead, string path) {
	fin.open(path);
	if (!fin.is_open()) {
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
		pCur->sc.endYear = convertStringToInt(endYear);
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

void saveSemester(ofstream& fout, semesterNode* pHead, string path) {
	fout.open(path);
	if (!fout.is_open()) {
		return;
	}
	if (pHead == nullptr) return;
	semesterNode* pCur = pHead;
	while (pCur != nullptr) {
		fout << setw(2) << setfill('0') << pCur->smt.number << ",";
		fout << setw(2) << setfill('0') << pCur->smt.startDate.day << setw(2) << setfill('0') << pCur->smt.startDate.month << setw(4) << setfill('0') << pCur->smt.startDate.year << ",";
		fout << setw(2) << setfill('0') << pCur->smt.endDate.day << setw(2) << setfill('0') << pCur->smt.endDate.month << setw(4) << setfill('0') << pCur->smt.endDate.year;
		if (pCur->pNext != nullptr)
			fout << "\n";
		pCur = pCur->pNext;
	}
	fout.close();
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

void loadCourse(ifstream& fin, courseNode*& pHead, string path) {
	fin.open(path);
	if (!fin.is_open()) {
		return;
	}
	string ID, name, teacher, credit, student, dayOfWeek[2], time[2];
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

void addCourse(courseNode*& pHead, courseInfo newCourse) {
	courseNode* pIns = nullptr;
	if (pHead == nullptr) {
		pIns = new courseNode;
		pIns->course = newCourse;
		pIns->pNext = nullptr;
		pHead = pIns;
		return;
	}
	if (compareString_Alphabet(pHead->pNext->course.ID, newCourse.ID) == true) {
		pIns = new courseNode;
		pIns->course = newCourse;
		pIns->pNext = pHead;
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