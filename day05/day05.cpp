#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
//g++ day05.cpp -std=c++20
int main(int argc, char *argv[])
{
  std::string filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  int part1 = 0;
  int part2 = 0;

  std::map<int, std::list<int>> order;
  for (std::string line; std::getline(file, line) && !line.empty();) {
    std::stringstream ss(line);
    int x, y;
    ss >> x;
    ss.ignore(1);
    ss >> y;
    order[x].push_back(y);
  }

  for (std::string line; std::getline(file, line);) {
    std::stringstream ss(line);
    std::vector<int> manual;
    for (int page; ss >> page;) {
      manual.emplace_back(page);
      ss.ignore(1);
    }
    bool is_safe = true;
    for (int i = 1; i < manual.size(); i++) {
      int a = manual[i-1];
      int b = manual[i];
      auto it = std::find(order[a].begin(), order[a].end(), b);
      if (it == order[a].end()) {
        is_safe = false;
        break;
      }
    }

    if (is_safe) {
      part1 += manual[manual.size() / 2];
    } else {
      std::sort(manual.begin(), manual.end(), [&order](int a, int b){
        auto it = std::find(order[b].begin(), order[b].end(), a);
        return it == order[b].end();
      });
      part2 += manual[manual.size() / 2];
    }
  }

  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
