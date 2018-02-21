//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include "Bacteria.h"
#include "Coordinate.h"
#include "World.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>

using namespace std;

World::World() { } //default constructor

World::World(Bacteria [] board, int boundary, int output, string name) //overload constructor
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
}

void play()
{
    //where all the rules about living and dying goes

    for(int i = 0; i < gameBoard.length(); ++i)
    {
      for(int j = 0; j <gameBoard[].length(); ++j)
      {
          int neighbors = 0;

          if(gameBoard[i][j].getAlive() == false)
          { continue; }

          if(bMode == 0)
          {
            //Classic mode
            if(gameBoard[i][j].getAlive())
            {
              neighbors++;
            }
          }
          else if(bMode == 1)
          {
            //Doughnut mode
            if(gameBoard[i][j].getAlive())
            {
              neighbors++;
            }
          }

          if(neighbors < 2 || neighbors > 3)
          {
            tempBoard[i][j].triggerDeath();
          }
          if(neighbors == 3)
          {
            do {
              int randLoc;
              do {
                randLoc = ((int)rand() / (RAND_MAX));
              } while(randLoc < 0 || randLoc > 8);
              //grab a random location around the bacteria to repopulate in
              if(/* selection */.getAlive() == false)
              {
                /* selection */.triggerLife();
                break;
              }
            } while(true);
            //maybe a function to find neighbor cells that takes input of the row and column
          }
      }
    }

    for(int i = 0; i < gameBoard.length(); ++i)
    {
      for(int j = 0; j <gameBoard[].length(); ++j)
      {
          gameBoard[i][j] = tempBoard[i][j];
      }
    }
}

void output()
{
    iteration++;
    string results = "\nCycle number " + (string)iteration + ":\n";
    for(int i = 0; i < gameBoard.length(); i++)
    {
      for(int j  0; j < gameBoard[].length(); j++)
      {
          if(gameBoard[i][j].getAlive())
          {
            results += "X";
          }
          else
          {
            results += "-";
          }
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
