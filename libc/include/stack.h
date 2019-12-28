#ifndef _STACK_H
#define _STACK_H 1

#include <stdint-gcc.h>

extern "C++" namespace std
{
    template <typename T>
    class stack
    {
    private:
        T data[];
        size_t sp; // stack pointer

    public:
        size_t getStackPtr();
        int getData(T buffer[]);
        int push(T element);
        T pop();
        stack(size_t size);
    };
}

#endif