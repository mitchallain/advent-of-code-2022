#include <iostream>
#include <regex>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>
#include <stack>

#include "tree.h"

std::regex kCdRe(R"(^\$ cd (.+)$)");
std::regex kLsRe(R"(^\$ ls$)");
std::regex kDirRe(R"(^dir (\w+)$)");
std::regex kFileRe(R"(^(\d+) (.+)$)");

// recursively search tree for directories with total size less than 100000
// and add their sizes together
int findLittleDirs(const TreeNode& tn, int size)
{
  int total = 0;
  if (tn.getSize() <= 100000 && tn.getNodeSize() == 0)
  {
    std::cout << "Found little dir: " << tn.getName() << " with size: " << tn.getSize()
              << std::endl;
    total += tn.getSize();
  }
  for (const auto& child : tn.children)
  {
    total += findLittleDirs(*child, size);
  }
  return total;
}

int findSmallestSizeGreaterThan(const TreeNode& tn, int threshold, int smallest)
{
  if (tn.getNodeSize() == 0 && tn.getSize() > threshold && tn.getSize() < smallest)
  {
    smallest = tn.getSize();
    std::cout << "Could delete " << tn.getName() << " and save " << smallest << std::endl;
  }
  for (const auto& child : tn.children)
  {
    smallest = findSmallestSizeGreaterThan(*child, threshold, smallest);
  }
  return smallest;
}

void testTree()
{
  Tree t;
  t.root = std::make_shared<TreeNode>("root", 0);
  t.root->addChild(std::make_shared<TreeNode>("child1", 0));
  t.root->children[0]->addChild(std::make_shared<TreeNode>("child2", 2));

  std::cout << t << std::endl;
}

std::shared_ptr<Tree> buildTree(const std::vector<std::string>& input)
{
  auto tree = std::make_shared<Tree>();
  tree->root = std::make_shared<TreeNode>("root", 0);

  std::stack<std::shared_ptr<TreeNode>> stack;
  stack.push(tree->root);
  for (const auto& line : input)
  {
    bool cd = false;
    std::string node;
    int size = 0;
    std::smatch match;
    if (std::regex_match(line, match, kCdRe))
    {
      node = match[1];
      cd = true;
    }
    else if (std::regex_match(line, match, kDirRe))
    {
      node = match[1];
    }
    else if (std::regex_match(line, match, kFileRe))
    {
      size = std::stoi(match[1]);
      node = match[2];
    }
    else
    {
      continue;
    }

    if (node == "/")
    {
      // empty the stack and push root
      while (!stack.empty())
      {
        stack.pop();
      }
      stack.push(tree->root);
    }
    else if (node == "..")
    {
      stack.pop();
    }
    else
    {
      // search for node name in children using find_if and equal_to
      auto current = stack.top();
      auto it = std::find_if(
          current->children.begin(), current->children.end(),
          [&node](const std::shared_ptr<TreeNode>& n) { return n->getName() == node; });
      if (it == current->children.end())
      {
        // not found, add new node
        auto new_node = std::make_shared<TreeNode>(node, size);
        current->addChild(new_node);

        if (cd)
        {
          stack.push(new_node);
        }
      }
      else
      {
        if (cd)
        {
          stack.push(*it);
        }
      }
    }
  }

  return tree;
}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // do some setup
  std::vector<std::string> lines;
  std::string str;

  // iterate over lines of the input file
  while (std::getline(std::cin, str))
  {
    lines.push_back(str);
  }

  // create a tree
  auto tree = buildTree(lines);
  std::cout << *tree << std::endl;

  int sum = findLittleDirs(*tree->root, 0);

  int total = tree->root->getSize();
  int needed = 30000000 - (70000000 - total);
  std::cout << "Need to delete " << needed << " bytes" << std::endl;
  int smallest_size = findSmallestSizeGreaterThan(*tree->root, needed, total);

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() << " microseconds" << std::endl;

  std::cout << "Part One\n";
  std::cout << "--------\n";
  std::cout << sum;
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Part Two\n";
  std::cout << "--------\n";
  std::cout << smallest_size;
  std::cout << std::endl;

  return 0;
}
