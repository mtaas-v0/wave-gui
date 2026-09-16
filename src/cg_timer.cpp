/*! \file cg_timer.cpp
 *  \brief Enter description here.
 *  \author Georgi Gerganov
 */

#include "cg_logger.h"
#include "cg_timer.h"

#ifndef DOXYGEN_HIDE

#include <chrono>

namespace CG {
class TimerImplementation {
public:
    TimerImplementation() {
        start();
    };

    void start() {
        _tStart = std::chrono::high_resolution_clock::now();
    }

    float time() {
        _tEnd = std::chrono::high_resolution_clock::now();
        return 1e-3*std::chrono::duration_cast<std::chrono::milliseconds>(_tEnd - _tStart).count();
    };

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _tStart;
    std::chrono::time_point<std::chrono::high_resolution_clock> _tEnd;
};
}

#endif

namespace CG {

CG_EXPORT  Timer::Timer() { m_timer = new TimerImplementation; m_timer->start(); }

CG_EXPORT  Timer::~Timer() { delete m_timer; }

CG_EXPORT  void Timer::start() { m_timer->start(); }

CG_EXPORT  float Timer::time() { return m_timer->time(); }
}
