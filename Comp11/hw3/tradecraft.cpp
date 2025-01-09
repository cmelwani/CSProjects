// tradecraft.cpp
// Purpose: the code finds the shift_amount of an encrypted input text without
// knowledge of what the decrypted text is.
// Created by Cheryl Melwani (cmelwa01)
// Date: Oct 1, 2019

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char findFreqLetter(string filename);
int findShiftAmount(char freq_letter);

/* function contract:
arguments: int argc, char *argv[]
description: this function checks if there is an error opening the input file
and it outputs the shift amount to the user
return value: an integer
*/

int main(int argc, char *argv[]) {
	if(argc < 2){
		cerr << "ERROR: A filename must be specified as the first argument.\n";
		exit(EXIT_FAILURE);
	}

	string filename = argv[1];
	char freq_letter = findFreqLetter(filename);

	cout << "The shift amount is: " << findShiftAmount(freq_letter) << endl;

	return 0;
}

char findFreqLetter (string filename) {

	ifstream myFile;
 	myFile.open(filename);

	if(myFile.fail()) {
	 cout << "Opening the input file failed." << endl;
	 exit(EXIT_FAILURE);
 }

/* finding the length of the text inside the input file */
char c;
char arr[5000];
int file_length = 0;

 while (myFile.get(c)) {
	 arr[file_length] = c;
	 file_length++;
 }

/* function contract:
arguements: string filename
expectation about arguement: it has to be the string that contains the name
of the input file that the code is working on.
description: this function finds the most frequent letter.
return value: a character (the most frequent letter)
expectation about the return value: the character being returned should
represent the most frequent letter within the input text.
*/

	int temp_max_count = 0;
	int count = 0;
	char freq_letter;
	for (char x = 'A'; x <= 'z'; x++)
	{
		for (int i = 0; i < file_length; i++)
		{
			if(arr[i] == x)
			{
				count++;
			}
			if(count > temp_max_count)
			{
				temp_max_count = count;
				freq_letter = x;
			}
		}
		count = 0;
	}

	myFile.close();
 return freq_letter;

}

/* function contract:
argument: character called freq_letter
expectation about argument: the argument is the return value of the function
above.
description: this function finds the shift amount.
return value: integer (the shift amount)
expecation about the return value:
*/

int findShiftAmount (char freq_letter) {

	int shift_amount = 0;
	shift_amount = freq_letter - 'e';
	return shift_amount;

}
