class CHTimerListener
{
public:
    virtual void Update() = 0;
};

class CHTimer
{
public:
    CHTimer();
    ~CHTimer();
    bool start(CHTimerListener *listener, uint32_t _delay);
    void stop(CHTimerListener *listener);
    static CHTimer *get();
    static void release();
private:
    uint32_t m_PeriodMax;
};
