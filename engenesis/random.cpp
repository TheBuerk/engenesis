#include "random.h"
#include <ctime>
#include <cstdlib>
#include <cassert>

namespace egn {


    namespace
    {
        int seed(unsigned int s)
        {
            std::srand(s);
            return s;
        }
        // Seeding the std::rand(), can be re-seed with another value later
        int seed_value = seed(static_cast<unsigned int>(std::time(NULL)));
    }


    void seed(unsigned int s)
    {
        std::srand(s);
    }

    int random(int min, int max)
    {
        assert(min <= max);
        return std::rand() % (max - min + 1) + min;
    }

    float random(float min, float max)
    {
        assert(min <= max);
        return static_cast<float>(std::rand()) / RAND_MAX * (max - min) + min;
    }

}
