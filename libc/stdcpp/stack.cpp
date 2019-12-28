#include <stddef.h>
#include <stack.h>

using std::stack;

template<typename T>
size_t stack<T>::getStackPtr() {
    return 0;
}

template<typename T>
int stack<T>::getData(T buffer[]) {
    size_t bufSize = sizeof buffer;
    size_t dataSize = sizeof data;

    
}

template<typename T>
int stack<T>::push(T element) {
    return 0;
}

template<typename T>
T stack<T>::pop() {
    return 0;
}

template<typename T>
stack<T>::stack(size_t size) {
    return;
}