/* Created by: Anna Wang and Cheryl Melwani */
/* February 5th 2021 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <readaline.h>
#include <seq.h>
#include <table.h>
#include <atom.h>
#include <assert.h>

struct MatchInfo{
        char *fileName;
        int lineNum;
};


char *parseArray(char *line, int num, int *wordLen);
char *findWord(char *line, int i , int *wordLen, char *wordArr, int counter);
void matchLine(const char *atom, Table_T table, struct MatchInfo temp);
void print(Table_T);

/* Name: main() 
   Function: Handles opening the file from command line 
   and calling helper functions */
int main(int argc, char *argv[]) {
    char *line = NULL;
    char *wordArr = NULL;
    int lineCounter;
    int num;
    const char *x;

    Table_T table = Table_new (1000, NULL, NULL);
    struct MatchInfo temp;
    
    //Open command file(s) if given 
    if (argc >= 2) {
        FILE *inputfd;
        for (int i = 1; i< argc; i++) {
            temp.fileName = argv[i];
            inputfd = fopen(temp.fileName, "r");

            assert(inputfd != NULL);
            assert(!ferror(inputfd));
            
            lineCounter = 0;
            /* Go through the file and read every line using readaline.*/
            while (!feof(inputfd)) {
                num = readaline(inputfd, &line);
                if(num == 0) {
                    break;
                }
                lineCounter++;
                temp.lineNum = lineCounter;
                int wordLen = 0;
                /* Change every line read into a series of word chars
                   only and identify unique word groups using atom. */
                wordArr = parseArray(line, num, &wordLen); 
                x = Atom_new(wordArr, wordLen);
                free(wordArr);
                free(line);
                matchLine(x, table, temp);
            }
            fclose(inputfd);
        }
        print(table);
    } 
    Table_free(&table);
    return EXIT_SUCCESS;
}

/* Name: parseArray() 
   Function:  parse through the contiguous array of bytes using 
   readaline's output. Serves as a helper function to pass 
   in parameters to recursive function */
char *parseArray(char *line, int num, int *wordLen) {
    char *wordArr = (char *) malloc(num * sizeof(char));
    assert(wordArr != NULL); 
    int i = 0;
    int counter = 0;
    wordArr = findWord(line, i, wordLen, wordArr, counter);
    return wordArr;
}

/* Name: findWord() 
   Function: Helper function for parseArray, parses for word characters 
   from a given series of characters. */
char *findWord(char *line, int i , int *wordLen, char *wordArr, int counter) {
    if(line[i] == '\n') {
        return wordArr;
    }
    if(line[i] == EOF) {
        return wordArr;
    }
    if( (*(line + i) >= 'a' && *(line + i) <= 'z')  || 
    (*(line + i) >= '0' && *(line + i) <= '9') || 
    (*(line + i) == '_') || (*(line + i) >= 'A' && *(line + i) <= 'Z')) {
        wordArr[*wordLen] = *(line + i);
        i++;
        (*wordLen)++;
        counter = 0;
        findWord(line, i, wordLen, wordArr, counter);
    } 
    else if (counter == 1) {
        findWord(line, i+1, wordLen, wordArr, counter);
    } 
    else {
        wordArr[*wordLen] = ' ';
        (*wordLen)++;
        findWord(line, i+1, wordLen, wordArr, counter +1);
    }
    return wordArr;
}

/* Name: matchLine()
   Function: handles storing key-value pairs into the table structure. 
   The atom word groups are the keys being entered into the table.
   A sequence of matchInfo structs serves as the keys. 
   Populates the table so that it contains match groups that can be 
   accessed to print. */
void matchLine(const char *atom, Table_T table, struct MatchInfo temp) {
    if( Table_get(table, atom) == NULL ){
        struct MatchInfo *test = malloc(sizeof(*test)); 
        assert(test != NULL); 
        test->fileName = temp.fileName;
        test->lineNum = temp.lineNum;

        Seq_T seq = Seq_new(100);
        Seq_addhi(seq, test); 
        Table_put(table, atom, seq);
        
    } else {
        //adding temp struct to the end of the sequence at that key
        struct MatchInfo *test = malloc(sizeof(*test)); 
        assert(test != NULL); 
        test->fileName = temp.fileName;
        test->lineNum = temp.lineNum;
        Seq_addhi((Table_get(table, atom)), test);
    }
}

void print(Table_T table) {
    
    void **array = Table_toArray(table, NULL); 
    /* For every key in the table, check if they have more than 1 
    match. If they do, print word group and all matches. */
    int first = 0;
    for (int i = 0; array[i]; i += 2) {
        int matchNum = Seq_length(array[i+1]); 
        if(matchNum > 1) {
            if(first == 0){
                char *key = array[i];
                printf("%s\n", key); 

                /* Print every corresponding match */
                for(int j = 0; j < matchNum; j++) {
                    struct MatchInfo *test; 
                    test = Seq_get(array[i+1], j);
                    printf( "%-20s %7i\n", test->fileName, test->lineNum);
                }
                first++;
            } else {
                printf("\n");
                char *key = array[i];
                printf("%s\n", key); 
                /* Print every corresponding match */
                for(int j = 0; j < matchNum; j++) {
                    struct MatchInfo *test; 
                    test = Seq_get(array[i+1], j);
                    printf( "%-20s %7i\n", test->fileName, test->lineNum);
                }
            }
        }
        for(int j = 0; j < matchNum; j++) {
            free(Seq_get(array[i+1],j));
        }
        Seq_free((Seq_T*) &array[i+1]);
    }
    free(array);
}