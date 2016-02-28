/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/22/2016
** Description: Tournament functions file which defines the functions that were
** prototyped within the Tournament header file
*******************************************************************************/

#include <iostream>
#include <string>
#include "Tournament.hpp"
#include "Creature.hpp"
#include "Barbarian.hpp"
#include "Bluemen.hpp"
#include "Harrypotter.hpp"
#include "Medusa.hpp"
#include "Vampire.hpp"
#include "Fighterlineup.hpp"
#include "Loserpile.hpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;

/*----------------------------------------------------------------------------*/
/*
    Function Name: getCreatureString
    Function Parameters: CREATURES enum list item
    What the function does: takes a creature type from CREATURES enum list,
                            and depending on the type of creature, returns the
                            appropriate string name of that creature type
*/
string getCreatureString(CREATURES creatureType) {
    switch (creatureType) {
    case BARBARIAN :
        return "Barbarian";
    case BLUEMEN :
        return "Blue Men";
    case HARRYPOTTER :
        return "Harry Potter";
    case MEDUSA :
        return "Medusa";
    case VAMPIRE :
        return "Vampire";
    }
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: initializeCreature
    Function Parameters: CREATURES enum creature type, creature name string
    What the function does: takes a creature type and creature name string,
                            and depending on the creature type, initializes
                            a new creature of the appropriate creature type
                            subclass and returns a pointer to the new creature
*/
Creature *initializeCreature(CREATURES creatureType, string creatureName, string cName) {
    Creature *creature;

    switch (creatureType) {
    case BARBARIAN :
        creature = new Barbarian(creatureName, cName);
        return creature;
    case BLUEMEN :
        creature = new Bluemen(creatureName, cName);
        return creature;
    case HARRYPOTTER :
        creature = new Harrypotter(creatureName, cName);
        return creature;
    case MEDUSA :
        creature = new Medusa(creatureName, cName);
        return creature;
    case VAMPIRE :
        creature = new Vampire(creatureName, cName);
        return creature;
    }
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: playRound
    Function Parameters: the two teams' Fighterlineups and the losers pile
    What the function does: Calls attackAndDefend for each creature to
                            alernately attack each other, then calls
                            checkWinnerAndLoser to determine the state of them
                            if a creature does die, to add the creatures to
                            respective fighterlineups or loserpile, and if it
                            returns false, one team has lost all its players,
                            and the game is over.
*/
void playRound(Fighterlineup *team1, Fighterlineup *team2, Loserpile *losers) {
    Creature *player1 = team1->getCurrentFighter()->fighter;
    Creature *player2 = team2->getCurrentFighter()->fighter;
    bool continueGame = true, player1StillAlive = true, player2StillAlive = true;

    player2StillAlive = attackAndDefend(player1, player2);
    if (player2StillAlive == false) {
        continueGame = checkWinnerAndLoser(team1, team2, losers);
        if (continueGame != true) {
            cout << endl << "**************************************************" << endl;
            cout << "Game is over!!!!!" << endl;
            cin.ignore();
        }
        return;
    }

    cout << endl;
    usleep(30000);

    player1 = team1->getCurrentFighter()->fighter;
    player2 = team2->getCurrentFighter()->fighter;
    player1StillAlive = attackAndDefend(player2, player1);
    if (player1StillAlive == false) {
        continueGame = checkWinnerAndLoser(team1, team2, losers);
        if (continueGame != true) {
            cout << endl << "**************************************************" << endl;
            cout << "Game is over!" << endl;
            cin.ignore();
        }
        return;
    }

    healPlayers(team1, team2);
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: attackAndDefend
    Function Parameters: the attacking and defending Creature object pointers
    What the function does: has attacking creature attack defending creature,
                            and defender defending, decrementing their strength pts
                            based on damage done, and handling special cases
                            where attack may be 0 (when Vampire charms opponent)
                            or where it may be 99 (when Medusa glares), then
                            sets the stillAlive creature bool if the defender
                            dies in combat.  Returns false if the defender has
                            died
*/
bool attackAndDefend(Creature *attacker, Creature *defender) {
    int attack, defense, defenderPoints;
    string attackerName = attacker->getCharaName();
    string defenderName = defender->getCharaName();

    cout << attackerName << " just attacked " << defenderName << "!" << endl;
    attack = attacker->tryAttack(attacker, defender);
    usleep(30000);
    // first handle the Medusa edge case where she may glare (attack == 99)
    if (attack == 99) {
        cout << attackerName << " just turned " << defenderName << " into stone!!!" << endl;
        usleep(2000000);
        defender->setStrengthPts(0);
        defender->setStillAlive(false);
        attacker->incNumWins();
        return false;
    // there is another edge case where Vampire charms and attack == 0,
    // in which case we skip over the defense and updateStrengthPts entirely
    } else if (attack > 0) {
        cout << attackerName << " struck with " << attack << " damage points!" << endl;
        usleep(30000);
        defense = defender->defend();
        cout << defenderName << " blocked with a defense of " << defense << "!" << endl;
        usleep(30000);
        defender->updateStrengthPts(defense, attack);
    }
    defenderPoints = defender->getStrengthPts();
    cout << defenderName << " has " << defenderPoints << " strength points left!" << endl;

    if (defenderPoints == 0) {
        defender->setStillAlive(false);
        attacker->incNumWins();
        cout << defenderName << " got struck down!" << endl;
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: checkWinnerAndLoser
    Function Parameters: the two teams' Fighterlineups and the losers pile
    What the function does: checks to see if both current fighters are still
                            alive.  If one is dead, removes that fighter from
                            the team and adds to the loser pile.  If the
                            opponent fighter's team has more lined up,
                            removes that fighter from the front of the
                            Fighterlineup and adds back in to the back of the
                            lineup
*/
bool checkWinnerAndLoser(Fighterlineup *team1, Fighterlineup *team2, Loserpile *losers) {
    Fighter *team1CurFtr = team1->getCurrentFighter();
    Fighter *team2CurFtr = team2->getCurrentFighter();
    Creature *player1 = team1CurFtr->fighter;
    Creature *player2 = team2CurFtr->fighter;

    if (player1->getStillAlive() == false) {
        cout << "Removing " << player1->getCreatureName() << " " << player1->getCharaName();
        cout << " from " << team1->getTeamName() << "!" << endl;
        team1->remove();
        losers->add(player1);
        if (team2->getCurrentFighter()->nextFighter != NULL) {
            team2->remove();
            cout << "Moving " << player2->getCreatureName() << " " << player2->getCharaName();
            cout << " to the back of " << team2->getTeamName() << "!" << endl;
            team2->add(player2);
        }
    } else if (player2->getStillAlive() == false) {
        cout << "Removing " << player2->getCreatureName() << " " << player2->getCharaName();
        cout << " from " << team2->getTeamName() << "!" << endl;
        team2->remove();
        losers->add(player2);
        if (team1->getCurrentFighter()->nextFighter != NULL) {
            team1->remove();
            cout << "Moving " << player1->getCreatureName() << " " << player1->getCharaName();
            cout << " to the back of " << team1->getTeamName() << "!" << endl;
            team1->add(player1);
        }
    }

    team1CurFtr = team1->getCurrentFighter();
    team2CurFtr = team2->getCurrentFighter();

    if ((team1CurFtr == NULL) || (team2CurFtr == NULL)) {
        return false;
    } else {
        return true;
    }
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: healPlayers
    Function Parameters: the two teams' Fighterlineups
    What the function does: Iterates over the fighters in each team.  If any
                            fighter (not the current fighter doing the combat)
                            has > 0 wins, that fighter will be healed 2 strength
                            pts per round, if their current strength is under
                            20 pts
*/
void healPlayers(Fighterlineup *team1, Fighterlineup *team2) {
    Fighterlineup *teams[2] = { team1, team2 };
    Fighterlineup *curTeam;
    Fighter *curPlayer;
    int curStrength;

    for (int i = 0; i < 2; i++) {
        curTeam = teams[i];
        curPlayer = curTeam->getCurrentFighter()->nextFighter;  // we don't heal the current fighter
        while (curPlayer != NULL) {
            if (curPlayer->fighter->getNumWins() > 0) {
                curStrength = curPlayer->fighter->getStrengthPts();
                if (curStrength < 20) {
                    curPlayer->fighter->setStrengthPts(curStrength+2);
                    cout << curPlayer->fighter->getCreatureName() << " ";
                    cout << curPlayer->fighter->getCharaName() << " rested and healed some, ";
                    cout << "and now has " << curPlayer->fighter->getStrengthPts();
                    cout << " strength points!" << endl;
                }
            }

            curPlayer = curPlayer->nextFighter;
        }
    }
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: printTitle
    Function Parameters: string name of each creature in the contest
    What the function does: using the two provided creature name strings, prints
                            a customized match title with borders declaring
                            which creatures will be contending in the match
*/
void printTitle(string name1, string name2) {
    string titleString = "TITLE MATCH: " + name1 + " vs. " + name2;
    int len = titleString.length();
    for (int i = 0; i < len; i++) {
        cout << "=";
    }
    cout << endl;
    cout << titleString << endl;
    for (int i = 0; i < len; i++) {
        cout << "=";
    }
    cout << endl;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: showWinners
    Function Parameters: two team's Fighterlineups
    What the function does: finds the winning team, then gets the top 3 players
                            from the winning team (if alive).  In the next
                            section, sorts the 3 players according to who got
                            the most wins.  Finally, prints the 3 fighters in
                            order of 1st, 2nd and 3rd place
*/
void showWinners(Fighterlineup *team1, Fighterlineup *team2) {
    /* Get top 3 fighters from winning team */
    Fighter *winner;
    Fighterlineup *winningTeam;

    if (team1->getCurrentFighter() == NULL) {
        winningTeam = team2;
    } else if (team2->getCurrentFighter() == NULL) {
        winningTeam = team1;
    }

    int winnerCounter = 0;
    Fighter *nextFtr, *nextNextFtr;
    Fighter *orderedFighters[3];
    int numWinners = 1;

    int winnerWins, nextFtrWins, nextNextFtrWins;
    winner = winningTeam->getCurrentFighter();
    winnerWins = winner->fighter->getNumWins();
    nextFtr = winner->nextFighter;
    if (nextFtr != NULL) {
        nextFtrWins = nextFtr->fighter->getNumWins();
        nextNextFtr = nextFtr->nextFighter;
        numWinners++;
    }
    if (nextNextFtr != NULL) {
        nextNextFtrWins = nextFtr->fighter->getNumWins();
        numWinners++;
    }

    /* Compare each fighter's wincount, ordering them 1st, 2nd and 3rd place */
    if (nextFtr != NULL) {
        if (winnerWins >= nextFtrWins) {
            if (nextNextFtr != NULL) {
                if (nextFtrWins >= nextNextFtrWins) {
                    orderedFighters[0] = winner;
                    orderedFighters[1] = nextFtr;
                    orderedFighters[2] = nextNextFtr;
                } else {
                    if (winnerWins >= nextNextFtrWins) {
                        orderedFighters[0] = winner;
                        orderedFighters[1] = nextNextFtr;
                        orderedFighters[2] = nextFtr;
                    } else {
                        orderedFighters[0] = nextNextFtr;
                        orderedFighters[1] = winner;
                        orderedFighters[2] = nextFtr;
                    }
                }
            } else {
                orderedFighters[0] = winner;
                orderedFighters[1] = nextFtr;
            }
        } else {
            if (nextNextFtr != NULL) {
                if (nextFtrWins >= nextNextFtrWins) {
                    orderedFighters[0] = nextFtr;
                    orderedFighters[1] = nextNextFtr;
                    orderedFighters[2] = winner;
                } else {
                    if (nextNextFtrWins >= winnerWins) {
                        orderedFighters[0] = nextNextFtr;
                        orderedFighters[1] = nextFtr;
                        orderedFighters[2] = winner;
                    }
                }
            } else {
                orderedFighters[0] = nextFtr;
                orderedFighters[1] = winner;
            }
        }
    } else {
        orderedFighters[0] = winner;
    }

    /* Print winning fighters in order */
    cout << winningTeam->getTeamName() << " wins the tournament!!!!" << endl << endl;
    cin.ignore();
    cout << "The champions of the tournament are:" << endl;
    string place;
    for (int i = 0; i < numWinners; i++) {
        if (i == 0) {
            place = "1st place";
        } else if (i == 1) {
            place = "2nd place";
        } else if (i == 2) {
            place = "3rd place";
        }

        winner = orderedFighters[i];
        cout << "Coming in at " << place << ": ";
        cout << winner->fighter->getCreatureName() << " " << winner->fighter->getCharaName();
        cout << " with " << winner->fighter->getNumWins() << " wins!!!" << endl;
        winningTeam->remove();
    }
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: showLosers
    Function Parameters: Loserpile
    What the function does: prints the name of each loser on top of the loser
                            pile, then removes that loser, until there are no
                            more losers in the loserpile
*/
void showLosers(Loserpile *losers) {
    cout << endl << "The losers who got beat to a pulp are:" << endl;
    while (losers->getCurrentLoser() != NULL) {
        cout << losers->getCurrentLoser()->loser->getCreatureName() << " ";
        cout << losers->getCurrentLoser()->loser->getCharaName() << "!!!" << endl;
        losers->remove();
    }
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: closeGame
    Function Parameters: N/A
    What the function does: prints a parting message to the user, along with a
                            (very) fancy ASCII art emblem borrowed ;) off the
                            internet!
*/
void closeGame() {
// ASCII art for Emblem borrowed from joan g stark, who gets all the props :)
// See http://www.retrojunkie.com/asciiart/weapons/swords.htm
    usleep(800000);
    cout << endl << "See you next time in FANTASY COMBAT Tournament Edition!" << endl << endl;

    cout << "   |\\                     /) " << endl;
    cout << " /\\_\\\\__               (_//" << endl;
    cout << "|   `>\\-`     _._       //`) " << endl;
    cout << " \\ /` \\\\  _.-`:::`-._  //  " << endl;
    cout << "  `    \\|`    :::    `|/     " << endl;
    cout << "        |     :::     |       " << endl;
    cout << "        |.....:::.....|       " << endl;
    cout << "        |:::::::::::::|       " << endl;
    cout << "        |     :::     |       " << endl;
    cout << "        \\     :::     /      " << endl;
    cout << "         \\    :::    /       " << endl;
    cout << "          `-. ::: .-'         " << endl;
    cout << "           //`:::`\\\\        " << endl;
    cout << "          //   '   \\\\       " << endl;
    cout << "         |/         \\\\      " << endl;
}
