#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>
#include <unordered_map>

class Hangman {
public:
    Hangman(int wordLength, int maxGuesses, const std::string& dictionaryFile = "dictionary.txt");

    // Public methods
    void displayBoard() const;
    virtual bool updateBoard(char guess);
    bool checkWord(const std::string& guess) const;
    bool hasExceededGuesses() const;
    std::string getCurrentWordState() const;
    int getRemainingGuesses() const;
    bool isGameFinished() const;
    bool playerWon() const;
    virtual std::string getActualWord() const;   // Made this virtual for the EvilHangman override

protected:
    // Protected data members
    int numberOfGuesses;
    int maxGuesses;
    std::string wordToGuess;
    std::string displayString;
    std::vector<char> lettersGuessed;

    // Protected methods
    std::string getRandomWordFromFile(const std::string& dictionaryFile, int wordLength) const;
};

class EvilHangman : public Hangman {
public:
    EvilHangman(int wordLength, int maxGuesses, const std::string& dictionaryFile = "dictionary.txt");
    
    // Override the update method for Evil Hangman's behavior
    bool updateBoard(char guess) override;
    std::string getActualWord() const override;  // Override for EvilHangman

private:
    // Private data members specific to Evil Hangman
    std::unordered_map<std::string, std::vector<std::string> > wordFamilies;

    // Private methods specific to Evil Hangman
    void partitionWords(char guess);
    std::string determineBestFamily() const;
};

#endif // HANGMAN_H
