#ifndef STATE_MANAGER_H_INCLUDED
#define STATE_MANAGER_H_INCLUDED

#include "main.h"
#include "config.h"
#include "game_state.h"
#include <vector>

namespace egn
{
    class Game;

    /**
    * @class StateManager
    * @brief Handle states in the Game. Interface between Game and GameState classes
    */
    class EGNAPI StateManager
    {
        public:
            /**
            * Constructor
            */
            StateManager(Game* game);

            /**
            * Own the states, will delete them !
            */
            ~StateManager();


            /**
            * Returns true if there are no more GameState in the stack. If it is the case, the game will stop
            */
            bool    empty() const { return mActiveStates.empty(); }


            // States Handling

            /**
            * Push a GameState into the stack, this state will become the active one, the previous state (if exists) will be paused
            */
            void    push(GameState* state);

            /**
            * Will remove the active State from the stack and resume the last one if exists
            */
            void    pop();

            /**
            * Remove the actual state and push a new one
            */
            void    popAndPush(GameState* state);

            /**
            * Will reinit() the actual GameState. Usefull to restart a level, for example.
            */
            void    reset();

            // GameLoop Handling

            /**
            * Called by Game. Will clear the dead states
            */
            void    startGameLoop();

            /**
            * Call GameState::checkEvents() and GameState::update(sf::Time)
            */
            void    update(sf::Time  frameTime);

            /**
            * Call GameState::draw();
            */
            void    draw();

            /**
            * Deinit and pop all GameStates
            */
            void    popAllStates();

        protected:
            void    clear();

            std::vector<GameState*> mActiveStates; ///< GameStates
            std::vector<GameState*> mDeadStates; ///< GameStates

            Game*                   mGame; ///< Pointer on Game
            GameState*              mLoopState; ///< The actual Game Loop State
            bool                    mNeedToReset; ///< If the State has to be reseted

        private:
            StateManager(const StateManager&); ///< Non Copyable
            StateManager& operator=(const StateManager&); ///< Non Copyable
    };
}

#endif // STATE_MANAGER_H_INCLUDED
