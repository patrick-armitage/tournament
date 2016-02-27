#include <iostream>
#include <string>

#include "Creature.hpp"
#include "Fighterlineup.hpp"
#include "Loserpile.hpp"
#include "Tournament.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
    int numFighters;
    string team1Name, team2Name;
    cout << "Welcome to the Ultimate Creature Combat Tournament!!!" << endl;
    cin.ignore();
    cout << "What will be the name of the first team of fighters? ";
    cin >> team1Name;
    cin.ignore();
    cout << "What will be the name of the second team of fighters? ";
    cin >> team2Name;
    cin.ignore();
    cout << "How many fighters would you like each team to have? ";
    cin >> numFighters;

    Fighterlineup *team1 = new Fighterlineup(team1Name);
    Fighterlineup *team2 = new Fighterlineup(team2Name);
    Fighterlineup *teams[2] = { team1, team2 };
    Fighterlineup *curTeam;
    Loserpile *losers = new Loserpile;
    int selection;
    CREATURES creatureType;
    string creatureName, charaName;
    Creature *creature;

    for (int i = 0; i < 2; i++) {
        curTeam = teams[i];
        cout << "What are the fighting creatures in " << curTeam->getTeamName() << "?" << endl;
        for (int j = 0; j < numFighters; j++) {
            cout << "Please select type for " << curTeam->getTeamName();
            cout << " fighter " << j << ":" << endl;
            cout << "[0] Barbarian, [1] Blue Men, [2] Harry Potter,";
            cout << " [3] Medusa, [4] Vampire" << endl;
            cin >> selection;
            creatureType = static_cast<CREATURES>(selection);
            creatureName = getCreatureString(creatureType);
            cout << "Please enter the " << creatureName << "'s first name: ";
            cin >> charaName;
            creature = initializeCreature(creatureType, creatureName, charaName);
            curTeam->add(creature);
        }
    }
    // cout << "What are the fighting creatures in " << team2Name << "?" << endl;
    // for (int i = 0; i < numFighters; i++) {
    //     cout << "Please select type for creature " << i << ":" << endl;
    //     cout << "[0] Barbarian, [1] Blue Men, [2] Harry Potter, [3] Medusa, [4] Vampire" << endl;
    //     cin >> selection;
    //     creatureType = static_cast<CREATURES>(selection);
    //     creatureName = getCreatureString(creatureType);
    //     cout << "Please enter the " << creatureName << "'s first name: ";
    //     cin >> charaName;
    //     creature = initializeCreature(creatureType, creatureName, charaName);
    //     team2->add(creature);
    // }

    Fighter *fighterRef = team1->getCurrentFighter();
    Creature *crRef;
    cout << endl << "Fighting in " << team1->getTeamName() << ", we have:" << endl;
    while (fighterRef != NULL) {
        crRef = fighterRef->fighter;
        cout << crRef->getCreatureName() << " " << crRef->getCharaName() << "!!!" << endl;
        fighterRef = fighterRef->nextFighter;
    }

    fighterRef = team2->getCurrentFighter();
    cout << endl << "Fighting in " << team2->getTeamName() << ", we have:" << endl;
    while (fighterRef != NULL) {
        crRef = fighterRef->fighter;
        cout << crRef->getCreatureName() << " " << crRef->getCharaName() << "!!!" << endl;
        fighterRef = fighterRef->nextFighter;
    }

    cin.ignore();

    int roundCounter = 1;
    Fighter *team1CurFtr = team1->getCurrentFighter();
    Fighter *team2CurFtr = team2->getCurrentFighter();
    Creature *curCr1;
    Creature *curCr2;
    while ((team1CurFtr != NULL) && (team2CurFtr != NULL)) {
        curCr1 = team1->getCurrentFighter()->fighter;
        curCr2 = team2->getCurrentFighter()->fighter;
        cout << endl << "Starting Round " << roundCounter << "!" << endl;
        cout << "  It's " << curCr1->getCreatureName() << " " << curCr1->getCharaName();
        cout << " vs. " << curCr2->getCreatureName() << " " << curCr2->getCharaName();
        cout << "!!!" << endl;
        playRound(team1, team2, losers);
        team1CurFtr = team1->getCurrentFighter();
        team2CurFtr = team2->getCurrentFighter();
        roundCounter++;
    }
    showWinners(team1, team2);
    showLosers(losers);
    cin.ignore();
    closeGame();
    return 0;
}
