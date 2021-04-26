#include "utilityHeader.h"

void goToXY(SHORT posX, SHORT posY) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;
	SetConsoleCursorPosition(hStdout, Position);
}

int convertStringToInt(string a) {
	int result = 0;
	for (int i = 0; i < a.size(); i++) {
		result *= 10;
		result += int(a[i] - '0');
	}
	return result;
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