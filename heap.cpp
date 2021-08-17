#include <assert.h>

#include <iostream>
#include <sstream>
#include <vector>
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
    assert(index < size);
        return arr[index];
}
};  // namespace vector

namespace heap {
template <class T, class Payload = vector::Vector<T> >
class Heap {
    public:
        Heap();
        void push(T value);
        void show();
        T pop();
        size_t getSize() const;
        bool isEmpty() const;

    private:
        Payload data;

        void bubbleUp(T index);
        void bubbleDown(T index);
        T getLeftChild(T parent) const;
        T getRightChild(T parent) const;
        T getParent(T child) const;
};

template <class T, class Payload>
void Heap<T, Payload>::show() {
    T size = data.getSize();
    for (int i = 0; i < size; i++) {
        std::cout << data.getElement(i);
    }
}

template <class T, class Payload>
Heap<T, Payload>::Heap() : data() {}

template <class T, class Payload>
size_t Heap<T, Payload>::getSize() const {
    return this->data.getSize();
}

template <class T, class Payload>
bool Heap<T, Payload>::isEmpty() const {
    if (this->data.getSize() > 0) {
        return false;
    } else {
        return true;
    }
}

template <class T, class Payload>
inline T Heap<T, Payload>::getParent(T child) const {
    return (child - 1) / 2;
}

template <class T, class Payload>
inline T Heap<T, Payload>::getLeftChild(T parent) const {
    return 2 * parent + 1;
}

template <class T, class Payload>
inline T Heap<T, Payload>::getRightChild(T parent) const {
    return 2 * parent + 2;
}

template <class T, class Payload>
void Heap<T, Payload>::push(T value) {
        data.push(value);
        bubbleUp(data.getSize() - 1);
}

template <class T, class Payload>
void Heap<T, Payload>::bubbleUp(T index) {
    if (index && data.getElement(getParent(index)) < data.getElement(index)){
        std::swap(data.getElement(index), data.getElement(getParent(index)));
        bubbleUp(getParent(index));
    }
}

template <class T, class Payload>
T Heap<T, Payload>::pop() {
    std::swap(data.getElement(0), data.getElement(data.getSize() - 1));
    T value = data.popBack();
    bubbleDown(0);
    return value;
}

template <class T, class Payload>
void Heap<T, Payload>::bubbleDown(T index) {
    T largest = index;
    T left = getLeftChild(index);
    T right = getRightChild(index);

    if (left < data.getSize() && data.getElement(left) > data.getElement(index)) {
        largest = left;
    }
    if (right < data.getSize() && data.getElement(right) > data.getElement(largest)) {
        largest = right;
    }
    if (largest != index) {
        std::swap(data.getElement(index), data.getElement(largest));
        bubbleDown(largest);
    }
}
};  // namespace heap

template <class T, class Payload>
void fillBasket(int numOfFruits, heap::Heap<T, Payload>& basket) {
    T weight = 0;
    for (int i = 0; i < numOfFruits; ++i) {
        std::cin >> weight;
        basket.push(weight);
    }
}

template <class T>
inline T bite(T fruit) {
    if (!(fruit % 2)) {
        return fruit / 2;
    } else {
        return (fruit - 1) / 2;
    }
}

template <class T, class Payload>
void collectFruit(int maxWeight, heap::Heap<T, Payload>& basket, vector::Vector<T>& fruitVector) {
    T current = 0;
    T all = 0;
    int offset = 0;
    while (!basket.isEmpty()) {
        current = basket.pop();
        all += current;
        if (all > maxWeight) {
            basket.push(current);
            break;
        } else {
            fruitVector.push(current);
        }
    }
    return;
}

template <class T, class Payload>
size_t run(int maxWeight, heap::Heap<T, Payload>& basket) {
    if (maxWeight == 0) {
        return 0;
    }

    size_t count = 0;
    while (!basket.isEmpty()) {
        vector::Vector<T> fruitVector = {};
        collectFruit(maxWeight, basket, fruitVector);
        for (int i = 0; i < fruitVector.getSize(); ++i) {
            if (fruitVector.getElement(i) > 1) {
                basket.push(bite(fruitVector.getElement(i)));
            }
        }
        count++;
    }
    return count;
}

int main () {
    int numOfFruits = 0;
    heap::Heap<int> basket;

    std::cin >> numOfFruits;
    fillBasket(numOfFruits, basket);
    int maxWeight = 0;
    std::cin >> maxWeight;
    std::cout << run(maxWeight, basket);

    return 0;
}
