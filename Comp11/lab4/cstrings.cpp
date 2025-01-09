#include <iostream>
#include <fstream>
#include <cctype> //Lets us use the isalpha function

using namespace std;

const int SIZE = 50;
int get_line(ifstream &infile, char words[SIZE][SIZE]);
bool is_equal(char *s1, char *s2);
bool is_prefix(char *s1, char *s2);
char *find_substring(char *haystack, char *needle);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "ERROR: A filename must be specified as the first argument.\n";
    exit(EXIT_FAILURE);
  }

  /* Open the file */
  ifstream infile;
  infile.open(argv[1]); 

  /* Error check */
  if (!infile.is_open()) {
    cerr << "ERROR: Error opening file - ";
    cerr << "please check that you specified the correct file name\n";
    exit(EXIT_FAILURE);
  }

  int total_words;
  char words[SIZE][SIZE];
  while (!infile.eof()) {
    total_words = get_line(infile, words);




    /* DO NOT MODIFY THE CODE IN main() ABOVE OR BELOW THIS COMMENT BLOCK */
    /* YOUR CODE GOES HERE */
    /* DO NOT MODIFY THE CODE IN main() ABOVE OR BELOW THIS COMMENT BLOCK */





    total_words = 0;
  }

  infile.close();
}

/* Return true if the C-style strings s1 and s2 are equivalent, false otherwise. */
bool is_equal(char *s1, char *s2) {
  /* YOUR CODE GOES HERE. DELETE THE RETURN STATEMENT BELOW WHEN YOU'RE WORKING
   * ON THIS FUNCTION. */
  return false;
}

/* Return true if the C-style string s2 is a prefix of the C-style
 * string s1, false otherwise.*/
bool is_prefix(char *s1, char *s2) {
  /* YOUR CODE GOES HERE. DELETE THE RETURN STATEMENT BELOW WHEN YOU'RE WORKING
   * ON THIS FUNCTION. */
  return false;
}


/* Find the first occurrence of a string (the second parameter 'needle')
 * within another string (the first parameter 'haystack').
 * Return a pointer to the beginning of the substring in 'haystack',
 * or nullptr if 'needle' isn't found or if 'needle' and 'haystack'
 * represent the same string. */
char *find_substring(char *haystack, char *needle) {
  /* YOUR CODE GOES HERE. DELETE THE RETURN STATEMENT BELOW WHEN YOU'RE WORKING
   * ON THIS FUNCTION. */
  return nullptr;
}

/* Retrieve a line of input from a file, parse it into individual words, and
 * store those words in the "words_in_sentence" 2D-array. Each "row" of
 * words_in_sentence is another word. Return the total number of words read in.
 *
 * NOTE: We have to write "ifstream &infile" as a parameter to pass an input
 * file stream correctly. If you need to write a function that takes a file
 * stream as an argument, always put the '&' in front of the name of your
 * file stream.
 */
int get_line(ifstream &infile, char words_in_sentence[SIZE][SIZE]) {
  int spot = 0;
  int word_index = 0;
  char *next_word;

  int next_char = infile.get();
  while (!infile.eof() && next_char != '\n') {
    next_word = words_in_sentence[word_index];
    while (isalpha(next_char)) {
      next_word[spot] = next_char;
      ++spot;
      next_char = infile.get();  
    }
    if (spot > 0) {
      next_word[spot] = '\0';
      ++word_index;
      spot = 0;
    } else {
      next_char = infile.get();
    }
  }
  return word_index;
}
