// hw1_encrypt.cpp
// Purpose: This program decrypts a user-provided word
//          using a Caesar cipher.
// Written by: Cheryl Melwani (cmelwa01)
// Date : 17 September, 2019

#include <iostream>
#include <string>

using namespace std;

int main()
{

	string word_to_decrypt;
	int shift_amount;

	cout << "Enter the word that you would like to decrypt (in lowercase characters)";
	cout << endl;
	cout << "Word to decrypt: ";
	cin >> word_to_decrypt;
	cout << "Enter the shift amount: ";
	cin >> shift_amount;

	int length_of_word = word_to_decrypt.length();
	int curr_letter = 0;

	cout << "Decrypted word: ";

while( curr_letter < length_of_word ) {
		char new_letter;
 	 if( word_to_decrypt[curr_letter] > 96 + shift_amount )
		{
		new_letter = word_to_decrypt[curr_letter] - shift_amount;
	}else{
		new_letter = word_to_decrypt[curr_letter] + 26 - shift_amount;
	 }

	 cout << new_letter;

		curr_letter += 1;
	}

	cout << endl;

	return 0;
}
