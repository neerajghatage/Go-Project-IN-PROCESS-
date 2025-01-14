#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <set>

struct Record
{
    std::string fname;
    std::string bnum;
    std::string os;
    int pr;
};

class TreeNode
{
public:
    std::string value;
    std::string type; 
    std::unordered_map<std::string, std::shared_ptr<TreeNode>> children;
    int pr_sum;
    std::set<std::shared_ptr<TreeNode>> parents; 

    TreeNode(const std::string &val = "", const std::string &t = "")
        : value(val), type(t), pr_sum(0) {}
};

class StatisticsTree
{
private:
    std::shared_ptr<TreeNode> root;
    std::unordered_map<std::string, std::shared_ptr<TreeNode>> nodeMap; // Store nodes by their value and type
    std::vector<std::string> hierarchy{"fname", "bnum", "os"};

    std::shared_ptr<TreeNode> getOrCreateNode(const std::string &value, const std::string &type)
    {
        std::string key = type + ":" + value;
        auto it = nodeMap.find(key);
        if (it != nodeMap.end())
        {
            return it->second;
        }
        auto node = std::make_shared<TreeNode>(value, type);
        nodeMap[key] = node;
        return node;
    }

public:
    StatisticsTree()
    {
        root = std::make_shared<TreeNode>("root", "root");
        nodeMap["root:root"] = root;
    }

    void insert(const Record &record)
    {
        std::shared_ptr<TreeNode> current = root;
        current->pr_sum += record.pr;

        auto fname_node = getOrCreateNode(record.fname, "fname");
        if (current->children.find(record.fname) == current->children.end())
        {
            current->children[record.fname] = fname_node;
            fname_node->parents.insert(current);
        }
        fname_node->pr_sum += record.pr;
        current = fname_node;

        auto bnum_node = getOrCreateNode(record.bnum, "bnum");
        if (current->children.find(record.bnum) == current->children.end())
        {
            current->children[record.bnum] = bnum_node;
            bnum_node->parents.insert(current);
        }
        bnum_node->pr_sum += record.pr;
        current = bnum_node;

        auto os_node = getOrCreateNode(record.os, "os");
        if (current->children.find(record.os) == current->children.end())
        {
            current->children[record.os] = os_node;
            os_node->parents.insert(current);
        }
        os_node->pr_sum += record.pr;
    }

    std::unordered_map<std::string, int> computeGroupby(const std::string &groupByType)
    {
        std::unordered_map<std::string, int> result;

        for (const auto &pair : nodeMap)
        {
            if (pair.second->type == groupByType)
            {
                result[pair.second->value] = pair.second->pr_sum;
            }
        }

        return result;
    }
};

int main()
{
    std::vector<Record> data = {
        {"sam", "batch-1", "iOS", 23},
        {"john", "batch-2", "iOS", 14},
        {"sam", "batch-2", "win", 15},
        {"sam", "batch-1", "linux", 22}};

    StatisticsTree tree;
    for (const auto &record : data)
    {
        tree.insert(record);
    }

    std::cout << "\nGrouping results:\n";
    for (const auto &type : {"fname", "bnum", "os"})
    {
        std::cout << "\nGroup by " << type << ":\n";
        auto result = tree.computeGroupby(type);
        for (const auto &pair : result)
        {
            std::cout << pair.first << ": " << pair.second << "\n";
        }
    }

    return 0;
}
