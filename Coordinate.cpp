#include "Coordinate.h"
#include <iostream>

using namespace std;

Coordinate::Coordinate() { } //blank constructor

Coordinate::Coordinate(int a, int b) //overload constructor
{
    x = a;
    y = b;
}

~Coordinate() //deconstructor
{
    delete Coordinate;
}

int getX()
{
    return x;
}

int getY()
{
    return y;
}

void setX(int a);
{
    x = a;
}

void setY(int b)
{
    y = b;
}
