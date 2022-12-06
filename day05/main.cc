#include <iostream>
#include <regex>
#include <chrono>
#include <cmath>

struct MoveInstruction
{
  MoveInstruction(int count, int source, int target) : count(count), source(source), target(target)
  {
  }
  int count;
  int target;
  int source;
};

int index_to_column(int index)
{
  // 1 -> 1
  // 2 -> 5
  // 3 -> 9
  return (index * 4) - 3;
}

using Stack = std::vector<char>;
using Stacks = std::vector<Stack>;

Stacks string_to_stacks(const std::vector<std::string>& raw_stacks, int num_stacks)
{
  Stacks stacks;
  for (auto i = raw_stacks.rbegin(); i != raw_stacks.rend(); ++i)
  {
    for (int j = 1; j <= num_stacks; ++j)
    {
      int col = index_to_column(j);

      if (j >= stacks.size())
      {
        stacks.push_back(std::vector<char>());
      }

      if (col < (*i).size() && (*i)[col] != ' ')
      {
        std::cout << "Adding [" << (*i)[col] << "] to stack " << j << '\n';
        stacks[j - 1].push_back((*i)[col]);
      }
    }
  }
  return stacks;
}

std::ostream& operator<<(std::ostream& os, const Stacks& stacks)
{
  for (const auto stack : stacks)
  {
    for (auto i = stack.rbegin(); i != stack.rend(); ++i)
    {
      os << "[" << *i << "]" << '\n';
    }
    os << "-----\n";
  }
  return os;
}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // do some setup
  std::regex stack_nums_re(R"((?:(\d+)\s)+)");
  std::regex moves_re(R"(move (\d+) from (\d+) to (\d+))");
  std::string line;
  std::vector<std::string> raw_stacks;
  std::vector<MoveInstruction> instructions;


  int num_stacks;

  bool stack_input = true;

  // iterate over lines of the input file
  while (std::getline(std::cin, line))
  {
    std::smatch m;

    if (stack_input)
    {
      raw_stacks.push_back(line);

      if (std::regex_search(line, m, stack_nums_re))
      {
        stack_input = false;
        num_stacks = (line.size() + 3) / 4;
        raw_stacks.pop_back();

        std::cout << "Num stacks: " << num_stacks << std::endl;
      }
    }
    else if (std::regex_search(line, m, moves_re))
    {
      instructions.push_back(MoveInstruction(std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3])));
      line = m.suffix();
    }
  }

  Stacks stacks = string_to_stacks(raw_stacks, num_stacks);
  std::cout << instructions.size() << '\n';
  std::cout << stacks;


  for (const auto instr : instructions)
  {
    // for (int i = 0; i < instr.count; ++i)
    // {
    //   char c = stacks[instr.source - 1].back();
    //   std::cout << "Moving [" << c << "] to " << instr.target << '\n';
    //   stacks[instr.source - 1].pop_back();
    //   stacks[instr.target - 1].push_back(c);
    // }
    //

    std::cout << "Moving to " << instr.target << '\n';
    Stack& source = stacks[instr.source - 1];
    Stack& target = stacks[instr.target - 1];

    std::move(source.end() - instr.count, source.end(), std::back_inserter(target));
    source.erase(source.end() - instr.count, source.end());
    std::cout << stacks;
  }

  std::cout << stacks;

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  for (const auto stack : stacks)
  {
    if (stack.size())
    {
      std::cout << stack.back();
    }
  }

  std::cout << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << std::endl;

  return 0;
}
