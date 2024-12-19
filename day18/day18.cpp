#include <cstdio>
#include <deque>
#include <filesystem>
#include <fstream>
#include <set>
#include <string>
#include <iostream>
#include <vector>
//g++ day18.cpp -std=c++23 -O3

int find_path(const std::vector<std::string>& grid) {
  std::deque<std::tuple<int,int,int>> path{{0,0,0}};
  std::set<std::pair<int,int>> seen;
  std::vector<std::pair<int,int>> dirs{{-1,0},{0,1},{1,0},{0,-1}};
  int end = 70;
  while (!path.empty()) {
    auto [i,x,y] = path.front();
    path.pop_front();
    if (x == end && y == end)
      return i;
    if (seen.contains({x,y}))
      continue;
    seen.insert({x,y});
    for (auto [dx,dy] : dirs) {
      if (x+dx >= 0 && x+dx < grid[0].size() && y+dy >= 0 && y+dy < grid.size() &&
          grid[y+dy][x+dx] != '#') {
        path.emplace_back(i+1, x+dx, y+dy);
      }
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  int part1 = 0;
  std::string part2;
  std::vector<std::pair<int,int>> bytes;
  std::vector<std::string> grid(71, std::string(71, '.'));
  for (std::string line; std::getline(file, line);) {
    int x, y;
    std::sscanf(line.c_str(), "%d,%d", &x, &y);
    bytes.emplace_back(x, y);
  }

  for (int i = 0; i < bytes.size(); i++) {
    auto [x,y] = bytes[i];
    grid[y][x] = '#';
    int score = find_path(grid);
    if (i < 1024)
      part1 = score;

    std::cout << "\e[2J"; // clear terminal
    for (auto line : grid)
      std::cout << line << '\n';

    if (score == 0) {
      part2 = std::format("{},{}", x, y);
      std::cout << i << '\n';
      break;
    }
  }

  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
