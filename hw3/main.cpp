/* Cheryl Melwani (cmelwa01)
 * Feb 12, 2020
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "MetroSim.h"

using namespace std;

/* Purpose: main creates an instance of metrosim and calls respective
functions depending on whether the user inputs a test_command file or not.
Return: an integer
Parameters: int argc - the number of inputs in the command line arguements
after your executable. argv[] holds the names of those files. 
 */
int main(int argc, char *argv[]) {
	MetroSim ms;
	if(argc < 2){
        cerr << "ERROR: Not enough commands given " << endl;
        exit(EXIT_FAILURE);
    }
	if(argc == 3) {
		ms.openFile(argv[1]);
		ofstream output_file;
		output_file.open(argv[2]);
		ms.readCinFile(output_file);
		output_file.close();
	}
	else if(argc == 4) {
		ms.openFile(argv[1]);
		ofstream output_file;
		output_file.open(argv[2]);
		ms.readInputFile(argv[3], output_file);
		output_file.close();
	}
	return 0;
}
