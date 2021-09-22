#include <iostream>
#include "Letter.h"
#include <random>
#include "Timer.h"
#include "Windows.h"
#include <cstdlib>

std::string userString();

bool checkValidLetters(std::string const &str);

void recursiveInsert(std::string const &str, std::string const &letters,
                     Letter &insertTo,const Letter &dictionary);

std::string letterScrambler(std::string &letters);

const size_t DEFAULT_SIZE = 7;      // Number of Letters
const size_t MINIMUM_SIZE = 3;      // Number of Letters

int main() {
    std::cout << "Welcome to Hangman!!" << std::endl;
    Letter dictionary;
    std::string choice;
    size_t wordsFound = 0;
    size_t points = 0;
    Letter wordCombinations;
    Letter Guesses;
    std::string characterString = "";

    std::cout << "\nWould you like to use dictionary words   (Type y)" << std::endl;
    std::cin >> choice;

    bool trace = choice.at(0)=='Y' || choice.at(0)=='y';

    if (trace){
        dictionary.loadFromFile("wordsList.txt");
    }




    do {
        std::cout << "\nWould you like to generate your own words?   (Type y)" << std::endl;
        std::cin >> choice;

        trace = choice.at(0)=='Y' || choice.at(0)=='y';

        if (trace){
            std::cout << "What word would you like to add?" << std::endl;
            std::string word;
            std::cin >> word;
            dictionary.insert(word);
            std::cout << word << " has been added";
        }

    } while (choice.at(0)=='Y' || choice.at(0)=='y');



    std::cout << "Would you like a randomly generated word or choose your own. Enter '1' to get a "
                  << "randomly generated, a '2' to choose your own letters.";
    int choices = 0;
    do {
        std::cin >> choices;
        if (choices<1 || choices>2)
        {
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while ((choices<1 || choices>2) & std::cin.good());

    switch (choices)
    {
        case 1: {
            unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();
            // create the generator using the seed
            std::default_random_engine generator(seed);
            // create the appropriate distribution
            std::uniform_real_distribution<double> distribution(0, 25);
            // create random numbers as needed (the following will likely be in a loop)

            for (size_t i = 0; i < 7; ++i){
                int num = (int) distribution(generator);
                char letter = 'a' + num;
                characterString += letter;
            }
            break;
            }
        case 2: {
            std::cout << "Enter the seven letters you want to insert" << std::endl;
            std::string letters = userString();
            characterString = letters;
            break;
        }
        default:
            std::cout << "Non-int input. Halting program." << std::endl;
            exit(1);


    }

    recursiveInsert("", characterString, wordCombinations, dictionary);





    std::cout << std::endl << "Alright, we're ready to play!" << std::endl
        << "There are a total of " << wordCombinations.wordCount() << " combinations from the following letters.\n"
        << characterString << std::endl << "You can begin guessing now. You have one minute " << std::endl
        << "To scramble letters, type 'scramble', to show the list of letters, type 'list'" << std::endl;


    std::string userInput;
    bool thirtysecs = true;
    Timer t = Timer();
    size_t elapsed = 0;

    while (elapsed < 1000 * 60) {
        elapsed = t.Elapsed().count();
        if (thirtysecs && elapsed > 1000 * 30 ){
            thirtysecs = false;
            std::cout << "You only have 30 seconds left!" << std::endl;
        }
        Sleep(200);



        std::getline(std::cin, userInput);
        if (!userInput.empty() || std::cin.fail()) {
            for (size_t i = 0; i < userInput.size(); ++i) {
                userInput[i] = tolower(userInput[i]);
            }
            if (userInput == "scramble") {
                characterString = letterScrambler(characterString);
                std::cout << "Scrambled. Letters    ->      " << characterString << std::endl;
            }
            if (userInput == "list") {
                std::cout << characterString << std::endl;
            }
            if (wordCombinations.isWord(userInput)) {

                switch (userInput.size()) {
                    case 3:
                        points += 5;
                        break;
                    case 4:
                        points += 15;
                        break;
                    case 5:
                        points += 30;
                        break;
                    case 6:
                        points += 50;
                        break;
                    case 7:
                        points += 75;
                        break;
                }
                wordsFound++;
                std::cout << "You found a word: \"" << userInput << "\". You now have " << points
                          << " points! There are " << wordCombinations.wordCount() - wordsFound
                          << " words left!" << std::endl;
            }
        }

    }




    std::cout << std::endl << "Time is Up! You scored a total of " << points << " points! You found " << wordsFound
        << " of the " << wordCombinations.wordCount() << " words! Thanks for playing" << std::endl;



    return 0;
}



std::string userString(){
    std::string letters;
    bool validLetters;

    do{
        std::cout << "Enter seven letters that make up the words: ";
        std::cin >> letters;
        std::cout << std::endl;

        validLetters = checkValidLetters(letters);
        if (!validLetters){
            std::cout << "Please enter seven letters that are all lowercase" << std::endl;
        }
    } while (!validLetters);


    return letters;
}


bool checkValidLetters(std::string const &str) {
    if (str.length() != DEFAULT_SIZE){
        return false;
    }

    for (size_t i = 0; i < DEFAULT_SIZE; ++i){
        char ch = str[i];
        if (!(ch >= 'a' && ch <= 'z')){
            return false;
        }
    }

    return true;
}

void recursiveInsert(std::string const &str, std::string const &letters,
                     Letter &insertTo,const Letter &dictionary)
{
    if (dictionary.isWord(str) && str.length() >= MINIMUM_SIZE){
        insertTo.insert(str);
    }

    if (!dictionary.isPrefix(str) || letters.length() == 0){
        return;                       // The branch is done
    }

    std::string temp;
    for (size_t i = 0; i < letters.length(); ++i){
        if (letters.find(letters[i]) == i){     // Checks for more than one instance of a letter
            temp = letters;                     // Copy of letters to be changed
            recursiveInsert(str + letters[i], temp.erase(i, 1), insertTo, dictionary);
        }
    }

}


std::string letterScrambler(std::string &letters){
    srand(time(0));
    int holder;
    std::string newLetters = "";

    for (int i = letters.size() ; i > 0; --i){
        if (i == 0){
            newLetters += letters;
        }
        else{
            holder = rand() % i;
            newLetters += letters[holder];
            letters.erase(holder, 1);
        }
    }



    return newLetters;
}