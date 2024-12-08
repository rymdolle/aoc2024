#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  std::vector<std::string> grid;
  std::map<char, std::vector<std::pair<int,int>>> freq;
  for (std::string line; std::getline(file, line);) {
    for (int x = 0; x < line.size(); x++) {
      if (line[x] != '.') {
        freq[line[x]].push_back({x, grid.size()});
      }
    }
    grid.push_back(line);
  }

  std::set<std::pair<int,int>> part1;
  for (auto [k,v] : freq) {
    for (int i = 0; i < v.size() - 1; i++) {
      auto [x,y] = v[i];
      for (int j = i+1; j < v.size(); j++) {
        auto [x2,y2] = v[j];
        int dx = x2 - x;
        int dy = y2 - y;
        if (y-dy >= 0 && x-dx >= 0 && y-dy < grid.size() && x-dx < grid[0].size()) {
          part1.insert({x-dx, y-dy});
          grid[y-dy][x-dx] = '#';
        }
        if (y2+dy >= 0 && x2+dx >= 0 && y2+dy < grid.size() && x2+dx < grid[0].size()) {
          part1.insert({x2+dx, y2+dy});
          grid[y2+dy][x2+dx] = '#';
        }

        x2 -= dx;
        y2 -= dy;

        while (y2+dy >= 0 && x2+dx >= 0 && y2+dy < grid.size() && x2+dx < grid[0].size()) {
          grid[y2+dy][x2+dx] = '#';
          x2 += dx;
          y2 += dy;
        }

        int x3 = x - dx;
        int y3 = y - dy;
        while (y3-dy >= 0 && x3-dx >= 0 && y3-dy < grid.size() && x3-dx < grid[0].size()) {
          grid[y3-dy][x3-dx] = '#';
          x3 -= dx;
          y3 -= dy;
        }
      }
    }
  }

  int part2 = 0;
  for ( auto r : grid) {
    for ( auto c : r) {
      if (c != '.')
        part2++;
    }
  }

  std::cout << part1.size() << '\n';
  std::cout << part2 << '\n';
  return 0;
}
