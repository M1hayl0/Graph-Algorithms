#ifndef IMPLEMENTACIJA_STEKA__OOP_NACIN__STEK_H
#define IMPLEMENTACIJA_STEKA__OOP_NACIN__STEK_H

#include <iostream>
using namespace std;

template<typename T>
class Stek {
    T* stek;
    int top, duzina;

public:
    explicit Stek(int d) {
        top = -1;
        duzina = d;
        stek = new T[duzina];
    }

    ~Stek() { delete[] stek; }

    T dohvatiTop() const { return top; }

    void push(const T& t);
    void pop(T& t);
    void ispis() const;
};

template<typename T>
void Stek<T>::push(const T& t) {
    if (top == duzina - 1) {
        cout << "Overflow ";
        exit(0);
    }
    else {
        stek[++top] = t;
    }
}

template<typename T>
void Stek<T>::pop(T& t) {
    if (top == -1) {
        cout << "Underflow";
        exit(0);
    }
    else {
        t = stek[top--];
    }
}

template<typename T>
void Stek<T>::ispis() const {
    for (int i = 0; i < top + 1; i++) cout << stek[i] << " ";
    cout << endl;
}

#endif //IMPLEMENTACIJA_STEKA__OOP_NACIN__STEK_H
