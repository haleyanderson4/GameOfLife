//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include "World.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>

using namespace std;

World::World() {} //blank constructor

World::World(Bacteria** board, int boundary, int output, string name) //constructor
{
    bMode = boundary;
    vMode = output;
    oFile = name;
    iteration = 0;

    Bacteria** gameBoard = new Bacteria* [board.length()];
    Bacteria** tempBoard = new Bacteria* [board.length()];
    for(int i = 0; i < board.length(); i++)
    {
      gameBoard[i] = new Bacteria [board[].length()];
      tempBoard[i] = new Bacteria [board[].length()];
      //to make the 2d arrays
    }

    for(int i = 0; i < board.length(); i++)
    {
      for(int j = 0; j < board[].length(); j++)
      {
        gameBoard[i][j] = board[i][j];
        tempBoard[i][j] = board[i][j];
        //to intialize the gameBoard and the tempBoard as the map the player requested
      }
    }
}

World::~World()
{
    delete [] gameBoard;
    delete [] tempBoard;
}

void World::play()
{
    //where all the rules about living and dying goes

    for(int i = 0; i < gameBoard.length(); ++i)
    {
      for(int j = 0; j < gameBoard[].length(); ++j)
      {
          int neighbors = 0;

          if(i != 0 && j != 0 && i != gameBoard.length()-1 && j != gameBoard[].length()-1) { middles(); }
          else
          {
            if(bMode == 0) { cMode(); } //Classic mode
            else if(bMode == 1) { dMode(); } //Doughnut mode
            else if(bMode == 2) { mMode(); } //Mirror mode
          }

          if(neighbors < 2 || neighbors > 3) { tempBoard[i][j].triggerDeath(); }
          if(neighbors == 3) { tempBoard[i][j].triggerLife(); }
      }
    }

    for(int i = 0; i < gameBoard.length(); ++i)
    {
      for(int j = 0; j <gameBoard[].length(); ++j) { gameBoard[i][j] = tempBoard[i][j]; }
    }
}

void World::output()
{
    iteration++;
    string results = "\nCycle number " + (string)(iteration) + ":\n";
    for(int i = 0; i < gameBoard.length(); i++)
    {
      for(int j  0; j < gameBoard[].length(); j++)
      {
          if(gameBoard[i][j].getAlive()) { results += "X"; }
          else { results += "-"; }
      }
      results += "\n";
    }
    //to create the visual representation of the game board

    if(oMode == 2)
    {
      //output file
      ofstream outputFile;
      outputFile.open(oFile.out);
      outputFile << results << endl;
      outputFile.close();
    }
    else
    {
      //print results here
      cout<< results << endl;

      if(oMode == 0)
      {
        //pause
        //Sleep(1000);
        this_thread::sleep_for(std::chrono::milliseconds(2000));
      }
      if(oMode == 1)
      {
        //enter
        string whatever;
        cout<< "Please press enter to continue to the next generation." << endl;
        cin>> whatever;
      }
    }
}

void World::middles()
{
    if(gameBoard[i-1][j-1].getAlive()) { neighbors++; } //lower left diagonal
    if(gameBoard[i-1][j+1].getAlive()) { neighbors++; } //lower right diagonal
    if(gameBoard[i][j+1].getAlive()) { neighbors++; } //cell directly right
    if(gameBoard[i-1][j].getAlive()) { neighbors++; } //cell below
    if(gameBoard[i][j-1].getAlive()) { neighbors++; } //cell directly left
    if(gameBoard[i+1][j-1].getAlive()) { neighbors++; } //upper left diagonal
    if(gameBoard[i+1][j+1].getAlive()) { neighbors++; } //upper right diagonal
    if(gameBoard[i+1][j].getAlive()) { neighbors++; } //cell directly above
}

void World::cMode()
{
  //hard code the 4 corners
  if(i == 0 && j == 0)
  {
    if(gameBoard[0][1].getAlive()) { neighbors++; } //cell directly right
    if(gameBoard[1][1].getAlive()) { neighbors++; } //cell diagonal
    if(gameBoard[1][0].getAlive()) { neighbors++; } //cell directly below
  }
  if(i == 0 && j == gameBoard[].length()-1)
  {
    if(gameBoard[0][gameBoard[].length()-2].getAlive()) { neighbors++; } //cell directly left
    if(gameBoard[1][gameBoard[].length()-1].getAlive()) { neighbors++; } //cell directly below
    if(gameBoard[1][gameBoard[].length()-2].getAlive()) { neighbors++; } //cell diagonal
  }
  if(i == gameBoard.length()-1 && j == 0)
  {
    if(gameBoard[gameBoard.length()-1][1].getAlive()) { neighbors++; } //cell directly right
    if(gameBoard[gameBoard.length()-2][0].getAlive()) { neighbors++; } //cell directly above
    if(gameBoard[gameBoard[].length()-2][1].getAlive()) { neighbors++; } //cell diagonal
  }
  if(i == gameBoard.length()-1 && j == gameBoard[].length()-1)
  {
    if(gameBoard[gameBoard[].length()-1][gameBoard[].length()-2].getAlive()) { neighbors++; } //cell left
    if(gameBoard[gameBoard[].length()-2][gameBoard[].length()-1].getAlive()) { neighbors++; } //cell above
    if(gameBoard[gameBoard[].length()-2][gameBoard[].length()-2].getAlive()) { neighbors++; } //cell diagonal
  }

  //code all the in between the corners on the sides
  sides();
}

void World::dMode()
{
  //hard code 4 corners
  if(i == 0 && j == 0)
  {
    if(gameBoard[gameBoard.length()-1][j].getAlive()){ neighbors++; } //cell above
    if(gameBoard[gameBoard.length()-1][j+1].getAlive()) { neighbors++; } //cell upper right diagonal
    if(gameBoard[gameBoard.length()-1][gameBoard[].length()-1]].getAlive()){ neighbors++; } //upper left diagonal
    if(gameBoard[i][gameBoard[].length()-1].getAlive()) { neighbors++; } //left
    if(gameBoard[i+1][gameBoard[].length()-1].getAlive()) { neighbors++; } //lower left diagonal
    if(gameBoard[i][j+1].getAlive()) { neighbors++; } //cell right
    if(gameBoard[i+1][j+1].getAlive()) { neighbors++; } //cell lower right diagonal
    if(gameBoard[i+1][j].getAlive()) { neighbors++; } //cell below
  }

  if(i == 0 && j == gameBoard[].length()-1)
  {
    if(gameBoard[i+1][j].getAlive()) { neighbors++; } //cell below
    if(gameBoard[i+1][j-1].getAlive()) { neighbors++; } //cell lower left diagonal
    if(gameBoard[i+1][0].getAlive()) { neighbors++; } //lower right diagonal
    if(gameBoard[i][j-1].getAlive()) { neighbors++; } //cell left
    if(gameBoard[i][0].getAlive()) { neighbors++; } //cell right
    if(gameBoard[gameBoard.length()-1][j].getAlive()) { neighbors++; } //cell above
    if(gameBoard[gameBoard.length()-1][j-1].getAlive()) { neighbors++; } //cell upper left diagonal
    if(gameBoard[gameBoard.length()-1][0].getAlive()) { neighbors++; } //upper right diagonal
  }

  if(i == gameBoard.length()-1 && j == 0)
  {
    if(gameBoard[i][j+1].getAlive()) { neighbors++; } //cell left
    if(gameBoard[i][gameBoard[].length()-1].getAlive()) { neighbors++; } //cell right
    if(gameBoard[0][j].getAlive()) { neighbors++; } //cell below
    if(gameBoard[0][j+1].getAlive()) { neighbors++; } //cell lower right
    if(gameBoard[i-1][j].getAlive()) { neighbors++; } //cell above
    if(gameBoard[i-1][j+1].getAlive()) { neighbors++; } //cell upper right diagonal
    if(gameBoard[gameBoard.length()-1][gameBoard[].length()-1].getAlive()) { neighbors++; } //cell lower left diagonal
    if(gameBoard[i-1][gameBoard[].length()-1].getAlive()) { neighbors++; } //cell upper left diagonal
  }

  if(i == gameBoard.length()-1 && j == gameBoard[].length()-1)
  {
    if(gameBoard[i][j-1].getAlive()) { neighbors++; } //cell left
    if(gameBoard[i-1][j].getAlive()) { neighbors++; } //cell above
    if(gameBoard[i-1][j-1].getAlive()) { neighbors++; } //cell left upper diagonal
    if(gameBoard[i][0].getAlive()) { neighbors++; } //cell right
    if(gameBoard[i-1][0].getAlive()) { neighbors++; } //cell upper left diagonal
    if(gameBoard[0][j].getAlive()) { neighbors++; } //cell below
    if(gameBoard[0][j-1].getAlive()) { neighbors++; } //cell lower left diagonal
    if(gameBoard[0][0].getAlive()) { neighbors++; } //cell lower right diagonal
  }

  //code all the in between the corners on the sides with the extra for Doughnut
  sides();
  if(i == 0 && j != 0 && j != gameBoard[].length()-1)
  {
    if(gameBoard[gameBoard.length()-1][j-1].getAlive()) { neighbors++; } //cell upper left
    if(gameBoard[gameBoard.length()-1][j].getAlive()) { neighbors++; } //cell above
    if(gameBoard[gameBoard.length()-1][j+1].getAlive()) { neighbors++; } //cell upper right
  }

  if(i == gameBoard.length()-1 && j != 0 && j != gameBoard[].length()-1)
  {
    if(gameBoard[0][j-1].getAlive()) { neighbors++; } //cell lower left diagonal
    if(gameBoard[0][j].getAlive()) { neighbors++; } //cell below
    if(gameBoard[0][j+1].getAlive()) { neighbors++; } //cell lower right diagonal
  }

  if(i != 0 && i != gameBoard.length()-1 && j == 0)
  {
    if(gameBoard[i-1][gameBoard[].length()-1].getAlive()) { neighbors++; } //cell upper left diagonal
    if(gameBoard[i][gameBoard[].length()-1].getAlive()) { neighbors++; } //cell left
    if(gameBoard[i+1][gameBoard[].length()-1].getAlive()) { neighbors++; } //cell lower left diagonal
  }

  if(i != 0 && i != gameBoard.length()-1 && j == gameBoard[].length()-1)
  {
    if(gameBoard[i-1][0].getAlive()) { neighbors++; } //cell upper right diagonal
    if(gameBoard[i][0].getAlive()) { neighbors++; } //cell lower right
    if(gameBoard[i+1][0].getAlive()) { neighbors++; } //cell lower right diagonal
  }
}

void World::mMode()
{
  if(i == 0 && j == 0)
  {
    if(gameBoard[i][j].getAlive()) { neighbors += 3; } //because its own reflection counts as 3, left, above, diagonal
    if(gameBoard[i][j+1].getAlive()) { neighbors += 2; } //bc left counts as 2
    if(gameBoard[i+1][j].getAlive()) { neighbors += 2; } //bc below counts as 2
    if(gameBoard[i+1][j+1].getAlive()) { neighbors++; } //bc diagonal is only 1, no reflection
  }

  if (i == 0 && j == gameBoard[].length()-1)
  {
    if(gameBoard[i][j].getAlive()) { neighbors += 3; } //because its own reflection counts as 3, left, above, diagonal
    if(gameBoard[i][j-1].getAlive()) { neighbors += 2; } //bc left counts as 2
    if(gameBoard[i+1][j].getAlive()) { neighbors += 2; } //bc below counts as 2
    if(gameBoard[i+1][j-1].getAlive()) { neighbors++; } //bc diagonal is only 1, no reflection
  }

  if(i == gameBoard.length()-1 && j == 0)
  {
    if(gameBoard[i][j].getAlive()) { neighbors += 3; } //because its own reflection counts as 3, left, above, diagonal
    if(gameBoard[i-1][j].getAlive()) { neighbors += 2; } //bc above counts as 2
    if(gameBoard[i][j+1].getAlive()) { neighbors += 2; } //bc right counts as 2
    if(gameBoard[i-1][j+1].getAlive()) { neighbors++; } //bc diagonal is only 1, no reflection
  }

  if(i == gameBoard.length()-1 && j == gameBoard[].length()-1)
  {
    if(gameBoard[i][j].getAlive()) { neighbors += 3; } //because its own reflection counts as 3, left, above, diagonal
    if(gameBoard[i][j-1].getAlive()) { neighbors += 2; } //bc left counts as 2
    if(gameBoard[i+1][j].getAlive()) { neighbors += 2; } //bc above counts as 2
    if(gameBoard[i-1][j-1].getAlive()) { neighbors++; } //bc diagonal is only 1, no reflection
  }

  sides();
  //all the extra sides for mirror mode
  if((i == 0 || i == gameBoard.length()-1) && j != 0 && j != gameBoard[].length()-1)
  {
    //top & bottom sides
    if(gameBoard[i][j-1].getAlive()) { neighbors++; } //cell right diagonal
    if(gameBoard[i][j+1].getAlive()) { neighbors++; } //cell left diagonal
  }

  if(i != 0 && i != gameBoard.length()-1 && (j == 0 || j == gameBoard[].length()-1) )
  {
    //left & right sides
    if(gameBoard[i+1][j].getAlive()) { neighbors++; } //cell left diagonal
    if(gameBoard[i-1][j].getAlive()) { neighbors++; } //cell right diagonal
  }
}

void World::sides()
{
  if(bMode == 2)
  {
    if(gameBoard[i][j].getAlive()) { neighbors++; } //cell reflection on self for mirror mode
  }

  //code all the in between the corners on the sides
  if(i == 0 && j != 0 && j != gameBoard[].length()-1)
  {
    if(gameBoard[i][j+1].getAlive()) { neighbors++; } //cell right
    if(gameBoard[i][j-1].getAlive()) { neighbors++; } //cell left
    if(gameBoard[i+1][j-1].getAlive()) { neighbors++; } //cell lower left
    if(gameBoard[i+1][j].getAlive()) { neighbors++; } //cell below
    if(gameBoard[i+1][j+1].getAlive()) { neighbors++; } //cell lower right
  }

  if(i == gameBoard.length()-1 && j != 0 && j != gameBoard[].length()-1)
  {
    if(gameBoard[i][j+1].getAlive()) { neighbors++; } //cell right
    if(gameBoard[i][j-1].getAlive()) { neighbors++; } //cell left
    if(gameBoard[i-1][j-1].getAlive()) { neighbors++; } //cell upper left
    if(gameBoard[i-1][j].getAlive()) { neighbors++; } //cell above
    if(gameBoard[i-1][j+1].getAlive()) { neighbors++; } //cell upper right
  }

  if(i != 0 && i != gameBoard.length()-1 && j == 0)
  {
    if(gameBoard[i][j+1].getAlive()) { neighbors++; } //cell right
    if(gameBoard[i+1][j].getAlive()) { neighbors++; } //cell below
    if(gameBoard[i-1][j].getAlive()) { neighbors++; } //cell above
    if(gameBoard[i-1][j+1].getAlive()) { neighbors++; } //cell upper right
    if(gameBoard[i+1][j+1].getAlive()) { neighbors++; } //cell lower right
  }

  if(i != 0 && i != gameBoard.length()-1 && j == gameBoard[].length()-1)
  {
    if(gameBoard[i][j-1].getAlive()) { neighbors++; } //cell left
    if(gameBoard[i+1][j].getAlive()) { neighbors++; } //cell below
    if(gameBoard[i-1][j].getAlive()) { neighbors++; } //cell above
    if(gameBoard[i-1][j-1].getAlive()) { neighbors++; } //cell upper left
    if(gameBoard[i+1][j-1].getAlive()) { neighbors++; } //cell lower left
  }
}
