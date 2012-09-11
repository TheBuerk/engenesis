#include "stop_watch.h"


namespace egn {

    StopWatch::StopWatch(bool initrunning) : mBuffer(sf::Time::Zero), mRunning(initrunning)
    {
        //ctor
    }

    StopWatch::~StopWatch()
    {
        //dtor
    }

    sf::Time StopWatch::getElapsedTime() const
    {
        if(mRunning)
            return (mBuffer + mClock.getElapsedTime());

        return mBuffer;
    }

    bool StopWatch::isRunning() const
    {
        return mRunning;
    }

    void StopWatch::start()
    {
        if(!mRunning)
        {
            mRunning = true;
            mClock.restart();
        }
    }

    void StopWatch::stop()
    {
        if(mRunning)
        {
            mBuffer += mClock.getElapsedTime();
            mRunning = false;
        }
    }

    void StopWatch::restart(bool stillrunning)
    {
        mBuffer = sf::Time::Zero;
        mRunning = stillrunning;
        mClock.restart();
    }


} // namespace
