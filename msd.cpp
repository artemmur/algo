#include <assert.h>

#include <iostream>
#include <functional>
#include <fstream>

#define VECTOR_INIT_SIZE 8

namespace vector {
template <class T>
class Vector {
    public:
        Vector() : capacity(0), size(0), arr(nullptr) {}
        ~Vector();
        explicit Vector(size_t size);

        //Vector(const Vector& rhs);
        //Vector(Vector&& lhs);

        void push(T data);
        T popBack();
        T& getFront() const;
        T& getBack() const;
        const size_t& getCapacity() const;
        const size_t& getSize() const;
        T& getElement(size_t index) const;
        void setElement(size_t index, T value);

    private:
        size_t capacity;
        size_t size;
        T* arr;
};

/*template<class T>
Vector<T>::Vector(const Vector& rhs) : capacity(rhs.capacity), size(rhs.size), arr(nullptr) {
    if (rhs.arr != nullptr) {
        arr = new T[capacity];
        for (; rhs.arr != rhs.arr + size;) {
            arr++ = rhs.arr++;
        }
    }
}*/

/*template<class T>
Vector<T>::Vector(Vector<T>&& rhs) : capacity(0), size(0), arr(nullptr) {
    if (rhs.getSize() > 0) {
        Vector(rhs.getSize());
        for (size_t i = 0; i < rhs.getSize(); i++) {
        push_back(rhs.getElement(i));
        }
    }
}*/

template <class T>
Vector<T>::Vector(size_t size) : capacity(0), size(size), arr(nullptr) {
    T *buf = new T[size];
    arr = buf;
    return;
}

template <class T>
Vector<T>::~Vector() {
    delete[] arr;
}

template <class T>
void Vector<T>::setElement(size_t index, T value) {
    assert(index < size);
    arr[index] = value;
}

template <class T>
void Vector<T>::push(T data) {
if (capacity == 0) {
    arr = new T[VECTOR_INIT_SIZE];
    capacity = 8;
}

if (size == capacity) {
    T* buf = new T[2 * capacity];

    for (size_t i = 0; i < capacity; i++) {
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
const size_t& Vector<T>::getCapacity() const {
    return capacity;
}

template <class T>
const size_t& Vector<T>::getSize() const {
    return size;
}

template <class T>
T& Vector<T>::getElement(size_t index) const {
    if (index > size) {
        printf("index -> %zu\n", index);
        exit(1);
    }
        return arr[index];
}
};  // namespace vector

template <class T>
void fillVector(vector::Vector<T>& arr) {
    std::string buf;
    while (std::cin >> buf) {
        arr.push(buf);
    }
}

template <class T>
void msd(vector::Vector<T>& arr, int lo, int hi, int d) {
    if (hi <= lo + 1) {
        return;
    }

    vector::Vector<std::string> temp(arr.getSize());
    for (size_t i = 0; i < arr.getSize(); i++) {
        temp.push(arr.getElement(i));
    }  // copy

    vector::Vector<int> count(256 + 1);

    for (size_t i = 0; i < arr.getSize(); i++) {
        std::string buf = arr.getElement(i);
        //count[(uint8_t)buf.at(d) + 1]++;
        count.setElement((uint8_t)buf.at(d) + 1, count.getElement((uint8_t)buf.at(d) + 1) + 1);
    }
    for (int k = 1; k < 256; k++) {
        //count[k] += count[k - 1];
        count.setElement(k, count.getElement(k) + count.getElement(k - 1));
    }
    for (size_t i = 0; i < arr.getSize(); ++i) {
        std::string buf = arr.getElement(i);
        temp.setElement(count.getElement((uint8_t)buf.at(d)+ 1), arr.getElement(i));
    }
    for (size_t i = 0; i < arr.getSize(); i++) {
        arr.setElement(i, temp.getElement(i));
    }
    for (int i = 1; i < 255; i++) {
        msd(arr, lo + count.getElement(i), lo + count.getElement(i + 1), d + 1);
    }
}

template <class T>
void showVector(vector::Vector<T>& arr) {
    for (size_t i = 0; i < arr.getSize(); i++ ) {
        std::cout << arr.getElement(i) << std::endl;
    }
}

int main() {
    vector::Vector<std::string> arr;
    fillVector(arr);
    msd(arr, 0, arr.getSize(), 0);
    showVector(arr);

    return 0;
}
