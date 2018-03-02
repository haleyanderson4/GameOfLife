//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include <iostream>
#include "Bacteria.h"
#include "Mode.h"

using namespace std;

class World
{
  public:
    World(); //blank constructor
    ~World(); //deconstructor
    void setWorldGenerate(int boundary, int output, string name, int columns, int rows, int mode); //overload constructor
    void setWorldTranslate(int boundary, int output, string name, string board, int mode, int c, int r); //overload constructor

    void play();
    void output();

    bool end(Bacteria** oldBoard);

  private:
    Bacteria** gameBoard;

    int bMode;
    int vMode;
    string oFile;
    int iteration;
    int oMode;
    int neighbors;

    string board;
};
