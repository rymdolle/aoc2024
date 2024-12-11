#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <list>

long split_stone(long start, int n) {
  long total = 1;
  std::list<long> stones = {start};
  for (int i = 0; i < n; i++) {
    for (auto it = stones.begin(); it != stones.end(); it++) {
      auto& stone = *it;
      if (stone == 0) {
        stone++;
        continue;
      }
      std::string stone_str = std::to_string(stone);
      if (stone_str.length() % 2 == 0) {
        stone = std::stoi(stone_str.substr(stone_str.length()/2));
        stones.insert(it, std::stoi(stone_str.substr(0, stone_str.length()/2)));
        total++;
      } else {
        stone *= 2024;
      }
    }
  }

  return total;
}

int main(int argc, char *argv[])
{
  std::string filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  int part1 = 0;
  int part2 = 0;
  std::list<int> stones;
  for (std::string line; std::getline(file, line);) {
    std::stringstream ss(line);
    long stone;
    while (ss >> stone)
      stones.emplace_back(stone);
  }

  for (auto it = stones.begin(); it != stones.end(); it++) {
    part1 += split_stone(*it, 25);
  }

  for (auto s : stones)
    std::cout << s << ' ';
  std::cout << '\n';
  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
