#include <iostream>
#include <string>
#include <array>
#include <chrono>
#include <vector>

constexpr int k_a_Offset = static_cast<int>('a');
constexpr int k_A_Offset = static_cast<int>('A') - (static_cast<int>('z') - k_a_Offset + 1);

int char_to_priority(const char c)
{
  int ord = static_cast<int>(c);
  if (ord >= k_a_Offset)
  {
    return ord - k_a_Offset;
  }
  else
  {
    return ord - k_A_Offset;
  }
}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // do some setup
  std::string str;
  std::array<std::bitset<3>, 52> grouped_counts;
  grouped_counts.fill(0);
  std::bitset<52> compartment_1{0};
  int sum_1 = 0;
  int sum_2 = 0;
  int intragroup_idx = 0;

  // std::cout << static_cast<int>('a') << " " << static_cast<int>('A');
  // std::cout << " " << k_a_Offset << " " << k_A_Offset << '\n';

  // iterate over lines of the input file
  while (std::getline(std::cin, str))
  {
    auto mid = str.begin() + str.size() / 2;
    for (auto c = str.begin(); c != mid; ++c)
    {
      int idx = char_to_priority(*c);
      compartment_1[idx] = true;
    }

    for (auto c = mid; c != str.end(); ++c)
    {
      int idx = char_to_priority(*c);
      if (compartment_1[idx])
      {
        // std::cout << idx + 1 << '\n';
        sum_1 += idx + 1;
        break;
      }
    }
    compartment_1 = 0;

    // part two
    for (const auto c : str)
    {
      int idx = char_to_priority(c);
      grouped_counts[idx][intragroup_idx] = true;

      if (grouped_counts[idx].all())
      {
        // std::cout << idx + 1 << '\n';
        sum_2 += idx + 1;
        break;
      }
    }

    intragroup_idx += 1;
    if (intragroup_idx == 3)
    {
      intragroup_idx = 0;
      grouped_counts.fill(0);
    }
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << sum_1 << '\n';
  std::cout << std::endl;

  std::cout << "Part Two\n";
  std::cout << "--------\n";
  std::cout << sum_2 << '\n';
  std::cout << std::endl;

  return 0;
}
