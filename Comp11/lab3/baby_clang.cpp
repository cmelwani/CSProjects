#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc < 2){
		cerr << "ERROR: A filename must be specified as the first argument.\n";
		exit(EXIT_FAILURE);
	}

	bool valid_braces = true;

ifstream myFile;
//argv[1] accesses the first argument which is the name of the file
myFile.open(argv[1]);
//check that the file opened
if(myFile.fail()) {
	cout << "Opening the input file failed." << endl;
	exit(EXIT_FAILURE);
}

int count = 0;
int count2 = 0;
char c;

while (myFile.get(c)) {
	if (c == '{') {
		 count++;
	}

	if (c == '}') {
		count2++;
	}

	//can't have more closing braces than opening braces
	if (count2 > count) {
		return 1;
	}
}

if (count == count2) {
valid_braces = true;
} else {
valid_braces = false;

}
//close the file
myFile.close();

	/* DO NOT MODIFY THE CODE ABOVE OR BELOW THIS COMMENT BLOCK */
	/*                  YOUR CODE GOES HERE                     */
	/* DO NOT MODIFY THE CODE ABOVE OR BELOW THIS COMMENT BLOCK */


	if(valid_braces){
		return 0;
	}else{
		return 1;
	}
}
