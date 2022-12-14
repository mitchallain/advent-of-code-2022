#include <iostream>
#include <string>

#include "tree.h"

int TreeNode::getSize() const
{
  int tree_size = size_;
  for (auto child : children)
  {
    tree_size += child->getSize();
  }
  return tree_size;
}

std::ostream& TreeNode::putNodes(std::ostream& os, int level) const
{
  os << std::string(level, ' ');
  os << getName() << ": " << getSize() << std::endl;
  if (children.size() > 0)
  {
    for (auto child : children)
    {
      child->putNodes(os, level + 1);
    }
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const TreeNode& tn) { return tn.putNodes(os, 0); }

// output text representing the contents of the tree
std::ostream& operator<<(std::ostream& os, const Tree& t)
{
  if (t.root == nullptr)
  {
    return os << "Tree is empty";
  }
  else
  {
    return os << *t.root;
  }
}

// void put_node_recursive(const std::shared_ptr<const TreeNode> tn, const int level)
// {
//   // indent according to recursion depth
//   for (int l = 0; l < level; ++l)
//   {
//     std::cout << "  ";
//   }
//
//   // write the node name and size
//   std::cout << tn->getName() << ": " << tn->getSize() << std::endl;
//
//   // if children exist, recurse
//   if (tn->children.size() > 0)
//   {
//     for (auto child : tn->children)
//     {
//       put_node_recursive(child, level + 1);
//     }
//   }
// }
