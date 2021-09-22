//
// Created by Jeffrey on 6/1/2021.
//

#include "Timer.h"

Timer::Timer(){

}


milliseconds Timer::Elapsed()
{
    return std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - start);
}


//namespace EngineUtils {
//    Timer::Timer() {
//        TInstance = nullptr;
//        Reset();
//        TtimeScale = 1.0f;
//        TdeltaTime = std::chrono::duration<float>(0.0f);
//    }
//
//
//    Timer *Timer::instance() {
//        if (TInstance == nullptr) {
//            TInstance = new Timer();
//        }
//        return TInstance;
//    }
//
//
//    void Timer::Release() {
//        delete TInstance;
//        TInstance = nullptr;
//    }
//
//
//    Timer::~Timer() {}
//
//    void Timer::Reset() {
//        TstartTime = std::chrono::system_clock::now();
//
//    }
//
//
//    float Timer::deltaTime() {
//        return TdeltaTime.count();
//    }
//
//
//    float Timer::TimeScale() {
//        return TtimeScale;
//    }
//
//
//    void Timer::Tick() {
//        TdeltaTime = std::chrono::system_clock::now() - TstartTime;
//    }
//
//}