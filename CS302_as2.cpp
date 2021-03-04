/*
Name: Lucas Allen, 5004607031, CS302 Assignment #2
Description: This program uses a recursive backtracking algorithm to solve a given sudoku puzzle.
Input: A fileName (puzzle0#.txt), and "NO" if the user wants to exit the program.
Output: Prompt for a filename, the intial board when the puzzle is read in, the solved "result" board, further
prompts for filename until user says "NO".
*/
#include <iostream>
#include <fstream>
#include <iomanip>

int EMPTY_CELL=0;

using namespace std;

//function declarations
bool sudoku(int [][9], int r, int c, int n);
bool checkConstraints(int[][9], int r, int c, int n);
bool checkRow(int [][9],int r, int n);
bool checkColumn(int [][9], int c, int n);
bool checkSector(int [][9], int r, int c, int n);
bool checkEmpty(int [][9], int &r, int &c);

/*
*function description: checkRow is a boolean function that returns true if the number passed in to the function is already present in the row.
*parameters: the game board, row, number
*return value: a boolean value
*/
bool checkRow(int sudokuBoard[9][9], int row, int number)
{
  for(int column=0; column<9; column++)
  {
    if(sudokuBoard[row][column]==number)       //if board[row][column]==number, then the number is already in the row
    {
      return true;
    }
  }
  return false;
}
/*
*function description: CheckColumn is a boolean function that returns true if the number passed in to the function is already present in the row
*parameters:  the game board, column, number
*return value: a boolean value
*/
bool checkColumn(int sudokuBoard[9][9], int column, int number)
{

  for(int row=0; row<9; row++)
  {
    if(sudokuBoard[row][column]==number)                      //if board[i][column]==number, then the number is already in the column
    {
      return true;
    }
  }
  return false;
}
/*
*function description: checkSector is a boolean function that returns true if the number passed in to the function is already present in the 3x3 sector that the cell is in
*parameters: the game board, row, column, and number
*return value: a boolean value
*/
bool checkSector(int sudokuBoard[9][9], int row, int column, int number )
{
  int tempRow = row - row%3;
  int tempColumn = column - column%3;
  for(int i=tempRow; i < tempRow + 3; i++)
  {
    for(int j=tempColumn; j < tempColumn + 3; j++)
    {
      if(sudokuBoard[i][j]==number)
      {
        return true;
      }
    }
  }
  return false;
}
/*
*function description: Check constraints checks to see if checkRow, checkColumn, or checkSector return false, if they do, then the number cannot be inserted into the current cell
*parameters: the game board, the row, the column
*return value: a boolean value
*/
bool checkConstraints(int sudokuBoard[9][9], int row, int column, int number)
{
  return !(checkRow(sudokuBoard,row, number) || checkColumn(sudokuBoard,column, number) || checkSector(sudokuBoard, row, column, number));
}
/*
*function description: checkEmpty searched through each cell to find the next empty cell
*parameters: the game board, row(by reference), column(by reference)
*return value: a booleam value
*/
bool checkEmpty(int sudokuBoard[9][9], int &row, int &column)
{
  for(row=0; row<9; row++)
  {
    for(column=0; column<9; column++)
    {
      if(sudokuBoard[row][column]==0)
      {
        return true;
      }
    }
  }return false;
}
/*
*function description: Sudoku uses a recursive backtracking algorithm to play the game
*parameters: the game board, row, column, and number
*return value: a boolean value
*/
bool sudoku(int sudokuBoard[9][9], int row, int column, int number)
{

  if(!checkEmpty(sudokuBoard,row,column))           //if every cell has been filled then do not call the function again
  {
    return true;
  }
  for(int number=1; number<=9; number++)
  {
    if(checkConstraints(sudokuBoard, row, column, number))    //use the number 1-9 from the for loop to check if the number can be inserted
    {
      sudokuBoard[row][column]=number;                        // if it can, set the current cell to the accepted number

      if(sudoku(sudokuBoard, row, column+1, number))
      {
        return true;
      }sudokuBoard[row][column]=EMPTY_CELL;                    //Cell becomes EMPTY_CELL if the wrong cell was chosen, this is how we know when to backtrack
    }
  }
  return false;
}
/*
*function description: This function prints out the game board. Does not print the intial game board(which is done in main)
*parameters: the game board
*return value: none
*/
void printBoard(int sudokuBoard[9][9])
{
  cout<<"Sudoku puzzle solved: "<<endl;
  cout<<"_________________________"<<endl;
  for(int i=0; i<9; i++)
  {
    if(i==3 || i==6 || i==9)
    {
      cout<<"_________________________";
      cout<<endl;
    }
    cout<<"|";
    for(int j=0; j<9; j++)
    {
      if(j==3 || j==6 || j==9)
      {
        cout<<"|";
      }

      if(sudokuBoard[i][j]==0)
      {
        cout<<setw(2)<<'-'<<setw(2);
      }else{
      cout<<setw(2)<<sudokuBoard[i][j]<<setw(2);
      }
    }
    cout<<"|";
    if(i<9){
    cout<<endl;
    }
  }
  cout<<"_________________________"<<endl;
}

int main()
{
  int i=0;
  int j=0;
  int row=0;
  int column=0;
  int number=1;                       //variable number starts at one because acceptable numbers are 1-9
  int sudokuBoard[9][9];              // the 9x9 game board

  bool goodFile=false;
  string fileName;                    //user input file name
  ifstream iFile;

  while(goodFile==false)
  {
    prompt:                           //label: prompt which allows for exiting of the while loop when necessary(when error)
    cout<<"Enter intial Sudoku board file: ";
    cin>>fileName;
    if(fileName=="NO" || "no")        //if the user inputs case insensitive "NO", exit the program
    {
      cout<<"Goodbye"<<endl;
      exit(0);
    }
    //if file name is not one given in assignment handout reprompt the user.
    if(fileName!="puzzle01.txt" && fileName!="puzzle02.txt" && fileName!= "puzzle03.txt" && fileName!="puzzle04.txt" && fileName!= "puzzle05.txt" && fileName!="puzzle06.txt")
    {
      cout<<"That's not a file I can read! Try again."<<endl;
      goto prompt;      //error occurred. Exiting the loop, jumping back up to the prompt
    }
    iFile.open(fileName);
    if(iFile.fail())
    {
      iFile.clear();
      goodFile=false;
      cout<<"bad/missing file!";
      goto prompt;      //error occurred. Exiting the loop, jumping back up to the prompt
    }else{
      goodFile=true;    //if no error, then good file open
    }

    cout<<endl;
    cout<<"Initial board read in: "<<endl<<endl;
    cout<<"_________________________"<<endl;
    for(i=0; i<9; i++)
    {
      if(i==3 || i==6 || i==9)
      {
        cout<<"_________________________";
        cout<<endl;
      }
      cout<<"|";
      for(j=0; j<9; j++)
      {
        if(j==3 || j==6 || j==9)
        {
          cout<<"|";
        }
        iFile>>sudokuBoard[i][j];       //read contents of file into sudoku board array
        if(sudokuBoard[i][j]==0)
        {
          cout<<setw(2)<<'-'<<setw(2);
        }else{
        cout<<setw(2)<<sudokuBoard[i][j]<<setw(2);
        }
      }
      cout<<"|";
      cout<<endl;
    }
    cout<<"_________________________"<<endl;
    cout<<endl;
    iFile.close();                    // close file after data read in
  }
  //function calls commented out but used for testing
  //checkRow(sudokuBoard, row, number);
  //checkColumn(sudokuBoard, column, number);
  //checkSector(sudokuBoard, row, column, number);
  //checkConstraints(sudokuBoard, row, column, number);

  sudoku(sudokuBoard, row, column, number);       //sudoku function call
  printBoard(sudokuBoard);                        //print board function call
  if(sudoku(sudokuBoard, row, column, number))    //if the puzzle is solved (function returns true) then go back to prompt
  {
    goto prompt;      //go back to prompt because puzzle solved. Should not exit until user input "NO"
  }else{
    cout<<"Guess it didn't work..."<<endl;    //else, the puzzle was not solved, exit
    return (0);
  }
  //cout<<sudokuBoard[0][0];                 //used for testing to see the contents of specific cells
  //cout<<sudokuBoard[0][4]<<endl;
}
