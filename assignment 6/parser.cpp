/*
 * File: parser.cpp
 * ----------------
 * Implements the parser.h interface.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "exp.h"
#include "parser.h"
#include "strlib.h"
#include "tokenscanner.h"
#include "program.h"
#include "statement.h"
#include "evalstate.h"
using namespace std;

/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner & scanner) {
   Expression *exp = readE(scanner);
   if (scanner.hasMoreTokens()) {
      error("parseExp: Found extra token: " + scanner.nextToken());
   }
   return exp;
}

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * This version of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each recursive level, the parser reads operators and
 * subexpressions until it finds an operator whose precedence is greater
 * than the prevailing one.  When a higher-precedence operator is found,
 * readE calls itself recursively to read in that subexpression as a unit.
 */

Expression *readE(TokenScanner & scanner, int prec) {
   Expression *exp = readT(scanner);
   string token;
   while (true) {
      token = scanner.nextToken();
      int newPrec = precedence(token);
      if (newPrec <= prec) break;
      Expression *rhs = readE(scanner, newPrec);
      exp = new CompoundExp(token, exp, rhs);
   }
   scanner.saveToken(token);
   return exp;
}

/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner) {
   string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   if (type == WORD) return new IdentifierExp(token);
   if (type == NUMBER) return new ConstantExp(stringToInteger(token));
   if (token != "(") error("Illegal term in expression");
   Expression *exp = readE(scanner);
   if (scanner.nextToken() != ")") {
      error("Unbalanced parentheses in expression");
   }
   return exp;
}

//creates one of the seven possible statements, or returns an error if the input is invalid. Then it adds them to the program
//it also recognizes list, run and clear (help was not implemented for simplicity, it would just be a help message)

void parseStatement(TokenScanner &scanner, Program &program, EvalState &eval){
    string token = scanner.nextToken();
    TokenType type = scanner.getTokenType(token);
    if(type == NUMBER){
        int lineNum = stringToInteger(token);
        if(lineNum<0)
            error("Can't have negative line numbers");
        if(scanner.hasMoreTokens()){
            string nextToken = scanner.nextToken();

            if(nextToken == "LET"){
                string varName = scanner.nextToken();
                string equals = scanner.nextToken();
                if(equals!="=")
                    error("Illegal assignment statement");
                Expression *exp = parseExp(scanner);
                Statement *st = new LetStmt(varName,exp);
                program.addSourceLine(lineNum, st->toString());
                program.setParsedStatement(lineNum,st);

            }else if(nextToken == "PRINT"){
                Expression *expr = parseExp(scanner);
                Statement *st = new PrintStmt(expr);
                program.addSourceLine(lineNum, st->toString());
                program.setParsedStatement(lineNum,st);

            }else if(nextToken == "INPUT"){
                string charName = scanner.nextToken();
                Statement *st = new InputStmt(charName);
                if(scanner.hasMoreTokens())
                    error("Illegal expression");
                program.addSourceLine(lineNum, st->toString());
                program.setParsedStatement(lineNum, st);

            }else if(nextToken == "REM"){
                string comment="";
                while(scanner.hasMoreTokens()){
                    comment+=scanner.nextToken()+ " ";
                }
                Statement *st = new RemStmt(comment);
                program.addSourceLine(lineNum, st->toString());
                program.setParsedStatement(lineNum, st);

            }else if(nextToken == "GOTO"){
                string nextLineS = scanner.nextToken();
                int nextLine  = stringToInteger(nextLineS);
                Statement *st  = new GotoStmt(nextLine);
                program.addSourceLine(lineNum, st->toString());
                program.setParsedStatement(lineNum, st);

            }else if(nextToken == "IF"){
                Expression *exp = readE(scanner,0);
                if(scanner.hasMoreTokens()){
                    string thenToken = scanner.nextToken();
                    if(thenToken=="THEN"){
                        if(scanner.hasMoreTokens()){
                            int jumpLine = stringToInteger(scanner.nextToken());
                            Statement *st = new IfStmt(exp, jumpLine);
                            program.addSourceLine(lineNum, st->toString());
                            program.setParsedStatement(lineNum, st);
                        } else error("No line to jump to");
                    }else error("Invalid syntax: expected 'THEN' token");
                }else error("Invalid syntax: expected 'THEN' token");

            }else if(nextToken == "END"){
                Statement *st = new EndStmt();
                program.addSourceLine(lineNum, st->toString());
                program.setParsedStatement(lineNum, st);
            }

            else{
                error("Unrecoginesed command");
            }
        }else{
            program.removeSourceLine(lineNum);
        }

    }else if(token=="RUN")
        program.run(eval);
    else if(token=="LIST")
        program.list();
    else if(token=="CLEAR")
        program.clear();
    else
        error("Unrecognised command");

}

/*
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */

int precedence(string token) {
   if(token == "<" || token == ">" || token =="=") return 1;
   if (token == "+" || token == "-") return 2;
   if (token == "*" || token == "/") return 3;
   return 0;
}
