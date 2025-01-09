/*
 *      main.cpp
 *      PartyPlaylist
 *      Comp 15 Lab 3
 *
 *      Simple test program that tests the code for the lab.  The
 *      testing is not as thorough as one might like, but it's a
 *      start.  You should extend the CircularBuffer tests at
 *      least.  What cases are important to test?
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Updated by Mark A. Sheldon, Tufts University
 *                 Documenation, factored testing into separate
 *                 functions.
 *      2019-08-01 Modified by Alice Dempsey
 *      2020-01-31 Modified by Juliana vega
 *                 Removed "sequence" wording
 *
 */

#include <iostream>

#include "CircularBuffer.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

void testCircularBuffer(string songs[], int numSongs);
void testStack(string songs[], int numSongs);
void testQueue(string songs[], int numSongs);

int main()
{
        string songs[10] = {"1: I Don't Care", "2: Bad Guy", "3: Talk",
                            "4: If I Can't Have You", "5: Sucker",
                            "6: Hey Look, Ma, I Made It", "7: Truth Hurts",
                            "8: Senorita", "9: You Need To Calm Down",
                            "10: Dancing with a Stranger"};

        const int numSongs = sizeof(songs) / sizeof(string);

        testCircularBuffer(songs, numSongs);

        // Uncomment each test as you write each part
        //testStack(songs, numSongs);
        //testQueue(songs, numSongs);

        cout << "\n\t\t**** Wrap-Up Questions ****\n"
             << "In your opinion, which data structure is better for a DJ"
             << " table? \nWhich one is better for a Top 10 Countdown on the"
             << " radio?\n\n";
        cout << "How do stacks and queues interact with each other?\n"
             << "What happens when you dequeue into a stack and then"
             << " pop everything off?\n\n";

        return 0;
}

/**********************************************************************
 *******************  TEST ONE: Testing Buffer  **********************
 ***********************************************************************/

//
// TODO: Write more tests for testing the Buffer.
//       You can use the songs array for your tests.
//
void testCircularBuffer(string songs[], int numSongs)
{
        cout << "Testing CircularBuffer: \n";

        CircularBuffer myBuffer(1);

        myBuffer.addAtBack("Hello");
        myBuffer.addAtBack("World");
        myBuffer.addAtFront("Heyo");

        cout << "Printing CircularBuffer:\n";
        myBuffer.printBuffer();
}

/**********************************************************************
 **********************  TEST TWO: Testing Stack  **********************
 ***********************************************************************/

void testStack(string songs[], int numSongs)
{
        cout << "\nTesting Stack: \n";

        Stack myStack;
        myStack.printStack();     // Should print an empty stack

        // add all songs to the stack
        for (int i = 0; i < numSongs; i++) {
                cout << "Adding " << songs[i] << " to playlist.\n";
                myStack.push(songs[i]);
        }
        cout << "On August 1, the top ten pop songs were: \n";

        myStack.printStack();     // Be sure all songs are there

        cout << "But we're missing the best song!\n";

        myStack.push("Old Town Road");
        cout << "Playing " << myStack.pop() << endl;

        cout << "Love that song. Let's request it again.\n";

        myStack.push("Old Town Road");
        cout << "Playing " << myStack.pop() << endl;

        myStack.push("Old Town Road");
        cout << "Playing " << myStack.pop() << endl;

        myStack.push("Old Town Road");
        cout << "Playing " << myStack.pop() << endl;

        cout << "Now, the top ten should still be there: \n";
        myStack.printStack();

        cout << "Nice work! Try recreating this test for the queue.\n"
            << "What's different? What would be a better test for a queue?\n";
}

/**********************************************************************
 ********************  TEST THREE: Testing Queue  **********************
 ***********************************************************************/
//
// TODO: Write more tests for testing the queue.
//       Think about how a queue keeps track of the next song and how you can
//       test that through enqueue and dequeue
//
void testQueue(string songs[], int numSongs)
{
        cout << "\nTesting Queue: \n";

        Queue myQueue;
        myQueue.printQueue();     // Should print empty queue

}
