#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Date {
    int y, m, d;
};

const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int countLeapYears(Date d){
    int years = d.y;
 
    // Check if the current year needs to be considered for the count of leap years or not
    if (d.m <= 2)
        years--;
 
    // An year is a leap year if it is a multiple of 4, multiple of 400 and not a multiple of 100.
    return years / 4 - years / 100 + years / 400;
}

float roundFloatToTwoDigits(float var) 
{ 
    // EXAMPLE:
    // 37.66666 * 100 = 3766.66 
    // 3766.66 + .5 = 3767.16    for rounding off value 
    // then type cast to int so value is 3767 
    // then divided by 100 so the value converted into 37.67 
    float value = (int)(var * 100 + .5); 
    return (float)value / 100; 
} 

float getMonthsDifference(Date dt1, Date dt2){
    // Second Alghoritm:
    // count months difference between dwo dates
    long int monthsDifference = (dt2.y * 12 + dt2.m) - (dt1.y * 12 + dt1.m);
    float completeMonthsFloatDifference= (float) monthsDifference;
    // count days difference between dwo dates
    int daysDifference = dt2.d - dt1.d;
    int daysInLastMonth;
    // check which was last month (need to know how much of the month is one day for this current month eg.: for February is 1/28, for December is 1/31)
    if (dt2.d = 1){
        if(dt2.m = 1){
            daysInLastMonth = monthDays[12];
        }
        daysInLastMonth = monthDays[dt2.m-1];
    }
    daysInLastMonth = monthDays[dt2.m];
    
    float lastMonthRestDifference =  (float)daysDifference/(float)daysInLastMonth;
    float totalMonthsDifference = completeMonthsFloatDifference + lastMonthRestDifference;
    return roundFloatToTwoDigits(totalMonthsDifference);
}

int getDaysDifference(Date dt1, Date dt2)
{
    // First Alghoritm:
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1'
    // initialize count using years and day
    long int n1 = dt1.y * 365 + dt1.d;
 
    // Add days for months in given date
    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];
 
    // Since every leap year is of 366 days, Add a day for every leap year
    n1 += countLeapYears(dt1);
 
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt2'
    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);
 
    // return difference between two counts
    return (n2 - n1);
}

bool getFileContentToVector(string fileName, vector<string> & vecOfStrings)
{
    // Open the File
    ifstream inputFile(fileName.c_str());
    // Check if object is valid
    if(!inputFile)
    {
        cerr << "Cannot open the File : "<< fileName << endl;
        return false;
    }
    string str;
    // Read the next line from File untill it reaches the end.
    
    while (getline(inputFile, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0){
            vecOfStrings.push_back(str);
        }
    }
    //Close The File
    inputFile.close();
    return true;
}

float convertDaysToMonths (int dayDifference){
    // First Alghoritm:
    float months = (float) dayDifference / 30.42;
    float months2Decimal = 0.0;
    months2Decimal = roundFloatToTwoDigits(months);
    return months2Decimal;
}

void convertVectorToStruct(vector<string> & vecOfStrings, Date & dt1, Date & dt2 ){
        // Split vectors with file content (eg.: 2020-01-01) using String Streams to adequate years, months and days in Data structure
        int i = 0;
        for(string & line : vecOfStrings){
            istringstream stringStream(line);
	        string token;
            // Split lines form file to structure data, every token is single data eg.: 2020
            while(getline(stringStream, token, '-')) {
                //dataVector.push_back(token);
                if (i == 0){
                string s = token;
                istringstream(s) >> dt1.y ;
                }
                if (i == 1){
                string s = token;
                istringstream(s) >> dt1.m ;
                }
                if (i == 2){
                string s = token;
                istringstream(s) >> dt1.d;
                }
                if (i == 3){
                string s = token;
                istringstream(s) >> dt2.y;
                }
                if (i == 4){
                string s = token;
                istringstream(s) >> dt2.m;
                }
                if (i == 5){
                string s = token;
                istringstream(s) >> dt2.d;
                }
                i++;
	        }
        }
}

void saveContentToFile(string fileName, float monthsDifference){
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
    if(result){
        convertVectorToStruct(vecOfStrings, dt1, dt2);
    }
    // Alghorith 1: count total days difference and count mounths difference from average amount of days per month in the year (365/12)
    int dayDifference = getDaysDifference(dt1, dt2);
    float monthsDifference = convertDaysToMonths(dayDifference);
    saveContentToFile("output2.txt", monthsDifference);

    // Alghoritm 2: count total months difference and add incomplete months (rest of days) as percent of current month eg. 0.07 are difference of 2 days in December
    float monthsDifferenceSecondAlghoritm = getMonthsDifference(dt1, dt2) ;
    saveContentToFile("output.txt", monthsDifferenceSecondAlghoritm);   

    system("pause");
    return 0;
}