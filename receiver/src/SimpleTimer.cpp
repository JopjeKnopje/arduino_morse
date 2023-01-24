#include "SimpleTimer.hpp"


SimpleTimer::SimpleTimer(const char *name)
{
    _name = name;
}

void SimpleTimer::start()
{
   _start = millis(); 
}

void SimpleTimer::stop()
{
    _stop = millis();
}

int SimpleTimer::delta()
{
    _delta = _stop - _start;
    return _delta;
}