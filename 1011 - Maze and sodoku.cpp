#include "lpclib.h"
#include "grid.h"
#include "vector.h"
#include <windows.h>
#include <cstdarg>
using namespace std;


// This function draws the current maze state from the given grid. Assumes these characters are used:
// space = open
// x = wall
// . = path
// G = goal
void DrawMaze(Grid<char> & maze);

// This function creates a  grid from a sequence of strings, ending with an empty string.
Grid<char> CreateGrid(char * contents, ...);

// This is a recursive function that determines if the
// maze is solvable from the current state, comprised
// of the current state of the whole maze and
// the current location (r, c) of the adventurer
bool SolveMaze (int r, int c, Grid<char> & currentState);

// This function "draws" a 4x4 sudoku board using text output
void DrawSudoku(Grid<char> & board);

bool SolveSudoku(Grid<char> & board);

bool BoardIsOk(Grid<char> & board);

int main()
{
    Grid<char> board = CreateGrid(
        "ABCD",
        "CDAB",
        "BAD ",
        "    ",
        "");


    DrawSudoku(board); GetLine();
    if (SolveSudoku(board) == true)
        DrawSudoku(board);
    else
        cout << "That board has no solution!n";

    GraphicsWindow (600, 600, "white");
    Grid<char> maze1 = CreateGrid(
    "xxxxx",
    "xGx x",
    "xxx x",
    "x @ x",
    "x x x",
    "x x x",
    "xxxxx",
    "");

    DrawMaze(maze1);
    cout << "Ready to solve? Press enter: ";
    string garbage = GetLine();
    if (SolveMaze(3, 2, maze1) == true)
        DrawMaze(maze1);
    else
        cout << "Sorry, no solution!n";
  return 0;
}

bool SolveSudoku(Grid<char> & board)
{
    // negative base case:
    if (!BoardIsOk(board))
        return false;
    // positive base case: if solved, yay! and stop
    bool foundEmptyCell = false;
    foreach (char c in board)
    {
        if (c == ' ')
        {
            foundEmptyCell = true;
            break;
        }
    }
    if (foundEmptyCell == false)
        return true;  // the current board is solved.

    // next available empty cell == ?
    int r, c;
    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            if (board.getAt(r, c) == ' ')
                goto done;
        }
    }
    done:

    // foreach choice, try it, undoit if the board
    // isn't solvable from that state
    for (char x='A'; x <= 'D'; x++)
    {
        // make the current choice
        board.setAt(r, c, x);
        DrawSudoku(board); GetLine();
        // if it is now solvable, we're done!
        if (SolveSudoku(board) == true)
            return true;
        else
            // unmake that choice!
            board.setAt(r, c, ' ');
        DrawSudoku(board); GetLine();
    }
    // backtrack
    return false;
}

bool BoardIsOk(Grid<char> & board)
{
    cout << "Ok? ";
    string yn = GetLine();
    return (yn == "y");
}

bool IsOpen(int r, int c, Grid<char> & grid)
{
    return (grid.getAt(r, c) == ' '
        || grid.getAt(r, c) == 'G');
}

bool SolveMaze (int r, int c, Grid<char> & currentState)
{
    // HERE IS THE GENERAL RECURSIVE BACKTRACKING ALGORITHM

    //Base case:
    if (currentState.getAt(r, c) == 'G')
    {
        return true;
    }

    currentState.setAt(r, c, '.');
    DrawMaze(currentState);
    string garbage = GetLine();

    if (IsOpen(r-1, c, currentState))
    {
        if (SolveMaze(r-1, c, currentState) == true)
            return true;
    }
    if (IsOpen(r, c+1, currentState))
    {
        if (SolveMaze(r, c+1, currentState) == true)
            return true;
    }
    if (IsOpen(r+1, c, currentState))
    {
        if (SolveMaze(r+1, c, currentState) == true)
            return true;
    }
    if (IsOpen(r, c-1, currentState))
    {
        if (SolveMaze(r, c-1, currentState) == true)
            return true;
    }

    currentState.setAt(r, c, ' ');
    DrawMaze(currentState);
    string garbage2 = GetLine();

    return false;
}


static void DrawMazePre()
{
  static bool done = false;
  if (!done)
    {
      done = true;
      cout << "Setupn";

      DefineColor(" ", 255, 255, 255);
      DefineColor("x", 70, 70, 70);
      DefineColor(".", 150, 150, 200);
      DefineColor("G", 0, 200, 0);
      DefineColor("@", 0, 128, 128);
    }
}

void DrawMaze(Grid<char> & maze)
{
  DrawMazePre();
  int dim1 = GetWidth() / maze.numCols();
  int dim2 = GetHeight() / maze.numRows();
  int sidelen = min(dim1, dim2);

  DrawRectangle(0, 0, GetWidth(), GetHeight(), "white", true);

  int xadj = (GetWidth() - sidelen*maze.numCols()) / 2;
  int yadj = (GetHeight() - sidelen*maze.numRows()) / 2;

  for (int r = 0; r < maze.numRows(); r++)
    {
      for (int c = 0; c < maze.numCols(); c++)
        {
	  char what = maze.getAt(r, c);
	  if (what == '@')
            {
	      DrawRectangle(xadj + c*sidelen+1, yadj + r*sidelen+1, sidelen-2, sidelen-2, " ", true);
	      DrawCircle(xadj + c*sidelen + sidelen/2, yadj + r*sidelen + sidelen/2, sidelen/2 - 2, "@", true);
            }
	  else
	    DrawRectangle(xadj + c*sidelen+1, yadj + r*sidelen+1, sidelen-2, sidelen-2, string() + what, true);
        }
    }
  UpdateDisplay();
}

Grid<char> CreateGrid(char * contents, ...)
{
  Vector<string> lines;
  va_list arguments;
  va_start ( arguments, contents );
  string line = contents;
  int len = (int) line.length();

  while (1)
    {
      lines.add(line);
      line = va_arg (arguments, char *);
      if (line == "")
	break;
      if (line.length() != len)
	Error("Grid format is invalid");
    }

  Grid<char> g(lines.size(), len);

  for (int r = 0; r < g.numRows(); r++)
    {
      for (int c = 0; c < g.numCols(); c++)
        {
	  g.setAt(r, c, lines[r][c]);
        }
    }
  return (g);
}

void DrawSudoku(Grid<char> & board)
{
  if (board.numCols() != 4 || board.numRows() != 4)
    Error ("Sudoku board must be 4x4");

  system("cls");
  cout << "+-------+n";
  for (int r = 0; r < 4; r++)
    {
      cout << "|";
      for (int c = 0; c < 4; c++)
        {
	  cout << board.getAt(r, c);
	  if (c % 2 == 0)
	    cout << " ";
	  else
	    cout << "|";
        }
      cout << "n";
      if (r % 2 == 1)
	cout << "+-------+n";
    }
}



}
