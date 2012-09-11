#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "main.h"
#include "config.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state_manager.h"
#include "content_manager.h"
#include "entity_manager.h"

namespace egn
{
    class GameState;

    /**
    * @class Game
    * @brief Englobe la sf::RenderWindow de SFML, gère les GameStates et la boucle principale du jeu ainsi que les ressources
    */
    class EGNAPI Game
    {
        public:
            // Constructeurs
            /**
            * @brief Game Constructor
            * @param title The window title
            * @param width The window width
            * @param height The window height
            * @param style The window sf::Style
            */
            Game(const std::string& title, int width = 800, int height = 600, unsigned long style = sf::Style::Default);

            /**
            * Deletes the EntityManager and the StateManager
            */
            virtual ~Game();


            /**
            * Returns a pointer on the sf::RenderWindow
            */
            sf::RenderWindow*   app() { return &mApp; }




            EntityManager*                 mEntityManager; ///< Fast access to the Entity Manager
            StateManager*                  mStateManager; ///< Fast access to the State Manager

            ContentManager<sf::Texture>    mTextures;   ///< Fast access to Texture Manager
            ContentManager<sf::Sound>      mSounds;     ///< Fast access to Sound Manager


        public:
            /**
            * @brief Run the game. Will call initialize(), load(), unload() when exiting and State game loop methods
            */
            void gameloop();


        protected:

            // Main Methods
            /**
            * @brief Used to initialize game logic, variables, etc...
            */
            virtual void initialize();

            /**
            * @brief Used to load textures, sounds, musics, fx, etc...
            */
            virtual void load();

            /**
            * @brief Used to unload textures, sounds, musics, fx, etc...
            */
            virtual void unload();



            sf::RenderWindow               mApp;


    };
}

#endif // GAME_H_INCLUDED
