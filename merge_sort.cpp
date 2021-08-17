#include <assert.h>

#include <iostream>
#include <functional>
#include <ctime>

#define VECTOR_INIT_SIZE 8

#define INIT_PERSON 0

namespace vector {
template <class T>
class Vector {
    public:
        Vector() : arr(nullptr), capacity(0), size(0) {}
        ~Vector();
        explicit Vector(size_t size);
        void push(T data);
        T popBack();
        T& getFront() const;
        T& getBack() const;
        const size_t& getCapacity() const;
        const size_t& getSize() const;
        T& getElement(size_t index) const;
        void setElement(size_t index, T value);

    private:
        T* arr;
        size_t capacity;
        size_t size;
};

template <class T>
Vector<T>::Vector(size_t size) : arr(nullptr), capacity(0), size(size) {
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

    for (size_t i = 0;i < capacity;i++) {
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
}; // namespace vector

struct date {
    short day;
    short mounth;
    int year;
};

struct person {
    date birth;
    date death;
    size_t x1;
    size_t x2;
};

template <class T>
void fillVector(size_t count, vector::Vector<T>& allPersons) {
    for (size_t i = 0; i < count; ++i) {
        person newPerson = person();
        std::cin >> newPerson.birth.day;
        std::cin >> newPerson.birth.mounth;
        std::cin >> newPerson.birth.year;

        std::cin >> newPerson.death.day;
        std::cin >> newPerson.death.mounth;
        std::cin >> newPerson.death.year;

        newPerson.x1 = (newPerson.birth.year + 18) * 10000 +
                newPerson.birth.mounth * 100 +
                newPerson.birth.day;

        newPerson.x2 = newPerson.death.year * 10000 +
                newPerson.death.mounth * 100 +
                newPerson.death.day;

        if (newPerson.x1 < newPerson.x2) {
            allPersons.push(newPerson);
        }
    }

    for (size_t i = 0; i < allPersons.getSize(); ++i) {
        size_t lastday = allPersons.getElement(i).x1 + (62 * 10000);
        if (lastday < allPersons.getElement(i).x2) {
            allPersons.getElement(i).x2 = lastday - 1;
        } else {
            allPersons.getElement(i).x2--;
        }
    }
}

template <class T>
void showVector(vector::Vector<T>& arr){
    for (size_t i = 0; i < arr.getSize(); i++) {
        std::cout << arr.getElement(i).first << " ";
    }
}

template <class T>
void merge(vector::Vector<T>& arr, size_t l, size_t m, size_t r)
{
    size_t n1 = m - l + 1;
    size_t n2 =  r - m;
    vector::Vector<T> L(n1);
    vector::Vector<T> R(n2);

    for (size_t i = 0; i < n1; i++) {
        L.setElement(i, arr.getElement(l + i));
    }
    for (size_t j = 0;j < n2; j++) {
        R.setElement(j, arr.getElement(m + 1 + j));
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = l;
    while (i < n1 && j < n2) {
        if (L.getElement(i) <= R.getElement(j)) {
            arr.setElement(k, L.getElement(i));
            i++;
        } else {
            arr.setElement(k, R.getElement(j));
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr.setElement(k, L.getElement(i));
        i++;
        k++;
    }
    while (j < n2) {
        arr.setElement(k, R.getElement(j));
        j++;
        k++;
    }
}

template <class T>
void mergeSort(vector::Vector<T>& arr, size_t l, size_t r) {
    if (l < r) {
        size_t m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

size_t run(size_t count) {
    vector::Vector<person> allPersons;
    fillVector(count, allPersons);

    if (allPersons.getSize() == 0 || allPersons.getSize() == 1) {
        return 0;
    }

    vector::Vector<std::pair <int, bool> > points(allPersons.getSize() * 2);
    for (size_t i = 0; i < allPersons.getSize(); i++) {
        points.setElement(i * 2,
                        std::make_pair(allPersons.getElement(i).x1, false));

        points.setElement(i * 2 + 1,
                        std::make_pair(allPersons.getElement(i).x2, true));
    }

    mergeSort(points, 0, points.getSize() - 1);
    //showVector(points);

    int c = 0;
    int res = 0;
    for (size_t i = 0; i < points.getSize(); i++) {
        if (c > res) {
            res = c;
        }
        (points.getElement(i).second) ? c-- : c++;
    }
    return res;
}

int main () {
    size_t count = 0;
    std::cin >> count;
    std::cout << run(count) << std::endl;
    return 0;
}
