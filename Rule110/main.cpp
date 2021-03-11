// ====================================== //
// https://en.wikipedia.org/wiki/Rule_110 //
// ====================================== //
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

const int COLS = 30;
const int ROWS = 15;

const char LOOK_UP[2] = { ' ', '*' };

std::unordered_map<std::string, bool> TABLE = {
  {"   ", 0},
  {"  *", 1},
  {" * ", 1},
  {" **", 1},
  {"*  ", 0},
  {"* *", 1},
  {"** ", 1},
  {"***", 0},
};

struct Row {
  bool cells[COLS];
};

Row generate_random_row();
Row generate_next_state(const Row& prev);
void print_row(const Row& row);

int main(int argc, char* argv[])
{
  srand(time(0)); 
  Row row = generate_random_row();

  for (int i = 0; i < ROWS; ++i)
  {
    std::cout << '|';
    print_row(row);
    std::cout << "|\n";
    
    row = generate_next_state(row);
  }
  
  std::cin.get();
  return 0;
}

Row generate_random_row()
{
  Row random_row = {}; 

  for (int i = 0; i < COLS; ++i)
    random_row.cells[i] = (rand() % 2);

  return random_row;
}

Row generate_next_state(const Row& prev)
{
  Row next_state = {}; 

  for (int i = 1; i < COLS - 1; ++i)
  {
    const std::string state = std::string() + 
                              LOOK_UP[prev.cells[i - 1]] +
                              LOOK_UP[prev.cells[i]] + 
                              LOOK_UP[prev.cells[i + 1]]; 

    next_state.cells[i] = TABLE[state];
  }

  return next_state;
}

void print_row(const Row& row)
{
  for (int i = 0; i < COLS; ++i)
    std::cout << LOOK_UP[row.cells[i]];
}
