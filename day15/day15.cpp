#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int move(std::pair<int,int> start, int dx, int dy, std::vector<std::string>& grid) {
  int moves = 0;
  auto [x,y] = start;
  if (grid[y+dy][x+dx] == '#')
    return moves;

  if (grid[y+dy][x+dx] == '.')
    return moves+1;

  while (grid[y+dy][x+dx] == 'O') {
    x += dx;
    y += dy;
    if (grid[y+dy][x+dx] == '#')
      return 0;
    moves++;
  }

  return moves;
}

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  int part1 = 0;
  int part2 = 0;
  std::vector<std::string> grid;
  std::vector<std::pair<int,int>> moves;

  std::pair<int,int> start;
  for (std::string line; std::getline(file, line) && !line.empty();) {
    if (auto it = line.find("@"); it != std::string::npos) {
      start = {it, grid.size()};
    }
    grid.emplace_back(line);
  }

  for (std::string line; std::getline(file, line);) {
    for (auto c : line) {
      if (c == '>')
        moves.emplace_back( 1,  0);
      if (c == 'v')
        moves.emplace_back( 0,  1);
      if (c == '<')
        moves.emplace_back(-1,  0);
      if (c == '^')
        moves.emplace_back( 0, -1);
    }
  }

  for (auto [dx,dy] : moves) {
    auto& [x,y] = start;
    grid[y][x] = '.';

    int moves = move({x,y}, dx, dy, grid);
    if (moves > 0) {
      x += dx;
      y += dy;
    }
    if (grid[y][x] == 'O') {
      grid[y+(moves*dy)][x+(moves*dx)] = 'O';
    }
    grid[y][x] = '@';
  }
  for (auto line : grid)
    std::cout << line << '\n';

  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[0].size(); x++) {
      if (grid[y][x] == 'O') {
        part1 += y * 100 + x;
      }
    }
  }

  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
