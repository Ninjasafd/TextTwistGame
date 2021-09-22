//
// Created by Jeffrey on 6/1/2021.
//


#include <chrono>
#ifndef HANGMAN_TIMER_H
#define HANGMAN_TIMER_H


typedef std::chrono::high_resolution_clock high_resolution_clock;
typedef std::chrono::milliseconds milliseconds;


class Timer {
private:
    std::chrono::time_point<std::chrono::system_clock> start = high_resolution_clock::now();




public:
    Timer();

    milliseconds Elapsed();

    void wait();
};


#endif //HANGMAN_TIMER_H
