#include "hangman.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Hangman methods

Hangman::Hangman(int wordLength, int maxGuesses, const std::string& dictionaryFile)
    : maxGuesses(maxGuesses), numberOfGuesses(0) {
    wordToGuess = getRandomWordFromFile(dictionaryFile, wordLength);
    displayString = std::string(wordLength, '-');
}

std::string Hangman::getRandomWordFromFile(const std::string& dictionaryFile, int wordLength) const {
    std::vector<std::string> validWords;
    std::ifstream inFile(dictionaryFile);
    std::string word;

    while (inFile >> word) {
        if (word.length() == wordLength) {
            validWords.push_back(word);
        }
    }
    inFile.close();

    srand(time(nullptr));
    if (validWords.empty()) {
        throw std::runtime_error("empty");
    }
    int randomIndex = rand() % validWords.size();
    return validWords[randomIndex];
}

void Hangman::displayBoard() const {
    std::cout << "Word: " << displayString << "\n";
    std::cout << "Guesses: " << numberOfGuesses << "/" << maxGuesses << "\n";
    std::cout << "Guessed Letters: ";
    for (char letter : lettersGuessed) {
        std::cout << letter << " ";
    }
    std::cout << "\n";
}

bool Hangman::updateBoard(char guess) {
    bool guessIsCorrect = false;

    guess = std::tolower(guess);

    for(size_t i = 0; i < wordToGuess.size(); i++) {
        if(wordToGuess[i] == guess) {
            displayString[i] = guess;  
            guessIsCorrect = true;
        }
    }


    if(guessIsCorrect) {
        return true;
    } else {
        numberOfGuesses++; 
        if(numberOfGuesses >= maxGuesses) {
            //end game

            return true;
        }
        return false;
    }
}


bool Hangman::checkWord(const std::string& guess) const {
    return wordToGuess == guess;
}

bool Hangman::hasExceededGuesses() const {
    return numberOfGuesses >= maxGuesses;
}

std::string Hangman::getCurrentWordState() const {
    return displayString;
}

int Hangman::getRemainingGuesses() const {
    return maxGuesses - numberOfGuesses;
}

bool Hangman::isGameFinished() const {
    return hasExceededGuesses() || displayString.find('-') == std::string::npos;
}

bool Hangman::playerWon() const {
    return displayString.find('-') == std::string::npos;
}

std::string Hangman::getActualWord() const {
    return wordToGuess;
}

// EvilHangman methods

EvilHangman::EvilHangman(int wordLength, int maxGuesses, const std::string& dictionaryFile): Hangman(wordLength, maxGuesses, dictionaryFile) {

    for(size_t i = 0; i < wordToGuess.size(); i++) {
        displayString[i] = '_';
    }

    for(size_t i = 0; i < wordToGuess.size(); i++) {
        std::string pattern = displayString;
        pattern[i] = wordToGuess[i];
        wordFamilies[pattern].push_back(wordToGuess);
    }
}


bool EvilHangman::updateBoard(char guess) {
    std::unordered_map<std::string, std::vector<std::string> > families;

    for (const auto& word : wordFamilies) {
        std::string pattern = word.first;
        for (char &c : pattern) {
            if (c != guess) {
                c = '_';
            }
        }

        families[pattern].insert(families[pattern].end(), word.second.begin(), word.second.end());
    }

    size_t maxSize = 0;
    std::string bestPattern;
    int minGuessChars = INT_MAX; 
    for (const auto& pair : families) {
        int guessCharCount = std::count(pair.first.begin(), pair.first.end(), guess);
        if (pair.second.size() > maxSize || (pair.second.size() == maxSize && guessCharCount < minGuessChars)) {
            maxSize = pair.second.size();
            bestPattern = pair.first;
            minGuessChars = guessCharCount;
        }
    }

    wordFamilies = families;

    for (size_t i = 0; i < bestPattern.size(); i++) {
        if (bestPattern[i] != '_') {
            displayString[i] = bestPattern[i];
        }
    }

    return bestPattern.find(guess) != std::string::npos;
}


void EvilHangman::partitionWords(char guess) {
    std::unordered_map<std::string, std::vector<std::string> > newFamilies;

    for(const auto& word : wordFamilies) {
        std::string pattern = word.first;
        for(char &c : pattern) {
            if(c != guess) {
                c = '_';
            }
        }
        newFamilies[pattern].insert(newFamilies[pattern].end(), word.second.begin(), word.second.end());
    }

    wordFamilies = newFamilies;
}

std::string EvilHangman::determineBestFamily() const {
    size_t maxSize = 0;
    std::string bestPattern;

    for(const auto& pair : wordFamilies) {
        if(pair.second.size() > maxSize) {
            maxSize = pair.second.size();
            bestPattern = pair.first;
        }
    }

    return bestPattern;
}

std::string EvilHangman::getActualWord() const {
    if (wordFamilies.empty()) return "UNKNOWN";
    return wordFamilies.begin()->second[0];
}

int main() {
    EvilHangman game(5, 10, "dictionary.txt");

    std::cout << "object is to guess the word before you are hung." << std::endl;

    while(true) {
        std::cout << "The word now looks like this: " << game.getCurrentWordState() << std::endl;
        std::cout << "You have " << game.getRemainingGuesses() << " guesses left." << std::endl;
        
        std::cout << "Guess a letter: ";
        char guess;
        std::cin >> guess;

        if(game.updateBoard(guess)) {
            std::cout << "That guess is correct." << std::endl;
        } else {
            std::cout << "There are no '" << guess << "'s in the word." << std::endl;
        }

        if(game.isGameFinished()) {
            if(game.playerWon()) {
                std::cout << "You guessed the word: " << game.getCurrentWordState() << std::endl;
            } else {
                std::cout << "Sorry, the word was: " << game.getActualWord() << std::endl;
            }
            break;
        }
    }
    game.displayBoard();
    std::cout << "Exit" << std::endl;
    return 0;
}