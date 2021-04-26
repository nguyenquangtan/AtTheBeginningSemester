#include "structLibraryHeader.h"
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

void loadSchoolYear(ifstream& fin, schoolYearNode*& pHead, string path);
void deleteSchoolYear(schoolYearNode*& pHead);
void loadSemester(ifstream& fin, semesterNode*& pHead, string path);
void deleteSemester(semesterNode*& pHead);
void saveSemester(ofstream& fout, semesterNode* pHead, string path);
void insertSemester(semesterNode*& pHead, semester tempsmt);
void loadCourse(ifstream& fin, courseNode*& pHead, string path);
void deleteCourse(courseNode*& pHead);
void addCourse(courseNode*& pHead, courseInfo newCourse);
void saveCourse(ofstream& fout, courseNode* pHead, string path);
void loadDCourse(ifstream& fin, courseDNode*& pHead, string path);
void deleteDCourse(courseDNode*& pHead);
void saveDCourse(ofstream& fout, courseDNode* pHead, string path);

#endif