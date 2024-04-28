// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T arr[size];
    int top;

public:
    TStack() : top(-1) {}

    void push(T val) {
        if (top < size - 1) {
            arr[++top] = val;
        }
    }

    T pop() {
        if (top >= 0) {
            return arr[top--];
        }
        return T();
    }

    T peek() {
        if (top >= 0) {
            return arr[top];
        }
        return T();
    }

    bool isEmpty() {
        return top == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
