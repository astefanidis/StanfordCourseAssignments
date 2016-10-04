/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include <string>
using namespace std;

void lowerCase(string &word){
    for(int i=0; i<word.length(); i++){
        word[i] = tolower(word[i]);
    }
}

Vector<string> findLadder(Lexicon &english, string wordBegin, string wordEnd){
    Vector<string> result;
    lowerCase(wordBegin);  //in case it has uppercase, to avoid checking uppercase separately
    lowerCase(wordEnd);
    Lexicon checked;      //the words we already checked
    checked.add(wordBegin);
    Queue<Vector<string> > ladderQueue;  //a queue containing all the possible ladders
    Vector<string> currentLadder;        //the ladder we are examining at the time
    currentLadder.add(wordBegin);
    ladderQueue.enqueue(currentLadder);

    while(!ladderQueue.isEmpty()){    //while there are still ladders to be checked
        currentLadder = ladderQueue.dequeue();
        string initWord = currentLadder[currentLadder.size()-1];  //the word we will check for new ladders is always the last one
        if(initWord == wordEnd){
            result = currentLadder;
            break;
        }

        for(int i=0; i<initWord.length(); i++){
            string changedWord = initWord;   //the word we will change, we want to keep the original as well
            for(char c='a'; c<='z'; c++){
                changedWord[i] = c;
                if(english.contains(changedWord) && !checked.contains(changedWord)){  //if it exists and we haven't already seen it
                    Vector<string> newLadder = currentLadder;
                    newLadder.add(changedWord);  //create a copy of the ladder with this word in its end
                    ladderQueue.enqueue(newLadder);
                    checked.add(changedWord);
                    if(changedWord == wordEnd){
                        result = newLadder;
                        break;
                    }
                }
            }
        }


    }

    return result;
}

int main() {

    Lexicon english("EnglishWords.txt");
    string exitCheck = " ";
    while(true){
        cout << "Enter start word (RETURN to quit): ";
        string startWord = getLine();
        if(startWord.length() == 0){
            break;
        }
        cout << "Enter destination word: ";
        string dest = getLine();
        Vector<string> result = findLadder(english, startWord, dest);
        if(result.size()==0){
            cout << "\nNo ladder found" << endl;
        }else{
            cout << "Found ladder: ";
            for(string s : result){
                cout << s << " ";
            }
        }
        cout << endl;
    }

	return 0;
}
