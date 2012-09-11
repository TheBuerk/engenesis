#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "main.h"
#include "config.h"
#include "component.h"
#include "message.h"
#include <unordered_map>

namespace egn
{

    class System;
    class EntityManager;

    /**
    * @class Entity
    * @brief An Entity is anything that have a behavior or data in the Game. Entities are handled by an EntityManager.
    *        Entities store their Properties in a PropertyManager
    */
    class EGNAPI Entity
    {
        public:
            /**
            * @brief Default constuctor
            */
            Entity(EntityManager* mng);

            /**
            * @brief Destructor
            */
            virtual ~Entity();


            /**
            * @brief Returns the unique ID of the Entity (an integer32)
            */
            const unsigned int id() const;

            // Components

            /**
            * Adds the specified Component to the Entity, set its owner and and init() it. Entity will own (so delete) the Component
            * unlest it changes its owner
            */
            void addComponent(Component* comp);

            /**
            * Checks if th Entity has the specified component. If yes, return true.
            */
            bool hasComponent(const std::string& compId) const;

            /**
            * Returns the asked Component if found, else return NULL
            */
            template <class T>
            Component* getComponent(const std::string& compId)
            {
                std::unordered_map<std::string, Component*>::iterator it = mComponents.find(compId);
                if(it != mComponents.end())
                {
                    Component* c = dynamic_cast<T>(it->second);
                    if(!c)
                    {
                        FLOG << "Error while casting component " << compId << " in " << typeid(T).name() << " ! Exiting game..." << std::endl;
                        throw( egn::exception("Error while casting component.", __FILE__, __LINE__) );
                    }

                    return c;
                }

                WLOG << "Component " << compId << " asked but not found in entity !" << std::endl;
                return NULL;
            }

            /**
            * Drops the specified Component and delete it
            */
            void dropComponent(const std::string& compId);

            /**
            * Drops the specified Component without deleting it
            */
            void dropComponentWithoutDeletion(const std::string& compId);


            // Systems

            /**
            * @brief Adds a System to the Entity
            */
            void addSystem(System* system);

            /**
            * @brief Checks if Entity has the specified System
            * @param systemId The System ID to check for
            * @return True if te Entity belongs to the System, false otherwise
            */
            bool hasSystem(const std::string& systemId) const;

            /**
            * @brief Drops the specified System
            */
            void dropSystem(const std::string& systemId);


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
            void        sendMessage(const Message& message);




            EntityManager*  entityManager() const { return mManager; }



        protected:
            /**
            * @brief Drop all the Systems
            */
            void dropAllSystems();

            /**
            * @brief Drop all the Components
            */
            void dropAllComponents();

            std::unordered_map<std::string, System*>   mSystems; ///< Systems this Entity belongs to
            std::unordered_map<std::string, Component*>   mComponents; ///< Systems this Entity belongs to
            EntityManager*                              mManager; ///< Entity Manager

        private:
            Entity(const Entity&); ///< Non copyable
            Entity& operator=(const Entity&); ///< Non copyable

            const unsigned int   mId; ///< Stores the Entity ID (unique integer)
            static unsigned int  _nextId;   ///< Stores the next Entity ID

            void eraseSystem(std::unordered_map<std::string, System*>::iterator it);
    };

}


#endif // ENTITY_H_INCLUDED
