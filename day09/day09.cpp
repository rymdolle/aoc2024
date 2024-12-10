#include <fstream>
#include <string>
#include <iostream>
#include <list>

int main(int argc, char *argv[])
{
  std::string filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  long part1 = 0;
  long part2 = 0;
  std::string line;
  std::getline(file, line);
  std::list<int> files;
  std::list<int> spaces;
  for (int i = 0; i < line.length(); i++) {
    if (i % 2 == 0)
      files.push_back(line[i] - '0');
    else
      spaces.push_back(line[i] - '0');
  }

  int total = 0;
  for (auto f : files) {
    total += f;
  }
  int total_files = files.size();
  int file_id = 0;
  int file_back = total_files - 1;
  for (int i = 0; i < total && !files.empty();) {
    for (int f = 0; f < files.front(); f++, i++) {
      std::cout << "a "
                << files.front() << ' ' << i << '*' << file_id << '=' << i * file_id << '\n';
      part1 += i * file_id;
    }
    file_id++;
    files.pop_front();
    for (int s = 0; s < spaces.front() && !files.empty();) {
      if (files.back() == 0) {
        files.pop_back();
        file_back--;
        continue;
      }
      std::cout << "b "
                << files.back() << ' ' << i << '*' << file_back << '=' << i * file_back << '\n';
      part1 += i * file_back;
      i++;
      s++;
      files.back()--;
    }
    spaces.pop_front();
  }

  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
