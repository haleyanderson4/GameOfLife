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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

World::World() { } //blank constructor

World::~World() { delete [] gameBoard; }

void World::setWorldGenerate(int boundary, int output, string name, int columns, int rows, int mode) //constructor
{
    Bacteria** gameBoard = new Bacteria*[rows];
    for(int i = 0; i < rows; ++i)
    {
      gameBoard[i] = new Bacteria [columns];
    }

    srand (time(NULL));
    for(int i = 0; i < sizeof(gameBoard); i++)
    {
      for(int j = 0; j < sizeof(gameBoard[0]); j++)
      {
        int randNum;

        randNum = (int) rand() % 4;

        //get rand number between 0 and 3 to get 1/4 chance of having bacteria

        if(randNum == 0) { gameBoard[i][j].triggerLife(); }
        else { gameBoard[i][j].triggerDeath(); }
      }
    }

    bMode = boundary;
    vMode = output;
    oFile = name;
    iteration = 0;
    oMode = mode;
}

void World::setWorldTranslate(int boundary, int output, string name, string board, int mode, int c, int r) //constructor
{
    Bacteria** gameBoard = new Bacteria*[r];
    for(int i = 0; i < r; ++i)
    {
      gameBoard[i] = new Bacteria[c];
    }

    int count = 0;
    for(int i = 0; i < r; ++i)
    {
      for(int j = 0; j < c; ++j)
      {
        if(board.substr(count,1) == "X" || board.substr(count,1) == "x") { gameBoard[i][j].triggerLife(); }
        //turning the map into the game board!
        if(board.substr(count,1) != "-" && board.substr(count,1) != "X" && board.substr(count,1) != "x")
        {
          //if it's not recognized, ask for a recognized character
          do {
            string newVal;
            cout<< "Your map had an invalid input in position [" << i << "][" << j << "]. Please enter '-' for no bacteria in this location or 'X' for a live bacteria." << endl;
            cin>> newVal;
            if(newVal == "X" || newVal == "x")
            {
              gameBoard[i][j].triggerLife();
              break;
              //if they still did it wrong they have to try again until they submit to my will
            }
            else if(newVal != "-" && newVal != "X" && newVal != "x") { cout<< "Please only use the format given. Try again." << endl; }
          } while(true);
        }
        count++;
      }
    }

    bMode = boundary;
    vMode = output;
    oFile = name;
    iteration = 0;
    oMode = mode;
}

void World::play()
{
  for(int x = 1; x <= 100; ++x)
  {
    //if you havent finished by 100 ends there so its not endless
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
  cout<< "Your game has timed out after 100 loops." << endl;
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
