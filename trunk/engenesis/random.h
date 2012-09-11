#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include "main.h"

namespace egn {

    /**
    *   @brief Set a seed value for std::rand, automatically called once when program starts
    *   @param s A seed value
    */
    void EGNAPI seed(unsigned int s);

    /**
    *   @brief A function to get a random (int) number between two values. Beware to give the minimal value FISRT !
    *   @param min The minimal value that can be returned
    *   @param max The maximal value that can be returned
    *   @return An random int value
    */
    int EGNAPI random(int min, int max);

    /**
    *   @brief A function to get a random (floating) number between two values. Beware to give the minimal value FISRT !
    *   @param min The minimal value that can be returned
    *   @param max The maximal value that can be returned
    *   @return An random floating value
    */
    float EGNAPI random(float min, float max);


}

#endif // RANDOM_H_INCLUDED
