#include <assert.h>

#include <iostream>
#include <sstream>

#define VECTOR_INIT_SIZE 8

template<class T>
class Vector {
    public:
        Vector() : arr(nullptr), capacity(0), size(0) {}
        ~Vector();
        void push(int data);
        const size_t& getCapacity() const;
        const size_t& getSize() const;
        const T getElement(size_t index) const;

    private:
        T* arr;
        size_t capacity;
        size_t size;
};

template<class T>
Vector<T>::~Vector() {
  delete[] arr;
}

template<class T>
void Vector<T>::push(int data) {
if (capacity == 0) {
    arr = new int[VECTOR_INIT_SIZE];
    capacity = 8;
}

if (size == capacity) {
    int* buf = new int[2 * capacity];

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

template<class T>
const size_t& Vector<T>::getCapacity() const {
    return capacity;
}

template<class T>
const size_t& Vector<T>::getSize() const {
    return size;
}

template<class T>
const T Vector<T>::getElement(size_t index) const {
    assert(index < size);
        return arr[index];
}

template<class T>
int binarySearch(const Vector<T>& vector,size_t l_range, size_t r_range, T target) {
    while (l_range <= r_range) {
        size_t middle = l_range + (r_range - l_range) / 2;
        if (middle < vector.getSize()) {
            if (vector.getElement(middle) == target) {
                return 1;  // found
            }
            if (vector.getElement(middle) < target) {
                l_range = middle + 1;
            } else {
                r_range = middle - 1;
            }
        } else {
            break;
        }
    }
    return 0;  // not found
}

template <typename T>
int exponentialSearch(const Vector<T>& arr, size_t size, T key)
{
    if (size == 0) {
        return 0;
    }

    size_t bound = 1;
    while (bound < size && arr.getElement(bound) < key) {
        bound *= 2;
    }

    return binarySearch(arr, bound/2, std::min(bound + 1, size), key);
}

template<class T>
Vector<T> intersection(const Vector<T>& lhs, const Vector<T>& rhs) {
    Vector<T> result;
    size_t index = 0;
    while (rhs.getSize() > index) {
        if (exponentialSearch(lhs, (lhs.getSize() - 1), rhs.getElement(index))) {
            result.push(rhs.getElement(index));
            index++;
        } else {
            index++;
        }
        
    }
    return result;
}

template<class T>
void makeArray(const int size, Vector<T>& Vector) {
    int data = 0;
    for (int i = 0; i < size; ++i) {
        std::cin >> data;
        Vector.push(data);
    }
    return;
}

template<class T>
void printToStdout(const Vector<T>& Vector) {
    for (size_t i = 0; i < Vector.getSize(); ++i) {
        std::cout << Vector.getElement(i) << " ";
    }
    return;
}

int main() {
    Vector<int> lhs;
    Vector<int> rhs;

    int rhs_size = 0;
    std::cin >> rhs_size;

    int lhs_size = 0;
    std::cin >> lhs_size;

    makeArray(rhs_size, rhs);
    makeArray(lhs_size, lhs);

    printToStdout(intersection(rhs, lhs));

    return 0;
}