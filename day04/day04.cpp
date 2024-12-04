#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//g++ day04.cpp -std=c++20

int part1(const std::vector<std::string>& g) {
  int total = 0;
  for (int y = 0; y < g.size(); y++) {
    for (int i = 0; i < g[y].size(); i++) {
      // left and right
      if (g[y].substr(i).starts_with("XMAS"))
        total++;
      if (g[y].substr(i).starts_with("SAMX"))
        total++;
    }
    for (int x = 0; x < g[0].length(); x++) {
      // down + up
      if (y <= g.size() - 4) {
        if (g[y][x]=='X' && g[y+1][x]=='M' && g[y+2][x]=='A' && g[y+3][x]=='S')
          total++;
        if (g[y][x]=='S' && g[y+1][x]=='A' && g[y+2][x]=='M' && g[y+3][x]=='X')
          total++;
      }

      // diag left
      if (x >= 3  && y >= 3) {
        if (g[y][x]=='X' && g[y-1][x-1]=='M' && g[y-2][x-2]=='A' && g[y-3][x-3]=='S')
          total++;
        if (g[y][x]=='S' && g[y-1][x-1]=='A' && g[y-2][x-2]=='M' && g[y-3][x-3]=='X')
          total++;
      }

      // diag right
      if (x < g[0].size() && y >= 3) {
        if (g[y][x]=='X' && g[y-1][x+1]=='M' && g[y-2][x+2]=='A' && g[y-3][x+3]=='S')
          total++;
        if (g[y][x]=='S' && g[y-1][x+1]=='A' && g[y-2][x+2]=='M' && g[y-3][x+3]=='X')
          total++;
      }
    }
  }

  return total;
}

int part2(const std::vector<std::string>& g) {
  int total = 0;
  for (int y = 1; y < g.size() - 1; y++) {
    for (int x = 1; x < g[0].length() - 1; x++) {
      if (g[y][x]=='A') {
        if ((g[y-1][x-1]=='M' && g[y+1][x+1]=='S') && (g[y-1][x+1]=='M' && g[y+1][x-1]=='S'))
          total++;
        if ((g[y-1][x-1]=='M' && g[y+1][x+1]=='S') && (g[y-1][x+1]=='S' && g[y+1][x-1]=='M'))
          total++;
        if ((g[y-1][x-1]=='S' && g[y+1][x+1]=='M') && (g[y-1][x+1]=='S' && g[y+1][x-1]=='M'))
          total++;
        if ((g[y-1][x-1]=='S' && g[y+1][x+1]=='M') && (g[y-1][x+1]=='M' && g[y+1][x-1]=='S'))
          total++;
      }
    }
  }

  return total;
}

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::vector<std::string> grid;
  for (std::string line; std::getline(file, line);) {
    grid.emplace_back(line);
  }

  std::cout << part1(grid) << '\n';
  std::cout << part2(grid) << '\n';
  return 0;
}
