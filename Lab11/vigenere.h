#ifndef VIGENERE_H
#define VIGENERE_H

#include <string>

class Vigenere {
public:
    Vigenere(std::string key);
    ~Vigenere();
    std::string encrypt(std::string msg);
    std::string decrypt(std::string msg);
    bool isEncrypted(std::string en_result, std::string de_result);
    void setKey(std::string key);

private:
    std::string key;
    int shift(char c);
};

#endif