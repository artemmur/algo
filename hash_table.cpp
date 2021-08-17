#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <iostream>

#define INIT_SIZE 8

#define FIRST_PRIME 19
#define SECOND_PRIME 23

class Hash_table {
public:
    explicit Hash_table(const std::function<size_t(const std::string& l_value, const int& l_prime)> l_func);
    ~Hash_table() = default;

    bool Push(const std::string& l_key);
    bool Has(const std::string& l_key) const;
    bool Remove(const std::string& l_key);

private:
    void grow();

private:
    struct _hash_node {
        enum class State {
            FREE,
            BUSY,
            DELETE
        };
        std::string value;
        State state = State::FREE;
    };
    float _load_factor;
    std::function<size_t(const std::string&, const int&)> _hash;
    std::vector<_hash_node> _data;
};

Hash_table::Hash_table(const std::function<size_t(const std::string& l_value, const int& l_prime)> l_func)
        : _load_factor(0), _hash(l_func), _data(INIT_SIZE) {}

bool Hash_table::Has(const std::string& l_key) const {
    size_t first_hash = _hash(l_key, FIRST_PRIME);
    size_t second_hash = _hash(l_key, SECOND_PRIME) * 2 + 1;

    for (size_t i = 0; i < _data.size(); ++i) {
        size_t index = (first_hash + second_hash * i) % _data.size();
        const auto& node = _data[index];
        if (node.state == _hash_node::State::FREE) {
            return false;
        }
        if (node.state != _hash_node::State::FREE &&
                node.value == l_key) {
            return node.state == _hash_node::State::BUSY;
        }
    }
    return false;
}

bool Hash_table::Push(const std::string& l_key) {
    if (_load_factor >= 0.75) {
        grow();
    }

    size_t first_hash = _hash(l_key, FIRST_PRIME);
    size_t second_hash = _hash(l_key, SECOND_PRIME) * 2 + 1;

    for (size_t i = 0; i < _data.size(); ++i) {
        size_t index = (first_hash + second_hash * i) % _data.size();
        auto& node = _data[index];
        if (node.state == _hash_node::State::FREE) {
            node.value = l_key;
            node.state = _hash_node::State::BUSY;
            _load_factor += 1.0 / _data.size();
            return true;
        }
        if (node.state == _hash_node::State::BUSY &&
            node.value == l_key) {
            return false;
        }
        if (node.state == _hash_node::State::DELETE) {
            if (Has(l_key)) {
                return false;
            }
            node.value = l_key;
            node.state = _hash_node::State::BUSY;
            return true;
        }
    }
    return false;
}

bool Hash_table::Remove(const std::string& l_key) {
    size_t first_hash = _hash(l_key, FIRST_PRIME);
    size_t second_hash = _hash(l_key, SECOND_PRIME) * 2 + 1;

    for (size_t i = 0; i < _data.size(); ++i) {
        size_t index = (first_hash + second_hash * i) % _data.size();
        auto& node = _data[index];
        if (node.state == _hash_node::State::FREE) {
            return false;
        }
        if (node.state == _hash_node::State::BUSY &&
            node.value == l_key) {
            node.state = _hash_node::State::DELETE;
            return true;
        }
        if (node.state == _hash_node::State::DELETE && node.value == l_key) {
            return false;
        }
    }
    return false;
}

void Hash_table::grow() {
    std::vector<_hash_node> new_data(_data.size() * 2);
    size_t num_of_element = 0;
    for (size_t i = 0; i < _data.size(); ++i) {
        const auto& node = _data[i];
        if (node.state == _hash_node::State::BUSY) {
            num_of_element++;
            size_t first_hash = _hash(node.value, FIRST_PRIME);
            size_t second_hash = _hash(node.value, SECOND_PRIME) * 2 + 1;

            for (size_t j = 0; j < new_data.size(); ++j) {
                size_t new_index = (first_hash + second_hash * j) % new_data.size();
                auto& new_node = new_data[new_index];

                if (new_node.state == _hash_node::State::FREE) {
                    new_node.value = node.value;
                    new_node.state = _hash_node::State::BUSY;
                    break;
                }
            }
        }
    }
    _data = std::move(new_data);
    _load_factor = static_cast<float>(num_of_element) / _data.size();
    return;
}

int main() {
    Hash_table hash_table([](const std::string& l_key, const int& l_prime) {
        size_t hash = 0;
        for (const auto& Char : l_key) {
            hash = hash * l_prime + Char;
        }
        return hash;
    });

    char operation = 0;
    std::string key;

    auto get_status = [](bool operation) {
        if (operation) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
    };

    while (std::cin >> operation >> key) {
        switch (operation) {
            case '+':
                get_status(hash_table.Push(key));
                break;

            case '-':
                get_status(hash_table.Remove(key));
                break;

            case '?':
                get_status(hash_table.Has(key));
                break;

            default:
                break;
        }
    }
    return 0;
}
