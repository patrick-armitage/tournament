/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Medusa methods file which defines the methods of the
** die class that were prototyped within the GameBoard header file
*******************************************************************************/

#include <string>
#include <iostream>
#include "Medusa.hpp"

using std::string;
using std::cout;
using std::endl;

/*----------------------------------------------------------------------------*/
/*
    Function Name: Medusa
    Function Parameters: integer number of sides
    What the function does: initializes a new instance of the Medusa class,
                            setting number of sides to the provided sides arg
*/
Medusa::Medusa(string name, string cName) : Creature(name, cName) {
    setCreatureType(MEDUSA);
    setStrengthPts(8);
    setArmorPts(3);
    setAttackDieSides(6);
    setNumAttackDice(2);
    setNumDefenseDice(1);
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: attack
    Function Parameters: n/a
    What the function does: custom attack function which sets the result of
                            rollAttack() to an integer.  If Medusa rolls a 12, she
                            glares at her opponent, and Game functions will later
                            interpret a 12 from Medusa as a 99, signaling the
                            instant death of her opponent.  Calls glare method for
                            a creative ASCII art representation of Medusa
*/
int Medusa::attack() {
    int attackRoll = rollAttack();

    if (attackRoll == 12) {
        cout << "Critical Strike!!!  Medusa GLARES at her opponent!" << endl;
        usleep(800000);
        glare();
        usleep(2000000);
    }

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
int Medusa::defend() {
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
bool Medusa::charm() {
    return false;
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: updateStrengthPts
    Function Parameters: defense and opponent's attack roll integers
    What the function does: basic update function which gets Medusa's current
                            strength and armor, and calculates total damage done
                            by subtracting the sum of defense roll and armor
                            from the opponent's attack roll.  If damage done > 0,
                            sets Medusa's strength points, subtracting the damage
                            inflicted from current strength points
*/
void Medusa::updateStrengthPts(int defenseRoll, int opponentRoll) {
    int currStrength = getStrengthPts();
    int armor = getArmorPts();
    int damageDone = opponentRoll - (defenseRoll + armor);

    if (damageDone > 0) {
        setStrengthPts(currStrength - damageDone);
    }
}

/*--------------------------------------------------------------------------------*/
/*
    Function Name: glare
    Function Parameters: n/a
    What the function does: prints a creative ASCII art picture of Medusa glaring.
                            Creepy! O.O
*/
void Medusa::glare() {
// ASCII art for Medusa borrowed from jgs, who gets all the props :)
// See http://ascii.co.uk/art/medusa
    cout << "               ,--.             " << endl;
    cout << "      ,--.  .--,`) )  .--,      " << endl;
    cout << "   .--,`) \\( (` /,--./ (`       " << endl;
    cout << "  ( ( ,--.  ) )\\ /`) ).--,-.    " << endl;
    cout << "   ;.__`) )/ /) ) ( (( (`_) )   " << endl;
    cout << "  ( (  / /( (.' '-.) )) )__.'-, " << endl;
    cout << " _,--.( ( /`         `,/ ,--,) )" << endl;
    cout << "( (``) \\,` ==.    .==  \\( (`,-; " << endl;
    cout << " ;-,( (_) ~6~ \\  / ~6~ (_) )_) )" << endl;
    cout << "( (_ \\_ (      )(      )__/___.'" << endl;
    cout << "'.__,-,\\ \\     ''     /\\ ,-.    " << endl;
    cout << "   ( (_/ /\\    __    /\\ \\_) )   " << endl;
    cout << "    '._.'  \\  \\__/  /  '._.'    " << endl;
    cout << "        .--`\\      /`--.        " << endl;
    cout << "             '----'             " << endl;
}
