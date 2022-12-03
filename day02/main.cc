#include <iostream>
#include <regex>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

constexpr int k_A_Offset = static_cast<int>('A') - 1;
constexpr int k_X_Offset = static_cast<int>('X') - 1;

bool is_winning_shape(int us, int them)
{
  return ((us > them) && (us != 3 || them != 1)) || (us == 1 && them == 3);
}

int part1_p2_score(const char abc, const char xyz)
{
  // 2 beats 1
  // 3 beats 2
  // 1 beats 3
  int p1 = static_cast<int>(abc) - k_A_Offset;
  int p2 = static_cast<int>(xyz) - k_X_Offset;
  std::cout << p1 << " vs. " << p2 << '\n';

  int outcome;
  if (p1 == p2) { outcome = 3; }
  else if (is_winning_shape(p2, p1))  { outcome = 6; }
  else { outcome = 0; }

  std::cout << "P2 Score: " << outcome + p2 << '\n';

  return outcome + p2;
}

int part2_p2_score(const char abc, const char xyz)
{
  int p1 = static_cast<int>(abc) - k_A_Offset;
  // peak laziness
  int guess1 = p1 % 3 + 1;
  int guess2 = (p1 + 1) % 3 + 1;
  std::cout << "P1: " << p1;
  if (xyz == 'X')
  {
    std::cout << " - need loss, trying " << guess1 << " and " <<  guess2 << '\n';
    if (is_winning_shape(guess1, p1)) { return guess2 + 0; }
    else { return guess1 + 0; }
  }
  else if (xyz == 'Y') { std::cout << " - need draw\n"; return p1 + 3; }
  else
  {
    std::cout << " - need win, trying " << guess1 << " and " <<  guess2 << '\n';
    if (is_winning_shape(guess1, p1)) { return guess1 + 6; }
    else { return guess2 + 6; }
  }
}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // do some setup
  // std::regex e(R"((\w+) (\d+))");
  std::string str;
  int part1_total_score = 0;
  int part2_total_score = 0;

  // iterate over lines of the input file
  while (std::getline(std::cin, str))
  {
    part1_total_score += part1_p2_score(str[0], str[2]);

    int part2_inc_score = part2_p2_score(str[0], str[2]);
    std::cout << "Score: " << part2_inc_score << '\n';
    part2_total_score += part2_inc_score;
    std::cout << "------\n";
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" <<std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << "Total Score: " << part1_total_score << '\n';
  std::cout << std::endl;

  std::cout << "Part Two\n";
  std::cout << "--------\n";
  std::cout << "Total Score: " << part2_total_score << '\n';
  std::cout << std::endl;

  return 0;
}
