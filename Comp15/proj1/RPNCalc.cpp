
/*
COMP15 Project 1
CHERYL MELWANI (cmelwa01)
27th February 2020
The RPNCalc.cpp is the main implementation file of the calculator that includes
the other h files like Datum and DatumStack. The RPNCalc.cpp implements all
of the public and private functions found in the RPNCalc.h file.
*/

#include "RPNCalc.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

/* Constructor */
RPNCalc::RPNCalc() {

}

/* Destructor -- no allocated memory on the heap for this assignment
Purpose: Delete any new allocated memory on the heap */
RPNCalc::~RPNCalc() {
    stack.clear();
}

/* Purpose: is to check if a string can be changed into an integer and that
integer will then be stored in a pointer called resultp
Return type: boolean. true if the string can be changed into an integer and
false if it cannot
Parameters: string s and an integer pointer
*/

bool RPNCalc::got_int(string s, int *resultp) {
    return sscanf(s.c_str(), "%d", resultp) == 1;
}

/* Purpose: is to run all the queries that the user or a file will put in.
Calls runHelper which actually takes in an istream.
Return type: void
Parameters: none
*/
void RPNCalc::run() {
    runHelper(cin);
}

/* Purpose: the runHelper function does the bulk of taking in an istream
and reading in the commands from that istream whether it be a cin or a file.
The commands are then used to call all the other functionalities. The function
will keep reading from cin or from the file until the user quits or the file
ends or the file says "quit" in it.
Return type: void
Parameters: istream called input
*/
void RPNCalc::runHelper(istream &input) {
    string query;
    int x = 0;
    bool check = false;
    while (check == false && input >> query) {
        if (query == "#t" || query == "#f" || got_int(query, &x) == true){
            pushRunHelper(query);
        }
        else if (query == "{") {
            string RString = parseRString(input);
            Datum d = Datum(RString);
            stack.push(d);
        }
        else if (query == "not") {
            notQuery();
        }
        else if (query == "print") {
            printQuery();
        }
        else if (query == "clear") {
            clearQuery();
        }
        else if (query == "drop") {
            dropQuery();
        }
        else if (query == "dup") {
            dupQuery();
        }
        else if (query == "swap") {
            swapQuery();
        }
        else if (query == "quit") {
            check = true;
            cout << "Thank you for using CalcYouLater. " << endl;
            return;
        }
        else if (query == "+" || query == "-" || query == "*" || query == "/" ||
        query == "mod") {
            operationQuery(query);
        }
        else if (query == "<" || query == ">" || query == "<=" || query == ">=") {
            comparisonQuery(query);
        }
        else if (query == "==") {
            equalQuery();
        }
        else if (query == "exec") {
            execQuery();
        }
        else if (query == "file") {
            fileQuery();
        }
        else if (query == "if") {
            ifQuery();
        }
        else if (query[0] == '#') {
            cerr << "Error: invalid boolean " << query << endl;
        }
        else {
            cerr << query << ":  unimplemented" << endl;
        }
    }
    return;
}

/* Purpose: The purpose of this function is that its a helper function to the
one above to reduce line length and to implement commands that all have
some sort of pushing involved.
return: void
Parameters: string query
*/
void RPNCalc::pushRunHelper(string query) {
    int x = 0;
    if(query == "#t") {
        Datum d = Datum(true);
        stack.push(d);
    } else if (query == "#f") {
        Datum d = Datum(false);
        stack.push(d);
    }
    else if(got_int(query, &x)) {
        Datum d = Datum(x);
        stack.push(d);
    }
}

/* Purpose: A function that parses through an r-string and returns that r_string
as a string. The function throws an error if the brackets in the r_string
do not match up.
Return type: string
Parameters: an input stream
*/
string RPNCalc::parseRString(istream &input) {
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
    try {
        if (counter != 0) {
            throw runtime_error("reached end of program when searching for }");
        }
    } catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }

    if (r_string.at(0) == ' ') {
        open_bracket = "{";
    }
    else {
        open_bracket = "{ ";
    }
    r_string = open_bracket + r_string;

    return r_string;
}

/* Purpose: the purpose is to implement the not query that pushes false on the
stack if the top of the stack is true and vice versa.
Return type: void
Parameters: none
*/
void RPNCalc::notQuery() {
    try {
        Datum front = stack.top();
        stack.pop();
        if (front.getBool() == true) {
            Datum d = Datum(false);
            stack.push(d);
        }
        else if (front.getBool() == false) {
            Datum d = Datum(true);
            stack.push(d);
        }
    } catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}

/* Purpose: the purpose is to print the top of the stack whether it be an
int, bool, or rString.
Return type: void
Parameters: none
*/
void RPNCalc::printQuery() {
    try {
        Datum front = stack.top();
        if (front.isInt()) {
            cout << front.getInt() << endl;
        }
        else if (front.isBool()) {
            if (front.getBool() == true) {
                cout << "#t" << endl;
            } else {
                cout << "#f" << endl;
            }
        }
        else if (front.isRString()) {
            cout << front.getRString() << endl;
        }
    } catch (runtime_error &exc) {
       cerr << "Error: " << exc.what() << endl;
   }
}

/* Purpose: the purpose is to clear the stack
Return type: void
Parameters: none
*/
void RPNCalc::clearQuery() {
    stack.clear();
}

/* Purpose: the purpose is to implement the drop query function that pops
the first thing in the stack.
Return type: void
Parameters: none
*/
void RPNCalc::dropQuery() {
    try {
        stack.pop();
    } catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}

/* Purpose: the purpose of this function is to duplicate the first datum
on the stack.
Return type: void
Parameters: none
*/
void RPNCalc::dupQuery() {
    try{
        Datum front = stack.top();
        stack.push(front);
    } catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}

/* Purpose: the purpose of this function is to swap the two functions on the
top of the stack.
Return type: void
Parameters: none
*/
void RPNCalc::swapQuery() {
    try{
        Datum top1 = stack.top();
        stack.pop();
        Datum top2 = stack.top();
        stack.pop();
        stack.push(top1);
        stack.push(top2);
    } catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}

/* Purpose: the purpose of this function is to account for all of the
operations including +,-,/,* and mod. It takes in a query
in order to tell which specific operator to implement.
Return type: void
Parameters: string query
*/
void RPNCalc::operationQuery(string query) {
    try {
        Datum top1 = stack.top();
        int x = top1.getInt();
        stack.pop();
        Datum top2 = stack.top();
        int y = top2.getInt();
        stack.pop();
        int total = 0;
        if (query == "+") {
            total = y + x;
        }
        else if (query == "-") {
            total = y - x;
        }
        else if (query == "*") {
            total = y * x;
        }
        else if (query == "/") {
            if(x == 0) {
                cerr << "Error: division by 0." << endl;
            } else {
                total = y / x;
            }
        }
        else if (query == "mod") {
            total = y % x;
        }
        Datum d = Datum(total);
        stack.push(total);
    } catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}

/* Purpose: the purpose is to implement the == operation since this operation
can work with any and all types of datums as opposed to just integers like
all of the other comparison operations.
Return type: void
Parameters: none
*/
void RPNCalc::equalQuery() {
    try{
        Datum top1 = stack.top();
        stack.pop();
        Datum top2 = stack.top();
        stack.pop();
        bool outcome = false;
        outcome = (top1 == top2);
        Datum d = Datum(outcome);
        stack.push(d);
    }  catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}

/* Purpose: the purpose of this function is to implement the queries that
involve comparisons like < and >=. All of these queries only take in an
integer Datum so it makes sense to group them together. It takes in a query
in order to tell which specific comparison operator to implement.
Return type: void
Parameters: string query
*/
void RPNCalc::comparisonQuery(string query) {
    try {
        Datum top1 = stack.top();
        int x = top1.getInt();
        stack.pop();
        Datum top2 = stack.top();
        int y = top2.getInt();
        stack.pop();
        bool outcome = true;
        if (query == "<") {
            outcome = (y < x);
        }
        else if (query == ">") {
            outcome = (y > x);
        }
        else if (query == "<=") {
            outcome = (y <= x);
        }
        else if (query == ">=") {
            outcome = (y >= x);
        }
        Datum d = Datum(outcome);
        stack.push(d);
    } catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}

/* Purpose: the purpose of this function is to implement the exec query that
can read in an rstring as actual commands. this function calls the runHelper
function. It takes into account specific errors and tries and catches like
all the other functions.
Return type: void
Parameters: string query
*/
void RPNCalc::execQuery() {
    try{
        Datum top = stack.top();
        stack.pop();
        if (top.isRString() == false) {
            cerr << "Error: cannot execute not rstring" << endl;
            return;
        }
        string rString = top.getRString();
        rString.erase(rString.begin(), rString.begin() + 2);
        rString.pop_back();
        rString.pop_back();

        stringstream input(rString);
        runHelper(input);
    } catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}

/* Purpose: the purpose of this function is to pop of the first datum on the
stack. If that datum is an rstring it will process it as a filename. If it
can be read then the function will open that file and if if cannot it will
produce an error.
Return type: void
Parameters: none
*/
void RPNCalc::fileQuery() {
    try {
        Datum top = stack.top();
        stack.pop();
        if (top.isRString() == false) {
            cerr << "Error: file operand not rstring" << endl;
            return;
        }
        string filename = top.getRString();
        filename.erase(filename.begin(), filename.begin() + 2);
        filename.pop_back();
        filename.pop_back();

        ifstream infile;
        infile.open(filename.c_str());
        if (infile.fail()) {
          cerr << "Unable to read " << filename << endl;
        }
        runHelper(infile);
        infile.close();
    } catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}

/* Purpose: the purpose of this function is to implement the if query that
works in 3 parts. The first being a condition, the second being a true case
and the third being a false case. The function implements the true or false
case depending on whether the condition is true or false. It accounts for
errors like all the other functions.
Return type: void
Parameters: none
*/
void RPNCalc::ifQuery() {
    try {
        Datum f_case = "";
        Datum t_case = "";
        bool condition = false;

        if (stack.top().isRString() == false) {
            cerr << "Error: expected rstring in if branch" << endl;
            return;
        } else {
            f_case = stack.top();
            stack.pop();
        }

        if (stack.top().isRString() == false) {
            cerr << "Error: expected rstring in if branch" << endl;
            return;
        } else {
            t_case = stack.top();
            stack.pop();
        }

        if (stack.top().isBool() == false) {
            cerr << "Error: expected boolean in if test" << endl;
            return;
        } else {
            condition = stack.top().getBool();
            stack.pop();
        }

        if (condition == true) {
            stack.push(t_case);
            execQuery();
        } else if (condition == false) {
            stack.push(f_case);
            execQuery();
        }
    } catch (runtime_error &exc) {
        cerr << "Error: " << exc.what() << endl;
    }
}
