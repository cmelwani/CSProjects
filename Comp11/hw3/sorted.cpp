// sorted.cpp
// Purpose: read a list of numbers from a file and output them in order
// of highest to lowest (only positive numbers).
// Created by Cheryl Melwani (cmelwa01)
// Date: Oct 1, 2019

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {

	if(argc < 2) {
		cerr << "ERROR: A filename must be specified as the first argument.\n";
		exit(EXIT_FAILURE);
	}

	ifstream myFile;
//argv[1] accesses the first argument which is the name of the file
	myFile.open(argv[1]);

//check that the file opened
	if(myFile.fail()) {
		cout << "Opening the input file failed." << endl;
		exit(EXIT_FAILURE);
	}

	int number;
	int arr[26];
	int count = 0;

/* all the numbers in the input file is being put into an array called unsorted.
a counter is also being created that represents how many integers are in the
input file.
*/
	while (myFile >> number) {
		arr[count] = number;
		count++;
	}

	myFile.close();

/* sort the array in descending order.
the first for loop starts on index 0 and the second for loop starts on index 1.
if j > i then switch the two values where i = j and j = i, to sort the array
in proper descending order and so the highest number comes first. the nested
for loops compare the two numbers next to each other throughout the array and
switches the order to put the highest number between the two, first.
*/

	int temp = 0;
	for(int i = 0; i < 26; i++) {
		for(int j = i + 1; j < 26; j++)	{
			if(arr[i] < arr[j]) {
				  temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
			}
		}
	}

//printing the sorted array
	cout << "Here is the sorted array: ";
  for(int i = 0; i < count; i++) {
    cout << "\n" << arr[i] << "\n";
    //n stands for new line
  }

}
