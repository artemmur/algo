#include <functional>
#include <stack>
#include <iostream>

namespace avl {
struct Node {
    Node* left;
    Node* right;
    int value;
    unsigned char height;
    Node(const int value) :
            left(nullptr),
            right(nullptr),
            value(value),
            height(1) {}
};

class AVL {
public:
    AVL() : _root(nullptr) {}
    ~AVL();

    void Add(const int l_value);
    void Delete(const int l_value);
    void Remove(const int l_value);
    Node* GetRoot() const;
    void Traverse(std::function<void(Node*)>);

private:
    unsigned char getHeight(Node* l_root) const;
    int bFactor(Node* l_root) const;
    void fixHeight(Node* l_root);
    Node* findMin(Node*& l_root);
    Node* addRecursive(Node* l_root, int l_value);
    Node* deleteRecursive(Node* root, int key);
    Node* rotateRight(Node* l_root);
    Node* rotateLeft(Node* l_root);
    Node* balance(Node* l_root);

private:
    Node* _root;
};

AVL::~AVL() {
    Traverse([](Node* l_node) {
        delete l_node;
    });
}

Node* AVL::GetRoot() const {
    return _root;
}

unsigned char AVL::getHeight(Node* l_root) const {
    return (l_root ? l_root->height : 0);
}

Node* AVL::findMin(Node*& l_root) {
    Node* min = nullptr;
    if (!l_root->left) {
        min = l_root;
        l_root = l_root->right;
        min->right = nullptr;
        return min;
    }
    min = findMin(l_root->left);
    l_root = balance(l_root);
    return min;
}

int AVL::bFactor(Node* l_root) const {
    return getHeight(l_root->right) - getHeight(l_root->left);
}

void AVL::fixHeight(Node* l_root) {
    if (!l_root) {
        return;
    }

    int hl = getHeight(l_root->left);
    int hr = getHeight(l_root->right);
    l_root->height = (hl < hr ? hr : hl) + 1;
}

Node* AVL::rotateRight(Node* l_root) {
    if (!l_root) {
        return nullptr;
    }

    Node* temp = l_root->left;
    l_root->left = temp->right;
    temp->right = l_root;
    fixHeight(l_root);
    fixHeight(temp);
    return temp;
}

Node* AVL::rotateLeft(Node* l_root) {
    if (!l_root) {
        return nullptr;
    }

    Node* temp = l_root->right;
    l_root->right = temp->left;
    temp->left = l_root;
    fixHeight(l_root);
    fixHeight(temp);
    return temp;
}

Node* AVL::balance(Node* l_root) {
    if (!l_root) {
        return nullptr;
    }

    fixHeight(l_root);
    int bf = bFactor(l_root);
    if (bf == 2) {
        if (bFactor(l_root->right) < 0) {
            l_root->right = rotateRight(l_root->right);
        }
        return rotateLeft(l_root);
    }
    if (bf == -2) {
        if (bFactor(l_root->left) > 0) {
            l_root->left = rotateLeft(l_root->left);
        }
        return rotateRight(l_root);
    }
    return l_root;
}

Node* AVL::addRecursive(Node* l_root, int l_value) {
    if (!l_root) {
        return new Node(l_value);
    }
    if (l_value < l_root->value) {
        l_root->left = addRecursive(l_root->left, l_value);
    } else {
        l_root->right = addRecursive(l_root->right, l_value);
    }
    return balance(l_root);
}

void AVL::Add(const int l_value) {
    _root = addRecursive(_root, l_value);
}

Node* AVL::deleteRecursive(Node* l_root, int l_value) {
    if (!l_root) {
        return nullptr;
    }

    if (l_value < l_root->value) {
        l_root->left = deleteRecursive(l_root->left, l_value);
    } else if (l_value > l_root->value) {
        l_root->right = deleteRecursive(l_root->right, l_value);
    } else {
        Node* left = l_root->left;
        Node* right = l_root->right;
        delete l_root;

        if (!right) {
            return left;
        }

        Node* min = findMin(right);
        min->left = left;
        min->right = right;
        return balance(min);
    }
    return balance(l_root);
}

void AVL::Delete(const int l_value) {
    _root = deleteRecursive(_root, l_value);
}

void AVL::Traverse(std::function<void(Node*)> func) {
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
}  // namespace avl

size_t getNumOfNodes(avl::Node* l_root) {
    if (!l_root) {
        return 0;
    }

    size_t num = 1;
    num += getNumOfNodes(l_root->left);
    num += getNumOfNodes(l_root->right);
    return num;
}

int ordStatRecursive(avl::Node* l_root, size_t l_ord) {
    size_t numOfNodes = getNumOfNodes(l_root->left);
    size_t ord = 0;
    if (numOfNodes > l_ord) {
        ord = ordStatRecursive(l_root->left, l_ord);
    } else if (numOfNodes < l_ord) {
        ord = ordStatRecursive(l_root->right, l_ord - numOfNodes - 1);
    } else {
        ord = l_root->value;
    }
    return ord;
}

int ordStat(avl::AVL& l_tree, size_t l_ord) {
    auto root = l_tree.GetRoot();
    if (!root) {
        return 0;
    }
    return ordStatRecursive(root, l_ord);
}

int main() {
    avl::AVL avlTree;
    size_t cmd = 0;
    std::cin >> cmd;
    for (size_t i = 0; i < cmd; ++i) {
        int value = 0;
        size_t ord = 0;
        std::cin >> value >> ord;
        if (value >= 0) {
            avlTree.Add(value);
        } else {
            avlTree.Delete(abs(value));
        }
        std::cout << ordStat(avlTree, ord) << std::endl;
    }
    return 0;
}
