//
// Created by Jeffrey on 5/14/2021.
//

#include "Letter.h"
#include <fstream>
#include <iostream>


Letter::Letter() : root(' ', false)
{
// Nothing else to do
}

void Letter::insert(const std::string& word)
{
    root.insert(word);
}



void Letter::loadFromFile(const std::string& filename){
    std::ifstream infile;
    openFile(infile, filename);

    std::string temp;
    while (infile >> temp){
        root.insert(temp);
    }

    infile.close();
}

bool Letter::isWord(const std::string& word) const{
    return root.isWord(word);
}


bool Letter::isPrefix(const std::string& pre) const{
    return root.isPrefix(pre);
}


void Letter::print() const{
    root.print("");
}


size_t Letter::wordCount() const{
    return root.wordCount();
}


void Letter::openFile(std::ifstream &infile, const std::string &fname)
{
    infile.open(fname.c_str());
    if (infile.fail()) {
        std::cout << "Error opening input data file" << std::endl;

        throw std::invalid_argument("File Cannot be Opened");
    }
}