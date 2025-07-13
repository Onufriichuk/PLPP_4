#include <stddef.h>

void caesar_encrypt(char* data, int len, int key) {
    for (int i = 0; i < len; ++i)
        if (data[i] >= 32 && data[i] <= 126)
            data[i] = 32 + (data[i] - 32 + key) % 95;
}

void caesar_decrypt(char* data, int len, int key) {
    for (int i = 0; i < len; ++i)
        if (data[i] >= 32 && data[i] <= 126)
            data[i] = 32 + (data[i] - 32 - key + 95) % 95;
}
