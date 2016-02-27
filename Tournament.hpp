/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/10/2016
** Description: Game function prototypes, used as utility methods and called
** directly within main.cpp, they include getCreatureString and
** initializeCreature for deciding which subclass to use, and printTitle,
** playRound and closeGame to control the flow of the game
*******************************************************************************/

#include <string>
#include "Creature.hpp"
#include "Fighterlineup.hpp"
#include "Loserpile.hpp"

#ifndef TOURNAMENT_HPP
#define TOURNAMENT_HPP

using std::string;

string getCreatureString(CREATURES creatureType);
Creature *initializeCreature(CREATURES creatureType, string creatureName, string creatureCName);
void playRound(Fighterlineup *team1, Fighterlineup *team2, Loserpile *losers);
bool attackAndDefend(Creature *attackingPlayer, Creature *defendingPlayer);
bool checkWinnerAndLoser(Fighterlineup *team1, Fighterlineup *team2, Loserpile *losers);
void healPlayers(Fighterlineup *team1, Fighterlineup *team2);
void printTitle(string name1, string name2);
void showWinners(Fighterlineup *team1, Fighterlineup *team2);
void showLosers(Loserpile *losers);
void closeGame();

#endif
