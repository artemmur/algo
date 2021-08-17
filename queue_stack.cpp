#include <assert.h>

#include <iostream>
#include <functional>

#define VECTOR_INIT_SIZE 8

namespace vector {
template <class T>
class Vector {
    public:
        Vector() : arr(nullptr), capacity(0), size(0) {}
        ~Vector();
        void push(T data);
        T popBack();
        T& getFront() const;
        T& getBack() const;
        const T& getCapacity() const;
        const T& getSize() const;
        T& getElement(T index) const;

    private:
        T* arr;
        T capacity;
        T size;
};

template <class T>
Vector<T>::~Vector() {
    delete[] arr;
}

template <class T>
void Vector<T>::push(T data) {
if (capacity == 0) {
    arr = new int[VECTOR_INIT_SIZE];
    capacity = 8;
}

if (size == capacity) {
    int* buf = new int[2 * capacity];

    for (int i = 0; i < capacity; i++) {
        buf[i] = arr[i];
    }

    delete[] arr;
    capacity *= 2;
    arr = buf;
}

arr[size] = data;
size++;
}

template <class T>
T& Vector<T>::getFront() const {
    return this->arr[0];
}

template <class T>
T& Vector<T>::getBack() const {
    return this->arr[size - 1];
}

template <class T>
T Vector<T>::popBack() {
    assert(size > 0);
    T buf = arr[size - 1];
    size--;
    return buf;
}

template <class T>
const T& Vector<T>::getCapacity() const {
    return capacity;
}

template <class T>
const T& Vector<T>::getSize() const {
    return size;
}

template <class T>
T& Vector<T>::getElement(T index) const {
    if (index > size) {
        printf("index -> %d\n", index);
        exit(1);
    }
        return arr[index];
}
};  // namespace vector

namespace stack {
    template <class T, class Payload = vector::Vector<T> >
    class Stack {
    public:
        Stack() : data() {}
        void push(T value);
        T pop();
        const T& top() const;
        bool isEmpty();
    private:
        Payload data;
    };

    template <class T, class Payload>
    void Stack<T, Payload>::push(T value) {
        data.push(value);
    }

    template <class T, class Payload>
    T Stack<T, Payload>::pop() {
        return data.popBack();
    }

    template <class T, class Payload>
    const T& Stack<T, Payload>::top() const {
        return data.getBack();
    }

    template <class T, class Payload>
    bool Stack<T, Payload>::isEmpty() {
        if (data.getSize() == 0) {
            return true;
        } else {
            return false;
        }
    }

};  // namespace stack

namespace queue {
    template<class T, class Data = stack::Stack<T> >
    class Queue
    {
    public:
        void enQueue(T value);
        T deQueue();
    private:
        Data stack1;
        Data stack2;
    };

    template <class T, class Data>
    void Queue<T, Data>::enQueue(T value) {
        stack1.push(value);
    }

    template <class T, class Data>
    T Queue<T, Data>::deQueue() {
        if (stack1.isEmpty() && stack2.isEmpty()) {
            return -1;
        }

        if (stack2.isEmpty()) {
            while (!stack1.isEmpty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }

        int value = stack2.top();
        stack2.pop();
        return value;
    }

}  // namespace queue

template <class T>
std::string run (size_t numberOfCommand, queue::Queue<T>& queue) {
    size_t count = 0;
    for (size_t i = 0; i < numberOfCommand; ++i) {
        int cmd = 0;
        T value = 0;
        std::cin >> cmd;
        std::cin >> value;

        if (cmd == 3) {
            queue.enQueue(value);
            count++;
        }

        if (cmd == 2) {
            T firstElement = queue.deQueue();
            if (firstElement == value) {
                count++;
            }
        }
    }

    if (count != numberOfCommand) {
        return "NO";
    }

    return "YES";
}

int main() {
    size_t numberOfCommand = 0;
    queue::Queue<int> queue;
    std::cin >> numberOfCommand;
    std::cout << run(numberOfCommand, queue) << std::endl;
    return 0;
}