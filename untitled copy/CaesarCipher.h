#pragma once
#include <string>
#include <dlfcn.h>
#include <stdexcept>

class CaesarCipher {
    void* handle = nullptr;
    using crypt_func = void(*)(char*, int, int);
    crypt_func encrypt_func = nullptr;
    crypt_func decrypt_func = nullptr;
public:
    CaesarCipher(const std::string& libPath) {
        handle = dlopen(libPath.c_str(), RTLD_LAZY);
        if (!handle) throw std::runtime_error("Cannot load library");
        encrypt_func = (crypt_func)dlsym(handle, "caesar_encrypt");
        decrypt_func = (crypt_func)dlsym(handle, "caesar_decrypt");
        if (!encrypt_func || !decrypt_func) throw std::runtime_error("Cannot load functions");
    }
    std::string encrypt(const std::string& data, int key) {
        std::string out = data;
        encrypt_func(&out[0], out.size(), key);
        return out;
    }
    std::string decrypt(const std::string& data, int key) {
        std::string out = data;
        decrypt_func(&out[0], out.size(), key);
        return out;
    }
    ~CaesarCipher() { if (handle) dlclose(handle); }
};