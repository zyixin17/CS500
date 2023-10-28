#include <iostream>
#include <unordered_map>
#include <sstream>
#include <cctype>

class Pirate {
public:
    Pirate() {
        initTransMap();
    }

    std::string toPirate(const std::string& english) const;

private:
    std::unordered_map<std::string, std::string> transMap;

    void initTransMap();
    std::string lower(const std::string& word) const;
};

void Pirate::initTransMap() {
    transMap["hello"] = "ahoy";
    // Replace "excuse me" with "excuseme" to avoid confusion with "me"
    // Then use same method to replace "excuseme" with "arrr"
    transMap["excuseme"] = "arrr";
    transMap["sir"] = "matey";
    transMap["boy"] = "matey";
    transMap["man"] = "matey";
    transMap["madame"] = "proud beauty";
    transMap["officer"] = "foul blaggart";
    transMap["the"] = "th'";
    transMap["my"] = "me";
    transMap["your"] = "yer";
    transMap["is"] = "be";
    transMap["are"] = "be";
    transMap["restroom"] = "head";
    transMap["restaurant"] = "galley";
    transMap["hotel"] = "fleabag inn";
    transMap["coins"] = "doubloons";
    transMap["pirate"] = "buccaneer";
    transMap["friend"] = "mate";
    transMap["you"] = "ye";
}

// all lowercase
std::string Pirate::lower(const std::string& word) const {
    std::string result;
    for (char c : word) {
        result += tolower(c);
    }
    return result;
}

std::string Pirate::toPirate(const std::string& english) const {
    std::string result, word, punctuation;
    std::string temp = english;
    size_t pos = 0;

    // Replace "excuse me" with "excuseme"
    while (true) {
        size_t pos1 = temp.find("excuse me", pos);
        size_t pos2 = temp.find("Excuse me", pos);

        if (pos1 == std::string::npos && pos2 == std::string::npos) break;

        if (pos2 == std::string::npos || (pos1 != std::string::npos && pos1 < pos2)) {
            temp.replace(pos1, 9, "excuseme");
            pos = pos1 + 9;
        } else {
            temp.replace(pos2, 9, "excuseme");
            pos = pos2 + 9;
        }
    }

    std::istringstream iss(temp);

    while (iss >> word) {
        punctuation = "";
        while (!word.empty() && ispunct(word.back())) {
            punctuation = word.back() + punctuation;
            word.pop_back();
        }
        std::string lowerWord = lower(word);
        if (transMap.find(lowerWord) != transMap.end()) {
            result += transMap.at(lowerWord) + punctuation + " ";
        } else {
            result += word + punctuation + " ";
        }
    }

    return result.substr(0, result.length() - 1);  // Remove trailing space
}


int main() {
    Pirate translator;

    // Test cases
    std::string test1 = "Hello, madame, would you direct me to the nearest hotel?";
    std::string test2 = "Sir, what is the name of your best restaurant?";
    std::string test3 = "Excuse me, officer, my friend is lost. He is a fellow pirate looking for coins to pay the restaurant.";
    std::string test4 = "Hello madame, how are you?";
    std::string test5 = "Excuse me excuse me excuse me!!!";

    std::cout << "Test1" << std::endl;
    std::cout << "English: " << test1 << " \n" << "Pirate: " << translator.toPirate(test1) << " \n " << std::endl;
    std::cout << "Test2" << std::endl;
    std::cout << "English: " << test2 << " \n" << "Pirate: " << translator.toPirate(test2) << " \n " << std::endl;
    std::cout << "Test3" << std::endl;
    std::cout << "English: " << test3 << " \n" << "Pirate: " << translator.toPirate(test3) << " \n " << std::endl;
    std::cout << "Test4" << std::endl;
    std::cout << "English: " << test4 << " \n" << "Pirate: " << translator.toPirate(test4) << " \n " << std::endl;
    std::cout << "Test5" << std::endl;
    std::cout << "English: " << test5 << " \n" << "Pirate: " << translator.toPirate(test5) << " \n " << std::endl;
    
    return 0;
}
