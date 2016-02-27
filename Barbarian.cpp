/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Barbarian methods file which defines the methods of the
** die class that were prototyped within the Barbarian header file
*******************************************************************************/

#include <string>
#include "Barbarian.hpp"

/*--------------------------------------------------------------------------------*/
/*
    Function Name: Barbarian
    Function Parameters: creature's name string
    What the function does: initializes a new instance of the Barbarian subclass,
                            setting its type, strengthPts, armorPts, attackDieSides,
                            numAttackDice, and numDefenseDice to Barbarian defaults
*/
Barbarian::Barbarian(string name, string cName) : Creature(name, cName) {
    setCreatureType(BARBARIAN);
    setStrengthPts(12);
    setArmorPts(0);
    setAttackDieSides(6);
    setNumAttackDice(2);
    setNumDefenseDice(2);
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: attack
    Function Parameters: n/a
    What the function does: simple attack function which sets the result of
                            rollAttack() to an integer and returns its result, since
                            Barbarian has no special attack ability
*/
int Barbarian::attack() {
    int attackRoll = rollAttack();

    return attackRoll;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: defend
    Function Parameters: n/a
    What the function does: simple defense function which sets the result of
                            rollDefense() to an integer and returns its result,
                            since Barbarian has no special defense ability
*/
int Barbarian::defend() {
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
bool Barbarian::charm() {
    return false;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: updateStrengthPts
    Function Parameters: defense and opponent's attack roll integers
    What the function does: custom update function which gets Barbarian's current
                            strength, and calculates total damage done by
                            subtracting the sum of defense roll and armor from the
                            opponent's attack roll.  If damage done > 0, sets his
                            strength points, subtracting the damage inflicted from
                            current strength points
*/
void Barbarian::updateStrengthPts(int defenseRoll, int opponentRoll) {
    int currStrength = getStrengthPts();
    int damageDone = opponentRoll - defenseRoll;

    if (damageDone > 0) {
        setStrengthPts(currStrength - damageDone);
    }
}
