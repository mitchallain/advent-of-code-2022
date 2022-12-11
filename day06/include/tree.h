#ifndef AOC22_DAY06_TREE_H_
#define AOC22_DAY06_TREE_H_

#include <memory>
#include <vector>

/**
 * @brief A node in a tree.
 *
 */
class TreeNode
{
 public:
  friend std::ostream& operator<<(std::ostream& os, const TreeNode& tn);

  TreeNode(std::string name, int size) : name_(name), size_(size) {}
  std::ostream& putNodes(std::ostream& os, int level) const;

  void addChild(std::shared_ptr<TreeNode> child) { children.push_back(child); }
  const std::string& getName() const { return name_; }
  int getNodeSize() const { return size_; }
  int getSize() const;

  std::vector<std::shared_ptr<TreeNode>> children;

 protected:
  std::string name_;
  int size_;
};

class Tree
{
 public:
  friend std::ostream& operator<<(std::ostream& os, const Tree& t);
  Tree() : root(nullptr) {}
  std::shared_ptr<TreeNode> root;
};

void put_node_recursive(const std::shared_ptr<const TreeNode> tn, const int level);

#endif  // AOC22_DAY06_TREE_H_
