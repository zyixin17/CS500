#include "vigenere.h"
#include <cctype>
#include <iostream>

Vigenere::Vigenere(std::string key) {
    setKey(key);
}

Vigenere::~Vigenere() {
    // Destructor
}

std::string Vigenere::encrypt(std::string msg) {
    std::string result;
    for (size_t i = 0, j = 0; i < msg.length(); ++i) {
        char c = msg[i];
        if (std::isalpha(c)) {
            c = std::toupper(c);
            result += (c - 'A' + shift(key[j])) % 26 + 'A';
            j = (j + 1) % key.length();
        } else {
            result += c;
        }
    }
    return result;
}

std::string Vigenere::decrypt(std::string msg) {
    std::string result;
    for (size_t i = 0, j = 0; i < msg.length(); ++i) {
        char c = msg[i];
        if (std::isalpha(c)) {
            c = std::toupper(c);
            result += (c - shift(key[j]) - 'A' + 26) % 26 + 'A';
            j = (j + 1) % key.length();
        } else {
            result += c;
        }
    }
    return result;
}


bool Vigenere::isEncrypted(std::string en_result, std::string de_result) {
    return encrypt(de_result) == en_result;
}

void Vigenere::setKey(std::string key) {
    this->key = key;
}

int Vigenere::shift(char c) {
    return std::toupper(c) - 'A';
}

// Test
int main() {
    std::string key = "WAR";
    std::string message = "CS IS COOL";

    Vigenere cipher(key);
    std::string encryptedMessage = cipher.encrypt(message);
    std::string decryptedMessage = cipher.decrypt(encryptedMessage);

    std::cout << "Key: " << key << std::endl;
    std::cout << "Original Message: " << message << std::endl;
    std::cout << "Encrypted Message: " << encryptedMessage << std::endl;
    std::cout << "Decrypted Message: " << decryptedMessage << std::endl;

    return 0;
}