// Stack header for Tinuk's stdib (I doubt this is in the actual libc/libc++ standard but I'm leaving it
// since it'll probably be useful in general for me and for anyone who makes userspace programs on Tinuk)
// Copyright (C) 2020 Skipper1931 (GPL-3.0 License)

#ifndef _STACK_H
#define _STACK_H 1

#include <stdint.h>

extern "C++" namespace std
{
    template <typename T>
    class stack
    {
        private:
            T data[100];
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