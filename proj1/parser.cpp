
/* CHERYL MELWANI (cmelwa01)
18th February 2020
*/

#include "DatumStack.h"
#include <string>
#include <iostream>
#include <istream>
#include <fstream>

using namespace std;

string parseRString(istream &input);

/* Purpose: To test whether the parse string function works
Return type: int
Parameters: int argc and char *argv[] -- takes in the files provided in the
executable
*/
int main(int argc, char *argv[]) {

    if (argc == 2) {
        ifstream infile;
        infile.open(argv[1]);
         if(infile.fail()) {
          cerr << "Error: coult not open file ParserTest.txt" << endl;
          exit(EXIT_FAILURE);
        }
        string first_char;
        while (infile >> first_char) {
            if (first_char == "{") {
                string parser = parseRString(infile);
                cout << "This is the final RString: " << parser << endl;
            }
        }
        infile.close();
    } else {
        cout << "Please input an RString: ";
        string parser = parseRString(cin);
        cout << "This is the final RString: " << parser << endl;
    }
    return 0;
}

/* Purpose: A function that parses through an r-string and returns that r_string
as a string. The function throws an error if the brackets in the r_string
do not match up.
Return type: string
Parameters: an input stream
*/
string parseRString(istream &input) {
    string c;
    int counter = 1;
    string r_string;
    string open_bracket;

    while (input >> c) {
        if (c == "{") {
             counter++;
        }
        if (c == "}") {
            counter--;
        }

        r_string = r_string + " " + c;

        if (counter == 0) {
            break;
        }
    }
    if (counter != 0) {
        throw runtime_error("RString not valid! ");
    }

    if (r_string.at(0) == ' ') {
        open_bracket = "{";
    } else {
        open_bracket = "{ ";
    }
    r_string = open_bracket + r_string;

    return r_string;
}
