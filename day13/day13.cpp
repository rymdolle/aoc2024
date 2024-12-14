#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <future>
#include <list>
#include <string>
#include <iostream>
#include <thread>

struct machine {
  struct Prize {
    long x;
    long y;
  } prize;
  struct A {
    long x;
    long y;
  } a;
  struct B {
    long x;
    long y;
  } b;
};

long solve_naive(int index, machine m) {
  long a{0}, b{0};
  while (m.prize.x > 0 && m.prize.y > 0) {
    if (m.prize.x % m.b.x == 0 && m.prize.y % m.b.y == 0 && m.prize.x / m.b.x == m.prize.y / m.b.y) {
      b += m.prize.x / m.b.x;
      m.prize.x /= m.b.x;
      m.prize.y /= m.b.y;
      std::cout << "PASS: " << index << ' ' << a << ',' << b << "\n\n";
      return a * 3 + b;
    }

    a += 1;
    m.prize.x -= m.a.x;
    m.prize.y -= m.a.y;
  }

  std::cout << "FAIL " << index << "\n\n";
  return 0;
}

long solve(int index, machine m) {
  //A = (px*by - prizey*bx) / (ax*by - ay*bx)
  //B = (ax*py - ay*px) / (ax*by - ay*bx)
  long a = (m.prize.x*m.b.y - m.prize.y*m.b.x) / (m.a.x*m.b.y - m.a.y*m.b.x);
  long b = (m.a.x*m.prize.y - m.a.y*m.prize.x) / (m.a.x*m.b.y - m.a.y*m.b.x);
  std::pair<long,long> A = {m.a.x * a + m.b.x * b, m.a.y * a + m.b.y * b};
  std::pair<long,long> B = {m.prize.x, m.prize.y};
  if (A == B) {
    std::cout << "PASS: (solve) " << index << ' ' << a << ',' << b << "\n\n";
    return a * 3 + b;
  }
  std::cout << "FAIL (solve) " << index << "\n\n";
  return 0;
}

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  long part1 = 0;
  long part2 = 0;

  const size_t maxThreads = 24;
  std::list<std::future<void>> tasks;
  std::mutex resultMutex;

  int index = 1;
  for (std::string line; std::getline(file, line); index++) {
    struct machine m;
    std::sscanf(line.c_str(), "Button A: X+%ld, Y+%ld", &m.a.x, &m.a.y);
    //std::cout << "A:     " << m.a.x << ',' << m.a.y << '\n';
    std::getline(file, line);

    std::sscanf(line.c_str(), "Button B: X+%ld, Y+%ld", &m.b.x, &m.b.y);
    //std::cout << "B:     " << m.b.x << ',' << m.b.y << '\n';
    std::getline(file, line);

    std::sscanf(line.c_str(), "Prize: X=%ld, Y=%ld", &m.prize.x, &m.prize.y);
    //std::cout << "Prize: " << m.prize.x << ',' << m.prize.y << '\n';
    std::getline(file, line);

    part1 += solve_naive(index, m);
    m.prize.x += 10'000'000'000'000;
    m.prize.y += 10'000'000'000'000;
    part2 += solve(index, m);

    auto task = [index, &part2, &resultMutex](machine m) {
      long result = solve_naive(index, m);
      std::lock_guard<std::mutex> lock(resultMutex);
      part2 += result;
    };

    //tasks.emplace_back(std::async(std::launch::async, task, m));
    while (tasks.size() >= maxThreads) {
      for (auto it = tasks.begin(); it != tasks.end();) {
        if (it->wait_for(std::chrono::seconds(0)) == std::future_status::ready)
          it = tasks.erase(it);
        else
          it++;
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }

  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
