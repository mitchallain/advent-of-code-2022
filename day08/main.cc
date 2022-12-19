#include <Eigen/Dense>
#include <chrono>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

Eigen::MatrixXi parseInputToMatrix(const std::vector<std::string>& input)
{
  // parse input array to an eigen matrix
  Eigen::MatrixXi m(input.size(), input[0].size());
  for (size_t i = 0; i < input.size(); ++i)
  {
    for (size_t j = 0; j < input[i].size(); ++j)
    {
      m(i, j) = input[i][j] - '0';
    }
  }

  return m;
}

int countVisible(const Eigen::MatrixXi& m)
{
  Eigen::MatrixXi visible(m.rows(), m.cols());
  std::vector<int> tallest(m.rows(), -1);

  // sweep l to r
  for (auto i = 0; i < m.rows(); ++i)
  {
    for (auto j = 0; j < m.cols(); ++j)
    {
      if (m(i, j) > tallest[i])
      {
        // std::cout << i << " " << j << " is visible from left" << std::endl;
        ++visible(i, j);
        tallest[i] = m(i, j);
      }
    }
  }

  std::fill(tallest.begin(), tallest.end(), -1);
  // sweep r to l
  for (auto i = 0; i < m.rows(); ++i)
  {
    for (auto j = m.cols() - 1; j >= 0; --j)
    {
      if (m(i, j) > tallest[i])
      {
        // std::cout << i << " " << j << " is visible from right" << std::endl;
        ++visible(i, j);
        tallest[i] = m(i, j);
      }
    }
  }

  tallest.resize(m.cols());
  std::fill(tallest.begin(), tallest.end(), -1);
  // sweep t to b
  for (auto j = 0; j < m.cols(); ++j)
  {
    for (auto i = 0; i < m.rows(); ++i)
    {
      if (m(i, j) > tallest[j])
      {
        // std::cout << i << " " << j << " is visible from top" << std::endl;
        ++visible(i, j);
        tallest[j] = m(i, j);
      }
    }
  }

  std::fill(tallest.begin(), tallest.end(), -1);
  // sweep b to t
  for (auto j = 0; j < m.cols(); ++j)
  {
    for (auto i = m.rows() - 1; i >= 0; --i)
    {
      if (m(i, j) > tallest[j])
      {
        // std::cout << i << " " << j << " is visible from bottom" << std::endl;
        ++visible(i, j);
        tallest[j] = m(i, j);
      }
    }
  }
  // count visible trees
  // std::cout << visible << std::endl;
  return visible.count();
}

int highestScore(const Eigen::MatrixXi& m)
{
  int max_score = 0;
  for (auto i = 0; i < m.rows(); ++i)
  {
    for (auto j = 0; j < m.cols(); ++j)
    {
      // std::cout << "For location " << i << " " << j << std::endl;
      int score = 1;
      int dist = 0;

      // look left
      for (auto k = j - 1; k >= 0; --k)
      {
        ++dist;
        if (m(i, k) >= m(i, j))
        {
          break;
        }
      }
      // std::cout << "left dist: " << dist << std::endl;
      score *= dist;
      dist = 0;

      // look right
      for (auto k = j + 1; k < m.cols(); ++k)
      {
        ++dist;
        if (m(i, k) >= m(i, j))
        {
          break;
        }
      }
      // std::cout << "right dist: " << dist << std::endl;
      score *= dist;
      dist = 0;

      // look up
      for (auto k = i - 1; k >= 0; --k)
      {
        ++dist;
        if (m(k, j) >= m(i, j))
        {
          break;
        }
      }
      // std::cout << "up dist: " << dist << std::endl;
      score *= dist;
      dist = 0;

      // look down
      for (auto k = i + 1; k < m.rows(); ++k)
      {
        ++dist;
        if (m(k, j) >= m(i, j))
        {
          break;
        }
      }
      // std::cout << "down dist: " << dist << std::endl;
      score *= dist;

      if (score > max_score)
      {
        // std::cout << "new max score: " << score << " at " << i << " " << j << std::endl;
        max_score = score;
      }
      std::getchar();
    }
  }
  return max_score;
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

  auto m = parseInputToMatrix(lines);
  int visible_trees = countVisible(m);
  int scenic_score = highestScore(m);

  // std::cout << m.rows() << "x" << m.cols() << std::endl;

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << "Number of visible trees: " << visible_trees << std::endl;
  std::cout << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << "Highest scenic score: " << scenic_score << std::endl;
  std::cout << std::endl;

  return 0;
}
