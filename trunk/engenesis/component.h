#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include "main.h"
#include "config.h"
#include <string>

namespace egn
{
    class Entity;
    class Message;

    /**
    * @class Component
    * @brief A component is a part of an Entity, it can be some datas or functionnality
    */
    class EGNAPI Component
    {
        public:
            /**
            * Constructor
            */
            Component(const std::string& ID);

            /**
            * Destructor
            */
            virtual ~Component();

            /**
            * Returns the Component ID name
            */
            const std::string id() const { return mId; }

            /**
            * Returns the Component Entity Owner
            */
            Entity*           owner() const { return mOwner; }

            /**
            * Sets the Entity that own the Component
            */
            void              setOwner(Entity* owner);

            /**
            * Change its Entity Owner, can be usefull to pass a Component from an Entity to another
            */
            void              changeOwner(Entity* owner);

            /**
            * Initialise the Component, will use mOwner to register some events
            */
            virtual void init() = 0;

            /**
            * De-Initialise the Component, will use mOwner to unregister some events
            */
            virtual void deinit() = 0;

            /**
            * When a message arrive
            */
            virtual void message(const Message& message) = 0;



        protected:
            const std::string   mId;
            Entity*             mOwner;

        private:
            Component(const Component&); ///< Non copyable
            Component& operator=(const Component&); ///< Non copyable
    };
}

#endif // COMPONENT_H_INCLUDED
