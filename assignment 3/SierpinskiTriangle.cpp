/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the Sierpinski Triangle problem from
 * Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
using namespace std;

/* Main program */

//0.5 is 1/2 wich is sin(30), 0.88 is sqrt(3)/2 which is cos(30)

void drawCenterTriangle(int x, int y, int width, GWindow &gw){
    int yp = y -0.44*width;
    gw.drawLine(x,yp,x-0.5*width,yp+0.88*width);
    gw.drawLine(x,yp,x+0.5*width,yp+0.88*width);
    gw.drawLine(x-0.5*width,yp+0.88*width,x+0.5*width,yp+0.88*width);
}

//calls drawTriangles with 3 different centers, one on top, one on the
//right and one on the left

void drawTriangles(int n, GWindow &gw, int x, int y, int width){
    if(n==0){
        drawCenterTriangle(x,y,width,gw);
    }else{
        drawTriangles(n-1,gw,x,y - 0.33*width, width/2);
        drawTriangles(n-1, gw, x + 0.25*width, y + 0.11*width, width/2);
        drawTriangles(n-1, gw, x - 0.25*width, y + 0.11*width, width/2);
    }
}

int main() {
   GWindow gw(600, 500);
   int height = 200;
   drawTriangles(4,gw,300,250,height);
   return 0;
}
