#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "main.h"
#include <SFML/System.hpp>

namespace egn {

/**
* @class StopWatch
* @brief Create a stoppable watch, used for timers or to handle time, animations, etc...
* @code
egn::StopWatch clock; // Create a stoppable clock
clock.start(); // Start the clock
while(true)
{
    // Do something...

    // This code is useless and ugly, but it's a demonstration :
    if(!clock.isRunning())
        clock.reset(true);   // Reset the clock and restart it

    if(clock.getElapsedTime() > 1.f)    // If elapsed time is bigger than 1 sec
        clock.stop();
}
* @endcode
*/
class EGNAPI StopWatch
{
    public:
        /**
        * @brief StopWatch constructor
        */
        StopWatch(bool initrunning = false);

        /**
        * @brief Virtual default destructor
        */
        virtual ~StopWatch();

        /**
        * @brief Return the elapsed time since the start or last reset
        * @return Elapsed time
        */
        sf::Time getElapsedTime() const;

        /**
        * @brief Is the StopWatch running ?
        * @return true if it's running
        */
        bool isRunning() const;

        /**
        * @brief Start the StopWatch
        */
        void start();

        /**
        * @brief Stop the StopWatch
        */
        void stop();

        /**
        * @brief Reset the StopWatch
        * @param stillrunning If true, the StopWatch will keep running, by default it stops !
        */
        void restart(bool stillrunning = false);

    private:
        sf::Clock   mClock;
        sf::Time    mBuffer;
        bool        mRunning;
};
}

#endif // STOPWATCH_H
