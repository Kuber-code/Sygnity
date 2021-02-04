// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <ctime>// do uzycia typu daty do obliczenia roznicy w seundach sekund
// uzyc jeszcze uint64_t

using namespace std;

struct Date {
	int y, m, d;
};

const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

double roundDoubleToTwoDigits(double var) // zastapic funkcja round z cmath.h
{ 
	// EXAMPLE:
	// 37.66666 * 100 = 3766.66 
	// 3766.66 + .5 = 3767.16    for rounding off value 
	// then type cast to int so value is 3767 
	// then divided by 100 so the value converted into 37.67 
	double value = (int)(var * 100 + .5);
	return (double)value / 100;
}

double getMonthsDifference(Date dt1, Date dt2) { // to zamienic na to ze stack overflow  https://stackoverflow.com/questions/9987562/determining-the-difference-between-dates
	// Second Alghoritm:
	// count months difference between dwo dates
	long int monthsDifference = (dt2.y * 12 + dt2.m) - (dt1.y * 12 + dt1.m);
	double completeMonthsdoubleDifference = (double)monthsDifference;
	//cout << "completeMonthsdoubleDifference" << completeMonthsdoubleDifference << endl;
	// count days difference between dwo dates
	int daysDifference = dt2.d - dt1.d;
	if (daysDifference == 0) {
		// wtedy nie liczyc w ogole dni
	}
	int daysInLastMonth;
	// check which was last month (need to know how much of the month is one day for this current month eg.: for February is 1/28, for December is 1/31)
	daysInLastMonth = monthDays[dt2.m - 1];
	//cout << "daysInLastMonth: " << daysInLastMonth << endl;
	double lastMonthRestDifference = (double)daysDifference / (double)daysInLastMonth;
	double totalMonthsDifference = completeMonthsdoubleDifference + lastMonthRestDifference;


	cout << "daysDifference" << daysDifference << endl;
	cout << "daysInLastMonth" << daysInLastMonth << endl;
	cout << "lastMonthRestDifference" << lastMonthRestDifference << endl;
	cout << "totalMonthsDifference" << totalMonthsDifference << endl;
	cout << "completeMonthsdoubleDifference" << completeMonthsdoubleDifference << endl;
	return roundDoubleToTwoDigits(totalMonthsDifference);
	//return totalMonthsDifference;
}

bool getFileContentToVector(string fileName, vector<string> & vecOfStrings)
{
	// Open the File
	ifstream inputFile(fileName.c_str());
	// Check if object is valid
	if (!inputFile)
	{
		cerr << "Cannot open the File : " << fileName << endl;
		return false;
	}
	string str;
	// Read the next line from File untill it reaches the end.

	while (getline(inputFile, str))
	{
		// Line contains string of length > 0 then save it in vector
		if (str.size() > 0) {
			vecOfStrings.push_back(str);
		}
	}
	//Close The File
	inputFile.close();
	return true;
}

bool isNumber(const string& s)   // w cmath - check if string is a digit  z bilbioteki standardowej
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	//return !s.empty() && it == s.end();
	bool result = !s.empty() && it == s.end();
	if (result) {
		//cout << "input value is OK" << endl;
		return true;
	}else{
		cout << "Input value is NOT a valid number" << endl;
		return false;
	}
}

bool isMonthNumberCorrect(int m) {
	if (m >= 1 && m <= 12) {
		return true;
	}else{
		cout << "Month number is NOT a valid number" << endl;
		return false;
	}
}

bool isYearALeapYear(int y) 
{ 
    // If a year is multiple of 400, 
    // then it is a leap year 
    if (y % 400 == 0) 
        return true; 
 
    // Else If a year is multiple of 100, 
    // then it is not a leap year 
    if (y % 100 == 0) 
        return false; 
 
    // Else If a year is multiple of 4, 
    // then it is a leap year 
    if (y % 4 == 0) 
        return true; 
    return false; 
} 

bool isDayNumberCorrect(int y, int m, int d){
	cout << "y " << y << endl;
	cout << "m " << m << endl;
	cout << "d " << d << endl;
	if (d < 1 || d > 31){
		cout << "Day number is NOT a valid number" << endl;
		return false;
	}
	if (m < 1 || m > 12) {
		cout << "Day number is NOT a valid number" << endl;
		return false;
	}
	if (m == 3 || m == 5 || m == 8 || m == 10 && d > 30){
		cout << "Day number is NOT a valid number" << endl;
		return false;		
	}
	if (m == 1){
		if (isYearALeapYear(y)){
			if (d > 29){
				cout << "Day number is NOT a valid number" << endl;
				return false;
			}
		}else{
			if (d > 28){
				cout << "Day number is NOT a valid number" << endl;
				return false;
			}
		}
	}
	cout << "Day number is OK" << endl;
	return true;
}
//const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


void convertVectorToStruct(vector<string> & vecOfStrings, Date & dt1, Date & dt2) {
	// Split vectors with file content (eg.: 2020-01-01) using String Streams to adequate years, months and days in Data structure
	int i = 0;
	for (string & line : vecOfStrings) {
		istringstream stringStream(line);
		string token;
		// Split lines form file to structure data, every token is single data eg.: 2020
		while (getline(stringStream, token, '-')) {
			//dataVector.push_back(token);
			if (i == 0) {                            ////////  to  do: zamienic te ify na swich , token zmienic nazwe,
				if (!isNumber(token)) 
					break;
				istringstream(token) >> dt1.y;
			}
			if (i == 1) {
				if (!isNumber(token))
					break;
				istringstream(token) >> dt1.m;
				if (!isMonthNumberCorrect(dt1.m))
					break;
			}
			if (i == 2) {
				if (!isNumber(token)) 
					break;
				istringstream(token) >> dt1.d;
				if (!isDayNumberCorrect(dt1.y, dt1.m, dt1.d))
					break;
			}
			if (i == 3) {
				if (!isNumber(token))
					break;
				istringstream(token) >> dt2.y;
			}
			if (i == 4) {
				if (!isNumber(token))
					break;
				istringstream(token) >> dt2.m;
				if (!isMonthNumberCorrect(dt2.m))
					break;
			}
			if (i == 5) {
				//token.pop_back();
				if (!isNumber(token))
					break;
				istringstream(token) >> dt2.d;
				cout << "token " << token;
				cout << "dt2.d " << dt2.d;
				if (!isDayNumberCorrect(dt2.y, dt2.m, dt2.d))
					break;
			}
			i++;
		}
	}
}

void saveContentToFile(string fileName, double monthsDifference) {
	// Create and open a text file
	ofstream MyFile(fileName);
	// Write to the file
	MyFile << monthsDifference;
	// Close the file
	MyFile.close();
}

int main()
{
	// Declare data
	vector<string> vecOfStrings;
	Date dt1 = { 2020, 1, 1 };
	Date dt2 = { 2020, 1, 2 };
	// Get the contents of file to vector, if the data is valid
	bool result = getFileContentToVector("input.txt", vecOfStrings);
	if (result) {
		convertVectorToStruct(vecOfStrings, dt1, dt2);
	}

	// Alghoritm 2: count total months difference and add incomplete months (rest of days) as percent of current month eg. 0.64 are difference of 2 days in December
	double monthsDifferenceSecondAlghoritm = getMonthsDifference(dt1, dt2);
	saveContentToFile("output.txt", monthsDifferenceSecondAlghoritm);

	system("pause");
	return 0;
}
