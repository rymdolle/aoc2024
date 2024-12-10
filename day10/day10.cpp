#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>

std::set<std::pair<int,int>> find_part1(std::pair<int,int> start, const std::vector<std::string>& grid) {
  auto [x,y] = start;
  std::set<std::pair<int,int>> seen;
  std::vector<std::pair<int,int>> directions = {{0,-1},{0,1},{-1,0},{1,0}};
  for (auto [dx,dy] : directions) {
    if (x+dx >= grid[0].size() || x+dx < 0 || y+dy >= grid.size() || y+dy < 0)
      continue;
    if (grid[y+dy][x+dx] == grid[y][x] + 1) {
      if (grid[y+dy][x+dx] == '9') {
        seen.insert({x+dx,y+dy});
      }
      auto seen2 = find_part1({x+dx, y+dy}, grid);
      seen.insert(seen2.begin(), seen2.end());
    }
  }
  return seen;
}

int find_part2(std::pair<int,int> start, const std::vector<std::string>& grid) {
  int score = 0;
  auto [x,y] = start;
  std::vector<std::pair<int,int>> directions = {{0,-1},{0,1},{-1,0},{1,0}};
  for (auto [dx,dy] : directions) {
    if (x+dx >= grid[0].size() || x+dx < 0 || y+dy >= grid.size() || y+dy < 0)
      continue;
    if (grid[y+dy][x+dx] == grid[y][x] + 1) {
      if (grid[y+dy][x+dx] == '9') {
        score++;
      }
      score += find_part2({x+dx, y+dy}, grid);
    }
  }
  return score;
}

int main(int argc, char *argv[])
{
  std::string filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  int part1 = 0;
  int part2 = 0;
  std::vector<std::string> grid;
  std::vector<std::pair<int,int>> start;
  for (std::string line; std::getline(file, line);) {
    for (int x = 0; x < line.length(); x++) {
      if (line[x] == '0') {
        start.emplace_back(x, grid.size());
      }
    }
    grid.push_back(line);
  }

  for (auto position : start) {
    auto seen = find_part1(position, grid);
    auto score = find_part2(position, grid);
    part1 += seen.size();
    part2 += score;
  }

  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
