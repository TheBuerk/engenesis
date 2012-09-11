#ifndef NON_COPYABLE_H_INCLUDED
#define NON_COPYABLE_H_INCLUDED

#include "main.h"

namespace egn {

    /**
    * @class NonCopyable
    * @brief A non copyable class
    */

    class EGNAPI NonCopyable
    {
        protected:
            /**
            * @brief Default constructor
            */
            NonCopyable() { }

        private:
            /**
            * @brief Default copy constructor
            */
            NonCopyable(const NonCopyable& from);

            /**
            * @brief Default operator =
            */
            const NonCopyable& operator=(const NonCopyable& from);
    };

}

#endif // NON_COPYABLE_H_INCLUDED
