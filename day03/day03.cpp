#include <fstream>
#include <iostream>
//g++ day03.cpp -std=c++20
int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::string data(std::istreambuf_iterator<char>{file}, {});
  int part1 = 0;
  int part2 = 0;
  bool enable = true;
  while (!data.empty()) {
    if (data.starts_with("do()")) {
      enable = true;
      data = data.substr(4);
    }
    if (data.starts_with("don't()")) {
      enable = false;
      data = data.substr(7);
    }
    if (data.starts_with("mul(")) {
      data = data.substr(4);
      size_t len;
      int a = std::stoi(data, &len, 10);
      if (data[len] == ',') {
        data = data.substr(len + 1);
        int b = std::stoi(data, &len, 10);
        if (data[len] == ')') {
          data = data.substr(len);
          part1 += a * b;
          if (enable) {
            part2 += a * b;
          }
        }
      }
    }

    data = data.substr(1);
  }
  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
