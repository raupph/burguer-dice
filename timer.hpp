#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

struct Timer { std::chrono::steady_clock::time_point start; };
void timerStart(Timer *timer);
double timerStop(Timer *timer); /* returns time in seconds */

#endif