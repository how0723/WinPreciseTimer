#include <iostream>
#include <vector>
#include "CHTimer.h"
#include "timer.h"

class Test : public CHTimerListener
{
public:
    Test(int _id);
    ~Test();
    virtual void Update();
private:
    int id;
};

void Test::Update()
{
    printf("id=%d now=%f\n", id, Timer::get()->getElapsedTimeInMilliSec());
}

Test::Test(int _id)
{
    id = _id;
}

Test::~Test()
{
}

int main()
{
    std::vector<Test *> testors;
    for (int i = 0; i < 16; i++)
    {
        testors.emplace_back(new Test(i));
    }

    Timer::get()->start();
    for (auto p : testors)
    {
        CHTimer::get()->start(p, 500);
    }
    getchar();
    for (auto p : testors)
    {
        CHTimer::get()->stop( p);
    }
    getchar();
    return 0;
}