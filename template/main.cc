#include <iostream>
#include <regex>
#include <chrono>

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // do some setup
  std::regex e(R"((\w+) (\d+))");
  std::string str;

  // iterate over lines of the input file
  while (std::getline(std::cin, str))
  {
    std::smatch m;
    while (std::regex_search(str, m, e))
    {
      std::cout << str << std::endl;
      str = m.suffix();
    }
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" <<std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << std::endl;

  return 0;
}
