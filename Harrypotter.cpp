/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Harrypotter methods file which defines the methods of the
** die class that were prototyped within the Harrypotter header file
*******************************************************************************/

#include <string>
#include <iostream>
#include "Harrypotter.hpp"

using std::cout;
using std::endl;

/*--------------------------------------------------------------------------------*/
/*
    Function Name: Harrypotter
    Function Parameters: creature's name string
    What the function does: initializes a new instance of the Harry Potter subclass,
                            setting its type, strengthPts, armorPts, attackDieSides,
                            numAttackDice, numDefenseDice and hasRevived to Harry's
                            defaults
*/
Harrypotter::Harrypotter(string name, string cName) : Creature(name, cName) {
    setCreatureType(HARRYPOTTER);
    setStrengthPts(10);
    setArmorPts(0);
    setAttackDieSides(6);
    setNumAttackDice(2);
    setNumDefenseDice(2);
    setHasRevived(false);
}

/*---------------------------------------------------------------------------------------*/
/*
    Function Names: setHasRevived, getHasRevived
    Functions' Parameters: setters use corresponding values of data members
    What the functions do: getter and setter for Harry's unique revived boolean data member
*/
void Harrypotter::setHasRevived(bool revived) {
    hasRevived = revived;
}

bool Harrypotter::getHasRevived() {
    return hasRevived;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: attack
    Function Parameters: n/a
    What the function does: simple attack function which sets the result of
                            rollAttack() to an integer and returns its result, since
                            Harry has no special attack ability
*/
int Harrypotter::attack() {
    int attackRoll = rollAttack();

    return attackRoll;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: defend
    Function Parameters: n/a
    What the function does: simple defense function which sets the result of
                            rollDefense() to an integer and returns its result,
                            since Harry has no special defense ability
*/
int Harrypotter::defend() {
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
bool Harrypotter::charm() {
    return false;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: updateStrengthPts
    Function Parameters: defense and opponent's attack roll integers
    What the function does: custom update function which gets Harry's current
                            strength, and calculates total damage done by
                            subtracting the sum of defense roll and armor from the
                            opponent's attack roll.  If damage done > 0, sets Harry's
                            strength points, subtracting the damage inflicted from
                            current strength points.  If Harry's strength == 0 after
                            damage is inflicted, and hasRevived == false, invokes
                            Harry's special Hogwarts ability where he dies, but
                            rises again for the sake of protecting Hogwarts from
                            this intruder
*/
void Harrypotter::updateStrengthPts(int defenseRoll, int opponentRoll) {
    int currStrength = getStrengthPts();
    int damageDone = opponentRoll - defenseRoll;

    // check if this is a mortal blow first before setting damage done
    if (damageDone >= currStrength) {
        if (!hasRevived) {
            cout << "Harry Potter was struck down!!!" << endl;
            usleep(1000000);
            cout << "He's not breathing...  He sleeps the sleep of death...  He...wait!" << endl;
            usleep(2000000);
            cout << "\"FOR HOGWAAAAAAAAAAAAAARTS!!!!!\"" << endl;
            usleep(1000000);
            // cool "wand" ASCII art for effect ;)
            cout << "━━━━━━━━☆ﾟ.*･｡ﾟ" << endl;
            usleep(2000000);
            cout << "Harry Potter gets back up with DOUBLE the strength as before!!!!" << endl;
            usleep(1000000);
            // now hasRevived = true, so this resurrection will not happen again
            setHasRevived(true);
            setStrengthPts(20);
        } else {
            // if hasRevived is already true, Harry dies for keeps =,(
            setStrengthPts(0);
        }
    } else if (damageDone > 0) {
        setStrengthPts(currStrength - damageDone);
    }
}
