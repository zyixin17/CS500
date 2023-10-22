#include <iostream>
#include <cstring>

class MyString {
private:
    char* data;
    int size;

public:
    MyString(const char* input) {
        size = strlen(input);
        data = new char[size + 1];
        for(int i = 0; i < size; i++) {
            data[i] = input[i];
        }
        data[size] = '\0';
    }

    ~MyString() {
        delete[] data;
    }

    const char* ToString() const {
        return data;
    }

    int length() {
        return size;
    }

    MyString operator+(const MyString& other) {
        int newSize = size + other.size;
        char* resultData = new char[newSize + 1];
        for(int i = 0; i < size; i++) {
            resultData[i] = data[i];
        }
        for(int j = 0; j < other.size; j++) {
            resultData[size + j] = other.data[j];
        }
        resultData[newSize] = '\0';
        return MyString(resultData);
    }

    friend std::ostream& operator<<(std::ostream& out, const MyString& s) {
        out << s.data;
        return out;
    }

    MyString substr(int start, int n = -1) {
        if (start >= size) {
            return MyString("");
        }

        if (n == -1 || start + n > size) {
            n = size - start;
        }

        char* subData = new char[n + 1];
        for(int i = 0; i < n; i++) {
            subData[i] = data[start + i];
        }
        subData[n] = '\0';
        return MyString(subData);
    }
};

int main() {
    MyString s1("Hello");
    MyString s2(", World!");

    std::cout << "Hello + , World!" << std::endl;

    MyString s3 = s1 + s2;
    std::cout << s3.ToString() << std::endl;
    std::cout << s1.length() << std::endl;
}
