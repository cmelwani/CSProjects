// encrypt.cpp
// Purpose: This program encrypts a user-provided word
//          using a 5-shift Caesar cipher.
// Written by: Megan Monroe (mmonroe)

#include <iostream>
#include <string>

using namespace std;

int main()
{

	const int shift_amount = 4;
	string word_to_encrypt;

	// Get the word to encrypt from the user
	cout << "Enter the word that you would like to encrypt (in lowercase characters)";
	cout << endl;
	cout << "Word to encrypt: ";
	cin >> word_to_encrypt;

	int length_of_word = word_to_encrypt.length();
	int curr_letter = 0;

	// Generate the encrypted output
	cout << "Encrypted word: ";

	// Loop through each character of the word
	while( curr_letter < length_of_word )
	{
		char new_letter;
		if( word_to_encrypt[curr_letter] < 'w' )
		{
			new_letter = word_to_encrypt[curr_letter] + shift_amount;
		// Some characters require us to loop back to the start of the alphabet
		}else{
			new_letter = word_to_encrypt[curr_letter] - 26 + shift_amount;
		}

		cout << new_letter;

		// Move to the next character
		curr_letter = curr_letter + 1;
	}

	cout << endl;

	return 0;
}
