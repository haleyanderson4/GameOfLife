//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include "Bacteria.h"
#include <iostream>

using namespace std;

Bacteria::Bacteria() { alive = false; } //constructor

Bacteria::~Bacteria() { delete this; }

bool Bacteria::getAlive() { return alive; }

void Bacteria::setAlive(bool status) { alive = status; }

void Bacteria::triggerDeath() { alive = false; }

void Bacteria::triggerLife() { alive = true; }

//bacteria is a thing basically that just stores the alvie boolean, but its easier to have an
//object so i dont mess up the alvie vs dead
