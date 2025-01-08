/*
 * FunkeyTable.cpp --- compare two different methods of handling hash
 * table collisions and two different hash functions.
 *
 * your job:  code the insert functions and expand function
 *  our job:  run the insert functions and report results
 *
 * Based on a previous lab by Ben Hescott, I think.
 *
 * Mark A. Sheldon, Tufts University, Spring 2017
 */

#include <iostream>
#include <stdio.h>
#include <functional>

#include "FunkeyTable.h"

using namespace std;

/*
 * Constructor allocates and initializes two empty tables
 * of the INITIAL_TABLE_SIZE
 */
FunkeyTable::FunkeyTable()
{
        currentTableSize = INITIAL_TABLE_SIZE;
        numItemsInTable  = 0;

        chainedTable     = new ChainNode *[currentTableSize];
        linearTable      = new TableEntry[currentTableSize];

        for (int i = 0; i < currentTableSize; i++) {
                chainedTable[i]        = nullptr;
                linearTable[i].isEmpty = true;
        }
}

/*
 * Delete all nodes in list starting with given node
 */
void FunkeyTable::deleteList(ChainNode *node)
{
    ChainNode *temp = node;
    while(node != nullptr) {
        temp = node->next;
        delete node;
        node = temp;
    }
}

/*
 * destructor
 */
FunkeyTable::~FunkeyTable()
{
    for(int i = 0; i < currentTableSize; i++) {
        linearTable[i].key = nullptr;
        linearTable[i].value.chartPosition = 0;
        linearTable[i].value.bpm = 0;
        deleteList(chainedTable[i]);
        chainedTable[i] = nullptr;
    }

    delete [] linearTable;
    delete [] chainedTable;
        // TODO: Students write code here
}


static size_t good_hash_function(KeyType key)
{
        return std::hash<KeyType>{}(key);
}

static size_t bad_hash_function(KeyType key)
{
        return key.length();
}

static size_t hashValue(KeyType key, FunkeyTable::HashFunction hashFunction)
{
        if (hashFunction == FunkeyTable::BAD_HASH_FUNCTION)
                return bad_hash_function(key);
        else
                return good_hash_function(key);
}

/*
 * Linear Probing
 *
 * Return number of collisions before finding a spot
 *
 */
int FunkeyTable::insertProbing(KeyType key, ValueType value,
                               HashFunction hashFunction)
{
        int    attempt = 0;
        bool   found   = false;

        // NOTE:  You can put things here if it helps you
        int hash_index = hashValue(key, hashFunction);

        while (not found) {
            hash_index++;
            hash_index %= currentTableSize;
            attempt++;
        }

        if(linearTable[hash_index].isEmpty == true) {
            numItemsInTable++;
            linearTable[hash_index].key = key;
            linearTable[hash_index].value = value;
            linearTable[hash_index].isEmpty = false;
        }

        return attempt;
}

/*
 * Return length of list starting at given node
 */
int FunkeyTable::listLength(ChainNode *nodep)
{
    int length = 0;
    ChainNode *curr_node = nodep;
    while(curr_node != nullptr) {
        curr_node = curr_node->next;
        length++;
    }
    return length;
}

/*
 * Chained hashing --- each spot in table is a linked list
 *
 * Return number of items in that spot before insertion
 */
int FunkeyTable::insertChaining(KeyType key, ValueType value,
                                HashFunction hashFunction)
{
        int hash_index = hashValue(key, hashFunction);
        int num_items = listLength(chainedTable[hash_index]);
        chainedTable[hash_index]->key = key;
        chainedTable[hash_index]->value = value;
        chainedTable[hash_index]->next = nullptr;
        return num_items;
}




/*
 * Expand both of the hash tables
 */
void FunkeyTable::expand(HashFunction hashFunction)
{
        // TODO: Students write code here
}

void FunkeyTable::printTableEntry(TableEntry entry)
{
        if (entry.isEmpty)
                cout << "empty";
        else
                cout << "key:  "
                     << entry.key
                     << "; value:  {"
                     << entry.value.chartPosition
                     << ", "
                     << entry.value.bpm
                     << "}";
}

void FunkeyTable::printChainNode(ChainNode *nodep)
{
        cout << "key:  " << nodep->key
             << "; value:  {" << nodep->value.chartPosition
             << ", " << nodep->value.bpm << "}";
}

/*
 * Print both hash tables
 * Could break this up into two print functions
 */
void FunkeyTable::print()
{
        cout << "Linear table" << endl;

        for (int i = 0; i < currentTableSize; ++i) {
                cout << i << ":  ";
                printTableEntry(linearTable[i]);
                cout << endl;
        }
        cout << endl << "Chained table" << endl;

        for (int i = 0; i < currentTableSize; ++i) {
                ChainNode *curr = chainedTable[i];
                cout << i << ":  [ ";
                while (curr != NULL) {
                        printChainNode(curr);
                        curr = curr->next;
                        if (curr != NULL)
                                cout << ", ";
                }
                cout << "]" << endl;
        }
        cout << endl;
}
