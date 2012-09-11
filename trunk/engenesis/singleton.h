#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

#include "main.h"

namespace egn {

/**
    * @class Singleton
    * @brief Defines the Pattern Singleton interface.
    * @details A Singleton is a class that instanciate only one object. Each time you ask for an object of type Singleton, the same instance that has been created and returned before will be returned to you.\n
    * @code
class MyClass : public my::Singleton< MyClass >
{
    // MyClass methods and attributes
};

// Later in the code :
MyClass* instance1 = MyClass::Instance();
MyClass* instance2 = MyClass::Instance();

// instance1 == instance2
    @endcode
*/
template<class T>
class EGNAPI Singleton
{
    public:
        /**
        * @brief Ask for a pointer of type T. The same instance will be return at each call
        */
        static T* Instance()
        {
            if(!instance)   instance = new T();
            return instance;
        }

        virtual ~Singleton() {  }


    private:
        static T* instance;
};
template<class T>
T* Singleton<T>::instance = 0;

}

#endif // SINGLETON_H_INCLUDED
