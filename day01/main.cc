#include <iostream>
#include <regex>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // do some setup
  // std::regex e(R"((\w+) (\d+))");
  std::string str;
  int elf_sum = 0;

  // iterate over lines of the input file
  std::vector<int> elf_loads;
  while (std::getline(std::cin, str))
  {
    if (!str.empty())
    {
      elf_sum += std::stoi(str);
    }
    else
    {
      elf_loads.push_back(elf_sum);
      elf_sum = 0;
    }
  }
  elf_loads.push_back(elf_sum);

  std::sort(elf_loads.begin(), elf_loads.end(), std::greater<int>());

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" <<std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << "Elf Load #1: " << elf_loads[0] << '\n';
  std::cout << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << "Elf Load #2: " << elf_loads[1] << "\n";
  std::cout << "Elf Load #3: " << elf_loads[2] << "\n";
  std::cout << "Three Elf Load: "
    << std::accumulate(elf_loads.begin(),
        std::next(elf_loads.begin(), 3), 0) << "\n";
  std::cout << std::endl;

  return 0;
}
