//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include <iostream>
#include "Bacteria.h"

using namespace std;

class World
{
  public:
    World(); //blank constructor
    World(int boundary, int output, string name, int columns, int rows, int timeO, int mode); //overload constructor
    World(int boundary, int output, string name, string fileName, int timeO, int mode); //overload constructor
    ~World(); //deconstructor

    void play();
    void output();

    void middles(int i, int j);
    void sides(int i, int j);

    void mMode(int i, int j);
    void cMode(int i, int j);
    void dMode(int i, int j);

    void getRowsAndColumns(string fileName);
    void generateGameMap(Bacteria** gameBoard);
    void translateGameMap(string fileName);

    bool end();

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
