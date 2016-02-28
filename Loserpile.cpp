/*******************************************************************************
** Author: Patrick Armitage
** Date: 02/22/2016
** Description: Loserpile methods file which defines the methods of the
** Loserpile class that were prototyped within the Loserpile header file
*******************************************************************************/
#include <iostream>

#include "Loserpile.hpp"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------------*/
/*
    Function Name: Loserpile
    Function Parameters: N/A
    What the function does: sets current loser to NULL
*/
Loserpile::Loserpile() {
    setCurrentLoser(NULL);
}

/*----------------------------------------------------------------------------*/
/*
    Function Names: setCurrentLoser, getCurrentLoser
    Functions' Parameters: setter receives Loser struct param for queue loser
    What the functions do: getter and setter which act as public options to
                           read/write the Loserpile class's private loser
*/
void Loserpile::setCurrentLoser(Loser *loser) {
    currentLoser = loser;
}

Loser *Loserpile::getCurrentLoser() {
    return currentLoser;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: add
    Function Parameters: loser Creature object
    What the function does: initializes a new Loser struct setting its loser to
                            the provided Creature pointer.  Then gets the pile's
                            current loser, setting it as the new loser's prev
                            loser, and sets new loser as the current loser.
*/
void Loserpile::add(Creature *loser) {
    Loser *stackLoser = new Loser;
    Loser *currLoser = getCurrentLoser();
    stackLoser->previousLoser = currLoser;
    stackLoser->loser = loser;
    setCurrentLoser(stackLoser);
    cout << "Added " << getCurrentLoser()->loser->getCreatureName() << " ";
    cout << getCurrentLoser()->loser->getCharaName() << " to the Loserpile!" << endl;
}

/*----------------------------------------------------------------------------*/
/*
    Function Name: remove
    Function Parameters: N/A
    What the function does: gets the current pile loser and the previos loser from
                            the current loser, then sets the previous loser as the
                            new current loser, deleting the old current loser and
                            returning its loser Creature pointer
*/
Creature *Loserpile::remove() {
    Loser *currLoser = getCurrentLoser();
    Loser *prevLoser = currLoser->previousLoser;

    setCurrentLoser(prevLoser);
    Creature *loser = currLoser->loser;
    delete currLoser;
    return loser;
}
