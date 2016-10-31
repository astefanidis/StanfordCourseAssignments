/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
   programList = NULL;
   firstLine = -1;
}

Program::~Program() {
    delete programList;
}

void Program::clear() {
   listItem *newList = new listItem;
   newList = NULL;
   delete programList;
   programList = newList;
   firstLine = -1;
}


void Program::addSourceLine(int lineNumber, string line) {
   if(line == "")
       removeSourceLine(lineNumber);
   else{
       listItem *curr = new listItem;
       listItem *prev =  new listItem;
       listItem *newEntry = new listItem;
       newEntry->lineNumber = lineNumber;
       newEntry->sourceStatement = line;
       prev=NULL;

       //if it's the first entry, then add it to the first position
       if(firstLine == -1){
           firstLine = lineNumber;
           programList = new listItem;
           programList->lineNumber=lineNumber;
           programList->sourceStatement=line;
           programList->next=NULL;
       }else{
           for(curr = programList; curr!=NULL; curr = curr->next){
                if(curr->lineNumber >= lineNumber) break;
                prev = curr;
           }

           //if it already exists, replace it
           if(curr!=NULL && curr->lineNumber == lineNumber){

                   curr->sourceStatement = line;
                   curr->parsedStatement = NULL;

           }else{

               //if it goes to the first position
               if(prev==NULL){
                    newEntry->next = programList;
                    programList = newEntry;
               }else if(curr==NULL){
                   //if it goes to the last position
                   prev->next = newEntry;
                   newEntry->next = NULL;
               }else{
                   prev->next = newEntry;
                   newEntry->next = curr;
               }
           }



       }
       if(firstLine > lineNumber){
           firstLine = lineNumber;
       }

   }



}

void Program::removeSourceLine(int lineNumber) {
    listItem *curr = new listItem;
    listItem *prev =  new listItem;
    prev = NULL;
    for(curr = programList; curr!=NULL; curr = curr->next){
         if(curr->lineNumber == lineNumber) break;
         prev = curr;
    }
    if(curr != NULL){
        //if it's the first
        if(prev == NULL){
            //if it's the only one in the list (no previous or next item)
            if(curr->next==NULL){
                delete programList;
                firstLine = -1;
            }else{
                listItem *newOne = new listItem;
                newOne = programList->next;
                delete programList;
                programList = newOne;
                firstLine = programList->lineNumber;
            }

        }else{
            prev->next = curr->next;
            delete curr;
        }
    }
}

string Program::getSourceLine(int lineNumber) {
   listItem *i = new listItem;
   for(i = programList; i!=NULL; i=i->next){
       if(i->lineNumber==lineNumber) break;
   }
   if(i==NULL) return "";
   else return i->sourceStatement;
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    listItem *i = new listItem;
    for(i = programList; i!=NULL; i=i->next){
        if(i->lineNumber==lineNumber) break;
    }
    if(i==NULL) error("This statement does not exist");
    i->parsedStatement=stmt;

}

Statement *Program::getParsedStatement(int lineNumber) {
    listItem *i = new listItem;
    for(i = programList; i!=NULL; i=i->next){
        if(i->lineNumber==lineNumber) break;
    }
    if(i==NULL) return NULL;
    else return i->parsedStatement;

}

int Program::getFirstLineNumber() {
   return firstLine;
}

int Program::getNextLineNumber(int lineNumber) {
    listItem *i = new listItem;
    for(i = programList; i!=NULL; i=i->next){
        if(i->lineNumber>lineNumber) break;
    }
    if(i==NULL) return -1;
    return i->lineNumber;
}

void Program::run(EvalState &eval){
    if(firstLine==-1){
        error("No program to run");
    }else{
        eval.setCurrentLine(firstLine);
        while(eval.getCurrentLine()!=-1){

            if(getParsedStatement(eval.getCurrentLine())!=NULL){
                int currLine = eval.getCurrentLine();
                Statement *newStatement = getParsedStatement(eval.getCurrentLine());
                newStatement->execute(eval);


                if(currLine == eval.getCurrentLine()) //the line will only be changed in goto, if and end, we don't want
                                                      //to fetch a new line in this case
                    eval.setCurrentLine(getNextLineNumber(eval.getCurrentLine()));
            }else{
                error("The line does not exist: " + integerToString(eval.getCurrentLine()));
            }

        }
    }

}

void Program::list(){
    if(firstLine==-1){
        error("No program to display");
    }else{
        listItem *i = new listItem;
        for(i = programList; i!=NULL; i=i->next){
            cout << i->lineNumber << " " << i->sourceStatement << endl;
        }
    }

}
