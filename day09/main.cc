#include <iostream>
#include <regex>
#include <chrono>
#include <map>
#include <cmath>
#include <vector>

struct Coordinate
{
  Coordinate() : x(0), y(0) {}
  Coordinate(int xi, int yi) : x(xi), y(yi) {}
  int x;
  int y;
};

// implement addition and subtraction operators on Coordinate
Coordinate operator+(const Coordinate& lhs, const Coordinate& rhs)
{
  return Coordinate(lhs.x + rhs.x, lhs.y + rhs.y);
}

Coordinate operator-(const Coordinate& lhs, const Coordinate& rhs)
{
  return Coordinate(lhs.x - rhs.x, lhs.y - rhs.y);
}

// comparison operator for Coordinate
bool operator==(const Coordinate& lhs, const Coordinate& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

// less than
bool operator<(const Coordinate& lhs, const Coordinate& rhs)
{
  return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}

// ostream operator for Coordinate
std::ostream& operator<<(std::ostream& os, const Coordinate& c)
{
  os << "(" << c.x << "," << c.y << ")";
  return os;
}

void updateTail(const Coordinate& prev, Coordinate& tail)
{
  Coordinate move = prev - tail;
  // absolute value of move
  if (std::abs(move.x) <= 1 && std::abs(move.y) <= 1)
  {
    move.x = 0;
    move.y = 0;
  }
  else
  {
    if (std::abs(move.x) == 2)
    {
      move.x /= 2;
    }
    if (std::abs(move.y) == 2)
    {
      move.y /= 2;
    }
  }

  // std::cout << "Prev: " << prev << " Tail: " << tail << " move: " << move << std::endl;

  tail = tail + move;
}

void visualizeSnek(const Coordinate& head, const std::vector<Coordinate>& tails)
{
  // find the min and max x and y
  int minx = head.x;
  int maxx = head.x;
  int miny = head.y;
  int maxy = head.y;

  for (const auto& tail : tails)
  {
    if (tail.x < minx)
    {
      minx = tail.x;
    }
    if (tail.x > maxx)
    {
      maxx = tail.x;
    }
    if (tail.y < miny)
    {
      miny = tail.y;
    }
    if (tail.y > maxy)
    {
      maxy = tail.y;
    }
  }

  // visualize the snake in a grid using . for empty spaces
  // and # for occupied spaces
  // positive y increases to the right and positive y increases up
  for (int y = maxy; y >= miny; --y)
  {
    for (int x = minx; x <= maxx; ++x)
    {
      Coordinate c(x, y);
      if (c == head)
      {
        std::cout << "H";
      }
      else if (std::find(tails.begin(), tails.end(), c) != tails.end())
      {
        std::cout << "#";
      }
      else
      {
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }
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

  Coordinate head;
  std::vector<Coordinate> tails(9);
  std::map<Coordinate, bool> p1_visited;
  std::map<Coordinate, bool> p2_visited;

  int p1_num_visited = 1;
  int p2_num_visited = 1;
  p1_visited[tails[0]] = true;
  p2_visited[tails[8]] = true;

  for (auto& line : lines)
  {
    Coordinate increment;
    switch (line[0])
    {
      case 'U':
        increment = Coordinate(0, 1);
        break;
      case 'D':
        increment = Coordinate(0, -1);
        break;
      case 'R':
        increment = Coordinate(1, 0);
        break;
      case 'L':
        increment = Coordinate(-1, 0);
        break;
    }

    for (int i = 0; i < std::stoi(line.substr(2)); ++i)
    {
      head = head + increment;
      Coordinate* prev = &head;

      for (auto& tail : tails)
      {
        // visualizeSnek(head, tails);
        // std::cout << "--------------" << std::endl;
        updateTail(*prev, tail);
        prev = &tail;
      }

      if (p1_visited.find(tails[0]) == p1_visited.end())
      {
        p1_visited[tails[0]] = true;
        ++p1_num_visited;
      }

      if (p2_visited.find(tails[8]) == p2_visited.end())
      {
        p2_visited[tails[8]] = true;
        ++p2_num_visited;
      }
    }

    // std::cout << "After movement " << line << ", head is " << head
    //   << " and tail 0 is " << tails[0] << " and tail 8 is " << tails[8] << std::endl;
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << "Number of visited locations: " << p1_num_visited << std::endl;
  std::cout << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << "Number of visited locations: " << p2_num_visited << std::endl;
  std::cout << std::endl;

  return 0;
}
