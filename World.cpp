//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include "World.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

World::World() {} //blank constructor

World::~World() { delete [] gameBoard; }

void World::setWorld(int boundary, int output, string name, int columns, int rows, int timeO, int mode) //constructor
{
    Bacteria** gameBoard = new Bacteria*[rows];
    for(int i = 0; i < rows; ++i)
    {
      gameBoard[i] = new Bacteria [columns];
    }

    generateGameMap(gameBoard);

    bMode = boundary;
    vMode = output;
    oFile = name;
    iteration = 0;
    timeOut = timeO;
    oMode = mode;
}

void World::setWorldTranslate(int boundary, int output, string name, string insides, int timeO, int mode, int c, int r) //constructor
{
    rowT = r;
    columnT = c;
    Bacteria** gameBoard = new Bacteria*[rowT];
    for(int i = 0; i < rowT; ++i)
    {
      gameBoard[i] = new Bacteria[columnT];
    }
    translateGameMap(insides);

    bMode = boundary;
    vMode = output;
    oFile = name;
    iteration = 0;
    timeOut = timeO;
    string board;
    oMode = mode;
    board = "";
}

void World::play()
{
  for(int x = 1; x <= timeOut; ++x)
  {
    //where all the rules about living and dying goes
    Bacteria** tempBoard = new Bacteria*[sizeof(gameBoard)];
    Bacteria** oldBoard = new Bacteria*[sizeof(gameBoard)];
    for(int i = 0; i < sizeof(gameBoard); ++i) { gameBoard[i] = new Bacteria [sizeof(gameBoard[0])]; }

    for(int i = 0; i < sizeof(gameBoard); i++)
    {
      for(int j = 0; j < sizeof(gameBoard[0]); j++)
      {
        tempBoard[i][j] = gameBoard[i][j];
        oldBoard[i][j] = gameBoard[i][j];
        //to intialize the tempBoard & old board as the same as the gameBoard
      }
    }

    for(int i = 0; i < sizeof(gameBoard); ++i)
    {
      for(int j = 0; j < sizeof(gameBoard[0]); ++j)
      {
          Mode num;
          num.setUp(gameBoard, i, j, bMode);
          neighbors = num.getNeighbors();
          //Mode exsists to count the neighbors

          if(neighbors < 2 || neighbors > 3) { tempBoard[i][j].triggerDeath(); }
          if(neighbors == 3) { tempBoard[i][j].triggerLife(); }
      }
    }

    for(int i = 0; i < sizeof(gameBoard); ++i)
    {
      for(int j = 0; j <sizeof(gameBoard[0]); ++j)
      {
        oldBoard[i][j] = gameBoard[i][j];
        gameBoard[i][j] = tempBoard[i][j];
      }
    }

    if(end(oldBoard))
    {
      cout<< "And that ends it!" << endl;
      break;
    }
  }
}

void World::output()
{
    iteration++;
    string results = "\nCycle number " + (string&)(iteration) + ":\n";
    for(int i = 0; i < sizeof(gameBoard); i++)
    {
      for(int j = 0; j < sizeof(gameBoard[0]); j++)
      {
          if(gameBoard[i][j].getAlive() == true) { results += "X"; }
          else { results += "-"; }
      }
      results += "\n";
    }
    //to create the visual representation of the game board

    if(oMode == 2)
    {
      //output file
      ofstream outputFile;
      outputFile.open(oFile);
      if (outputFile.is_open()) { outputFile << results << endl; }
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

void World::generateGameMap(Bacteria** gameBoard)
{
    for(int i = 0; i < sizeof(gameBoard); i++)
    {
      for(int j = 0; j < sizeof(gameBoard[0]); j++)
      {
        int randBac;

        do {
          randBac = ((int)rand() / (RAND_MAX));
        } while(randBac != 0 || randBac != 1 || randBac != 2 || randBac != 3);
        //get rand number between 1 and 4 to get 1/4 chance of having bacteria

        if(randBac == 0) { gameBoard[i][j].triggerLife(); }
        else { gameBoard[i][j].triggerDeath(); }
      }
    }
}

void World::translateGameMap(string board)
{
    for(int i = 0; i < sizeof(gameBoard); i++)
    {
      for(int j = 0; j < sizeof(gameBoard[0]); j++)
      {
        if(board.substr(0,1) == "X" || board.substr(0,1) == "x")
        {
          gameBoard[i][j].triggerLife();
        }
        else if(board.substr(0,1) == "-")
        {
          gameBoard[i][j].triggerDeath();
        }
        //turning the map into the game board!
        else
        {
          //if it's not recognized, ask for a recognized character
          do {
            string newVal;
            cout<< "Your map had an invalid input in position [" << i << "][" << j << "]. Please enter either '-' for no bacteria in this location or 'X' for a live bacteria." << endl;
            cin>> newVal;
            if(newVal == "-")
            {
              gameBoard[i][j].triggerDeath();
              break;
            }
            else if(newVal == "X" || newVal == "x")
            {
              gameBoard[i][j].triggerLife();
              break;
              //if they still did it wrong they have to try again until they submit to my will
            }
            else { cout<< "Please only use the format given. Try again." << endl; }
          } while(true);
        }
        board = board.substr(1);
      }
    }
}

bool World::end(Bacteria** oldBoard)
{
  for(int i = 0; i < sizeof(gameBoard); i++)
  {
    for(int j = 0; j < sizeof(gameBoard[0]); j++)
    {
      if (gameBoard[i][j].getAlive() != oldBoard[i][j].getAlive())
      {
        return false;
      }
      //to see if it's the same as the last generation
    }
  }

  for(int i = 0; i < sizeof(gameBoard); i++)
  {
    for(int j = 0; j < sizeof(gameBoard[0]); j++)
    {
      if (gameBoard[i][j].getAlive() == true)
      {
        return false;
      }
      //to see if they are all dead
    }
  }
  return true;
}
