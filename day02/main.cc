#include <iostream>
#include <regex>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

constexpr int k_A_Offset = static_cast<int>('A') - 1;
constexpr int k_X_Offset = static_cast<int>('X') - 1;

enum class GameResult
{
  kLoss = 0,
  kDraw = 1,
  kWin = 2,
};

GameResult get_result(int us, int them)
{
  switch (us - them)
  {
    case 0:
      return GameResult::kDraw;
    case 1:
    case -2:
      return GameResult::kWin;
    default:
      return GameResult::kLoss;
  }
}

int part1_p2_score(const char abc, const char xyz)
{
  int p1 = static_cast<int>(abc) - k_A_Offset;
  int p2 = static_cast<int>(xyz) - k_X_Offset;
  // std::cout << p1 << " vs. " << p2 << '\n';

  GameResult outcome = get_result(p2, p1);
  switch (outcome)
  {
    case GameResult::kWin: {
      return p2 + 6;
    }
    case GameResult::kDraw: {
      return p2 + 3;
    }
    default: {
      return p2;
    }
  }
}

int part2_p2_score(const char abc, const char xyz)
{
  int p1 = static_cast<int>(abc) - k_A_Offset;
  int p2;
  switch (xyz)
  {
    case 'X':
      p2 = (p1 + 1) % 3 + 1;
      return p2 + 0;
    case 'Y':
      p2 = p1;
      return p2 + 3;
    default:
      p2 = p1 % 3 + 1;
      return p2 + 6;
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
    // std::cout << "Score: " << part2_inc_score << '\n';
    part2_total_score += part2_inc_score;
    // std::cout << "------\n";
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;

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
