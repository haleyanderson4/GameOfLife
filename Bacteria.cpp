//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include "Bacteria.h"
#include "Coordinate.h"
#include <iostream>

using namespace std;

Bacteria::Bacteria() //constructor
{
    alive = false;
}

Bacteria::~Bacteria()
{
    delete Bacteria;
}

bool Bacteria::getAlive()
{
    return alive;
}

bool Bacteria::setAlive(bool status)
{
    alive = status;
}

void Bacteria::triggerDeath(Coordinate coor)
{
    alive = false;
}

void Bacteria::triggerLife(Coordinate coor)
{
    alive = true;
}
