//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include "World.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>

using namespace std;

World::World() {} //blank constructor

World::World(int boundary, int output, string name, int columns, int rows, int timeO, int mode) //constructor
{
    Bacteria gameBoard = new Bacteria [rows];
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

World::World(int boundary, int output, string name, string fileName, int timeO, int mode) //constructor
{
    int row, column;
    getRowsAndColumns(fileName);
    Bacteria gameBoard = new Bacteria [row];
    for(int i = 0; i < row; ++i)
    {
      gameBoard[i] = new Bacteria[column];
    }
    translateGameMap(fileName);

    bMode = boundary;
    vMode = output;
    oFile = name;
    iteration = 0;
    timeOut = timeO;
    string board;
    oMode = mode;
}

World::~World()
{
    delete [] gameBoard;
}

void World::play()
{
  for(int x = 1; x <= timeOut; ++x)
  {
    //where all the rules about living and dying goes
    Bacteria tempBoard = new Bacteria [gameBoard.length()][gameBoard[].length()];

    for(int i = 0; i < gameBoard.length(); i++)
    {
      for(int j = 0; j < gameBoard[].length(); j++)
      {
        tempBoard[i][j] = gameBoard[i][j];
        //to intialize thetempBoard as the same as the gameBoard
      }
    }

    for(int i = 0; i < gameBoard.length(); ++i)
    {
      for(int j = 0; j < gameBoard[].length(); ++j)
      {
          neighbors = 0;

          if(i != 0 && j != 0 && i != gameBoard.length()-1 && j != gameBoard[].length()-1) { middles(i, j); }
          else
          {
            if(bMode == 0) { cMode(i, j); } //Classic mode
            else if(bMode == 1) { dMode(i, j); } //Doughnut mode
            else if(bMode == 2) { mMode(i, j); } //Mirror mode
          }

          if(neighbors < 2 || neighbors > 3) { tempBoard[i][j].triggerDeath(); }
          if(neighbors == 3) { tempBoard[i][j].triggerLife(); }
      }
    }

    for(int i = 0; i < gameBoard.length(); ++i)
    {
      for(int j = 0; j <gameBoard[].length(); ++j) { gameBoard[i][j] = tempBoard[i][j]; }
    }

    if(end())
    {
      break;
    }
  }
}

void World::output()
{
    iteration++;
    string results = "\nCycle number " + (string)(iteration) + ":\n";
    for(int i = 0; i < gameBoard.length(); i++)
    {
      for(int j = 0; j < gameBoard[].length(); j++)
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

void World::middles(int i, int j)
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

void World::cMode(int i, int j)
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
  sides(i, j);
}

void World::dMode(int i, int j)
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
  sides(i, j);
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

void World::mMode(int i, int j)
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

  sides(i, j);
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

void World::sides(int i, int j)
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

void World::generateGameMap(Bacteria gameBoard)
{
    for(int i = 0; i < rows; i++)
    {
      for(int j = 0; j < columns; j++)
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

void getRowsAndColumns(fileName)
{
  string str;
  row = 0;
  board = "";
  ifstream file;
  file.open(fileName.c_str());
  if(file.is_open())
  {
    while(!file.eof())
    {
      getline(file, str);
      row++;
      column = str.length();
      board = board + str;
    }
  }
  file.close();
  //opens file and turns the inside into one big string!
  //also gets the row and column numbers
}

void World::translateGameMap(string fileName)
{
    for(int i = 0; i < gameBoard.length(); i++)
    {
      for(int j = 0; j < gameBoard[].length(); j++)
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
        str = str.substr(1);
      }
    }
}

bool World::end()
{
  int x = 0;
  for(int i = 0; i < gameBoard.length(); i++)
  {
    for(int j = 0; j < gameBoard[].length(); j++)
    {
      if (gameBoard[i][j].isAlive())
      {
        return false;
      }
      //to see if they are all dead
    }
  }
  return true;
}
