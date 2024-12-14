#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>

std::set<std::pair<int,int>> flood_fill(int x, int y,
                                        const std::vector<std::string>& grid,
                                        std::set<std::pair<int,int>> region = {}) {
  std::vector<std::pair<int,int>> directions{{1,0},{-1,0},{0,1},{0,-1}};
  region.insert({x,y});
  for (auto [dx,dy] : directions) {
    if (x+dx < 0 || x+dx >= grid[0].size())
      continue;
    if (y+dy < 0 || y+dy >= grid.size())
      continue;

    if (grid[y+dy][x+dx] == grid[y][x] && !region.contains({x+dx,y+dy})) {
      auto res = flood_fill(x+dx, y+dy, grid, region);
      region.insert(res.begin(), res.end());
    }
  }
  return region;
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
  for (std::string line; std::getline(file, line);) {
    grid.emplace_back(line);
  }

  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[0].size(); x++) {
      if (grid[y][x] == ' ')
        continue;
      auto region = flood_fill(x, y, grid);
      int fence = 0;
      for (auto& [x,y] : region) {
        fence += 4;
        if (region.contains({x+1,y}))
          fence--;
        if (region.contains({x-1,y}))
          fence--;
        if (region.contains({x,y+1}))
          fence--;
        if (region.contains({x,y-1}))
          fence--;
      }
      part1 += fence * region.size();
      std::cout << grid[y][x] << ' ' << region.size() << '*' << fence << '\n';
      for (auto [x,y] : region) {
        grid[y][x] = ' ';
      }
    }
  }

  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
