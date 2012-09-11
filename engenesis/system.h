#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include "main.h"
#include "config.h"
#include "entity.h"
#include <unordered_map>
#include <string>
#include <SFML/Window.hpp>

namespace egn
{
    class Game; // Forward declaration

    /**
    * @class System
    * @brief A System contains some IProperty that are reated to it, in order to handle events/update/draw them.
    */
    class EGNAPI System
    {
        public:
            /**
            * @brief Constructor
            * @param ID The System ID
            * @param game A pointer on Game
            */
            System(const std::string& ID, Game* game);

            /**
            * @brief Destructor
            */
            virtual ~System();

            // Management Methods

            /**
            * @brief Adds an Entity to the System, Entity Components that are handled by this System will be updated at each frame.
            *        Note : all needed Components will be given to the Entity automatically !
            * @param entity The Entity to add to this System
            * @return Returns the Entity ID, or 0 if an error occured
            */
            void add(Entity* entity);


            /**
            * @brief Checks if the System has the specified Entity registered
            * @param entityID The ID of the Entity you want to check for.
            * @return True if the System has the Entity, else otherwise
            */
            bool   has(const unsigned int entityID) const;


            /**
            * @brief Removes the specified Entity from this System
            * @param entityID The ID of the Entity you want to remove
            */
            void    drop(const unsigned int entityID);


            /**
            * @brief Drops all Entities from this System
            */
            void    dropAllEntities();


            // Update Methods


            /**
            * @brief Let registered Entities a chance to handle the specified Event
            * @param event The sf::Event to handle
            */
            virtual void handleEvent(sf::Event& event) = 0;


            /**
            * @brief Called once at each frame, it allow Properties to update themselves with the Frame Time (or not)
            * @param frameTime The sf::Time since the last call
            */
            virtual void update(sf::Time frameTime) = 0;


            /**
            * @brief Draw what Entities have to draw
            */
            virtual void draw() = 0;


            /**
            * @brief A chance for the System to init the Entity's Attributes before registering it
            */
            virtual void init(Entity* entity) = 0;

            /**
            * @brief A chance for the System to clean the Entity's Attributes before unregistering it
            */
            virtual void clean(Entity* entity) = 0;




            // Accessors

            /**
            * @brief Returns the System ID
            */
            const std::string   id() const { return mSystemId; }


        protected:
            /**
            * @brief Adds the properties used by this System to the Entity
            */
            virtual void addComponents(Entity* entity) = 0;

            std::unordered_map<unsigned int, Entity*>   mEntities; ///< List of all Entities managed by this System
            void eraseEntity(std::unordered_map<unsigned int, Entity*>::iterator it);

            Game*               mGame;      ///< Hold a pointer on the game/app
            const std::string   mSystemId;  ///< This System ID

    };

}

#endif // SYSTEM_H_INCLUDED
