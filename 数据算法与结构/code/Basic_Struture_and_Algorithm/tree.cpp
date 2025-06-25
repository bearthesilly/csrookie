#include <iostream>
#include <stdexcept>
#include <vector>

// 假设我们有一个模板类 Single_list 来存储子节点
template <typename T>
class Single_list {
private:
    std::vector<T> list;

public:
    void insert(T const &item) {
        list.push_back(item);
    }

    // 非 const 版本的 operator[]
    T& operator[](int index) {
        if (index < 0 || index >= list.size()) {
            throw std::out_of_range("Index out of range");
        }
        return list[index];
    }

    // const 版本的 operator[]，保证不修改成员变量
    const T& operator[](int index) const {
        if (index < 0) {
            throw std::out_of_range("Index cannot be negative");
        }
        // 将 index 转换为 std::size_t 以避免符号不匹配的比较
        if (static_cast<std::size_t>(index) >= list.size()) {
            throw std::out_of_range("Index out of range");
        }
        return list[index];
    }

    int size() const {
        return list.size();
    }
    
    void clear() {
        list.clear();
    }
};


template <typename Type>
class Simple_tree {
private:
    Type element;
    Simple_tree *parent_node;
    Single_list<Simple_tree *> children;

public:
    Simple_tree(Type const &elem = Type(), Simple_tree *parent = nullptr)
        : element(elem), parent_node(parent) {}

    // 返回当前节点的元素
    Type retrieve() const {
        return element;
    }

    // 返回父节点的指针
    Simple_tree *parent() const {
        return parent_node;
    }

    // 返回当前节点的子节点数量
    int degree() const {
        return children.size();
    }

    // 判断当前节点是否为根节点
    bool is_root() const {
        return parent_node == nullptr;
    }

    // 判断当前节点是否为叶节点
    bool is_leaf() const {
        return children.size() == 0;
    }

    // 返回第n个子节点的指针
    Simple_tree *child(int n) const {
        if (n < 0 || n >= children.size()) {
            throw std::out_of_range("Invalid child index");
        }
        return children[n];
    }

    // 计算树的高度
    int height() const {
        if (is_leaf()) {
            return 0;
        }
        int max_child_height = 0;
        for (int i = 0; i < children.size(); ++i) {
            max_child_height = std::max(max_child_height, children[i]->height());
        }
        return 1 + max_child_height;
    }

    // 插入一个新节点
    void insert(Type const &elem) {
        Simple_tree *new_child = new Simple_tree(elem, this);
        children.insert(new_child);
    }

    // 添加已经存在的子树为当前节点的子节点
    void attach(Simple_tree *child_tree) {
        if (child_tree == nullptr) {
            throw std::invalid_argument("Cannot attach a null tree");
        }

        // 如果该子树已经有父节点，则先从其原父节点分离
        if (child_tree->parent() != nullptr) {
            child_tree->detach();
        }

        // 将当前树作为子树的父节点
        child_tree->parent_node = this;
        children.insert(child_tree);
    }

    // 从父节点分离自己（detach）
    void detach() {
        if (parent_node != nullptr) {
            for (int i = 0; i < parent_node->children.size(); ++i) {
                if (parent_node->children[i] == this) {
                    parent_node->children[i] = parent_node->children[parent_node->children.size() - 1];
                    parent_node->children.size()--;
                    break;
                }
            }
        }
        parent_node = nullptr;
    }

    int size() const {
    // 当前节点的大小至少为1
    int total_size = 1; 

    // 遍历所有子节点，递归计算子树大小
    for (int i = 0; i < children.size(); ++i) {
        total_size += children[i]->size();  // 递归调用子节点的 size()
    }

    return total_size;
}
};

int main() {
    // 示例用法
    Simple_tree<int> root(10);
    root.insert(20);
    root.insert(30);

    Simple_tree<int> *child1 = root.child(0);
    Simple_tree<int> *child2 = root.child(1);

    std::cout << "Root: " << root.retrieve() << std::endl;
    std::cout << "Child 1: " << child1->retrieve() << std::endl;
    std::cout << "Child 2: " << child2->retrieve() << std::endl;
    std::cout << "Root height: " << root.height() << std::endl;
    std::cout << "Size: " << root.size() << std::endl;
    return 0;
}
