#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

class Maze {
public:
  Maze(int width, int height);
  string render() const;

private:
  void generate();
  bool filled_in();
  void join(int cell1, int cell2);
  int find(int cell);
  int adjacent(int cell);
  vector<int> cells;
  int width, height;
};

/*
 * Public functions
 * -----------------------
 */

Maze::Maze(int width, int height)
  : width(width), height(height), cells(width * height) {
  for (int i = 0; i < cells.size() ++i) cells[i] = i;
  srand(time(NULL));  /* seed random with time */
  generate();
}

ostream& operator<<(ostream& os, const Maze& maze) {
  return os << maze.render();
}

/* ._._._._.
 * ._. | . |
 * | |_._| |
 * |_._._._.
 */
string Maze::render() const {
  string ret = "\n\t.";
  for (int i = 0; i < width; ++i)
    ret += "_.";
  ret += "\n\t.";

  for (int i = 0; i < cells.size(); ++i) {
    if (cells[i] == i + width || cells[i + width] == i)
      ret += " ";
    else
      ret += "_";

    if (cells[i+1] == i || cells[i] == i+1)
      ret += ".";
    else
      ret += "|";

    if ((i+1) % width == 0 && i != cells.size()-1)
      ret += "\n\t|";
  }

  ret += "\n";

  return ret;
}

void Maze::generate() {
  int cell, adj;

  for (int i = 0; i < cells.size(); ++i) {
    do adj = adjacent(i); while (find(i) == find(adj));
    cout << i << ": " << adj << endl;
    join(i, adj);
  }
}

bool Maze::filled_in() {
  for (int i = 1; i < cells.size(); ++i)
    if (find(i) != find(0))
      return true;
  return false;
}

int Maze::adjacent(int cell) {
  enum Direction {UP, DOWN, LEFT, RIGHT};

  int direction = rand() % 4;
  switch (direction) {
  case UP:
    return cell - width >= 0 ? cell - width : adjacent(cell);
  case DOWN:
    return cell + width < cells.size() ? cell + width : adjacent(cell);
  case LEFT:
    return cell % width != 0 ? cell-- : adjacent(cell);
  case RIGHT:
    return (cell+1) % width != 0 ? cell++ : adjacent(cell);
  default:
    return adjacent(cell);
  }
}

void Maze::join(int cell1, int cell2) {
  cells[cell1] = cell2;
}

int Maze::find(int cell) {
  while (cells[cell] != cell)
    cell = cells[cell];
  return cell;
}

/*
 * Test program
 */

int main(int argc, char *argv[]) {
  int width, height;

  if (argc != 3) {
    cout << "Usage: " << argv[0] << " width height" << endl;
    return 1;
  }

  width = stoi(argv[1]);
  height = stoi(argv[2]);

  Maze maze(width, height);
  cout << maze.render() << endl;

  return 0;
}