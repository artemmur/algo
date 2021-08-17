#include <queue>
#include <functional>
#include <stack>
#include <iostream>

namespace btree {
struct Node {
    Node* left;
    Node* right;
    int value;
    Node(const int value) :
            left(nullptr),
            right(nullptr),
            value(value) {}
};

class Btree {
public:
    Btree(std::function<bool(const int, const int)> l_func) : _root(nullptr), _func(l_func) {}
    ~Btree();

    void Add(const int l_value);
    void Traverse(std::function<void(Node*)>);
    Node* GetRoot() const;

private:
    Node* _root;
    std::function<bool(const int, const int)> _func;
};

void Btree::Add(const int l_value) {
    if (!_root) {
        _root = new Node(l_value);
        return;
    }

    Node* temp = _root;
    while (true) {
        if (_func(temp->value, l_value)) {
            if (temp->right) {
                temp = temp->right;
            } else {
                temp->right = new Node(l_value);
                break;
            }
        } else {
            if (temp->left) {
                temp = temp->left;
            } else {
                temp->left = new Node(l_value);
                break;
            }
        }
    }
    return;
}

void Btree::Traverse(std::function<void(Node*)> func) {
    if (!_root) {
        return;
    }

    std::stack<Node*> stack;
    stack.push(_root);

    while (!stack.empty()) {
        auto curr = stack.top();
        stack.pop();
        if (curr->right != nullptr) {
            stack.push(curr->right);
        }

        if (curr->left != nullptr) {
            stack.push(curr->left);
        }
        func(curr);
    }
    return;
}

Node* Btree::GetRoot() const {
    return _root;
}

Btree::~Btree() {
    Traverse([](Node* l_node) {
        delete l_node;
        l_node = nullptr;
    });
}
}  // namespace Btree

namespace treap {
struct Node {
    Node* left;
    Node* right;
    int value;
    int weight;
    Node(const int l_value, const int l_weight,
            Node* l_left = nullptr, Node* l_right = nullptr) :
            left(l_left),
            right(l_right),
            value(l_value),
            weight(l_weight) {}
};

class Treap {
public:
    Treap(std::function<bool(const int, const int)> l_func) : _root(nullptr), _func(l_func) {}
    ~Treap();

    void Add(const int l_value, const int l_weight);
    void Traverse(std::function<void(Node*)>);
    Node* GetRoot() const;

private:
    void addRecursive(Node*& l_root, Node* l_child);
    Node* merge(Node* l_left, Node* l_right);
    void split(Node* l_root, const int l_key, Node*& l_left, Node*& l_right);

private:
    Node* _root;
    std::function<bool(const int, const int)> _func;
};

Node* Treap::merge(Node* l_left, Node* l_right) {
    if (l_left == nullptr) {
        return l_right;
    }
    if (l_right == nullptr) {
        return l_left;
    }
    if (l_left->weight > l_right->weight) {
        l_left->right = merge(l_left->right, l_right);
        return l_left;
    } else {
        l_right->left = merge(l_left, l_right->left);
        return l_right;
    }
}

void Treap::split(Node* l_root, const int l_value, Node*& l_left, Node*& l_right) {
    if (l_root == nullptr) {
        l_left = nullptr;
        l_right = nullptr;
    } else if (l_root->value <= l_value) {
        split(l_root->right, l_value, l_root->right, l_right);
        l_left = l_root;
    } else {
        split(l_root->left, l_value, l_left, l_root->left);
        l_right = l_root;
    }
}

Node* Treap::GetRoot() const {
    return _root;
}

void Treap::Add(const int l_value, const int l_weight) {
    auto node = new Node(l_value, l_weight);
    addRecursive(_root, node);
    return;
}

void Treap::addRecursive(Node*& l_root, Node* l_child) {
    if (l_root == nullptr) {
        l_root = l_child;
    } else if (l_child->weight > l_root->weight) {
        split(l_root, l_child->value, l_child->left, l_child->right);
        l_root = l_child;
    } else {
        addRecursive((_func(l_child->value, l_root->value) ?
                l_root->left : l_root->right), l_child);
    }
}

void Treap::Traverse(std::function<void(Node*)> func) {
    if (!_root) {
        return;
    }

    std::stack<Node*> stack;
    stack.push(_root);

    while (!stack.empty()) {
        auto curr = stack.top();
        stack.pop();
        if (curr->right != nullptr) {
            stack.push(curr->right);
        }

        if (curr->left != nullptr) {
            stack.push(curr->left);
        }
        func(curr);
    }
    return;
}

Treap::~Treap() {
    Traverse([](Node* l_node) {
        delete l_node;
        l_node = nullptr;
    });
}
}  // namespace Treap

template <class T>
size_t height(const T& tree) {
    auto root = tree.GetRoot();
    if (root == nullptr) {
        return 0;
    }

    std::queue<decltype(root)> queue;
    queue.push(root);

    size_t height = 0;
    while (true) {
        size_t node_count = queue.size();
        if (node_count == 0) {
        return height;
        }

        ++height;
        while (node_count > 0) {
            auto node = queue.front();
            queue.pop();
            if (node->left != nullptr) {
                queue.push(node->left);
            }
            if (node->right != nullptr) {
                queue.push(node->right);
            }
            --node_count;
        }
    }
}

int main() {
    btree::Btree bt([](const int a, const int b) {
        return a < b;
    });
    treap::Treap tp([](const int a, const int b) {
        return a < b;
    });
    size_t c = 0;
    std::cin >> c;
    for (size_t i = 0; i < c; ++i) {
        int value = 0;
        int weight = 0;
        std::cin >> value >> weight;
        tp.Add(value, weight);
        bt.Add(value);
    }
    std::cout << static_cast<int>(height(bt) - height(tp)) << "\n";
    return 0;
}
