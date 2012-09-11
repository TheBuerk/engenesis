#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED

#include <SFML/System.hpp>
#include "main.h"
#include "config.h"
#include "system.h"
#include <vector>

namespace egn
{
    class Game;

    class EGNAPI GameState
    {
        public:
            GameState(Game* game);

            virtual ~GameState();

            virtual void init() = 0;
            virtual void reinit() = 0;
            virtual void deinit() = 0;
            virtual void checkEvents() = 0;
            virtual void update(sf::Time elapsedTime) = 0;
            virtual void draw() = 0;

            Game* game() const { return mGame; }

            void pause() { mPaused = true; }
            void resume() { mPaused = false; }
            bool paused() const { return mPaused; }


            void addSystem(System* system);
            void updateSystems(sf::Time elapsedTime);

        protected:
            void removeSystems();

            Game*   mGame;
            bool    mPaused;

            std::vector<System*>    mSystems;
    };


}

#endif // GAME_STATE_H_INCLUDED
