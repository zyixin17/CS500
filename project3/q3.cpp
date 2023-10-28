#include <iostream>
#include <unordered_map>
#include <string>

int romanToDecimal(const std::string &str) {
    std::unordered_map<char, int> lookup;
    lookup['I'] = 1;
    lookup['V'] = 5;
    lookup['X'] = 10;
    lookup['L'] = 50;
    lookup['C'] = 100;
    lookup['D'] = 500;
    lookup['M'] = 1000;

    int add = 0; // addition value
    int sub = 0; // subtraction value

    for (int i = 0; i < str.size(); i++) {
        // smaller than the next one
        if (i < str.size() - 1 && lookup[str[i]] < lookup[str[i + 1]]) {
            sub += lookup[str[i]];
        } else {
            // larger than the next one
            add += lookup[str[i]];
        }
    }

    return add - sub;
}

int main() {
    std::string roman;
    std::cout << "Enter roman number:";
    std::cin >> roman;
    std::cout << "To decimal: " << romanToDecimal(roman) << std::endl;
    return 0;
}