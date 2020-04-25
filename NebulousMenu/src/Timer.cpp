#include "Timer.h"

Timer::Timer()
{
    //ctor
    startAt = 0;
}

Timer::~Timer()
{
    //dtor
}
void Timer::start()
{
    startAt = clock();

}

void Timer::stop()
{

}

void Timer::reset()
{
    startAt = clock();

}


clock_t Timer::getTicks()
{
    return clock()-startAt;

}


