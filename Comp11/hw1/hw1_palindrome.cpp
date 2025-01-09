// hw1_palindrome.cpp
// Purpose: This program prompts the user for a word and
// checks whether or not it is a true palindrome.
// Written by: Cheryl Melwani (cmelwa01)
// Date : 17 September, 2019

#include <iostream>
#include <string>

using namespace std;

int main() {

string user_word;

cout << "Greetings! I am the palindrome decider!" << endl;

bool decider = true;

while (decider) {

cout << "Please enter a word: ";
cin >> user_word;

int length_of_word = user_word.length();

//creating string variables to split user_word into 2 parts
string part1 = user_word.substr(0, length_of_word / 2);
string part2;

//if the length is odd vs. if its even
if(length_of_word % 2 == 1) {
  part2 = user_word.substr(length_of_word / 2 + 1);
} else {
  part2 = user_word.substr(length_of_word / 2);
}
//changing the order of chars in part2 by adding it to an empty string
//to compare to part1 properly
string empty_word = "";
for (int i = part2.length() - 1; i >= 0; i--) {
  empty_word += part2[i];
}

//manipulating output depending on if its a palindrome or not
if (part1 == empty_word && user_word.length() != 1) {
  cout << "Your word is a palindrome! Fantastic!" << endl;
  decider = true;
}
else if (part1[0] == empty_word[0] && part1[1] == empty_word[1] &&
  part1[2] == empty_word[2] && part1 != empty_word) {
    cout << "Not quite a palindrome, but close enough." << endl;
    decider = true;
} else {
  cout << "Your word is NOT a palindrome. Thanks anyway!" << endl;
 decider = false;
}

}
return 0;
}
