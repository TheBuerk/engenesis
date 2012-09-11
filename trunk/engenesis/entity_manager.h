#ifndef ENTITY_MANAGER_H_INCLUDED
#define ENTITY_MANAGER_H_INCLUDED

#include "main.h"
#include "config.h"
#include "entity.h"
#include "message.h"
#include <unordered_map>
#include <functional>


namespace egn
{
    /**
    * Stores all entities of the game and own them (delete,...)
    */
    class EGNAPI EntityManager
    {
        public:
            EntityManager();
            ~EntityManager();

            /**
            * Creates and returns a new Entity
            */
            Entity*     create();

            /**
            * Returns the asked Entity or NULL if not found
            */
            Entity*     get(const unsigned int ID);

            /**
            * Remove the specified entity (Will delete the Entity and all its Components and remove it from Systems !)
            */
            void        remove(const unsigned int ID);

            /**
            * Remove and delete all entities and components
            */
            void        reset();



            // Messages

            /**
            * Register a function/method to be called when a Message of type type is sent
            */
            void        registerMessage(const MessageType& type, Component*  reciever);

            /**
            * Unregister a type<>reciever
            */
            void        unregisterMessage(const MessageType& type, Component*  reciever);

            /**
            * Send the message to every Component tha registered for it
            */
            void        broadcast(const Message& message);





        private:
            EntityManager(const EntityManager&); ///< No copy
            EntityManager& operator=(const EntityManager&); ///< No copy

            void remove(std::unordered_map<unsigned int, Entity*>::iterator it);

            std::unordered_map<unsigned int, Entity*>   mEntities;
            std::unordered_multimap<MessageType, Component*>   mDispatcher;
    };

}

#endif // ENTITY_MANAGER_H_INCLUDED
