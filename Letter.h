//
// Created by Jeffrey on 5/14/2021.
//

#ifndef HANGMAN_LETTER_H
#define HANGMAN_LETTER_H

#include <string>
#include "LetterNode.h"

class Letter {
private:
    LetterNode root;

    void openFile(std::ifstream &infile, const std::string &fname);


public:
    Letter();

    void insert(const std::string& word);

    void loadFromFile (const std::string& filename);

    bool isWord (const std::string& word) const;

    bool isPrefix (const std::string& pre) const;

    void print() const;

    size_t wordCount() const;
};


#endif //HANGMAN_LETTER_H
