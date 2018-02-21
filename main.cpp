//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 350-02, Assignment 2

#include "Bacteria.h"
#include "Coordinate.h"
#include "World.h"
#include <iostream>
#include <math.h>

Bacteria [] generateGameMap(int columns, int rows);
Bacteria [] translateGameMap(string fileName);


int main(int argc, char const *argv[])
{
    int size = ;

    string response;
    string oFile;
    int bMode;
    int oMode;

    do {
      cout<< "Hi, welcome to the Game of Life." << endl;
      cout<< "Would you like to input a game map or have one randomly generated?" << endl;
      cout<< "Type Y if you have a map and anything else if not." << endl;
      cin>> response;
      if(response == "Y" || response == "y")
      {
        string fileName;
        cout<< "Enter the file name of your game map."
        if(!(argc==1))
        {
          cout<<"You entered the file name incorrectly. Please try again." << endl;
          continue;
        }
        else
        {
          try
          {
            cin>> fileName;
          }
          catch()
          {
            if(/*file name fails*/)
            {
              cout<<"You entered a file that can't be accessed. Please try again." << endl;
              continue;
            }
            //error catching for if you mess up the file input stuff
          }
        }
        translateGameMap(string fileName);
        //if they have their own file they can take in input and use it!
        break;
      }
      else
      {
        try
        {
          cout<< "Please enter the dimensions of your game map. \nColumns:" << endl;
          cin>> columns;
          cout<< "Rows:" << endl;
          cin>> rows;
        }
        catch()
        {
          if(/*they input the wrong thing*/)
          {
            cout<<"You entered an invalid input. Please try again." << endl;
            continue;
          }
        }
        //error handling for more input stuff wohoo

        generateGameMap(columns, rows);
        //this is to call random generation if they didnt have a file to input
      }
      cout<< "Your game map has been created." << endl;
      break;
    } while(true);

    do {
      cout<< "What kind of boundary mode would you like? Doughnut mode or Classic mode?" << endl;
      cout<< "Enter 'D' for Doughnut mode and 'C' for Classic mode." << endl;
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
      else
      {
        cout<< "Sorry that was not a valid response. Please try again." << endl;
      }
      //to get the different modes! Exciting! In a do while to make sure fail input is taken

    } while(true);

    do {
      cout<< "How would you like the generations to proceed? \nWould you like a slight pause between generations being printed,
      to press the 'enter' key to move to the next generation, or if the game should be output to a different file?" << endl;
      cout<< "Press 'P' for pauses, 'E' to enter, or 'O' to output the game to a file." << endl;
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
          cout<< "Please enter the name of the file you would like to output to." << endl;
          cin >> fileName;
          ofstream newFile;
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
        break;
      }
      else
      {
        cout<< "Sorry that was not a valid response. Please try again." << endl;
        //error catching
      }
      //to get user input on how they want to be able to see the game play

    } while (true);

    game = new World(gameBoard, bMode, oMode, oFile);
    cout<< "Welcome to the Game of Life!" << endl;
    game.play();
    cout<< "And thats the end of the Game of Life. Thanks for playing!" << endl;
    cout<< "Please press enter to exit" << endl;

    return 0;
}

Bacteria [] generateGameMap(int columns, int rows)
{
    Bacteria** gameBoard = new Bacteria* [rows];
    for(int i = 0; i < rows; i++)
    {
      gameBoard[i] = new Bacteria [columns];
    }
    //to make the 2d array

    for(int i = 0; i < rows; i++)
    {
      for(int j = 0; j < columns; j++)
      {
        int randBac;

        do {
          randBac = ((int)rand() / (RAND_MAX));
        } while(randBac != 0 || randBac != 1 || randBac != 2 || randBac != 3);
        //get rand number between 1 and 4 to get 1/4 chance of having bacteria

        if(randBac == 0)
        {
          gameBoard[i][j] = gameBoard[i][j].triggerLife();
        }
        else
        {
          gameBoard[i][j] = gameBoard[i][j].triggerDeath();
        }
      }
    }
    return gameBoard;
}

Bacteria [] translateGameMap(string fileName)
{
    int row = 0;
    int column;
    string board = "";
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

    Bacteria** gameBoard = new Bacteria* [row];
    for(int i = 0; i < row; i++)
    {
      gameBoard[i] = new Bacteria [column];
    }

    int loc = 0;
    for(int i = 0; i < row; i++)
    {
      for(int j = 0; j < column; j++)
      {
        if(board.charAt(loc) == 'X')
        {
          gameBoard[i][j] = gameBoard[i][j].triggerLife();
        }
        else if(board.charAt(loc) == '-')
        {
          gameBoard[i][j] = gameBoard[i][j].triggerDeath();
        }
        //turning the map into the game board!
        else
        {
          //if it's not recognized, ask for a recognized character
          do {
            string newVal;
            cout<< "Your map had an invalid input in position [" << i << "][" << j << "]. Please enter either '-' for no
            bacteria or 'X' for a live bacteria." << endl;
            cin>> newVal;
            if(newVal == '-')
            {
              gameBoard[i][j] = gameBoard[i][j].triggerDeath();
              break;
            }
            if(newVal == 'X')
            {
              gameBoard[i][j] = gameBoard[i][j].triggerLife();
              break;
              //if they still did it wrong they have to try again until they submit to my will
            }
          } while(true);
        }
        loc++;
      }
    }

    return gameBoard;
}
