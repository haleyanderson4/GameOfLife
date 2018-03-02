//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include "World.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>


int main(int argc, char **argv)
{
  string response;
  string oFile;
  string board;
  int bMode;
  int oMode;
  int mMode;

  int columns;
  int rows;

  int column;
  int row;

  cout<< "Hi, welcome to the Game of Life." << endl;
  cout<< "Would you like to input a game map or have one randomly generated?" << endl;
  cout<< "Type 'Y' if you have a map and anything else if not." << endl;
  cin>> response;
  if(response == "Y" || response == "y")
  {
    mMode = 0;
    do {
      cout<< "Enter the file name of your game map." << endl;
      if(!(argc==1))
      {
        cout<<"You entered the file name incorrectly. Please try again." << endl;
        continue;
      }
      else
      {
        try
        {
          int count = 1;
          string str;
          string fileName;
          ifstream newFile;
          cin >> fileName;
          newFile.open(fileName);
          if (newFile.is_open())
          {
            while(!newFile.eof())
            {
              if(count == 1)
              {
                getline(newFile, str);
                //column = (int&)str;
                count++;
              }
              if(count == 2)
              {
                getline(newFile, str);
                //row = (int&)str;
                count++;
              }
              getline(newFile, str);
              board = board + str;

              row++;
              column = str.length();
            }
            newFile.close();
          }
        }
        catch(exception e)
        {
          cout<<"You entered a file that can't be accessed. Please try again." << endl;
          continue;
          //error catching for if you mess up the file input stuff
        }
        //if they have their own file they can take in input and use it!
        break;
      }
    } while(true);
  }
  else
  {
    mMode = 1;
    do {
      try
      {
        cout<< "Please enter the dimensions of your game map. \nColumns:" << endl;
        cin>> columns;
        if(columns < 1)
        {
          cout<< "Please enter a valid number of columns." << endl;
          continue;
        }
        cout<< "Rows:" << endl;
        cin>> rows;
        if(rows < 1)
        {
          cout<< "Please enter a valid number of rows." << endl;
          continue;
        }
      }
      catch(exception e)
      {
        cout<<"You entered an invalid input. Please try again." << endl;
        continue;
      }
      //error handling for more input stuff wohoo

      //this is to call random generation if they didnt have a file to input
      cout<< "Your game map has been created." << endl;
      break;
    } while(true);
  }

  do {
    cout<< "What kind of boundary mode would you like? Doughnut mode, Mirror Mode, or Classic mode?" << endl;
    cout<< "Enter 'D' for Doughnut mode, 'M' for Mirror mode, and 'C' for Classic mode." << endl;
    cin>> response;
    if(response == "D" || response == "d" )
    {
      bMode = 1;
      break;
    }
    else if(response == "C" || response == "c")
    {
      bMode = 0;
      break;
    }
    else if(response == "M" || response == "m")
    {
      bMode = 2;
      break;
    }
    else
    {
      cout<< "Sorry that was not a valid response. Please try again." << endl;
    }
    //to get the different modes! Exciting! In a do while to make sure fail input is taken

  } while(true);

  do {
    cout<< "How would you like the generations to proceed? \nWould you like a slight pause between generations being printed, to press the 'enter' key to move to the next generation, or if the game should be output to a different file?" << endl;
    cout<< "Press 'P' for pauses, 'E' to enter, or 'O' to output the game to a file." << endl;
    cin>> response;
    if(response == "P" || response == "p" )
    {
      oMode = 0;
      break;
    }
    else if(response == "E" || response == "e" )
    {
      oMode = 1;
      break;
    }
    else if(response == "O" || response == "o" )
    {
      oMode = 2;

      do {
        string fileName;
        cout<< "Please enter the name of the file you would like to output to." << endl;
        ofstream newFile;
        cin >> fileName;
        newFile.open(fileName);
        if (newFile.is_open())
        {
          break;
        }
        else
        {
          cout<<"You entered a file that can't be accessed. Please try again." << endl;
          continue;
        }
      } while(true);

    }
    else
    {
      cout<< "Sorry that was not a valid response. Please try again." << endl;
      continue;
      //error catching
    }
    //to get user input on how they want to be able to see the game play
    break;
  } while (true);

  World game;
  if(mMode == 0)
  {
    //translate map
    game.setWorldTranslate(bMode, oMode, oFile, board, oMode, column, row);
  }
  else if(mMode == 1)
  {
    //generate map
    game.setWorldGenerate(bMode, oMode, oFile, columns, rows, oMode);
  }
  cout<< "Welcome to the Game of Life!" << endl;
  game.play();
  cout<< "And thats the end of the Game of Life. Thanks for playing!" << endl;
  cout<< "Please press enter to exit" << endl;

  return 0;
}
