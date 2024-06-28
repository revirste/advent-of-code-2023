#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main() {    
    ifstream CalibrationFile("calibration.txt");
    string currentLine;
    string currentDigitStr;
    string currLineDigits;
    int runningTotal = 0;
    
    int linecount = 0;
    while (CalibrationFile.good()) {
        getline(CalibrationFile, currentLine);


        /* Iterate through the current line, checking each element of the line string
           to see if it is a digit or not. If its a digit, append it to a separate string
           that represents the concatenated digit string for the current line.
        */
        int currDigitCount = 0;
        for (int i = 0; i < currentLine.size(); ++i)
        {

            if (isdigit(currentLine.at(i))) {
                ++currDigitCount;
                currentDigitStr = string(1, currentLine.at(i));
                currLineDigits.append(currentDigitStr);
                cout << "(DEBUG) The digit string is " << currentDigitStr << std::endl;
            }
        }


        /* If there are more than 2 digits in the current line,
           then obtain first and last element of currLineDigits
           and replace the existing currentDigitStr with the stripped
           version prior to it being operated on.

           Else if there is only 1 digit in the count, then duplicate that digit to
           arrive at our currLineDigits
        */
        if (currDigitCount > 2) {
            string currLineDigitsBack = string(1, currLineDigits.back());
            string currLineDigitsFront = string(1, currLineDigits.front());
            currLineDigits = "";
            currLineDigits.append(currLineDigitsFront);
            currLineDigits.append(currLineDigitsBack);
        } 
        else if (currDigitCount == 1) {
            currLineDigits.append(string(1, currLineDigits.at(0)));
        }


        /* If its not the end of the file, print to console which line we are on as well as
           what the concatenated digits are for that line. Then, add the concatenated
           digits to a running total to be used at the end of the program.
        */
        if (!CalibrationFile.eof()) {
            std::cout << "(DEBUG) The concatenated digits for line " << linecount << " are: " << currLineDigits << std::endl;
            runningTotal += stoi(currLineDigits);
        }
    

        /* Reset currLineDigits to be an empty string, increment our line count, and newline. */
        currLineDigits = "";
        ++linecount;
        std::cout << endl;
    }
    
    std::cout << "The total calibration value is " << runningTotal << std::endl;
    std::cout << "NICHOLASBLACK.DEV \nADVENT OF CODE - 2023 - DAY 1 \n" << std::endl;
    CalibrationFile.close();
    return 0;
}