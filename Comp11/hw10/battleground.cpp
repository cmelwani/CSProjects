/*
NAME: Cheryl Melwani / cmelwa01
Date: 20th November, 2019
Purpose: To code the collision part of the battle, determine who wins/loses,
and delete the necessary warrior.
 * battleground.cpp
 * COMP11 AVP
 */

#include "battleground.h"

using namespace std;

//BattleGround contstructor
BattleGround::BattleGround(){
    MAX_ASPEED = 1.5;
    MAX_PSPEED = 1.0;
    pred_head = nullptr;
    alien_head = nullptr;
    carn_head = nullptr;
    num_predators = 0;
    num_aliens = 0;
    num_carnage = 0;
    clearGrounds();
    screenDimensions();
}

//run the battle simulation
void BattleGround::simulate(bool stepwise){
    char refresh = ' ';
    rel_predators = 1;
    rel_aliens = 1;
    int num_steps = 0;

    screen_bg("black");
    screen_fg("white");
    hide_cursor();

    while(refresh != 'q' && refresh != 'w'){
        //reset the screen
        clearGrounds();
        screen_clear();
        screen_home();

        /*------------------THE FUNCTION YOU WRITE!-------------------*/
        engageBattles();
        /*------------------THE FUNCTION YOU WRITE!-------------------*/

        //draw warriors and battleground
        drawWarriors();
        drawGrounds();

        //check to see if the battle has been won
        if(num_aliens == 0){
            battleOver(false);
            break;
        }else if(num_predators == 0){
            battleOver(true);
            break;
        }

        //either continue the simulation or wait for a keystroke
        if(stepwise){
            refresh = getachar();
        }else{
            usleep(SLEEP);
            refresh = getacharnow(1);
        }

        //prep for the next cycle
        moveWarriors();
        num_steps++;

        //determine whether the next alien/predator should be released
        if(num_steps % alien_head->getRelease() == 0){
            rel_aliens++;
        }
        if(num_steps % pred_head->getRelease() == 0){
            rel_predators++;
        }
    }

    //write the battleground out to a file
    if(refresh == 'w'){
        outputGrounds(num_steps);
    }

    show_cursor();
    screen_bg("white");
    screen_fg("black");
}

/*------------------THE FUNCTION YOU WRITE!-------------------*/
//detects and handles collisions between aliens and predators
void BattleGround::engageBattles(){
  Alien *curr_a = alien_head;
  Predator *curr_p = pred_head;
  int count_predator = 0;
  Carnage *new_carnage = new Carnage();

  /*while both the current predator and alien are not nullptr's and the
  predator/alien count is less than the predator/alien amount on the screen */
  while(curr_p != nullptr && count_predator < rel_predators) {
    int count_alien = 0;
    while(curr_a != nullptr && count_alien < rel_aliens) {
    /* if the if-statement is true, then the two rectangles collide */
      if ((curr_p->getVPos() < (curr_a->getVPos()) + curr_a->getHeight()) &&
      ((curr_p->getVPos() + curr_p->getHeight()) > curr_a->getVPos()) &&
      (curr_p->getHPos() < (curr_a->getHPos() + curr_a->getWidth())) &&
      ((curr_p->getHPos() + curr_p->getWidth()) > curr_a->getHPos())) {
        /* the if and else statements determine whether the alien or
        predator has won -- by determining their strenghts */
        if (curr_a->getStrength() > curr_p->getStrength()) {
          /* weaken the winner */
          curr_a->weaken();
          /*set the carnage to the position of the warrior that has lost
          and then add the carnage. Set the carnage to nullptr so I can
          delete it later */
          new_carnage->setPos(curr_p->getVPos(), curr_p->getHPos());
          addCarnage(new_carnage);
          new_carnage = nullptr;
          /* call the helper function that deletes the warrior inside the
          link list */
          deletePredator(curr_p);
          /* reduces the number of predators and the number of Predators
          on the screen */
          num_predators--;
          rel_predators--;
        } else {
          /* same thing with the other warrior now */
          curr_p->weaken();
          new_carnage->setPos(curr_a->getVPos(), curr_a->getHPos());
          addCarnage(new_carnage);
          new_carnage = nullptr;
          deleteAlien(curr_a);
          num_aliens--;
          rel_aliens--;
        }
      }
      /*sets the curr_a to the next alien to iterate through all the aliens
      on the screen */
      curr_a = curr_a->getNext();
      count_alien++;
    }
    /*sets curr_a back to the alien head */
    curr_a = alien_head;
    count_alien = 1;
    /*sets the curr_p to the next predator to iterate through all the
    predators on the screen */
    curr_p = curr_p->getNext();
    count_predator++;
  }
  /* deletes data to account for valgrind */
  delete new_carnage;
}

/* Helper function that returns the pointer to the previous Alien of curr_a
so that I can delete the alien (if necessary) without loosing the rest of the
link list */
Alien *BattleGround::previousAlien(Alien *curr_a) {
  Alien *previous = alien_head;
  /*if alien that lost is the first alien in the linked list */
  if(curr_a == alien_head) {
    return nullptr;
  }
  /* else find the previous alien before curr_a */
  for(int i = 0; i < rel_aliens; i++) {
    if(previous->getNext() == curr_a) {
      return previous;
    }
  }
  return nullptr;
}

/* The same helper function as the one above except for the predator */
Predator* BattleGround::previousPredator(Predator *curr_p) {
  Predator *previous = pred_head;
  if(curr_p == pred_head) {
    return nullptr;
  }
  for(int i = 0; i < rel_predators; i++) {
    if(previous->getNext() == curr_p) {
      return previous;
    }
  }
  return nullptr;
}

/* The helper function that deletes the Alien from the linked list. Calls the
previousAlien function. */
void BattleGround::deleteAlien(Alien *curr_a) {
  Alien *temp = previousAlien(curr_a);
  /* If the alien is the only one on the linked list */
  if(temp == nullptr) {
    if(curr_a->getNext() == nullptr) {
      alien_head = nullptr;
      curr_a->setNext(nullptr);
    }
    /* If the alien is the alien_head on the linked list */
    alien_head = curr_a->getNext();
    curr_a->setNext(nullptr);
    } else {
    /* If the alien is a random alien within the linked list */
    temp->setNext(curr_a->getNext());
    curr_a->setNext(nullptr);
    }
    /* delete the necessary alien */
  delete curr_a;
}

/* The helper function that deletes the Predator from the linked list. Calls the
previousPredator function. Same exact methadology as the function above */
void BattleGround::deletePredator(Predator *curr_p) {
  Predator *temp = previousPredator(curr_p);
  if(temp == nullptr) {
    if(curr_p->getNext() == nullptr) {
      pred_head = nullptr;
      curr_p->setNext(nullptr);
    }
    pred_head = curr_p->getNext();
    curr_p->setNext(nullptr);
  } else {
    temp->setNext(curr_p->getNext());
    curr_p->setNext(nullptr);
  }
  delete curr_p;
}

//adds carnage to the linked list of carnage
void BattleGround::addCarnage(Carnage *c){
    if(carn_head == nullptr){
        carn_head = c;
    }else{
        Carnage *curr_c = carn_head;

        while(curr_c->getNext() != nullptr){
            curr_c = curr_c->getNext();
        }
        curr_c->setNext(c);
    }

    num_carnage++;
}

//(for testing only) write the BattleGround out to a file
void BattleGround::outputGrounds(int num_steps){
    string filename = to_string(num_steps) + "-steps.out";

    ofstream outfile(filename.c_str());
    outfile << "Aliens: " << num_aliens << endl;
    outfile << "Predators: " << num_predators << endl;

    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            outfile << grounds[r][c];
        }
        outfile << endl;
    }
    outfile << endl;
    outfile.close();
}

/*--------------------------------------------------------------------*/
/*  Functions that handle all of the battleground drawing mechanics   */
/*                (you will not need to directly use)                 */
/*--------------------------------------------------------------------*/

//clears the grounds image to be blank
void BattleGround::clearGrounds(){
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            grounds[r][c] = ' ';
            colors[r][c] = ' ';
        }
    }
}

//couts the BattleGround image
void BattleGround::drawGrounds(){
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {

            if(colors[r][c] == 'g'){
                screen_fg("green");
            }else if(colors[r][c] == 'r'){
                screen_fg("red");
            }else if(colors[r][c] == 'b'){
                screen_fg("blue");
            }else{
                screen_fg("white");
            }

            cout << grounds[r][c];
        }
        cout << endl;
    }
    cout << endl;
}

//calls the draw function for each alien, predator, and carnage
void BattleGround::drawWarriors(){
    //draw the predators
    Predator *curr_p = pred_head;
    int pred_count = 0;

    while(curr_p != nullptr && pred_count < rel_predators){
        curr_p->draw(this);
        curr_p = curr_p->getNext();
        pred_count++;
    }

    //draw the aliens
    Alien *curr_a = alien_head;
    int alien_count = 0;

    while(curr_a != nullptr && alien_count < rel_aliens){
        curr_a->draw(this);
        curr_a = curr_a->getNext();
        alien_count++;
    }

    //draw the carnage
    Carnage *curr_c = carn_head;

    while(curr_c != nullptr){
        curr_c->draw(this);
        curr_c = curr_c->getNext();
    }
}

//calls the move function for each alien, predator, and carnage
void BattleGround::moveWarriors(){
    //move the predators
    Predator *curr_p = pred_head;
    int pred_count = 0;

    while(curr_p != nullptr && pred_count < rel_predators){
        curr_p->move(HEIGHT, WIDTH);
        curr_p = curr_p->getNext();
        pred_count++;
    }

    //move the aliens
    Alien *curr_a = alien_head;
    int alien_count = 0;

    while(curr_a != nullptr && alien_count < rel_aliens){
        curr_a->move(HEIGHT, WIDTH);
        curr_a = curr_a->getNext();
        alien_count++;
    }

    //move the carnage
    Carnage *curr_c = carn_head;

    while(curr_c != nullptr){
        curr_c->move(HEIGHT, WIDTH);
        curr_c = curr_c->getNext();
    }
}

//if this function needs explaining, I'm worried
void BattleGround::battleOver(bool aliens_won){
    cout << endl << endl;
    if(aliens_won){
        cout << "   _____  .__  .__                        __      __.__      ._.\n";
        cout << "  /  _  \\ |  | |__| ____   ____   ______ /  \\    /  \\__| ____| |\n";
        cout << " /  /_\\  \\|  | |  |/ __ \\ /    \\ /  ___/ \\   \\/\\/   /  |/    \\ |\n";
        cout << "/    |    \\  |_|  \\  ___/|   |  \\___ \\    \\        /|  |   |  \\|\n";
        cout << "\\____|__  /____/__|\\___  >___|  /____  >   \\__/\\  / |__|___|  /_\n";
        cout << "        \\/             \\/     \\/     \\/         \\/          \\/\\/\n";
    }else{
        cout << "__________                    .___       __                         __      __.__      ._.\n";
        cout << "\\______   \\_______   ____   __| _/____ _/  |_  ___________  ______ /  \\    /  \\__| ____| |\n";
        cout << " |     ___/\\_  __ \\_/ __ \\ / __ |\\__  \\    __\\/  _ \\_  __ \\/  ___/ \\   \\/\\/   /  |/    \\ |\n";
        cout << " |    |     |  | \\/\\  ___// /_/ | / __ \\|  | (  <_> )  | \\/\\___ \\   \\        /|  |   |  \\|\n";
        cout << " |____|     |__|    \\___  >____ |(____  /__|  \\____/|__|  /____  >   \\__/\\  / |__|___|  /_\n";
        cout << "                        \\/     \\/     \\/                       \\/         \\/          \\/\\/\n";
    }
    cout << endl << endl;
}

/*--------------------------------------------------------------------*/
/* Functions that the Aliens/Predators/Carnage use to draw themselves */
/*                (you will not need to directly use)                 */
/*--------------------------------------------------------------------*/

//getter: returns the height of the BattleGround
int BattleGround::getHeight(){
    return HEIGHT;
}

//getter: returns the width of the BattleGround
int BattleGround::getWidth(){
    return WIDTH;
}

//updates the grounds image at the specified location
void BattleGround::updateAt(int row, int col, char newChar){
    grounds[row][col] = newChar;
}

//updates the color of the grounds image at the specified location
void BattleGround::colorAt(int row, int col, char newChar){
    colors[row][col] = newChar;
}

/*--------------------------------------------------------------------*/
/*       Functions that set up the initial battle configurations      */
/*                (you will not need to directly use)                 */
/*--------------------------------------------------------------------*/

//make sure that the display is large enough for the battle
void BattleGround::screenDimensions(){
    bool h_cleared = false;
    bool w_cleared = false;
    bool battleReady = false;
    string enter;

    while(!battleReady){
        //check the screen height
        if(get_screen_rows() < (HEIGHT + 1)){
            cout << "Not enough screenspace for a battle!" << endl;
            cout << "Please increase the height of your screen and hit Enter.";
            cout << endl;
            cin.ignore();
        }else{
            h_cleared = true;
        }

        //check the screen width
        if(get_screen_cols() < WIDTH){
            cout << "Not enough screenspace for a battle!" << endl;
            cout << "Please increase the width of your screen and hit Enter.";
            cout << endl;
            cin.ignore();
            h_cleared = false;
        }else{
            w_cleared = true;
        }

        battleReady = h_cleared & w_cleared;
    }
}

//read in the alien and predator army files and build the warrior lists
bool BattleGround::setupBattle(string alien_army, string predator_army){
    //Read in the alien army file
    ifstream a_infile(alien_army.c_str());
    if (a_infile.fail()) {
        cerr << "ERROR: Error opening file, please check "
             << alien_army << endl;
        exit(EXIT_FAILURE);
    }

    Alien *a = new Alien();
    bool success = a->readAlien(&a_infile);
    while (success) {
        addAlien(a);
        a = new Alien();
        success = a->readAlien(&a_infile);
    }

    delete a;
    a_infile.close();

    //Read in the predator army file
    ifstream p_infile(predator_army.c_str());
    if (p_infile.fail()) {
        cerr << "ERROR: Error opening file, please check "
             << predator_army << endl;
        exit(EXIT_FAILURE);
    }

    Predator *p = new Predator();
    success = p->readPredator(&p_infile);
    while (success) {
        addPred(p);
        p = new Predator();
        success = p->readPredator(&p_infile);
    }

    delete p;
    p_infile.close();

    return validateBattle();
}

//adds an alien to the linked list of aliens
void BattleGround::addAlien(Alien *a){
    if(alien_head == nullptr){
        alien_head = a;
    }else{
        Alien *curr_a = alien_head;

        while(curr_a->getNext() != nullptr){
            curr_a = curr_a->getNext();
        }
        curr_a->setNext(a);
    }

    num_aliens++;
}

//adds a predator to the linked list of predators
void BattleGround::addPred(Predator *p){
    if(pred_head == nullptr){
        pred_head = p;
    }else{
        Predator *curr_p = pred_head;

        while(curr_p->getNext() != nullptr){
            curr_p = curr_p->getNext();
        }
        curr_p->setNext(p);
    }

    num_predators++;
}

//verifies that neither army is cheating
bool BattleGround::validateBattle(){
    //validate the predator army
    Predator *curr_p = pred_head;
    int strength_sum = 0;
    float speed;

    //check that the army has warriors and the correct release interval
    if(curr_p == nullptr){
        cout << "Battle Cancelled: The Predators chickened out\n";
        return false;
    }else if(curr_p->getRelease() < PRELEASE){
        cout << "Battle Cancelled: Predator Army has failed their steriods test\n";
        return false;
    }

    //check that no predator has exceeded the speed or size limits
    while(curr_p != nullptr){
        strength_sum += curr_p->getStrength();
        speed = sqrt(pow(curr_p->getVSpeed(), 2.0) + pow(curr_p->getHSpeed(), 2.0));

        if(speed > MAX_PSPEED || curr_p->getHeight() > MAX_PDIM ||
            curr_p->getWidth() > MAX_PDIM || curr_p->getStrength() > MAX_PSTRENGTH){

            cout << "Battle Cancelled: Predator Army has failed their steriods test\n";
            return false;
        }
        curr_p = curr_p->getNext();
    }

    //check that the predator army has not exceeded the strength limit
    if(strength_sum > 10){
        cout << "Battle Cancelled: Predator Army has failed their steriods test\n";
        return false;
    }

    //validate the alien army
    Alien *curr_a = alien_head;
    strength_sum = 0;

    //check that the army has warriors and the correct release interval
    if(curr_a == nullptr){
        cout << "Battle Cancelled: The Aliens chickened out\n";
        return false;
    }else if(curr_a->getRelease() < ARELEASE){
        cout << "Battle Cancelled: Alien Army has failed their steriods test\n";
        return false;
    }

    //check that no alien has exceeded the speed or size limits
    while(curr_a != nullptr){
        strength_sum += curr_a->getStrength();
        speed = sqrt(pow(curr_a->getVSpeed(), 2.0) + pow(curr_a->getHSpeed(), 2.0));

        if(speed > MAX_ASPEED || curr_a->getHeight() > MAX_ADIM ||
            curr_a->getWidth() > MAX_ADIM || curr_a->getStrength() > MAX_ASTRENGTH){
            cout << "Battle Cancelled: Alien Army has failed their steriods test\n";
            return false;
        }
        curr_a = curr_a->getNext();
    }

    //check that the alien army has not exceeded the strength limit
    if(strength_sum > 10){
        cout << "Battle Cancelled: Alien Army has failed their steriods test\n";
        return false;
    }

    return true;
}

/*--------------------------------------------------------------------*/
/*        Functions that free memory when the battle is over          */
/*                (you will not need to directly use)                 */
/*--------------------------------------------------------------------*/

//BattleGround destructor
BattleGround::~BattleGround(){
    free_aliens(alien_head);
    free_predators(pred_head);
    free_carnage(carn_head);
}

//free the aliens list
void BattleGround::free_aliens(Alien *curr_a){
    if(curr_a == nullptr){
        return;
    }else{
        free_aliens(curr_a->getNext());
        delete curr_a;
    }
}

//free the predator list
void BattleGround::free_predators(Predator *curr_p){
    if(curr_p == nullptr){
        return;
    }else{
        free_predators(curr_p->getNext());
        delete curr_p;
    }
}

//free the carnage list
void BattleGround::free_carnage(Carnage *curr_c){
    if(curr_c == nullptr){
        return;
    }else{
        free_carnage(curr_c->getNext());
        delete curr_c;
    }
}
