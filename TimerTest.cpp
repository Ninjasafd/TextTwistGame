//
// Created by Jeffrey on 6/1/2021.
//


#include <iostream>
#include "Timer.h"
#include "Windows.h"
#include <cstdlib>


int main() {

    size_t counter = 0;
    Timer t = Timer();
    for (size_t i = 0; i < 10000; ++i){
//        auto elapsed = t.Elapsed();
        srand(time(0));
        counter++;
        std::cout << "#" << counter << "  " << std::to_string(rand()%7) << std::endl;
        Sleep(500);
    }



    return 0;
    }



