// my_ing.cpp
// Purpose: This program decides whether a user-provided
//          word ends in the suffix "ing"
// Written by: {your name and CS login}

#include <iostream>
#include <string>

using namespace std;

int main()
{
  // Your code goes here
  string user_word;

  cout<< "Greetings! I am the \"ing\" decider!";
  cout<< endl;
  cout<< "Please enter a word: ";
  cin >> user_word;

  int word_length = user_word.length();

  if (user_word[word_length - 1] == 'g') {
    if (user_word[word_length - 2] == 'n') {
      if (user_word[word_length - 3] == 'i') {
        cout<< "Your word ends in \"ing\"! Fantastic!";
        cout<< endl;
      }
    }

  } else {
    cout<< "Oh no! I think you meant " + user_word + "-ing!";
    cout<< endl;
  }
  return 0;
}
// you only use a while loop if you are changing the variable in the coniditional
// statement in your while loop
