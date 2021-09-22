//
// Created by Jeffrey on 5/14/2021.
//

#ifndef HANGMAN_LETTERNODE_H
#define HANGMAN_LETTERNODE_H

#include <string>
#include <iostream>

const size_t ALPHABET_SIZE = 26;


class LetterNode {
private:
    typedef LetterNode* NodePtr;
    char storedCharacter;
    bool endWord;
    NodePtr charArray[ALPHABET_SIZE];

public:
    // Constructor
    LetterNode(char c, bool b);

    // Copy Constructor
    LetterNode(const LetterNode& rhs);

    // Destructor
    ~LetterNode();


    // Assignment Operator
    const LetterNode& operator= (const LetterNode& rhs);


    void print (const std::string& str) const;


    size_t wordCount () const;



    void insert (const std::string& str);

    bool isPrefix (const std::string& pre) const;

    bool isWord (const std::string& str) const;

};


#endif //HANGMAN_LETTERNODE_H
