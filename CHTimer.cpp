#include <map>
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
#include "CHTimer.h"

CHTimer *g_instance = nullptr;
std::map<uint32_t, CHTimerListener *> g_listeners;

static void TimeProc(UINT uID, UINT UMsg, DWORD dwUser,
                     DWORD dw1, DWORD dw2)
{
    g_listeners[uID]->Update();
}

CHTimer::CHTimer()
{
    TIMECAPS TimeCap;
    ::timeGetDevCaps(&TimeCap, sizeof(TIMECAPS));
    TimeCap.wPeriodMax;
}

CHTimer *CHTimer::get()
{
    if (g_instance == nullptr)
    {
        g_instance = new CHTimer;
    }
    return g_instance;
}

void CHTimer::release()
{
    if (g_instance != nullptr)
    {
        delete g_instance;
        g_instance = nullptr;
    }
    if (!g_listeners.empty())
    {
        g_listeners.clear();
    }
}

bool CHTimer::start(CHTimerListener *listener, uint32_t _delay )
{
    bool Result = true;
    uint32_t m_Id;
    if ((m_Id = ::timeSetEvent(_delay, m_PeriodMax, (LPTIMECALLBACK)TimeProc,
                               (DWORD)(this), TIME_PERIODIC)) != NULL)
    {
        g_listeners.insert(std::map<uint32_t, CHTimerListener *>::value_type(m_Id, listener));
    }
    else
    {
        Result = false;
    }
    return Result;
}

void CHTimer::stop(CHTimerListener *listener)
{
    for (const auto &p : g_listeners)
    {
        if (p.second == listener)
        {
            ::timeKillEvent(p.first);
        }
    }
}

CHTimer::~CHTimer()
{
    for (const auto &p : g_listeners)
    {
        ::timeKillEvent(p.first);
    }
}
