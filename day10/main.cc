#include <iostream>
#include <regex>
#include <chrono>
#include <cmath>

void renderPixel(int cycle, int x)
{
  int column = cycle % 40;
  if (std::abs(x - column + 1) <= 1)
  {
    std::cout << "#";
  }
  else
  {
    std::cout << ".";
  }

  if (column == 0)
  {
    std::cout << std::endl;
  }
}

int checkCycle(int cycle, int x, int total)
{
  // std::cout << "Cycle " << cycle << " signal = " << cycle << " x " << x
  //   << " = " << cycle * x << std::endl;
  if ((cycle - 20) % 40 == 0)
  {
    // std::cout << "Cycle " << cycle << " signal " << cycle * x << std::endl;
    total += cycle * x;
  }
  return total;
}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  std::vector<std::string> lines;
  std::string str;

  // iterate over lines of the input file
  while (std::getline(std::cin, str))
  {
    lines.push_back(str);
  }

  std::regex e(R"((\w+) ?(-?\d+)?)");
  std::smatch m;
  int cycle = 1;
  int x = 1;
  int total = 0;
  for (const auto& line : lines)
  {
    if (std::regex_search(line, m, e))
    {
      renderPixel(cycle, x);

      if (m[1] == "addx")
      {
        ++cycle;
        total = checkCycle(cycle, x, total);
        renderPixel(cycle, x);
        x += std::stoi(m[2]);
      }
      ++cycle;
      total = checkCycle(cycle, x, total);
    }
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << "Total: " << total << std::endl;
  std::cout << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << std::endl;

  return 0;
}
