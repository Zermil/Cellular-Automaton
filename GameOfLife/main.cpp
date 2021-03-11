#include <iostream>
#include <conio.h>
#include <time.h>

const int ROWS = 10;
const int COLS = 30;
const char LOOK_UP[] = { ' ', '*' };

enum class State {
  DEAD,
  ALIVE,
};

struct Board {
  State states[ROWS][COLS];
};

Board generateNewBoard();
void printBoard(const Board& board);
int countNeighbours(const Board& board, int row, int col);
Board generateNextState(const Board& board);

int main(int argc, char* argv[])
{
  srand(time(NULL));

  Board board = generateNewBoard();
  printBoard(board);

  while (true)
  {
    const char c = tolower(_getch());

    if (c == 'e')
      break;

    switch (c)
    {
    case 'r':
      board = generateNewBoard();
      break;
    default:
      board = generateNextState(board);
      break;
    }

    system("cls");
    printBoard(board);
  }

  return 0;
}

Board generateNewBoard()
{
  Board randomBoard = {};

  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j) 
      randomBoard.states[i][j] = static_cast<State>(rand() % 2);
  }

  return randomBoard;
}

void printBoard(const Board& board)
{
  for (int i = 0; i < ROWS; ++i)
  {
    std::cout << '|';

    for (int j = 0; j < COLS; ++j)
      std::cout << LOOK_UP[static_cast<int>(board.states[i][j])];

    std::cout << "|\n";
  }
}

int countNeighbours(const Board& board, int row, int col)
{
  int neighbourCount = 0;

  for (int i = -1; i < 2; ++i)
  {
    for (int j = -1; j < 2; ++j)
    {
      // Skip self
      if (i == 0 && j == 0)
        continue;

      const int newRow = (row + i) < 0 ? ROWS - 1 : (row + i) % ROWS;
      const int newCol = (col + j) < 0 ? COLS - 1 : (col + j) % COLS;

      if (board.states[newRow][newCol] == State::ALIVE)
        neighbourCount++;
    }
  }

  return neighbourCount;
}

Board generateNextState(const Board& board)
{
  Board newGeneration = {};

  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j)
    {
      const State cell = board.states[i][j];
      const int neighbours = countNeighbours(board, i, j);

      switch (cell)
      {
      case State::ALIVE:
        newGeneration.states[i][j] = (neighbours == 2 || neighbours == 3) ? State::ALIVE : State::DEAD;
        break;
      case State::DEAD:
        newGeneration.states[i][j] = neighbours == 3 ? State::ALIVE : State::DEAD;
        break;
      }
    }
  }

  return newGeneration;
}