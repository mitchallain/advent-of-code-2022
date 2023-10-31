#include <Eigen/Dense>
#include <chrono>
#include <iostream>
#include <queue>
#include <regex>
#include <set>
#include <string>
#include <vector>

constexpr int k_a_Offset = static_cast<int>('a');
constexpr int k_z_Offset = static_cast<int>('z');

typedef Eigen::Array<bool, Eigen::Dynamic, Eigen::Dynamic> ArrayXb;

struct Coordinate
{
  int x;
  int y;

  // equality comparison
  bool operator==(const Coordinate& other) const { return x == other.x && y == other.y; }

  // inequality comparison
  bool operator!=(const Coordinate& other) const { return !(*this == other); }

  // less than comparison
  bool operator<(const Coordinate& other) const { return x < other.x || (x == other.x && y < other.y); }
};

typedef std::pair<int, Coordinate> CoordinateDistancePair;

struct Map
{
  Eigen::MatrixXi elevations;
  Coordinate start;
  Coordinate end;
};

// ostream operator for map state
std::ostream& operator<<(std::ostream& os, const Map& state)
{
  os << state.elevations << std::endl;
  os << "\n";
  os << "Start: " << state.start.x << ", " << state.start.y << std::endl;
  os << "End: " << state.end.x << ", " << state.end.y << std::endl;
  return os;
}

// return a unique ptr to a new map state instance
Map constructMap(const std::vector<std::string>& lines)
{
  Map map;
  map.elevations = Eigen::MatrixXi(lines.size(), lines[0].size());
  for (size_t i = 0; i < lines.size(); ++i)
  {
    for (size_t j = 0; j < lines[i].size(); ++j)
    {
      int elevation = lines[i][j] - k_a_Offset;
      if (lines[i][j] == 'S')
      {
        map.start.x = i;
        map.start.y = j;
        elevation = 0;
      }
      else if (lines[i][j] == 'E')
      {
        map.end.x = i;
        map.end.y = j;
        elevation = static_cast<int>('z') - k_a_Offset;
      }
      map.elevations(i, j) = elevation;
    }
  }
  return map;
}

std::vector<Coordinate> getTraversable(const Map& map, const Coordinate& current)
{
  std::vector<Coordinate> traversable;

  if (current.x > 0 &&
      (map.elevations(current.x - 1, current.y)
       - map.elevations(current.x, current.y) <= 1))
  {
    traversable.push_back(Coordinate{current.x - 1, current.y});
  }
  if (current.y > 0 &&
      (map.elevations(current.x, current.y - 1)
       - map.elevations(current.x, current.y) <= 1))
  {
    traversable.push_back(Coordinate{current.x, current.y - 1});
  }
  if (current.x < map.elevations.rows() - 1 &&
      (map.elevations(current.x + 1, current.y)
       - map.elevations(current.x, current.y) <= 1))
  {
    traversable.push_back(Coordinate{current.x + 1, current.y});
  }
  if (current.y < map.elevations.cols() - 1 &&
      (map.elevations(current.x, current.y + 1)
       - map.elevations(current.x, current.y) <= 1))
  {
    traversable.push_back(Coordinate{current.x, current.y + 1});
  }
  return traversable;
}

int djikstraShortestPathLength(const Map& map)
{
  // priority queue of coordinates
  std::priority_queue<CoordinateDistancePair, std::vector<CoordinateDistancePair>, std::greater<CoordinateDistancePair>> pq;
  pq.push(std::make_pair(0, map.start));

  // initializes the distances to infinity, start to zero
  Eigen::ArrayXi distances = Eigen::ArrayXi::Constant(map.elevations.rows(), map.elevations.cols(), std::numeric_limits<int>::max());
  distances(map.start.x, map.start.y) = 0;

  while (!pq.empty())
  {
    Coordinate current = pq.top().second;
    pq.pop();

    std::vector<Coordinate> traversable = getTraversable(map, current);
    for (auto& next : traversable)
    {
      int distance = distances(current.x, current.y) + 1;
      if (distance < distances(next.x, next.y))
      {
        distances(next.x, next.y) = distance;
        pq.push(std::make_pair(distance, next));
      }
    }
  }

  return distances(map.end.x, map.end.y);
}

// Eigen::MatrixXi tentative_distance
// std::set<Coordinate> unvisited

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

  auto map = constructMap(lines);
  std::cout << map << std::endl;

  // use djikstra's algorithm to find the shortest path
  // https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
  int length = djikstraShortestPathLength(map);

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << "Shortest path length: " << length << std::endl;
  std::cout << std::endl;

  std::cout << "Part Two\n";
  std::cout << "--------\n";
  std::cout << std::endl;

  return 0;
}
