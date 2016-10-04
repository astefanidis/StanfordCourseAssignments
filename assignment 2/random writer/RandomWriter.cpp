/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "simpio.h"
#include "filelib.h"
using namespace std;

void removeNewLines(string &s){
    for(int i=0; i<s.length(); i++){
        if(s[i]=='\n'){
            s.replace(i,1," ");
        }
    }
}

void printMarkov(string &contents, int order){
    Map<string, int> freq;   //contains the frequency of the appearance of every seed
    Map<string, Vector<char> > seeds; //contains the characters that follow each seed
    removeNewLines(contents);  //removes newlines from the string
    for(int i=0; i<=contents.length() - order; i++){ //adds each seed to the maps
        string seed = contents.substr(i , order);
        if(freq.containsKey(seed)){
            freq[seed]++;
        }
        else{
            freq[seed] = 1;
        }
        if(i!=contents.length()-order){ //if it is the last string of the file, we don't want to check the next letter because there is none
            seeds[seed].add(contents[i+order]);
        }
    }

    string currSeed;
    string maxFreqSeed;
    int maxFreq=-1;
    for(string s : freq){  //finds the seed with the biggest frequency so that the program can begin
        if(freq[s] > maxFreq){
            maxFreq = freq[s];
            maxFreqSeed = s;
        }
    }

    currSeed = maxFreqSeed;
    cout << currSeed;
    for(int i=order; i<2000; i++){
        if(!seeds.containsKey(currSeed))  //if the currSeed only appears as the last of the file then we can exit
            break;
        int rand = randomInteger(0,seeds[currSeed].size()-1);
        cout << seeds[currSeed].get(rand);  //randomly selects the next char and prints it

        currSeed = currSeed.substr(1,string::npos) + seeds[currSeed].get(rand); //updates the currSeed

    }


}

int main() {

    ifstream in;
    string filename = promptUserForFile(in, "Give me the file name: ", "Wrong name, try again: ");
    string fileContents = readEntireFile(filename);
    cout << "Give me the order of the Markov sequence: ";
    int x;
    cin >> x;
    cout << endl;
    printMarkov(fileContents, x);

	return 0;
}
