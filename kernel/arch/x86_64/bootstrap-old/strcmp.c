#include <string.h>

int strcmp(const char* a, const char* b) {
    int i = 0;
    
    while(1) {
        if(a[i] == b[i]) {
            if(a[i] == '\0')
                return 1;
        }
        else {
            return 0;
        }

        i++;
    }

    return -1;
}