//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include <iostream>
#pragma

using namespace std;

class Mode
{
  public:
    Mode();
    ~Mode();

    void setUp(Bacteria** board, int a, int b, int mode);

    int getNeighbors();
    void setNeighbors(int add);

    void middles(int i, int j);
    void sides(int i, int j);

    void mMode(int i, int j);
    void cMode(int i, int j);
    void dMode(int i, int j);

  private:
    int neighbors;
    int i;
    int j;
    int bMode;

    Bacteria** gameBoard;
};
