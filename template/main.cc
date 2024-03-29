#include <iostream>
#include <regex>
#include <chrono>

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // do some setup
  // std::regex e(R"((\w+) (\d+))");

  std::vector<std::string> lines;
  std::string str;

  // iterate over lines of the input file
  while (std::getline(std::cin, str))
  {
    lines.push_back(str);
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" <<std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << std::endl;

  std::cout << "Part Two\n";
  std::cout << "--------\n";
  std::cout << std::endl;

  return 0;
}
