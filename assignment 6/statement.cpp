/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "tokenscanner.h"
#include "exp.h"
#include "simpio.h"
#include "parser.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}


/* PRINT */
PrintStmt::PrintStmt(Expression *exp){

    this->exp = exp;

}

PrintStmt::~PrintStmt(){
    delete exp;
}

void PrintStmt::execute(EvalState &state){
    cout << exp->eval(state) << endl;
}

std::string PrintStmt::toString(){
    return "PRINT "+exp->toString();
}


/* REM */

RemStmt::RemStmt(std::string comment){
    this->comment = comment;
}

RemStmt::~RemStmt(){

}

void RemStmt::execute(EvalState &state){

}

std::string RemStmt::toString(){
    return "REM "+comment;
}

/* LET */

LetStmt::LetStmt(std::string varName, Expression *expr){
    this->varName = varName;

    exp = expr;
}

LetStmt::~LetStmt(){
    delete exp;
}

void LetStmt::execute(EvalState &state){
    int number = exp->eval(state);
    state.setValue(varName, number);
}

std::string LetStmt::toString(){
    return "LET " + varName + " = " + exp->toString();
}


/* INPUT */

InputStmt::InputStmt(std::string varName){
    this->varName=varName;
}

InputStmt::~InputStmt(){

}

void InputStmt::execute(EvalState &state){
    std::string s = getLine(" ? ");
    int num = stringToInteger(s);
    state.setValue(varName,num);
}

std::string InputStmt::toString(){
    return "INPUT "+varName;
}

/* GOTO */

GotoStmt::GotoStmt(int lineToGo){
    this->lineToGo = lineToGo;
}

GotoStmt::~GotoStmt(){

}

void GotoStmt::execute(EvalState &state){
    state.setCurrentLine(lineToGo);
}

std::string GotoStmt::toString(){
    return "GOTO " + integerToString(lineToGo);
}



/* IF */

IfStmt::IfStmt(Expression *exp, int lineToJump){
    this->lineToJump = lineToJump;
    this->exp = exp;
}

IfStmt::~IfStmt(){
    delete exp;
}

void IfStmt::execute(EvalState &state){
    if(exp->eval(state) == 1)
        state.setCurrentLine(lineToJump);
}

std::string IfStmt::toString(){
    return "IF " + exp->toString() + " THEN " + integerToString(lineToJump);
}

/* END */

EndStmt::EndStmt(){

}

EndStmt::~EndStmt(){

}

void EndStmt::execute(EvalState &state){
    state.setCurrentLine(-1);
}

std::string EndStmt::toString(){
    return "END";
}
