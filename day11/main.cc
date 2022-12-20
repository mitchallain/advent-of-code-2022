#include <iostream>
#include <regex>
#include <chrono>
#include <functional>
#include <vector>

typedef std::function<int(int)> UnaryIntOp;
typedef std::function<int(int, int)> BinaryIntOp;

struct Monkey
{
  Monkey(UnaryIntOp op, int test_divisible_by, int true_monkey, int false_monkey)
    : op(op),
      test_divisible_by(test_divisible_by),
      true_monkey(true_monkey),
      false_monkey(false_monkey),
      inspections(0)
  {
  }
  UnaryIntOp op;
  std::vector<int> items;
  int test_divisible_by;
  int true_monkey;
  int false_monkey;
  int inspections;
};

// ostream operator for Monkey
std::ostream& operator<<(std::ostream& os, const Monkey& m)
{
  os << "Monkey(" << m.items.size() << " items, test_divisible_by = " << m.test_divisible_by
    << ", true_monkey = " << m.true_monkey << ", false_monkey = " << m.false_monkey << ")";
  return os;
}

void simulateMonkeys(std::vector<Monkey>& monkeys, bool worry_thirds)
{
  for (auto& monkey : monkeys)
  {
    while (monkey.items.size() > 0)
    {
      ++monkey.inspections;
      int item = monkey.items.back();
      monkey.items.pop_back();

      item = monkey.op(item);
      if (worry_thirds)
      {
        item /= 3;
      }
      if (item % monkey.test_divisible_by == 0)
      {
        monkeys[monkey.true_monkey].items.push_back(item);
      }
      else
      {
        monkeys[monkey.false_monkey].items.push_back(item);
      }
    }

    // for (auto& monkey : monkeys)
    // {
    //   std::cout << monkey << std::endl;
    // }
    // std::cout << "\n";
  }
}

std::vector<Monkey> parseMonkeys(const std::string& input)
{
  std::regex e(R"(Monkey (\d+):\s+Starting items: ((?:\d+(?:, )?)+)\s+Operation: new = old ([+\-*/]) ((?:\d+)|(?:old))\s+Test: divisible by (\d+)\s+If true: throw to monkey (\d+)\s+If false: throw to monkey (\d+))");
  std::smatch m;
  std::vector<Monkey> monkeys;
  std::string str(input);
  while (std::regex_search(str, m, e))
  {
    // print each element in m with a comma and space between
    // std::cout << "Monkey " << m[1] << " has items " << m[2] << std::endl;
    // std::cout << m[3] << ", " << m[4] << ", " << m[5] << ", " << m[6] << ", " << m[7] << std::endl;

    std::vector<int> items;
    std::regex e2(R"((\d+))");
    std::smatch m2;
    std::string str2 = m[2];
    while (std::regex_search(str2, m2, e2))
    {
      items.push_back(std::stoi(m2[1]));
      str2 = m2.suffix();
    }

    // select op based on m[3]
    BinaryIntOp bop;
    switch (m[3].str()[0])
    {
      case '+':
        bop = std::plus<int>();
        break;
      case '-':
        bop = std::minus<int>();
        break;
      case '*':
        bop = std::multiplies<int>();
        break;
      case '/':
        bop = std::divides<int>();
        break;
    }

    // create a new function with a single argument
    // if m[4] is old, use the first argument twice
    // else use m[4] as the second argument
    UnaryIntOp op;
    if (m[4] == "old")
    {
      op = std::bind(bop, std::placeholders::_1, std::placeholders::_1);
    }
    else
    {
      op = std::bind(bop, std::placeholders::_1, std::stoi(m[4]));
    }

    monkeys.push_back(Monkey(op, std::stoi(m[5]), std::stoi(m[6]), std::stoi(m[7])));
    // reverse the items so they are in the correct order
    monkeys.back().items = std::vector<int>(items.rbegin(), items.rend());
    // std::cout << monkeys.back() << std::endl;

    str = m.suffix();
  }
  return monkeys;
}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // do some setup

  std::string str;
  std::string line;

  // iterate over lines of the input file
  while (std::getline(std::cin, line))
  {
    str += line;
  }

  std::vector<Monkey> monkeys = parseMonkeys(str);
  // std::cout << "\n\n";

  for (int i = 0; i < 20; ++i)
  {
    simulateMonkeys(monkeys, true);
  }

  std::vector<int> top_inspectors;
  std::transform(monkeys.begin(), monkeys.end(), std::back_inserter(top_inspectors),
    [](const Monkey& m) { return m.inspections; });
  std::sort(top_inspectors.begin(), top_inspectors.end(), std::greater<int>());
  std::cout << "Top inspectors: " << top_inspectors[0] << ", " << top_inspectors[1] << std::endl;
  int p1_mb = top_inspectors[0] * top_inspectors[1];

  // part two
  monkeys = parseMonkeys(str);

  for (int i = 0; i < 10000; ++i)
  {
    simulateMonkeys(monkeys, false);
  }
  top_inspectors.clear();
  std::transform(monkeys.begin(), monkeys.end(), std::back_inserter(top_inspectors),
    [](const Monkey& m) { return m.inspections; });
  std::sort(top_inspectors.begin(), top_inspectors.end(), std::greater<int>());
  std::cout << "Top inspectors: " << top_inspectors[0] << ", " << top_inspectors[1] << std::endl;
  auto p2_mb = static_cast<long long>(top_inspectors[0]) * top_inspectors[1];

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << "Monkey business: " << p1_mb << std::endl;
  std::cout << std::endl;

  std::cout << "Part Two\n";
  std::cout << "--------\n";
  std::cout << "Monkey business: " << p2_mb << std::endl;
  std::cout << std::endl;

  return 0;
}
