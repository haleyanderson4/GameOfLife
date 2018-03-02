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
    void setWorld(int boundary, int output, string name, int columns, int rows, int timeO, int mode); //overload constructor
    void setWorldTranslate(int boundary, int output, string name, string insides, int timeO, int mode, int c, int r); //overload constructor

    void play();
    void output();

    void generateGameMap(Bacteria** gameBoard);
    void translateGameMap(string fileName);

    bool end(Bacteria** oldBoard);

  private:
    Bacteria** gameBoard;

    int bMode;
    int vMode;
    string oFile;
    int iteration;
    int timeOut;
    int oMode;
    int neighbors;

    int rowT;
    int columnT;
    string board;
};
