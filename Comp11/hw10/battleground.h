/*
 * battleground.h
 * COMP11 AVP
 */

#ifndef BATTLEGROUND_H
#define BATTLEGROUND_H
#include <string>
#include <fstream>
#include <math.h>
#include <unistd.h>
#include "termfuncs.h"
#include "predator.h"
#include "alien.h"
#include "carnage.h"

class BattleGround{
  public:
	//constructor
	BattleGround();

	//destructor
	~BattleGround();

	//functions that main uses
	void simulate(bool singleStep);
	bool setupBattle(string alien_army, string predator_army);

	//functions that the Alien/Predator/Carnage classes use
	int getHeight();
	int getWidth();
	void updateAt(int row, int col, char newChar);
	void colorAt(int row, int col, char newChar);

  private:
	//functions you will directly deal with
	void engageBattles();
  Alien *previousAlien(Alien *curr_a);
  Predator *previousPredator(Predator *curr_p);
  void deleteAlien(Alien *curr_a);
  void deletePredator(Predator *curr_p);
	void addCarnage(Carnage *c);
	void outputGrounds(int num_cycles);

	//battleground drawing functions
	void clearGrounds();
	void drawGrounds();
	void drawWarriors();
	void moveWarriors();
	void battleOver(bool aliens_won);

	//setup functions
	void screenDimensions();
	void addPred(Predator *p);
	void addAlien(Alien *a);
	bool validateBattle();

	//functions for freeing memory
	void free_aliens(Alien *curr_a);
	void free_predators(Predator *curr_p);
	void free_carnage(Carnage *curr_c);

	//battleground constants
	static const int HEIGHT = 50;
	static const int WIDTH  = 150;
	static const int SLEEP  = 50000;

	//total number of predators, aliens, and carnage
	int num_predators;
	int num_aliens;
	int num_carnage;

	//number of released predators and aliens
	int rel_predators;
	int rel_aliens;

	//first alien/predator/carnage in linked lists
	Alien *alien_head;
	Predator *pred_head;
	Carnage *carn_head;

	//battleground image
	char grounds[HEIGHT][WIDTH];
	char colors[HEIGHT][WIDTH];

	//duplicate constants to verify your alien (and predator) specs
	static const int MAX_ADIM = 15;
	static const int MAX_PDIM = 20;
	static const int MAX_ASTRENGTH = 7;
	static const int MAX_PSTRENGTH = 10;
	static const int ARELEASE = 50;
	static const int PRELEASE = 100;
	float MAX_ASPEED;
	float MAX_PSPEED;
};

#endif
