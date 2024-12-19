#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <string_view>
#include <vector>
#include <ranges>

long find_pattern(std::vector<std::string> towels, std::string pattern) {
  static std::map<std::string, long> cache;
  long count = 0;
  if (cache.contains(pattern))
    return cache[pattern];
  if (pattern.empty())
    return 1;

  for (auto t : towels)
    if (pattern.starts_with(t))
      count += find_pattern(towels, pattern.substr(t.size()));

  cache[pattern] = count;
  return count;
}

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  long part1 = 0;
  long part2 = 0;
  std::vector<std::string> towels;
  if (std::string line; std::getline(file, line)) {
    using std::operator""sv;
    for (auto t : std::views::split(line, ", "sv))
      towels.emplace_back(std::string_view(t));
  }

  std::vector<std::string> patterns;
  for (std::string line; std::getline(file, line);) {
    if (line.empty())
      continue;
    patterns.emplace_back(line);
  }

  for (auto p : patterns) {
    long ways = find_pattern(towels, p);
    part2 += ways;
    if (ways > 0)
      part1++;
  }

  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
