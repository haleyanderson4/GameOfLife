//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include <iostream>
#include "Coordinate.h"

using namespace std;

class Bacteria
{
  public:
    Bacteria(); //constructor
    ~Bacteria(); //deconstructor

    bool getAlive();
    void setAlive(bool status);

    void triggerDeath(Coordinate coor);
    void triggerLife(Coordinate coor);

  private:
    bool alive;
}




//Next step is to make a list of all the functions and features i need to implement
//and then go through and check the ones that are "done" and make a to do list of things
//that need to be fix
//also create a makefile
