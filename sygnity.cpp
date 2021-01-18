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

double roundDoubleToTwoDigits(double var) 
{ 
    // EXAMPLE:
    // 37.66666 * 100 = 3766.66 
    // 3766.66 + .5 = 3767.16    for rounding off value 
    // then type cast to int so value is 3767 
    // then divided by 100 so the value converted into 37.67 
    double value = (int)(var * 100 + .5); 
    return (double)value / 100; 
} 

double getMonthsDifference(Date dt1, Date dt2){
    // Second Alghoritm:
    // count months difference between dwo dates
    long int monthsDifference = (dt2.y * 12 + dt2.m) - (dt1.y * 12 + dt1.m);
    double completeMonthsdoubleDifference = (double) monthsDifference;
    //cout << "completeMonthsdoubleDifference" << completeMonthsdoubleDifference << endl;
    // count days difference between dwo dates
    int daysDifference = dt2.d - dt1.d;
    if(daysDifference == 0){
        // wtedy nie liczyc w ogole dni
    }
    int daysInLastMonth;
    // check which was last month (need to know how much of the month is one day for this current month eg.: for February is 1/28, for December is 1/31)
    daysInLastMonth = monthDays[dt2.m-1];
        //cout << "daysInLastMonth: " << daysInLastMonth << endl;
    double lastMonthRestDifference =  (double)daysDifference/(double)daysInLastMonth;
    double totalMonthsDifference = completeMonthsdoubleDifference + lastMonthRestDifference;


    // cout << "daysDifference" << daysDifference << endl;
    // cout << "daysInLastMonth" << daysInLastMonth << endl;
    // cout << "lastMonthRestDifference" << lastMonthRestDifference << endl;
    // cout << "totalMonthsDifference" << totalMonthsDifference << endl;
    //cout << "completeMonthsdoubleDifference" << completeMonthsdoubleDifference << endl;
    return roundDoubleToTwoDigits(totalMonthsDifference);
    //return totalMonthsDifference;
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

void saveContentToFile(string fileName, double monthsDifference){
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

    // Alghoritm 2: count total months difference and add incomplete months (rest of days) as percent of current month eg. 0.64 are difference of 2 days in December
    double monthsDifferenceSecondAlghoritm = getMonthsDifference(dt1, dt2) ;
    saveContentToFile("output.txt", monthsDifferenceSecondAlghoritm);   

    system("pause");
    return 0;
}