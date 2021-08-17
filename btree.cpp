#include <vector>
#include <functional>
#include <stack>
#include <iostream>

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

Btree::~Btree() {
    Traverse([](Node* l_node) {
        delete l_node;
        l_node = nullptr;
    });
}

int main() {
    Btree bt([](const int a, const int b) {
        return a < b;
    });
    size_t c = 0;
    std::cin >> c;
    for (size_t i = 0; i < c; ++i) {
        int buf = 0;
        std::cin >> buf;
        bt.Add(buf);
    }
    bt.Traverse([](Node* l_node) {
        std::cout << l_node->value << " ";
    });
    return 0;
}
