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

template<class T>
void fillVector(vector::Vector<T>& arr, size_t size) {
    T value = 0;
    for (size_t i = 0; i < size; ++i) {
        std::cin >> value;
        arr.push(value);
    }
    return;
}

template<class T, class Comporator = std::less<T> >
size_t randPartition(vector::Vector<T>& arr, size_t leftIterator,
                            size_t rightIterator, Comporator comp) {

    size_t pivotIndex = rand() % (rightIterator - leftIterator);
    std::swap(arr.getElement(pivotIndex + leftIterator), arr.getElement(rightIterator));

    T pivot = arr.getElement(rightIterator);
    size_t j = rightIterator;
    size_t i = rightIterator;

    for (; i > leftIterator; i--) {
        if (!comp(arr.getElement(i), pivot)) {
            std::swap(arr.getElement(i), arr.getElement(j));
            j--;
        }
    }
    if (!comp(arr.getElement(i), pivot)) {
        std::swap(arr.getElement(i), arr.getElement(j));
    }
    if (arr.getElement(j) <= pivot) {
        j++;
    }

    std::swap(arr.getElement(j), arr.getElement(rightIterator));
    return j;
}

template<class T, class Comporator = std::less<T> >
void kthElement(vector::Vector<T>& arr, size_t size, size_t position, Comporator comp = Comporator()) {
    size_t leftIterator = 0;
    size_t rightIterator = size - 1;

    while (leftIterator < rightIterator) {
        size_t middle = randPartition(arr, leftIterator, rightIterator, comp);
        if (middle < position) {
            leftIterator = middle + 1;
        } else {
            rightIterator = middle;
        }
    }
}

int main() {
    size_t size;
    size_t position;
    std::cin >> size;
    std::cin >> position;

    vector::Vector<int> arr;
    fillVector(arr, size);
    kthElement(arr, arr.getSize(), position);
    std::cout << arr.getElement(position) << std::endl;
    return 0;
}