#include "timer.hpp"

void timerStart(Timer *timer)
{
    timer->start = std::chrono::steady_clock::now();
}
double timerStop(Timer *timer)
{
    auto fim = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(fim - timer->start).count();
}