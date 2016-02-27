/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Creature class prototypes, which define a large portion of
** functionality that each creature subclass will inherit, including getters and
** setters, tryAttack function to check for special creature abilities, the
** attack, defend, charm and updateStrengthPts virtual functions, and the dice
** rolling functions for attack and defense dice.
*******************************************************************************/

#include <string>

#ifndef CREATURE_HPP
#define CREATURE_HPP

using std::string;

enum CREATURES { BARBARIAN, BLUEMEN, HARRYPOTTER, MEDUSA, VAMPIRE };

class Creature {
 protected:
    CREATURES creatureType;
    string creatureName;
    string charaName;
    int strengthPts;
    int armorPts;
    int attackDieSides;
    int numAttackDice;
    int numDefenseDice;
    int numWins;
    bool stillAlive;

 public:
    Creature(string creatureName, string charaName);
    void setCreatureType(CREATURES);
    void setCreatureName(string creatureName);
    void setCharaName(string charaName);
    void setStrengthPts(int strengthPts);
    void setArmorPts(int armorPts);
    void setAttackDieSides(int attackDieSides);
    void setNumAttackDice(int numAttackDice);
    void setNumDefenseDice(int numDefenseDice);
    void incNumWins();
    void setStillAlive(bool stillAlive);
    CREATURES getCreatureType();
    string getCreatureName();
    string getCharaName();
    int getStrengthPts();
    int getArmorPts();
    int getAttackDieSides();
    int getNumAttackDice();
    int getNumDefenseDice();
    int getNumWins();
    bool getStillAlive();
    int tryAttack(Creature *self, Creature *opponent);
    virtual int attack() = 0;
    virtual int defend() = 0;
    virtual bool charm() = 0;
    virtual void updateStrengthPts(int defenseRoll, int opponentAttackRoll) = 0;
    int rollDie(int dieSides);
    int rollAttack();
    int rollDefense();
};

#endif
