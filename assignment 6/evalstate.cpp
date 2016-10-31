/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include <string>
#include "evalstate.h"
#include "map.h"
using namespace std;

/* Implementation of the EvalState class */

EvalState::EvalState() {
   currLine=-1;
}

EvalState::~EvalState() {
   /* Empty */
}

void EvalState::setValue(string var, int value) {
   symbolTable.put(var, value);
}

int EvalState::getValue(string var) {
   return symbolTable.get(var);
}

bool EvalState::isDefined(string var) {
   return symbolTable.containsKey(var);
}

//sets the current line of the program (for execution or listing)
void EvalState::setCurrentLine(int newLine){
    currLine = newLine;
}

//returns the current line of the program
int EvalState::getCurrentLine(){
    return currLine;
}
