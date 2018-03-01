//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include <iostream>

using namespace std;

class Bacteria
{
  public:
    Bacteria(); //constructor
    ~Bacteria(); //deconstructor

    bool getAlive();
    void setAlive(bool status);

    void triggerDeath();
    void triggerLife();

  private:
    bool alive;
};
