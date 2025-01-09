/*
 * snowcrash.cpp
 * Purpose: HW2
 * Submitted by: cheryl melwani -- cmelwa01
 // date: Sep 24 2019
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

const int SIZE = 10;

/* Function declarations must come before they are called */
void read_letter(string filename, int letter[SIZE][SIZE]);
void write_letter(string filename, int letter[SIZE][SIZE]);
void unscramble_ph4(int letter[SIZE][SIZE]);
void unscramble_ph3(int letter[SIZE][SIZE]);
void unscramble_ph2(int letter[SIZE][SIZE]);
void unscramble_ph1(int letter[SIZE][SIZE]);

/*
 * The main function takes three arguments:
 * 1.) The phase to unscramble down to
 * 2.) The input file to read the letter from
 * 3.) The name of the output file to write the unscrambled letter to
 */
int main(int argc, char *argv[])
{
	if(argc < 4)
	{
		cerr << "ERROR: Not enough arguments specified\n";
		exit(EXIT_FAILURE);
	}

	/* 2D array that will store the letter bitmap */
	int letter[SIZE][SIZE];
	int phase = (int)(argv[1][0]  - '0');

	/* Read the letter file into a 2D array */
	read_letter(argv[2], letter);

	/* Unscramble the letter */
	unscramble_ph4(letter);
	if(phase <= 3) unscramble_ph3(letter);
	if(phase <= 2) unscramble_ph2(letter);
	if(phase <= 1) unscramble_ph1(letter);

	/* Write the unscrambled letter to file */
	write_letter(argv[3], letter);

	return 0;
}

/* - - - - - - - - - - - - - - - - - - - - - */
/* - - - - - YOUR CODE GOES BELOW  - - - - - */
/* - - - - - - - - - - - - - - - - - - - - - */

void unscramble_ph4(int letter[SIZE][SIZE])
{
	cout << "Unscrambling Phase 4\n";
int start = letter[3][5];
letter[3][5] = letter[4][7];
letter[4][7] = letter[6][5];
letter[6][5] = letter[4][2];
letter[4][2] = start;

start = letter[6][7];
letter[6][7] = letter[6][2];
letter[6][2] = letter[3][5];
letter[3][5] = start;

start = letter[4][4];
letter[4][4] = letter[4][5];
letter[4][5] = start;
}

void unscramble_ph3(int letter[SIZE][SIZE])
{
	cout << "Unscrambling Phase 3\n";

	int temp[SIZE][SIZE];

// this part reverses phase 3 and moves the column back to the row.
	for(int i = 0; i < SIZE; i++)
	{
			for(int j = 0; j < SIZE; j++)
		{
		 temp[i][j] = letter[SIZE - j - 1][i];
			}
		}
//assigns temp array into letter array
		for(int i = 0; i < SIZE; i++)
		{
			for(int j = 0; j < SIZE; j++)
			{
				 letter[i][j] = temp[i][j];
			}
		}
}

void unscramble_ph2(int letter[SIZE][SIZE])
{
	cout << "Unscrambling Phase 2\n";

	int temp[SIZE/2][SIZE/2];

//assign letter array into temp array
	for(int i = 0; i < SIZE/2; i++)
	{
		for(int j = 0; j < SIZE/2; j++)
		{
			temp[i][j] = letter[i][j];
		}
	}
//split the grid into 4 quadrants and worked backwards.
// puts the fourth quadrant into a temp 5 by 5 array.
	for(int i = SIZE/2; i < SIZE; i++)
	{
		for(int j = SIZE/2; j < SIZE; j++)
		{
	letter[i - (SIZE/2)][j - (SIZE/2)] = letter[i][j];
		}
	}
//I then reversed the next step in phase 3, moving quadrant 3 back to
// quadrant 4.
	for(int i = SIZE/2; i < SIZE; i++)
	{
		for(int j = SIZE/2; j < SIZE; j++)
		{
			letter[i][j] = letter[i][j - (SIZE/2)];
		}
	}

//The last step in my code is to put quadrant 1 back to 2 and store that
// in temp array.
	for(int i = SIZE/2; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE/2; j++)
		{
			letter[i][j] = temp[i - (SIZE/2)][j];
		}
	}

}

void unscramble_ph1(int letter[SIZE][SIZE])
{
	cout << "Unscrambling Phase 1\n";

}


/* - - - - - - - - - - - - - - - - - - - - - */
/* - - - - - YOUR CODE GOES ABOVE  - - - - - */
/* - - - - - - - - - - - - - - - - - - - - - */

/*
 * Reads a letter from the specified file into a 2D array of ints
 * Input: the file name and the 2D array to write into
 */
void read_letter(string filename, int letter[SIZE][SIZE])
{
	/* Declare a variable to read in from the file */
    ifstream infile;
    infile.open(filename.c_str()); /* C-style string required */

    /* Error check */
    if (!infile.is_open())
    {
        cerr << "ERROR: Error opening file - ";
        cerr << "please check that you specified the correct file name\n";
        exit(EXIT_FAILURE);
    }

    char next_char;
    int count = 0;

    /* Read characters until we have the full 10x10 letter */
 	while(count < 100)
 	{
 		/*
 		 * If we hit the end of the file before we have the full letter,
 		 * we have a problem
 		 */
		if(infile.eof())
		{
			cerr << "ERROR: Letter file is not properly formatted.\n";
			exit(EXIT_FAILURE);
		}

		/* Get the next character from the file */
		infile.get(next_char);

		if((next_char == '0') || (next_char == '1'))
		{
			/* Convert the char to an int and store it in out letter array */
			letter[count / SIZE][count % SIZE] = (int)(next_char - '0');
			count++;
		}
 	}

    /* Close the file we're reading */
    infile.close();
}

/*
 * Writes a letter from a 2D array of ints into the specified file
 * Input: the file name and the 2D array to read from
 */
void write_letter(string filename, int letter[SIZE][SIZE])
{
	/* Declare a file variable to write to */
	ofstream outfile;
    outfile.open(filename.c_str()); // C-style string required

    /* Loop through our letter array and write out each digit */
	for(int i = 0; i < SIZE; i++)
 	{
 		for(int j = 0; j < SIZE; j++)
 		{
 			outfile << letter[i][j];
 		}
 		outfile << endl;
 	}

 	/* Close the file we're writing to */
 	outfile.close();
}
