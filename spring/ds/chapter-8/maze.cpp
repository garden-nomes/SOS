#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <climits>
using namespace std;

class Maze {
public:
  Maze(int width, int height);
  string render(bool path = false) const;

private:
  void generate();
  bool filled_in() const;
  void join(int cell1, int cell2);
  int find(int cell) const;
  bool walled(int cell, int adj) const;
  int adjacent(int cell) const;
  set<int> shortest_path(int start, int end) const;

  vector<int> cells;
  int width, height;
};

/*
 * Public functions
 * -----------------
 */

Maze::Maze(int width, int height)
  : width(width), height(height), cells(width * height, -1) {
  srand(time(NULL));  /* seed random with time */
  generate();
}

ostream& operator<<(ostream& os, const Maze& maze) {
  return os << maze.render();
}

string Maze::render(bool path) const {
  set<int> s_path;
  if (path)
    s_path = shortest_path(0, cells.size() - 1);

  string ret = ".";
  for (int i = 0; i < width; ++i)
    ret += "_.";
  ret += "\n.";

  for (int i = 0; i < cells.size(); ++i) {
    if (walled(i, i + width) || i + width > cells.size())
      if (path && s_path.count(i) != 0)
        ret += "\e[4m*\e[0m";
      else
        ret += "_"; //"\e[4m \e[0m";
    else
      if (path && s_path.count(i) != 0)
        ret += "*";
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

/*
 * Private functions
 * ------------------
 */

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

set<int> Maze::shortest_path(int start, int end) const {
  struct node {
    int id, prev, dist;
    bool visited;
  };

  class node_compare {
  public:
    bool operator()(const node *a, const node *b)
      { return a->dist > b->dist; }
  };

  node nodes[cells.size()];
  vector<node *> q;   /* let's just pretend this is a fib heap */
  set<int> ret;
  vector<node *> adjacent(4);
  node *n;

  /* initialize nodes */
  for (int i = 0; i < cells.size(); ++i) {
    nodes[i].id = i;
    nodes[i].prev = -1;
    nodes[i].dist = i == start ? 0 : INT_MAX;
    nodes[i].visited = false;
    q.push_back(&nodes[i]);
  }

  make_heap(q.begin(), q.end(), node_compare());    /* really should use fib heap though */

  /* run Dijkstra */
  while (!q.empty()) {
    n = q.front();
    pop_heap(q.begin(), q.end());
    q.pop_back();

    n->visited = true;

    /* find all adjacent cells */
    adjacent.clear();
    if ((n->id+1) % width != 0)
      adjacent.push_back(&nodes[n->id+1]);
    if (n->id % width != 0)
      adjacent.push_back(&nodes[n->id-1]);
    if (n->id + width < cells.size())
      adjacent.push_back(&nodes[n->id + width]);
    if (n->id - width > 0)
      adjacent.push_back(&nodes[n->id - width]);

    for (node *adj : adjacent) {
       if (!adj->visited && !walled(n->id, adj->id) && n->dist + 1 < adj->dist) {
         adj->dist = n->dist + 1;
         adj->prev = n->id;
       }
    }

    make_heap(q.begin(), q.end(), node_compare());
  }

  /* build path */
  n = &nodes[end];
  ret.insert(n->id);
  while (n->prev != -1) {
    n = &nodes[n->prev];
    ret.insert(n->id);
  }

  return ret;
}
/*
 * Test program
 */

int main(int argc, char *argv[]) {
  int width, height;
  bool path = false;

  if (argc != 3 && argc != 4) {
    cout << "Usage: " << argv[0] << " width height [--path]" << endl;
    return 1;
  }

  width = stoi(argv[1]);
  height = stoi(argv[2]);
  if (argc == 4 && strcmp(argv[3], "--path") == 0)
    path = true;


  Maze maze(width, height);
  cout << maze.render(path) << endl;

  return 0;
}

/*
 * Sample output:
 * $ ./maze 40 40 --path
 * ._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._._.
 * .*.*.*._| . ._| . |_._._. | . | ._. |_. |_. ._| |_. ._._. ._._._._. ._|_._. | | |
 * | |_|*|_. | | | |_. | |_. |_| |_|_. | | | | . ._._| |_. |_| ._| ._| |_. ._._| ._|
 * |_. |*|_._|_. . . |_| . |_. | | ._._._._| ._|_._. |_| ._|_._. ._| | ._. ._. ._| |
 * | |_.*.*.*. |_| |_|_. |_._. ._| . ._|_._._|_._._. ._| |_. | | | |_._| | . |_| | |
 * |_. | | .*| | |_. ._|_| ._._._._|_. | ._._. | | ._| . | . | ._. | ._._| |_| | ._|
 * |_._. ._|*|_|_._. | |_._| . | | ._. |_._._| ._._. | |_._|_|_| |_._._. | ._. | . |
 * | |_. | |*. |_. |_. |_._._|_._._|_. . . |_._|_._._. ._._._. | . . . |_._|_. ._| |
 * |_._. |_.*|_._._| ._. ._. | | ._| | |_|_. | |_. | |_._._|_._._|_| | | . ._. | ._|
 * | | ._| |*.*.*.*.*._|_| |_| . . | |_. | ._|_. ._._| ._. |_. | | | | ._| |_._| . |
 * | . ._| ._| | |*.*| |_. ._|_|_|_. | |_| | ._|_. ._._| ._|_. ._._| |_| |_._| | | |
 * | |_._. | | ._|*|_._. |_. | . ._. | ._._| ._. |_| | |_. |_._._._._|_._. ._. |_| |
 * | | |_. |_._|_.*.*| |_._|_._| ._|_._| ._._| | | | | . | . ._|_. | ._| | ._|_. ._|
 * | ._| | ._| | |_|*.*.*.*| ._| . | | | |_. |_. ._| |_| |_|_. | | |_. . |_._| . | |
 * |_._|_._| . | | | . | |*| |_._| ._. |_|_. | |_. | ._._._. |_. | | |_|_. | . | | |
 * |_. | . |_| ._._|_| |*.*| |_. |_._|_. | . |_._. | ._._|_._._. |_. | |_._._|_|_. |
 * |_._. | |_. . | |_. |*| | | |_. | |_._._| |_._. |_. | ._._._._._._| ._| | | ._| |
 * | ._|_| ._|_| |_._._.*| . | |_. |_. | |_. |_._. | |_| . ._._. |_. . ._| ._._|_. |
 * |_._. | . . | . ._.*.*|_|_. ._| . | | ._._. |_. | . |_|_| | | ._._| ._._._. ._| |
 * |_. ._|_| |_|_|_. |*|_| ._| |_._| ._|_| | ._._._|_|_. | . ._|_|_. |_|_._. | . . |
 * |_. ._| ._| | ._._|*. |_._. ._. ._. | ._. | ._| ._| | |_| | . |_. | | . | |_|_| |
 * | . | | | |_. |_.*.*|_|_. . | |_|_. . |_._._| | . . | |_. | | ._|_._._|_._. | ._|
 * | |_| | | | |_._|*.*.*._|_|_._| | |_| ._. ._|_._| | ._._| |_| . . . | | ._|_._. |
 * |_. ._| |_. ._._._|*.*|_. ._|_._. | |_._| |_._. | |_. ._| | . |_|_| |_. ._| ._| |
 * | |_. | ._._._. ._|*.*._| | ._._| | | |_. ._. | |_|_._._. |_| |_. | | ._|_. ._. |
 * | ._| |_| ._| . . | .*.*.*.*.*.*.*.*|*.*|_| ._| |_._._._. | | | ._. ._._|_._|_. |
 * |_. | ._| . ._|_| | ._|_. | . |_|_|*.*|*. . |_. ._| ._. . ._| |_| |_|_._._._. ._|
 * | |_. |_._| . ._|_._._| ._|_| ._. | |_|*|_|_|_._._._| |_| | ._. |_. | | |_. . . |
 * | |_. | |_._|_|_. |_._. |_. |_| ._| |_.*._._|_._._. . ._| ._| . . . ._| | |_|_| |
 * | |_. | | | ._._| | . |_._. ._._| | |*.*| | . | | ._|_. |_| | |_| | | | | . |_. |
 * |_._._. | ._. |_. . | |_._. ._| | ._|*.*. | | | |_._| |_._. |_._|_|_._. | | |_. |
 * |_. | |_._| ._| | |_| ._._. | | . ._|_.*|_| |_. ._. ._. | ._. ._|_. ._._|_| ._. |
 * | | | | ._|_._. |_|_._| ._| | . |_. |_.*._|_._|_|_._| ._|_._|_. ._|_. | | |_|_. |
 * | |_._. | | ._._._. | |_. ._|_|_| | . |*.*.*._. |_._._. | |_. ._._| | | ._|_._. |
 * | . | . |_._| |_._. | |_. |_._._. ._| . ._|*| |_. | . ._. . ._| ._| ._._. |_. ._|
 * |_|_._| ._|_. ._._| | | | | |_. |_| |_|_. |*.*.*|_|_|_. |_|_._._|_._|_. ._|_. | |
 * |_. |_. | | . . |_._._. |_._. |_. | | ._._|_. .*._|_._. | | ._| ._|_._._. |_. | |
 * | | . ._| ._|_|_| | ._. | | . | | | . ._. ._|_|*.*. | |*.*.*|_._. . | | | | |_. |
 * | |_|_. |_._. ._._._|_. | ._| | . ._| | |_._| |_|*|_| |*|_.*.*|_._| | |_._._._. |
 * | | | | ._| | ._. ._|_._|_| . . | | ._._._._| ._|*.*|*.*. |_.*|*.*.*.*|*.*|_.*.*|
 * |_._._._._._._._|_._._._._._|_|_|_|_._._._._._._._|*.*|_|_|_.*.*|_|_|*.*|*.*.*|*.
 */
