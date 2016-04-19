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
  bool filled_in() const;
  void join(int cell1, int cell2);
  int find(int cell) const;
  bool walled(int cell, int adj) const;
  int adjacent(int cell) const;
  vector<int> cells;
  int width, height;
};

/*
 * Public functions
 * -----------------------
 */

Maze::Maze(int width, int height)
  : width(width), height(height), cells(width * height, -1) {
  srand(time(NULL));  /* seed random with time */
  generate();
}

ostream& operator<<(ostream& os, const Maze& maze) {
  return os << maze.render();
}

string Maze::render() const {
  string ret = ".";
  for (int i = 0; i < width; ++i)
    ret += "_.";
  ret += "\n.";

  for (int i = 0; i < cells.size(); ++i) {
    if (walled(i, i + width) || i + width > cells.size())
      ret += "_";
    else
      ret += " ";

    if ((walled(i, i+1) || (i+1) % width == 0) && i+1 != cells.size())
      ret += "|";
    else
      ret += ".";

    if ((i+1) % width == 0 && i+1 != cells.size())
      ret += "\n|";
  }

  return ret;
}

void Maze::generate() {
  for (int i = 0, adj; i < cells.size()-1; ++i) {
    adj = adjacent(i);
    while (find(i) == find(adj))
      adj = adjacent(i);

    cells[i] = adj;
  }
}

bool Maze::filled_in() const {
  for (int i = 1; i < cells.size(); ++i)
    if (find(i) != find(0))
      return true;
  return false;
}

bool Maze::walled(int cell, int adj) const {
  return !(cells[cell] == adj || cells[adj] == cell);
}

int Maze::adjacent(int cell) const {
  vector<int> adjacent_cells;
  if ((cell+1) % width != 0) adjacent_cells.push_back(cell+1);
  if (cell % width != 0) adjacent_cells.push_back(cell-1);
  if (cell + width < cells.size()) adjacent_cells.push_back(cell + width);
  if (cell - width > 0) adjacent_cells.push_back(cell - width);

  return adjacent_cells[rand() % adjacent_cells.size()];
}

void Maze::join(int cell1, int cell2) {
  cells[cell1] = cell2;
}

int Maze::find(int cell) const {
  while (cells[cell] != -1)
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

/*
 * Sample output:
 *
 * $ ./maze 40 40
 * ._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._.
 * ._. ._._. | | ._. | |_. . | ._| |_._._. | | | . |_._. | ._._._| ._| |_._. | . ._|
 * |_._. ._| | . . |_| | |_| | . | . ._._._| ._|_| . . ._| | | ._|_. | |_. |_._| . |
 * | |_._._|_._|_|_._. |_._. |_| ._|_. . | ._|_. ._|_|_|_._._. | |_. | | |_._. . |_|
 * | . ._| ._| ._| | | | ._._|_._._|_._| |_. ._|_._._._._. ._._._|_. ._._._._._| ._|
 * | |_._| ._. | | |_. |_. ._| |_. | ._|_. | ._._._| |_. . ._. | | |_| . | |_. | | |
 * |_. ._|_|_._._. . | | ._| . | ._|_. . . ._. ._| | ._| | ._|_. ._. |_| | ._._| | |
 * | ._. |_. . | | |_| ._| . |_|_. | |_|_| |_._. | ._. |_| |_. |_| . . |_. | . . | |
 * | |_. |_. | ._| |_._._._|_. | | |_._._._. . |_| . |_|_._| | | . | |_. |_._| |_. |
 * |_._|_. ._| . | | ._|_. |_._. ._. ._| |_. |_| |_|_._._._._. ._|_|_._| . | |_| | |
 * | |_. |_| | |_._| ._|_. . |_._| ._._| | ._. . ._._| ._._|_._|_. | | |_| |_._. ._|
 * | . ._| ._. ._| | ._._| | | ._|_. ._| |_| . |_| |_._._. | |_._._._._. ._| |_. | |
 * | | | |_|_._._._. | | |_|_. | |_._._._. | | | ._._._| . | ._. ._| | | |_._. |_. |
 * |_|_. ._. | | |_. | | . . | | |_. ._. . | | |_._._. | | ._|_. ._._|_. | |_. |_. |
 * | |_._._|_. |_._. | . | |_._._| | |_. |_|_| | | ._| |_| | | . . | | . | | . ._._|
 * |_._. | . | ._._._. |_| ._._._. |_._|_._._. |_._._. . |_|_._| | ._|_|_._._| ._. |
 * |_. |_._| ._| . | |_| |_| |_. | | ._. ._._._._|_._._|_. | | |_| | |_. ._. |_. | |
 * | . | | ._|_._| . ._. ._|_. ._._._._|_._._. . ._| | . | ._._._._._. ._|_. ._|_| |
 * |_| |_. | | | |_| . |_. | |_| | | . ._. |_. | |_. ._| |_| ._._._|_._|_._. | | . |
 * | . | | | | ._. |_|_| | . ._| |_. | . | |_._| |_._. |_| . | | . ._._|_._._._._| |
 * |_|_. ._| |_._|_._._._._| . . . | |_| |_. | ._._. |_. |_| | | | ._| . | . | . ._|
 * | | ._| . | ._| |_. |_._._| | | |_. |_._|_._| |_._. | | |_. | |_. |_| ._|_| |_| |
 * | |_| ._| | |_._._. ._._. |_|_|_._._| ._| | ._| | | |_. ._._| |_. ._|_. | | | | |
 * | | |_. |_|_. ._|_. | ._._|_._. ._._._._|_._. ._._| | |_. | |_| ._|_. ._. | | . |
 * | |_. | | |_. |_. ._| |_._._. |_._._. |_. | | |_._. . | |_._. | | | |_| ._| | | |
 * | | |_. | . ._| . ._|_|_._._._._. | ._|_. . |_. ._| |_. | ._| . . | | ._|_._. | |
 * | ._| . | | . | |_| |_._._. | | | | |_._._| | | | ._|_. . . |_| | | . | | ._._| |
 * |_. |_|_. |_| |_. | |_. | ._._. . | . ._. ._| . |_. ._| | |_|_._|_._| ._|_| | | |
 * | |_. | | |_._. . | . | ._| ._. |_._|_| ._| ._| ._|_|_._| . | |_._. ._| ._| ._| |
 * | | | . | |_._._|_|_| ._|_._| ._. ._|_._|_._._| | . | | |_|_. ._| ._|_._._. | | |
 * |_. | |_| |_. | | |_. | | | . ._| . ._. ._._. |_. |_| ._. | |_. . | . ._| | | . |
 * | |_. |_. |_. ._._._._._._|_|_| |_| | ._._| |_|_. ._. ._|_. | . |_|_| ._._. . |_|
 * | ._._._._._._| | | ._. . |_. | ._| |_._. | | | ._._|_| |_._._| ._._| | |_._| . |
 * |_| | | ._| |_. | ._._|_| | | ._._. |_. . |_. ._|_._._. . . | |_. |_._. ._| ._| |
 * | ._._. | . | | |_._| . ._| |_| |_._| |_| |_. |_. |_. ._| |_._. |_._._._._| | | |
 * |_| | . . |_._._. . |_| | | | | | ._| | | |_._| | . |_| |_| . |_._. . | ._._| ._|
 * | | |_|_|_._. ._|_|_. | |_. ._. |_. | |_._. | | | |_._. ._| |_._. ._| | | . |_. |
 * | | | ._. . |_._._._| ._| ._._| | ._. ._|_. ._| | ._|_._. |_|_. |_._|_. |_|_._. |
 * | | . |_._|_._._. | ._| ._. . |_. ._|_| |_. | | ._|_._._._._. | | | ._|_. |_. ._|
 * | | | ._. | . |_. | ._._|_. |_| . . ._| . . | |_| |_. |_. ._| ._| ._. |_. ._|_. |
 * |_._|_|_._|_|_._._._._|_._._|_._|_|_._._|_|_._._._._._._._._._._._._|_._._._._|_.
 */