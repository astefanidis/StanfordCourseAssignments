/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */
 
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

const Lexicon english("EnglishWords.dat");

/* Function prototypes */

void welcome();
void giveInstructions();
string checkForConfig();
void initBoard(string s, Grid<char> &board);
void playerTurn(Grid<char> &board, Lexicon &wordsFound);
void computerTurn(Grid<char> &board, Lexicon &playerWords);

/* Main program */

int main() {
   GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
   initGBoggle(gw);
   welcome();
   giveInstructions();
   string s = checkForConfig();
   Grid<char> board(4,4);
   initBoard(s,board);
   Lexicon wordsFound;
   playerTurn(board, wordsFound);
   computerTurn(board, wordsFound);
   return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}

//checks to see if the user wants a custom board or a random one.
string checkForConfig(){
    cout << "If you want to configure your own board";
    cout << "Enter a series of 16 characters. If you want";
    cout << "A randomly generated board, hit enter";
    string s=getLine();
    return s;
}

//initializes the board
void initBoard(string s, Grid<char> &board){
    if(s==""){
        Vector<string> randomCubes;
        for(int i=0;i<16;i++){
            randomCubes.add(STANDARD_CUBES[i]);
        }
        for(int i=0; i<randomCubes.size();i++){
            int rand = randomInteger(i,randomCubes.size()-1);
            string temp = randomCubes[i];
            randomCubes[i] = randomCubes[rand];
            randomCubes[rand] = temp;
        }
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                int rand = randomInteger(0,5);
                board[i][j] = randomCubes.get(4*i+j)[rand];
            }
        }
//if the user wants a custom board he must at least provide 16 chars
    }else{
        while(s.length()<16){
            cout << "the string is too small" << endl;
            s = checkForConfig();
        }
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                board[i][j]=s[4*i+j];
            }

        }

    }

    drawBoard(4,4);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            labelCube(i,j,board[i][j]);
        }
    }
}


//will check if a word exists on the board, if it does it will return the letters used
Vector<Vector<int> > pathExists(Grid<char> &board, string word, Vector<Vector<int> > soFar ){
    if(word.length()==0){
        return soFar;  //if found , return the letters used
    }else{
        if(soFar.isEmpty()){   //if it's the first letter, then just find any letter that matches
            for(int i=0; i<board.height(); i++){
                for(int j=0; j<board.width(); j++){
                    Vector<Vector<int> > next = soFar;  //will hold the updated soFar, so that we preserve the previous
                    if(word[0] == board[i][j]){
                        Vector<int> nextLetter;
                        nextLetter.add(i);
                        nextLetter.add(j);
                        next.add(nextLetter); //add the coordinates of the letter used
                        Vector<Vector<int> > result = pathExists(board, word.substr(1), next);
                        if(result.size()!=0){
                            return result;
                        }
                    }
                }
            }
        }

        else{
            //if it's not the first letter, we have to check all 8 letters around it and see if it matches the char we want
            int prevI = soFar.get(soFar.size()-1)[0];
            int prevJ = soFar.get(soFar.size()-1)[1];
            Vector<Vector<int> > matches;
            if(prevI!=0){
                if(prevJ!=0){
                    if(word[0] == board[prevI-1][prevJ-1]){
                        Vector<int> temp;
                        temp.add(prevI-1);
                        temp.add(prevJ-1);
                        matches.add(temp);
                    }
                }
                if(prevJ!=board.width()-1){
                    if(word[0] == board[prevI-1][prevJ+1]){
                        Vector<int> temp;
                        temp.add(prevI-1);
                        temp.add(prevJ+1);
                        matches.add(temp);
                    }
                }

                if(word[0] == board[prevI-1][prevJ]){
                    Vector<int> temp;
                    temp.add(prevI-1);
                    temp.add(prevJ);
                    matches.add(temp);
                }
            }

            if(prevI!=board.height()-1){
                if(prevJ!=0){
                    if(word[0] == board[prevI+1][prevJ-1]){
                        Vector<int> temp;
                        temp.add(prevI+1);
                        temp.add(prevJ-1);
                        matches.add(temp);
                    }
                }
                if(prevJ!=board.width()-1){
                    if(word[0] == board[prevI+1][prevJ+1]){
                        Vector<int> temp;
                        temp.add(prevI+1);
                        temp.add(prevJ+1);
                        matches.add(temp);
                    }
                }

                if(word[0] == board[prevI+1][prevJ]){
                    Vector<int> temp;
                    temp.add(prevI+1);
                    temp.add(prevJ);
                    matches.add(temp);
                }
            }

            if(prevJ!=0){
                if(word[0] == board[prevI][prevJ-1]){
                    Vector<int> temp;
                    temp.add(prevI);
                    temp.add(prevJ-1);
                    matches.add(temp);
                }
            }

            if(prevJ!=board.width()-1){
                if(word[0] == board[prevI][prevJ+1]){
                    Vector<int> temp;
                    temp.add(prevI);
                    temp.add(prevJ+1);
                    matches.add(temp);
                }
            }

            //check all letters for duplicates (we can't use the same letter-cube again on the same word)
            for(Vector<int> match : matches){
                bool duplicate = false;
                for(int i=0; i<soFar.size(); i++){
                    if(soFar[i].equals(match)){
                        duplicate = true;
                        break;
                    }
                }
                if(!duplicate){  //if it's not a duplicate, find more paths with this letter added
                    Vector<Vector<int> > next = soFar;
                    next.add(match);
                    Vector<Vector<int> > result = pathExists(board, word.substr(1), next);
                    if(result.size()!=0){
                        return result;
                    }
                }
            }
        }
    }
    Vector<Vector<int> > result;
    return result;
}


Vector<Vector<int> > returnPath(Grid<char> &board, string word){  //wrapper function
    Vector<Vector<int> > path;
    path = pathExists(board, word, path);
    return path;
}

void capitalize(string &s){
    for(int i=0; i<s.length(); i++){
        s[i]-=32;
    }
}

void playerTurn(Grid<char> &board, Lexicon &wordsFound){
    cout << "Start giving me the words you found";
    cout << "one at a time. They must be bigger than 3 letters.";
    cout << "After each word, press enter." << endl;
    string s = getLine();
    Vector<Vector<int> > letters;
    capitalize(s);
    while(s!=""){
        if(s.length() < 4){                     //checks if the word the user inputs fits our criteria
            cout << "The word is too small" << endl;
        }else if(!english.contains(s)){
            cout << "This is not a word" << endl;
        }else if(wordsFound.contains(s)){
            cout << "You have already entered this word" << endl;
        }else{
            letters = returnPath(board,s);
            if(letters.size()!=0){
                cout << "Exists!";
                recordWordForPlayer(s,HUMAN);
                wordsFound.add(s);
                for(int i=0;i<letters.size(); i++){
                    highlightCube(letters[i][0], letters[i][1], true);
                }
            }else{
                cout << "The word does not exist on the board" << endl;

            }
        }

        s=getLine();
        capitalize(s);
        for(int i=0;i<letters.size(); i++){
            highlightCube(letters[i][0], letters[i][1], false);
        }

    }
}

//searches all the board. If it finds a word the user hasn't found, it adds it to the Lexicon
void findWords(Grid<char> &board, Lexicon &playerWords, Lexicon &computerWords, Vector<Vector<int> > previousLetters, string wordSoFar){
    if(wordSoFar==""){      //if it's the first letter, serially use all letters on the board
        for(int i=0;i<board.height();i++){
            for(int j=0; j<board.width(); j++){
                Vector<int> letterAdded;
                letterAdded.add(i);
                letterAdded.add(j);
                Vector<Vector<int> > prevLetters = previousLetters;
                prevLetters.add(letterAdded);
                findWords(board, playerWords, computerWords, prevLetters, wordSoFar+board[i][j]);
            }
        }
    }else{  //if it's not the first letter
        Vector<Vector<int> > lettersAround;
        int prevI = previousLetters.get(previousLetters.size()-1)[0];
        int prevJ = previousLetters.get(previousLetters.size()-1)[1];
        //finds all letters around the previous letter
        if(prevI!=0){
            if(prevJ!=0){
                Vector<int> temp;
                temp.add(prevI-1);
                temp.add(prevJ-1);
                lettersAround.add(temp);
            }


            if(prevJ!=board.width()-1){
                Vector<int> temp;
                temp.add(prevI-1);
                temp.add(prevJ+1);
                lettersAround.add(temp);
            }


            Vector<int> temp;
            temp.add(prevI-1);
            temp.add(prevJ);
            lettersAround.add(temp);

        }

        if(prevI!=board.height()-1){
            if(prevJ!=0){
                Vector<int> temp;
                temp.add(prevI+1);
                temp.add(prevJ-1);
                lettersAround.add(temp);
            }
            if(prevJ!=board.width()-1){
                Vector<int> temp;
                temp.add(prevI+1);
                temp.add(prevJ+1);
                lettersAround.add(temp);
            }


            Vector<int> temp;
            temp.add(prevI+1);
            temp.add(prevJ);
            lettersAround.add(temp);

        }

        if(prevJ!=0){
            Vector<int> temp;
            temp.add(prevI);
            temp.add(prevJ-1);
            lettersAround.add(temp);
        }

        if(prevJ!=board.width()-1){
            Vector<int> temp;
            temp.add(prevI);
            temp.add(prevJ+1);
            lettersAround.add(temp);
        }

        for(Vector<int> letter : lettersAround){  //checks for letters already used
            bool duplicate = false;
            for(int i=0; i<previousLetters.size(); i++){
                if(previousLetters[i].equals(letter)){
                    duplicate = true;
                    break;
                }
            }

            if(!duplicate){
                if(wordSoFar.length() >=3){  //if it's a word that fits the criteria, then add it to the words found
                    if(english.contains( wordSoFar + board[letter[0]][letter[1]] ) && !playerWords.contains(wordSoFar + board[letter[0]][letter[1]])
                            && !computerWords.contains(wordSoFar + board[letter[0]][letter[1]])){
                        computerWords.add(wordSoFar + board[letter[0]][letter[1]]);

                    }
                }
                if(english.containsPrefix(wordSoFar + board[letter[0]][letter[1]])){  //if it's
                    Vector<Vector<int> > prevLetters = previousLetters;
                    prevLetters.add(letter);
                    findWords(board, playerWords, computerWords, prevLetters, wordSoFar+board[letter[0]][letter[1]]);
                }
            }
        }




    }
}

void findRemainingWords(Grid<char> &board, Lexicon &playerWords, Lexicon &computerWords){
    Vector<Vector<int> > previousLetter;
    string wordSoFar="";
    findWords(board, playerWords, computerWords, previousLetter, wordSoFar);
}

void computerTurn(Grid<char> &board, Lexicon &playerWords){
    cout << "Good work! Now see how the computer did against you." << endl;
    Lexicon computerWords;
    findRemainingWords(board, playerWords, computerWords);
    for(string w : computerWords){
        recordWordForPlayer(w,COMPUTER);
    }
}


