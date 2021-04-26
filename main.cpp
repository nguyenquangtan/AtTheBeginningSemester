#include "menuHeader.h"

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