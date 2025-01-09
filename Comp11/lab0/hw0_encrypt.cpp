// encrypt.cpp
// Purpose: This program encrypts a user-provided word
//          using a 5-shift Caesar cipher.
// Written by: Megan Monroe (mmonroe)

#include <iostream>
#include <string>

using namespace std;

int main()
{

	string word_to_encrypt;
	int shift_amount;

	// Get the word to encrypt from the user
	cout << "Welcome! This is a program that runs a Caesar Cipher :)";
	cout << endl;
	cout << "Please ensure that you enter the word you intend to incrypt (in lower case letters !!)";
	cout << endl;
	cout << "Enter word to encrypt: ";
	cin >> word_to_encrypt;
	cout << "Please enter your desired shift amount: ";
	cin >> shift_amount;

	int length_of_word = word_to_encrypt.length();
	int curr_letter = 0;

	// Generate the encrypted output
	cout << "Here is the encrypted word! ";

// takes into account numbers greater than 26
if (shift_amount > 26) {
	shift_amount = shift_amount % 26;
}
	// takes into account the negative
if (shift_amount < 0) {
	shift_amount = 26 + shift_amount;
}

	// Loop through each character of the word
while( curr_letter < length_of_word ) {
		char new_letter;
 	 if( word_to_encrypt[curr_letter] < 123 - shift_amount ) // if not true you loop around the alphabet
		{
		new_letter = word_to_encrypt[curr_letter] + shift_amount;
	 //Some characters require us to loop back to the start of the alphabet
	}else{
		new_letter = word_to_encrypt[curr_letter] - 26 + shift_amount;
	 }

	 cout << new_letter;

	// Move to the next character
		curr_letter += 1;
	}

	cout << endl;

	return 0;
}

// EXPLANATION OF WHY (< 123 - shift_amount) OR (<= 122 - shift_amount)
// the shift amount has to be 123 because you have to subtract the shift amount by a number one more than z, z = 122
// if you just put in '< 122' then the entirety of the letter z gets skipped and you end up with an incorrect answer
// it becomes exclusive with just '< 122'
