#include <Arduino.h>

class SimpleTimer
{
private:
    int _delta;
    int _start;
    int _stop;
    const char *_name;
public:
    void start();
    void stop();
    int delta();
    void reset();
    SimpleTimer(const char *name);
};