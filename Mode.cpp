//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include <iostream>
#include "World.h"

using namespace std;

Mode::Mode() {} //blank constructor

Mode::~Mode() { delete gameBoard; neighbors = 0; }

void Mode::setUp(Bacteria** board, int a, int b, int mode)
{
    for(int i = 0; i < sizeof(board); ++i)
    {
      for(int j = 0; j < sizeof(board[0]); ++j)
      {
        gameBoard[i][j] = board[i][j];
      }
    }
    //intialize the gamebaord

    i = a;
    j = b;
    int bMode = mode;
    //tells it the center location

    if(i != 0 && j != 0 && i != sizeof(gameBoard)-1 && j != sizeof(gameBoard[0])-1) { middles(i, j); }
    else
    {
      if(bMode == 0) { cMode(i, j); } //Classic mode
      else if(bMode == 1) { dMode(i, j); } //Doughnut mode
      else if(bMode == 2) { mMode(i, j); } //Mirror mode
    }
}

void Mode::middles(int i, int j)
{
    if(gameBoard[i-1][j-1].getAlive() == true) { neighbors++; } //lower left diagonal
    if(gameBoard[i-1][j+1].getAlive() == true) { neighbors++; } //lower right diagonal
    if(gameBoard[i][j+1].getAlive() == true) { neighbors++; } //cell directly right
    if(gameBoard[i-1][j].getAlive() == true) { neighbors++; } //cell below
    if(gameBoard[i][j-1].getAlive() == true) { neighbors++; } //cell directly left
    if(gameBoard[i+1][j-1].getAlive() == true) { neighbors++; } //upper left diagonal
    if(gameBoard[i+1][j+1].getAlive() == true) { neighbors++; } //upper right diagonal
    if(gameBoard[i+1][j].getAlive() == true) { neighbors++; } //cell directly above
}

void Mode::cMode(int i, int j)
{
  //hard code the 4 corners
  if(i == 0 && j == 0)
  {
    if(gameBoard[0][1].getAlive() == true) { neighbors++; } //cell directly right
    if(gameBoard[1][1].getAlive() == true) { neighbors++; } //cell diagonal
    if(gameBoard[1][0].getAlive() == true) { neighbors++; } //cell directly below
  }
  if(i == 0 && j == sizeof(gameBoard[0])-1)
  {
    if(gameBoard[0][sizeof(gameBoard[0])-2].getAlive() == true) { neighbors++; } //cell directly left
    if(gameBoard[1][sizeof(gameBoard[0])-1].getAlive() == true) { neighbors++; } //cell directly below
    if(gameBoard[1][sizeof(gameBoard[0])-2].getAlive() == true) { neighbors++; } //cell diagonal
  }
  if(i == sizeof(gameBoard)-1 && j == 0)
  {
    if(gameBoard[sizeof(gameBoard)-1][1].getAlive() == true) { neighbors++; } //cell directly right
    if(gameBoard[sizeof(gameBoard)-2][0].getAlive() == true) { neighbors++; } //cell directly above
    if(gameBoard[sizeof(gameBoard[0])-2][1].getAlive() == true) { neighbors++; } //cell diagonal
  }
  if(i == sizeof(gameBoard)-1 && j == sizeof(gameBoard[0])-1)
  {
    if(gameBoard[sizeof(gameBoard[0])-1][sizeof(gameBoard[0])-2].getAlive() == true) { neighbors++; } //cell left
    if(gameBoard[sizeof(gameBoard[0])-2][sizeof(gameBoard[0])-1].getAlive() == true) { neighbors++; } //cell above
    if(gameBoard[sizeof(gameBoard[0])-2][sizeof(gameBoard[0])-2].getAlive() == true) { neighbors++; } //cell diagonal
  }

  //code all the in between the corners on the sides
  sides(i, j);
}

void Mode::dMode(int i, int j)
{
  //hard code 4 corners
  if(i == 0 && j == 0)
  {
    if(gameBoard[sizeof(gameBoard)-1][j].getAlive() == true){ neighbors++; } //cell above
    if(gameBoard[sizeof(gameBoard)-1][j+1].getAlive() == true) { neighbors++; } //cell upper right diagonal
    if(gameBoard[sizeof(gameBoard)-1][sizeof(gameBoard[0])-1].getAlive() == true){ neighbors++; } //upper left diagonal
    if(gameBoard[i][sizeof(gameBoard[0])-1].getAlive() == true) { neighbors++; } //left
    if(gameBoard[i+1][sizeof(gameBoard[0])-1].getAlive() == true) { neighbors++; } //lower left diagonal
    if(gameBoard[i][j+1].getAlive() == true) { neighbors++; } //cell right
    if(gameBoard[i+1][j+1].getAlive() == true) { neighbors++; } //cell lower right diagonal
    if(gameBoard[i+1][j].getAlive() == true) { neighbors++; } //cell below
  }

  if(i == 0 && j == sizeof(gameBoard[0])-1)
  {
    if(gameBoard[i+1][j].getAlive() == true) { neighbors++; } //cell below
    if(gameBoard[i+1][j-1].getAlive() == true) { neighbors++; } //cell lower left diagonal
    if(gameBoard[i+1][0].getAlive() == true) { neighbors++; } //lower right diagonal
    if(gameBoard[i][j-1].getAlive() == true) { neighbors++; } //cell left
    if(gameBoard[i][0].getAlive() == true) { neighbors++; } //cell right
    if(gameBoard[sizeof(gameBoard)-1][j].getAlive() == true) { neighbors++; } //cell above
    if(gameBoard[sizeof(gameBoard)-1][j-1].getAlive() == true) { neighbors++; } //cell upper left diagonal
    if(gameBoard[sizeof(gameBoard)-1][0].getAlive() == true) { neighbors++; } //upper right diagonal
  }

  if(i == sizeof(gameBoard)-1 && j == 0)
  {
    if(gameBoard[i][j+1].getAlive() == true) { neighbors++; } //cell left
    if(gameBoard[i][sizeof(gameBoard[0])-1].getAlive() == true) { neighbors++; } //cell right
    if(gameBoard[0][j].getAlive() == true) { neighbors++; } //cell below
    if(gameBoard[0][j+1].getAlive() == true) { neighbors++; } //cell lower right
    if(gameBoard[i-1][j].getAlive() == true) { neighbors++; } //cell above
    if(gameBoard[i-1][j+1].getAlive() == true) { neighbors++; } //cell upper right diagonal
    if(gameBoard[sizeof(gameBoard)-1][sizeof(gameBoard[0])-1].getAlive() == true) { neighbors++; } //cell lower left diagonal
    if(gameBoard[i-1][sizeof(gameBoard[0])-1].getAlive() == true) { neighbors++; } //cell upper left diagonal
  }

  if(i == sizeof(gameBoard)-1 && j == sizeof(gameBoard[0])-1)
  {
    if(gameBoard[i][j-1].getAlive() == true) { neighbors++; } //cell left
    if(gameBoard[i-1][j].getAlive() == true) { neighbors++; } //cell above
    if(gameBoard[i-1][j-1].getAlive() == true) { neighbors++; } //cell left upper diagonal
    if(gameBoard[i][0].getAlive() == true) { neighbors++; } //cell right
    if(gameBoard[i-1][0].getAlive() == true) { neighbors++; } //cell upper left diagonal
    if(gameBoard[0][j].getAlive() == true) { neighbors++; } //cell below
    if(gameBoard[0][j-1].getAlive() == true) { neighbors++; } //cell lower left diagonal
    if(gameBoard[0][0].getAlive() == true) { neighbors++; } //cell lower right diagonal
  }

  //code all the in between the corners on the sides with the extra for Doughnut
  sides(i, j);
  if(i == 0 && j != 0 && j != sizeof(gameBoard[0])-1)
  {
    if(gameBoard[sizeof(gameBoard)-1][j-1].getAlive() == true) { neighbors++; } //cell upper left
    if(gameBoard[sizeof(gameBoard)-1][j].getAlive() == true) { neighbors++; } //cell above
    if(gameBoard[sizeof(gameBoard)-1][j+1].getAlive() == true) { neighbors++; } //cell upper right
  }

  if(i == sizeof(gameBoard)-1 && j != 0 && j != sizeof(gameBoard[0])-1)
  {
    if(gameBoard[0][j-1].getAlive() == true) { neighbors++; } //cell lower left diagonal
    if(gameBoard[0][j].getAlive() == true) { neighbors++; } //cell below
    if(gameBoard[0][j+1].getAlive() == true) { neighbors++; } //cell lower right diagonal
  }

  if(i != 0 && i != sizeof(gameBoard)-1 && j == 0)
  {
    if(gameBoard[i-1][sizeof(gameBoard[0])-1].getAlive() == true) { neighbors++; } //cell upper left diagonal
    if(gameBoard[i][sizeof(gameBoard[0])-1].getAlive() == true) { neighbors++; } //cell left
    if(gameBoard[i+1][sizeof(gameBoard[0])-1].getAlive() == true) { neighbors++; } //cell lower left diagonal
  }

  if(i != 0 && i != sizeof(gameBoard)-1 && j == sizeof(gameBoard[0])-1)
  {
    if(gameBoard[i-1][0].getAlive() == true) { neighbors++; } //cell upper right diagonal
    if(gameBoard[i][0].getAlive() == true) { neighbors++; } //cell lower right
    if(gameBoard[i+1][0].getAlive() == true) { neighbors++; } //cell lower right diagonal
  }
}

void Mode::mMode(int i, int j)
{
  if(i == 0 && j == 0)
  {
    if(gameBoard[i][j].getAlive() == true) { neighbors += 3; } //because its own reflection counts as 3, left, above, diagonal
    if(gameBoard[i][j+1].getAlive() == true) { neighbors += 2; } //bc left counts as 2
    if(gameBoard[i+1][j].getAlive() == true) { neighbors += 2; } //bc below counts as 2
    if(gameBoard[i+1][j+1].getAlive() == true) { neighbors++; } //bc diagonal is only 1, no reflection
  }

  if (i == 0 && j == sizeof(gameBoard[0])-1)
  {
    if(gameBoard[i][j].getAlive() == true) { neighbors += 3; } //because its own reflection counts as 3, left, above, diagonal
    if(gameBoard[i][j-1].getAlive() == true) { neighbors += 2; } //bc left counts as 2
    if(gameBoard[i+1][j].getAlive() == true) { neighbors += 2; } //bc below counts as 2
    if(gameBoard[i+1][j-1].getAlive() == true) { neighbors++; } //bc diagonal is only 1, no reflection
  }

  if(i == sizeof(gameBoard)-1 && j == 0)
  {
    if(gameBoard[i][j].getAlive() == true) { neighbors += 3; } //because its own reflection counts as 3, left, above, diagonal
    if(gameBoard[i-1][j].getAlive() == true) { neighbors += 2; } //bc above counts as 2
    if(gameBoard[i][j+1].getAlive() == true) { neighbors += 2; } //bc right counts as 2
    if(gameBoard[i-1][j+1].getAlive() == true) { neighbors++; } //bc diagonal is only 1, no reflection
  }

  if(i == sizeof(gameBoard)-1 && j == sizeof(gameBoard[0])-1)
  {
    if(gameBoard[i][j].getAlive() == true) { neighbors += 3; } //because its own reflection counts as 3, left, above, diagonal
    if(gameBoard[i][j-1].getAlive() == true) { neighbors += 2; } //bc left counts as 2
    if(gameBoard[i+1][j].getAlive() == true) { neighbors += 2; } //bc above counts as 2
    if(gameBoard[i-1][j-1].getAlive() == true) { neighbors++; } //bc diagonal is only 1, no reflection
  }

  sides(i, j);
  //all the extra sides for mirror mode
  if((i == 0 || i == sizeof(gameBoard)-1) && j != 0 && j != sizeof(gameBoard[0])-1)
  {
    //top & bottom sides
    if(gameBoard[i][j-1].getAlive() == true) { neighbors++; } //cell right diagonal
    if(gameBoard[i][j+1].getAlive() == true) { neighbors++; } //cell left diagonal
  }

  if(i != 0 && i != sizeof(gameBoard)-1 && (j == 0 || j == sizeof(gameBoard[0])-1) )
  {
    //left & right sides
    if(gameBoard[i+1][j].getAlive() == true) { neighbors++; } //cell left diagonal
    if(gameBoard[i-1][j].getAlive() == true) { neighbors++; } //cell right diagonal
  }
}

void Mode::sides(int i, int j)
{
  if(bMode == 2)
  {
    if(gameBoard[i][j].getAlive() == true) { neighbors++; } //cell reflection on self for mirror mode
  }

  //code all the in between the corners on the sides
  if(i == 0 && j != 0 && j != sizeof(gameBoard[0])-1)
  {
    if(gameBoard[i][j+1].getAlive() == true) { neighbors++; } //cell right
    if(gameBoard[i][j-1].getAlive() == true) { neighbors++; } //cell left
    if(gameBoard[i+1][j-1].getAlive() == true) { neighbors++; } //cell lower left
    if(gameBoard[i+1][j].getAlive() == true) { neighbors++; } //cell below
    if(gameBoard[i+1][j+1].getAlive() == true) { neighbors++; } //cell lower right
  }

  if(i == sizeof(gameBoard)-1 && j != 0 && j != sizeof(gameBoard[0])-1)
  {
    if(gameBoard[i][j+1].getAlive() == true) { neighbors++; } //cell right
    if(gameBoard[i][j-1].getAlive() == true) { neighbors++; } //cell left
    if(gameBoard[i-1][j-1].getAlive() == true) { neighbors++; } //cell upper left
    if(gameBoard[i-1][j].getAlive() == true) { neighbors++; } //cell above
    if(gameBoard[i-1][j+1].getAlive() == true) { neighbors++; } //cell upper right
  }

  if(i != 0 && i != sizeof(gameBoard)-1 && j == 0)
  {
    if(gameBoard[i][j+1].getAlive() == true) { neighbors++; } //cell right
    if(gameBoard[i+1][j].getAlive() == true) { neighbors++; } //cell below
    if(gameBoard[i-1][j].getAlive() == true) { neighbors++; } //cell above
    if(gameBoard[i-1][j+1].getAlive() == true) { neighbors++; } //cell upper right
    if(gameBoard[i+1][j+1].getAlive() == true) { neighbors++; } //cell lower right
  }

  if(i != 0 && i != sizeof(gameBoard)-1 && j == sizeof(gameBoard[0])-1)
  {
    if(gameBoard[i][j-1].getAlive() == true) { neighbors++; } //cell left
    if(gameBoard[i+1][j].getAlive() == true) { neighbors++; } //cell below
    if(gameBoard[i-1][j].getAlive() == true) { neighbors++; } //cell above
    if(gameBoard[i-1][j-1].getAlive() == true) { neighbors++; } //cell upper left
    if(gameBoard[i+1][j-1].getAlive() == true) { neighbors++; } //cell lower left
  }
}

int Mode::getNeighbors() { return neighbors; }

void Mode::setNeighbors(int add) { neighbors += add; }
