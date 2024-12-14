#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

class robot {
public:
  int x, y;
  int dx, dy;
};

bool print(int width, int height, std::vector<robot> robots, bool output = false) {
  int max = 0;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int count = 0;
      for (auto& r : robots) {
        if (r.x == x && r.y == y) {
          count++;
        }
      }
      if (output) {
        if (count)
          std::cout << count;
        else
          std::cout << '.';
      }
      max = std::max(max, count);
    }
    if (output)
      std::cout << '\n';
  }
  if (output)
    std::cout << '\n';
  return max == 1;
}

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  int part1 = 0;
  int part2 = 0;
  std::vector<robot> robots;
  for (std::string line; std::getline(file, line);) {
    robot r;
    std::sscanf(line.c_str(), "p=%d,%d v=%d,%d", &r.x, &r.y, &r.dx, &r.dy);
    std::cout << r.x << ',' << r.y << ' ' << r.dx << ',' << r.dy << '\n';
    robots.push_back(r);
  }

  int width = 101;
  int height = 103;
  for (int i = 0; i < 10000; i++) {
    if (print(width, height, robots)) {
      part2 = i;
      print(width, height, robots, true);
      break;
    }
    for (auto& r : robots) {
      r.x += r.dx;
      if (r.x >= width) r.x -= width;
      if (r.x < 0) r.x += width;
      r.y += r.dy;
      if (r.y >= height) r.y -= height;
      if (r.y < 0) r.y += height;
    }
  }

  int q1 = 0;
  int q2 = 0;
  int q3 = 0;
  int q4 = 0;

  for (auto& r : robots) {
    if (r.x > width / 2 && r.y < height / 2)
      q1++;
    if (r.x < width / 2 && r.y < height / 2)
      q2++;
    if (r.x < width / 2 && r.y > height / 2)
      q3++;
    if (r.x > width / 2 && r.y > height / 2)
      q4++;
  }

  part1 = q1 * q2 * q3 * q4;

  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
