//
// Created by Jeffrey on 5/14/2021.
//

#include "LetterNode.h"

LetterNode::LetterNode(char c, bool b) : storedCharacter(c), endWord(b)
{
    for (size_t i = 0; i < ALPHABET_SIZE; ++i){
        charArray[i] = nullptr;
    }
}


LetterNode::LetterNode(const LetterNode &rhs) : storedCharacter(rhs.storedCharacter),
                                               endWord(rhs.endWord)
{
    for (size_t i = 0; i < ALPHABET_SIZE; ++i){
        if (rhs.charArray[i] == nullptr){
            charArray[i] = nullptr;
        }
        else {
            charArray[i] = new LetterNode(*(rhs.charArray[i]));
        }
    }
}


const LetterNode& LetterNode::operator= (const LetterNode& rhs){
    if (this != &rhs){
        LetterNode tmp(rhs);
        std::swap(storedCharacter, tmp.storedCharacter);
        std::swap(endWord, tmp.endWord);
        std::swap(charArray, tmp.charArray);
    }
    return *this;
}

LetterNode::~LetterNode(){
    for (size_t i = 0; i < ALPHABET_SIZE; ++i){
        delete charArray[i];
        charArray[i] = nullptr;
    }
}


void LetterNode::insert(const std::string& str){
    if (str.length() == 0){
        return;
    }

    size_t index = str[0]-'a';
    if (charArray[index] == nullptr){
        charArray[index] = new LetterNode(str[0],str.length() == 1);
    }
    else{
        if (str.length() == 1){
            charArray[index]->endWord = true;
        }
    }

    if (str.length() != 1){
        charArray[index]->insert(str.substr(1, str.length() - 1));
    }
}

bool LetterNode::isWord(const std::string& str) const{
    if (str.length() == 0){
        return false;
    }

    size_t index = str[0]-'a';
    if (str.length() == 1){
        if (charArray[index] != nullptr && charArray[index]->endWord){
            return true;
        }
        else{
            return false;
        }
    }

    return (charArray[index] != nullptr) &&
           charArray[index]->isWord(str.substr(1, str.length() - 1));
}


bool LetterNode::isPrefix(const std::string& pre) const{
    if (pre.length() == 0){
        return true;
    }

    size_t index = pre[0]-'a';
    if (pre.length() == 1){
        if (charArray[index] != nullptr){
            return true;
        }
        else{
            return false;
        }
    }

    return (charArray[index] != nullptr) &&
           charArray[index]->isPrefix(pre.substr(1, pre.length() - 1));
}



void LetterNode::print(const std::string& str) const{
    if (endWord) {
        std::cout << str + storedCharacter << std::endl;
    }

    for (size_t i = 0; i < ALPHABET_SIZE; ++i){
        if (charArray[i] != nullptr){
            if (storedCharacter == ' '){
                charArray[i]->print(str);
            }
            else{
                charArray[i]->print(str + storedCharacter);
            }

        }
    }

}


size_t LetterNode::wordCount () const{
    size_t counter = 0;

    for (size_t i = 0; i < ALPHABET_SIZE; ++i){
        if (charArray[i] != nullptr){
            if (charArray[i]->endWord){
                ++counter;
            }
            counter += charArray[i]->wordCount();
        }
    }

    return counter;
}