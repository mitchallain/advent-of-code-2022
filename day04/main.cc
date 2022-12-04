#include <iostream>
#include <regex>
#include <chrono>
#include <type_traits>

enum class MergeIntervals
{
  kLessDisjoint = 0,
  kLessOverlapping = 1,
  kSpanning = 2,
  kGreaterOverlapping = 3,
  kSpanned = 4,
  kGreaterDisjoint = 5,
};

struct Interval
{
  Interval() : lower(0), upper(0) {}
  Interval(int lower, int upper) : lower(lower), upper(upper) {}
  int lower;
  int upper;
};

std::ostream& operator<<(std::ostream& os, const Interval iv)
{
  os << iv.lower << "-" << iv.upper;
  return os;
}

MergeIntervals classify_intervals(const Interval a, const Interval b)
{
  MergeIntervals mi;
  if (a.lower <= b.lower)
  {
    if (a.upper < b.lower)
    {
      mi = MergeIntervals::kLessDisjoint;
    }
    else if ((a.lower == b.lower) && (b.upper > a.upper))
    {
      mi = MergeIntervals::kSpanned;
    }
    else if ((a.upper < b.upper) && (a.lower < b.lower))
    {
      mi = MergeIntervals::kLessOverlapping;
    }
    else
    {
      mi = MergeIntervals::kSpanning;
    }
  }
  else
  {
    if (b.upper < a.lower)
    {
      mi = MergeIntervals::kGreaterDisjoint;
    }
    else if (b.upper < a.upper)
    {
      mi = MergeIntervals::kGreaterOverlapping;
    }
    else
    {
      mi = MergeIntervals::kSpanned;
    }
  }
  return mi;
}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // do some setup
  std::regex e(R"((\d+)-(\d+),(\d+)-(\d+))");
  std::string str;
  int contained = 0;
  int overlapping = 0;

  // iterate over lines of the input file
  while (std::getline(std::cin, str))
  {
    std::smatch m;
    while (std::regex_search(str, m, e))
    {
      Interval a(std::stoi(m[1]), std::stoi(m[2]));
      Interval b(std::stoi(m[3]), std::stoi(m[4]));
      MergeIntervals mi = classify_intervals(a, b);

      std::cout << "First: " << a << ", Second: " << b;
      std::cout << " - " << static_cast<std::underlying_type_t<MergeIntervals>>(mi) << '\n';
      str = m.suffix();

      switch (mi)
      {
        case MergeIntervals::kSpanning:
        case MergeIntervals::kSpanned:
          contained += 1;
        case MergeIntervals::kLessOverlapping:
        case MergeIntervals::kGreaterOverlapping:
          overlapping += 1;
      }
    }
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << contained << '\n';
  std::cout << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << overlapping << '\n';
  std::cout << std::endl;

  return 0;
}
