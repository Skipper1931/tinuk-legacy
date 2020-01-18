// ../../include/stack.h implementation
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#include <stddef.h>
#include <stack.h>

using std::stack;

template<typename T>
size_t stack<T>::getStackPtr() {
    return sp;
}

template<typename T>
int stack<T>::getData(T buffer[]) {
    size_t bufSize = sizeof buffer;
    
    if (sizeof(buffer) < sp)
        return -1;

    for (int i = 0; i <= sp; i++) {
        buffer[i] = data[i];
    }

    return 0;
}

template<typename T>
int stack<T>::push(T element) {
    sp++;
    data[sp] = element;
    return 0;
}

template<typename T>
T stack<T>::pop() {
    T retval = data[sp];
    sp--;
    return retval;
}

template<typename T>
stack<T>::stack(size_t size) {
    return;
}