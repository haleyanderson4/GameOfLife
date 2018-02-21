//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include <iostream>
#include "Bacteria.h"
#include "Coordinate.h"

using namespace std;

class World
{
  public:
    World(); //blank constructor
    World(Bacteria [] board, int boundary, int output, string name); //overload constructor
    ~World(); //deconstructor

    void play();
    void output();

  private:
    Bacteria [] gameBoard;
    Bacteria [] tempBoard;

    int bMode;
    int vMode;
    string oFile;
    int iteration;
}
