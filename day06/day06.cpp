#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
//g++ day06.cpp -std=c++20 -O3

void turn(int& dx, int& dy) {
  if (dy < 0) { // turn right
    dx = 1;
    dy = 0;
  } else if (dx > 0) { // turn down
    dx = 0;
    dy = 1;
  } else if (dy > 0) { // turn left
    dx = -1;
    dy = 0;
  } else if (dx < 0) { // turn up
    dx = 0;
    dy = -1;
  }
}

bool in_bound(std::pair<int,int> pos, const std::vector<std::string>& grid) {
  return pos.first >= 0 && pos.second >= 0 && pos.first < grid[0].size() && pos.second < grid.size();
}

std::pair<int,int> find_block(std::pair<int,int> pos, int dx, int dy,
                              const std::set<std::pair<int,int>>& block,
                              const std::vector<std::string>& grid) {
  while (in_bound(pos, grid)) {
    if (block.contains({pos.first+dx,pos.second+dy}))
      return pos;
    pos.first += dx;
    pos.second += dy;
  }

  return pos;
}

std::set<std::pair<int,int>> find_path(std::pair<int,int> pos, int dx, int dy,
                              const std::set<std::pair<int,int>>& block,
                              const std::vector<std::string>& grid) {
  std::set<std::pair<int,int>> visits;
  while (in_bound(pos, grid)) {
    visits.insert({pos.first, pos.second});
    if (block.contains({pos.first+dx,pos.second+dy}))
      turn(dx, dy);
    pos.first += dx;
    pos.second += dy;
  }

  return visits;
}

int main(int argc, char *argv[])
{
  std::string filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  std::vector<std::string> grid;
  std::pair<int,int> start;
  std::set<std::pair<int,int>> block;
  for (std::string line; std::getline(file, line);) {
    if (auto it = line.find("^"); it != std::string::npos)
      start = {it, grid.size()};

    for (int i = 0; i < line.length(); i++)
      if (line[i] == '#')
        block.insert({i, grid.size()});

    grid.push_back(line);
  }

  auto part1 = find_path(start, 0, -1, block, grid);

  std::set<std::pair<int,int>> part2;
  for (auto v : part1) {
    // add a block for each of the already visited positions in the
    // path and cache input and output
    std::map<std::tuple<std::pair<int,int>, int, int>, std::pair<int,int>> cache;
    std::pair<int,int> pos = start;
    // add temp block
    block.insert(v);
    int dx = 0;
    int dy = -1;
    while (in_bound(pos, grid)) {
      if (cache.contains({pos, dx, dy})) {
        // if already visited position from same direction, we are in a loop
        pos = cache[{pos, dx, dy}];
        turn(dx, dy);
        part2.insert(v);
        break;
      }

      // if at position from new direction, keep going
      auto res = find_block(pos, dx, dy, block, grid);
      cache[{pos, dx, dy}] = res;
      pos = res;
      turn(dx, dy);
    }

    // remove block again
    block.erase(v);
  }

  std::cout << part1.size() << '\n';
  std::cout << part2.size() << '\n';
  return 0;
}
