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
 
    // Check if the current year needs to be
    //  considered for the count of leap years
    // or not
    if (d.m <= 2)
        years--;
 
    // An year is a leap year if it 
    // is a multiple of 4,
    // multiple of 400 and not a 
     // multiple of 100.
    return years / 4 
           - years / 100
           + years / 400;
}

int getDifference(Date dt1, Date dt2)
{
    // COUNT TOTAL NUMBER OF DAYS
    // BEFORE FIRST DATE 'dt1'
 
    // initialize count using years and day
    long int n1 = dt1.y * 365 + dt1.d;
 
    // Add days for months in given date
    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];
 
    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(dt1);
 
    // SIMILARLY, COUNT TOTAL NUMBER OF
    // DAYS BEFORE 'dt2'
 
    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);
 
    // return difference between two counts
    return (n2 - n1);
}

bool getFileContent(string fileName, vector<string> & vecOfStrings)
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
    string data[20];
    // Read the next line from File untill it reaches the end.
    int i = 1;
    while (getline(inputFile, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0){
            vecOfStrings.push_back(str);
            //stringstream stream(str);
            //loop to split string
            // while(getline(stream, data[i], '-') )
            // {
            //     //increase repetition number
            //     i++;
            // }
        }
           
    }
    //Close The File
    inputFile.close();
    return true;
}

int convertDaysToMonths (int dayDifference){
    
}

int main()
{
    vector<string> vecOfStrings;
    // Get the contents of file in a vector
    bool result = getFileContent("input.txt", vecOfStrings);
    Date dt1 = { 2020, 1, 1 };
    Date dt2 = { 2020, 1, 2 };
    if(result){
        // Print the vector contents
        vector<string> dataVector;
        int i=0;
        for(string & line : vecOfStrings){
            cout << line << endl;
            // ROBIE COŚ DLA KAŻDEJ LINIK Z TEXTU
            cout << "linie wektora"<<endl;
            istringstream ss(line);
	        string token;

            //vector<string> playerInfoVector;
            while(getline(ss, token, '-')) {
                dataVector.push_back(token);
                cout << token << '\n';
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
                // tutaj wyświetla mi podziuelonego stringa juz
                i++;
	        }
        }
    }

    //Date dt1 = { 2020, 12, 1 };
    //Date dt2 = { 2020, 12, 2 };
 
    // Function call
    int dayDifference =  getDifference(dt1, dt2);
    cout << "Difference between two dates is " << dayDifference;
    int monthDifference = convertDaysToMonths(dayDifference);
    system("pause");
    return 0;
}