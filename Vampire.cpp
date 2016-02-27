/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Vampire methods file which defines the methods of the
** die class that were prototyped within the Vampire header file
*******************************************************************************/

#include <stdlib.h>
#include <string>
#include <iostream>
#include "Vampire.hpp"

using std::cout;
using std::endl;

/*--------------------------------------------------------------------------------*/
/*
    Function Name: Vampire
    Function Parameters: creature's name string
    What the function does: initializes a new instance of the Vampire subclass,
                            setting its type, strengthPts, armorPts, attackDieSides,
                            numAttackDice, and numDefenseDice to Vampire defaults
*/
Vampire::Vampire(string name, string cName) : Creature(name, cName) {
    setCreatureType(VAMPIRE);
    setStrengthPts(18);
    setArmorPts(1);
    setAttackDieSides(12);
    setNumAttackDice(1);
    setNumDefenseDice(1);
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: attack
    Function Parameters: n/a
    What the function does: simple attack function which sets the result of
                            rollAttack() to an integer and returns its result, since
                            Vampire has no special attack ability
*/
int Vampire::attack() {
    int attackRoll = rollAttack();

    return attackRoll;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: defend
    Function Parameters: n/a
    What the function does: simple defense function which sets the result of
                            rollDefense to an integer and returns its result.
                            Vampire's charm ability is handled in Game methods when
                            opponent creature makes its attack
*/
int Vampire::defend() {
    int defenseRoll = rollDefense();

    return defenseRoll;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: charm
    Function Parameters: n/a
    What the function does: Vampire's special charm ability which prevents opponent
                            from even making an attack.  Randomly calculates 50/50
                            odds by modulo 2 (result must be 1 or 0), and if 1, sets
                            charmed boolean to true and calls vampWink printing
                            method, returning true, else, returns false
*/
bool Vampire::charm() {
    bool charmed = false;
    int random = rand() % 2;

    if (random > 0) {
        charmed = true;
        vampWink();
    }

    return charmed;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: vampWink
    Function Parameters: n/a
    What the function does: printing function which gets the Vampire's name and
                            prints a humorous message and ASCII art Vampire wink,
                            developed by yours truly ;)
*/
void Vampire::vampWink() {
    string name = getCreatureName();
    cout << name << " charmed his opponent into not attacking!!!" << endl;
    cout << "The debonair deceiver flashes a wink!!!!" << endl;
    usleep(800000);
    cout << " __  __ " << endl;
    cout << "  0  <  " << endl;
    cout << "\\______/" << endl;
    cout << "  ∨  ∨  " << endl;
    usleep(1000000);
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: updateStrengthPts
    Function Parameters: defense and opponent's attack roll integers
    What the function does: basic update function which gets Vampire's current
                            strength and armor, and calculates total damage done
                            by subtracting the sum of defense roll and armor
                            from the opponent's attack roll.  If damage done > 0,
                            sets Vampire's strength points, subtracting the damage
                            inflicted from current strength points
*/
void Vampire::updateStrengthPts(int defenseRoll, int opponentRoll) {
    int currStrength = getStrengthPts();
    int armor = getArmorPts();
    int damageDone = opponentRoll - (defenseRoll + armor);

    if (damageDone > 0) {
        setStrengthPts(currStrength - damageDone);
    }
}
