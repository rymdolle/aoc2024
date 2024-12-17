#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

std::vector<int> read_program(std::string line) {
  std::vector<int> program;
  std::stringstream ss(line);
  int instruction;
  while (ss >> instruction) {
    program.emplace_back(instruction);
    ss.ignore(1);
  }
  return program;
}

void print_program(const std::vector<int> program) {
  for (int i = 0; i < program.size() - 1 && !program.empty(); i++)
    std::cout << program[i] << ',';

  if (!program.empty())
    std::cout << program.back() << '\n';
}

long check_program(const std::vector<int>& program,
                   const std::vector<int>& output) {
  if (output.size() < program.size())
    return std::pow(10, 10);
  for (int i = program.size() - 1; i >= 4; i--) {
    if (program[i] != output[i]) {
      return std::pow(10, i-4);
    }
  }
  return 1;
}

long combo(int op, long a, long b, long c) {
  switch (op) {
  case 0:
  case 1:
  case 2:
  case 3:
    return op;
  case 4:
    return a;
  case 5:
    return b;
  case 6:
    return c;
  case 7:
  default:
    std::exit(1);
  }
}

int execute(int pc, int ip, int op, long& a, long& b, long& c,
            std::vector<int>& output) {
  switch (ip) {
  case 0:
    a /= std::pow(2, combo(op, a, b, c));
    break;

  case 1:
    b ^= op;
    break;

  case 2:
    b = combo(op, a, b, c) % 8;
    break;

  case 3:
    if (a != 0) return op;
    break;

  case 4:
    b ^= c;
    break;

  case 5:
    output.emplace_back(combo(op, a, b, c) % 8);
    break;

  case 6:
    b = a / std::pow(2, combo(op, a, b, c));
    break;

  case 7:
    c = a / std::pow(2, combo(op, a, b, c));
    break;
  }

  return pc + 2;
}

std::vector<int> run(std::vector<int> program, long& a, long& b, long& c) {
  std::vector<int> output;
  int pc = 0;
  while (pc < program.size()) {
    int ip = program[pc];
    int op = program[pc+1];
    pc = execute(pc, ip, op, a, b, c, output);
  }
  return output;
}

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::string part1;
  long part2 = 0;
  long a, b, c;
  std::string line;
  std::vector<int> program;
  std::getline(file, line);
  std::sscanf(line.c_str(), "Register A: %ld", &a);
  std::getline(file, line);
  std::sscanf(line.c_str(), "Register B: %ld", &b);
  std::getline(file, line);
  std::sscanf(line.c_str(), "Register C: %ld", &c);
  std::getline(file, line);
  std::getline(file, line);
  line = line.substr(9);

  std::vector<int> output;
  program = read_program(line);
  output = run(program, a, b, c);
  for (auto i : output) {
    part1.push_back('0' + i);
    part1.push_back(',');
  }
  part1.pop_back();

  do {
    part2 += check_program(program, output);
    std::cout << part2 << ' ' << output.size() << ' ';
    print_program(output);
    a = part2;
    b = 0;
    c = 0;
    output = run(program, a, b, c);
  } while (output != program);
  std::cout << '\n';

  std::cout << part1 << '\n';
  std::cout << part2 << '\n';
  return 0;
}
