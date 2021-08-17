#include <assert.h>

#include <iostream>
#include <sstream>

class Queue {
    public:
        Queue();
        Queue(const Queue& q) = delete;
        Queue& operator=(const Queue& q) = delete;
        ~Queue();

        void enqueue(const int data);

        int dequeue();

        bool is_empty() const {
            return tail == nullptr;
        }

        bool is_single() const {
            return (head == tail ? true : false);
        }

        int get_element() const {
            return head->data;
        }

        void move_to_end();

        friend std::ostream& operator<<(std::ostream& out, const Queue& queue);

    private:
        struct Node
        {
            int data;
            Node* next;
            Node() : next(nullptr) {}
        };
        Node* head;
        Node* tail;
};

Queue::Queue() : head(nullptr), tail(nullptr) {}

Queue::~Queue() {
    while(!is_empty()) {
        dequeue();
    }
}

    std::ostream& operator<<(std::ostream& out, const Queue& queue) {
        out << queue.head->data;
        return out;
    }

void Queue::move_to_end() {
    tail->next = head;
    head = head->next;
    tail = tail->next;
    tail->next = nullptr;
}

void Queue::enqueue(const int data) {
    Node* new_node = new Node();
    new_node->data = data;

    if (is_empty()) {
        head = new_node;
    } else {
        tail->next = new_node;
    }
    tail = new_node;
}

int Queue::dequeue() {
    assert(!is_empty());

    Node* tmp_node = head;
    int tmp_data = head->data;
    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete tmp_node;
    return tmp_data;
}

void make_queuery(const int size, Queue& queue) {
    for (int i = 1; i <= size; ++i) {
        queue.enqueue(i);
    }
    return;
}

void run(const int period, Queue& queue) {
    int count = 1;
    while (!queue.is_single()) {
        if (period != count) {
            queue.move_to_end();
            count++;
        } else {
            queue.dequeue();
            count = 1;
        }
    }
}

int main () {
    Queue queue;

    int size = 0;
    std::cin >> size;
    make_queuery(size, queue);

    int period = 0;
    std::cin >> period;
    run(period, queue);

    std::cout << queue;

    return 0;
}
