#include <iostream>
#include <cassert>

const int COLS = 60;
const int ROWS = 150;
const char LOOK_UP[2] = { ' ', '*' };

enum Direction {
  UP = 0,
  LEFT,
  DOWN,
  RIGHT,
  DIR_SIZE,
};

enum State {
  BLANK = 0,
  VISITED,
};

struct Board {
  State states[ROWS][COLS] = {};
};

struct Ant {
  int posX = ROWS / 2;
  int posY = COLS / 2;
  Direction direction = UP;
};

// Functions
void print_board(const Board &board);
void move_forward(Ant &ant);
void traverse_board(Ant &ant, Board &board);

int main(int argc, char* argv[])
{
  Ant ant;
  Board board;
  
  for (int i = 0; i < 11000; ++i)
    traverse_board(ant, board); 

  print_board(board);

  system("pause");
  return 0;
}

void print_board(const Board &board)
{
  for (int i = 0; i < ROWS; ++i)
  {
    std::cout << '|';

    for (int j = 0; j < COLS; ++j)
      std::cout << LOOK_UP[board.states[i][j]];

    std::cout << "|\n";
  }
}

void move_forward(Ant &ant)
{
  // Move Forward one unit.  
  switch (ant.direction)
  {
    case UP:
      ant.posY = ant.posY - 1 < 0 ? COLS - 1 : ant.posY - 1;
      break;
    case RIGHT:
      ant.posX = ant.posX + 1 >= ROWS ? 0 : ant.posX + 1;
      break;
    case LEFT:
      ant.posX = ant.posX - 1 < 0 ? ROWS - 1 : ant.posX - 1;
      break;
    case DOWN:
      ant.posY = ant.posY + 1 >= COLS ? 0 : ant.posY + 1;
      break;
    default:
      assert(false && "UwU, unreachable: fookie wookie");
  } 
}

void traverse_board(Ant &ant, Board &board)
{
  State cell_state = board.states[ant.posX][ant.posY];
  Direction direction = ant.direction;

  switch (cell_state) 
  {
    case BLANK:
      // turn 90* clockwise
      ant.direction = static_cast<Direction>(direction + 1 >= DIR_SIZE ? 0 : direction + 1);
      cell_state = VISITED;
      break;
    case VISITED:
      // turn 90* counter-clockwise
      ant.direction = static_cast<Direction>(direction - 1 < 0 ? DIR_SIZE - 1 : direction - 1);
      cell_state = BLANK; 
      break;
    default:
      assert(false && "OwO uncreachable!");
  }
  
  board.states[ant.posX][ant.posY] = cell_state;
  move_forward(ant);
}