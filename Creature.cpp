/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Creature methods file which defines the methods of the
** Creature class that were prototyped within the GameBoard header file
*******************************************************************************/

#include <stdlib.h>
#include <string>
#include <iostream>
#include "Creature.hpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;

/*----------------------------------------------------------------------------*/
/*
    Function Name: Creature
    Function Parameters: Creature's name string
    What the function does: initializes a new instance of the Creature class,
                            setting creature name and also setting stillAlive
                            boolean to true
*/
Creature::Creature(string name, string cName) {
    setCreatureName(name);
    setCharaName(cName);
    setStillAlive(true);
    numWins = 0;
}

/*---------------------------------------------------------------------------------------*/
/*
    Function Names: setCreatureType, setCreatureName, setStrengthPts, setArmorPts,
                    setAttackDieSides, setNumAttackDice, setNumDefenseDice, setStillAlive,
                    getCreatureType, getCreatureName, getStrengthPts, getArmorPts,
                    getAttackDieSides, getNumAttackDice, getNumDefenseDice, getStillAlive
    Functions' Parameters: setters use corresponding values of data members
    What the functions do: getters and setters which act as public options to
                           read/write the Creature class's private attribute methods
*/
void Creature::setCreatureType(CREATURES type) {
    creatureType = type;
}

void Creature::setCreatureName(string name) {
    creatureName = name;
}

void Creature::setCharaName(string cName) {
    charaName = cName;
}

void Creature::setStrengthPts(int pts) {
    // just in case pts is negative, we set it to 0 manually if it is
    if (pts >= 0) {
        strengthPts = pts;
    } else {
        strengthPts = 0;
    }
}

void Creature::setArmorPts(int pts) {
    armorPts = pts;
}

void Creature::setAttackDieSides(int sides) {
    // NOTE: we need to set attack sides, but not defense, since defense always uses
    // six-sided die, and therefore we only need to know # of defense dice for defense
    attackDieSides = sides;
}

void Creature::setNumAttackDice(int numDice) {
    numAttackDice = numDice;
}

void Creature::setNumDefenseDice(int numDice) {
    numDefenseDice = numDice;
}

void Creature::incNumWins() {
    numWins++;
}

void Creature::setStillAlive(bool alive) {
    stillAlive = alive;
}

CREATURES Creature::getCreatureType() {
    return creatureType;
}

string Creature::getCreatureName() {
    return creatureName;
}

string Creature::getCharaName() {
    return charaName;
}

int Creature::getStrengthPts() {
    return strengthPts;
}

int Creature::getArmorPts() {
    return armorPts;
}

int Creature::getAttackDieSides() {
    return attackDieSides;
}

int Creature::getNumAttackDice() {
    return numAttackDice;
}

int Creature::getNumDefenseDice() {
    return numDefenseDice;
}

int Creature::getNumWins() {
    return numWins;
}

bool Creature::getStillAlive() {
    return stillAlive;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: tryAttack
    Function Parameters: attacking and defending Creatures' pointers
    What the function does: gets the two creatures' types and name strings, and
                            before executing the attack roll, checks the types
                            to see if there are any special cases occurring.
                            If the type is Medusa, we must check to see if she
                            will glare, and if type is Vampire, the vamp may
                            charm the opponent
*/
int Creature::tryAttack(Creature *self, Creature *opponent) {
    bool charmed = false;
    int attack;
    string selfName = self->getCreatureName();
    CREATURES selfType = self->getCreatureType();
    string oppName = opponent->getCreatureName();
    CREATURES oppType = opponent->getCreatureType();

    if (selfType == MEDUSA) {
        attack = self->attack();
        if (attack == 12) {
            return 99;
        }
    }

    if (oppType == VAMPIRE) {
        charmed = opponent->charm();
    }

    if (charmed == false) {
        attack = self->attack();
        return attack;
    }

    return 0;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: rollDie
    Function Parameters: number of sides of the dice being rolled
    What the function does: generic dice rolling function which accepts number
                            of sides of dice and returns a random roll integer
                            which falls in the range of [1..diceSides]
*/
int Creature::rollDie(int dieSides) {
    int roll;
    int rollMax = dieSides - 1;

    // we modulo random against (dieSides - 1) and add 1, to restrict results to 1 thru dieSides
    roll = (rand() % rollMax) + 1;
    return roll;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: rollAttack
    Function Parameters: N/A
    What the function does: using helper functions rollDie() and getters, finds
                            the number of sides of attack dice and the number
                            of attack dice the creature possess, and rolls for
                            the number of dice sides for each attack dice in
                            the Creature's arsenal
*/
int Creature::rollAttack() {
    int roll = 0;
    int dieSides = getAttackDieSides();
    int numDie = getNumAttackDice();

    for (int i = 0; i < numDie; i++) {
        roll += rollDie(dieSides);
    }

    return roll;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: rollDefense
    Function Parameters: N/A
    What the function does: using helper functions rollDie() and getters, finds
                            the the number of defense dice the creature possess,
                            and rolls for 6-sided dice for each defense dice in
                            the Creature's arsenal
*/
int Creature::rollDefense() {
    int roll = 0;
    int numDie = getNumDefenseDice();

    for (int i = 0; i < numDie; i++) {
        // we pass in 6 for dieSides, since defense always uses 6-sided dice
        roll += rollDie(6);
    }

    return roll;
}
