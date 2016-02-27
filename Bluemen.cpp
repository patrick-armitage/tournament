/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Bluemen methods file which defines the methods of the
** die class that were prototyped within the Bluemen header file
*******************************************************************************/

#include <string>
#include <iostream>
#include "Bluemen.hpp"

using std::string;
using std::cout;
using std::endl;

/*--------------------------------------------------------------------------------*/
/*
    Function Name: Bluemen
    Function Parameters: creature's name string
    What the function does: initializes a new instance of the Bluemen subclass,
                            setting its type, strengthPts, armorPts, attackDieSides,
                            numAttackDice, and numDefenseDice to BlueMen defaults
*/
Bluemen::Bluemen(string name, string cName) : Creature(name, cName) {
    setCreatureType(BLUEMEN);
    setStrengthPts(12);
    setArmorPts(3);
    setAttackDieSides(10);
    setNumAttackDice(2);
    setNumDefenseDice(3);
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: attack
    Function Parameters: n/a
    What the function does: simple attack function which sets the result of
                            rollAttack() to an integer and returns its result, since
                            Blue Men have no special attack ability
*/
int Bluemen::attack() {
    int attackRoll = rollAttack();

    return attackRoll;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: defend
    Function Parameters: n/a
    What the function does: simple defense function which sets the result of
                            rollDefense() to an integer and returns its result,
                            since Bluemen have no special defense ability
*/
int Bluemen::defend() {
    int defenseRoll = rollDefense();

    return defenseRoll;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: charm
    Function Parameters: n/a
    What the function does: dummy function inherited by base class and defined only
                            as a placeholder; Vampire class makes use of this
                            function for a special ability
*/
bool Bluemen::charm() {
    return false;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: updateStrengthPts
    Function Parameters: defense and opponent's attack roll integers
    What the function does: basic update function which gets Blue Mens' current
                            strength and armor, and calculates total damage done
                            by subtracting the sum of defense roll and armor
                            from the opponent's attack roll.  If damage done > 0,
                            sets Blue Mens' strength points, subtracting the damage
                            inflicted from current strength points.  Then calls
                            checkDefenseLevel, which checks to see if Blue Men
                            still have enough men to support current number of
                            defense dice
*/
void Bluemen::updateStrengthPts(int defenseRoll, int opponentRoll) {
    int currStrength = getStrengthPts();
    int armor = getArmorPts();
    int damageDone = opponentRoll - (defenseRoll + armor);

    if (damageDone > 0) {
        setStrengthPts(currStrength - damageDone);
        checkDefenseLevel();
    }
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: checkDefenseLevel
    Function Parameters: n/a
    What the function does: checks current defense level, getting the current num
                            defense dice and strength points and calculating if
                            (strength points / 4) + 1 is lower than num of defense
                            dice.  This math works out to range [8..12] = 3 dice,
                            [4..7] = 2 dice, and [1..3] = 1 die.  If the check is
                            lower than current defense dice, sets numDefDice to
                            the checkDefense integer, and prints a mesage where
                            Blue Men recognize they are losing defense and shout
                            a rousing insult to one another ;)
*/
void Bluemen::checkDefenseLevel() {
    int numDefDice = getNumDefenseDice();
    int strPts = getStrengthPts();
    if (strPts == 0) { return; }

    // we add 1 to ensure rounding is correct, e.g. 8,9,10,11 str == defense dice of 3
    int checkDefense = (strPts / 4) + 1;

    if (checkDefense < numDefDice) {
        usleep(800000);
        cout << getCreatureName() << " are losing numbers!"  << endl;
        usleep(1500000);
        cout << "With only " << strPts << " men left,";
        cout << " they can only defend with " << checkDefense << " dice!!!" << endl;
        usleep(800000);
        showTheBlueMen(strPts);
        usleep(1400000);
        cout << "KEEP IT COMING YOU BLUE BLOCKHEADS!!!!" << endl;
        usleep(1200000);
        setNumDefenseDice(checkDefense);
    }
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: showTheBlueMen
    Function Parameters: current strength points integer
    What the function does: prints out small Blue Men stick figures for the numbers
                            of strength points left, for giggles! =D
*/
void Bluemen::showTheBlueMen(int strPts) {
    for (int i = 1; i <= strPts; i++) {
        cout << "\033[1;34m__@| ";
        if (i == strPts) { cout << endl; }
    }
    for (int i = 1; i <= strPts; i++) {
        cout << "  |  ";
        if (i == strPts) { cout << endl; }
    }
    for (int i = 1; i <= strPts; i++) {
        cout << " / \\ ";
        if (i == strPts) { cout << "\033[0m" << endl; }
    }
}
