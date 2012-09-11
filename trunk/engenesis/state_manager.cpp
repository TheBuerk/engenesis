#include "state_manager.h"
#include "game.h"

using namespace egn;


StateManager::StateManager(Game* game) : mGame(game), mLoopState(NULL), mNeedToReset(false)
{
    ILOG << "StateManager::ctor()" << std::endl;
}

StateManager::~StateManager()
{
    ILOG << "StateManager::dtor()" << std::endl;

    // Clear states
    popAllStates();
    clear();
}


void StateManager::push(GameState* state)
{
    if(!state)
    {
        FLOG << "Trying to push NULL state. Exiting game..." << std::endl;
        throw egn::exception("Trying to push NULL state.", __FILE__, __LINE__);
    }

    // Pause the actual State if exists
    if(!mActiveStates.empty())
    {
        mActiveStates.back()->pause();
    }

    ILOG << "Pushing a new GameState..." << std::endl;

    // Init state
    state->init();

    // Push it back
    mActiveStates.push_back(state);
}


void StateManager::pop()
{
    if(!mActiveStates.empty())
    {
        ILOG << "Poping a GameState..." << std::endl;

        // Get the actual state
        GameState* state = mActiveStates.back();

        // Deinit it
        state->deinit();

        // Remove from stack
        mActiveStates.pop_back();

        // Adding to dead states stack
        mDeadStates.push_back(state);

        // Resume the last State if exists
        if(!mActiveStates.empty())
        {
            mActiveStates.back()->resume();
        }
    }
}


void StateManager::popAndPush(GameState* state)
{
    pop();
    push(state);
}


void StateManager::reset()
{
    mNeedToReset = true;
}




void StateManager::startGameLoop()
{
    clear();

    if(!mActiveStates.empty())
    {
        mLoopState = mActiveStates.back();

        if(mNeedToReset)
        {
            mLoopState->reinit();
            mNeedToReset = false;
        }
    }
}


void StateManager::update(sf::Time frameTime)
{
    if(!mLoopState) return;

    mLoopState->checkEvents();
    mLoopState->update(frameTime);
}

void StateManager::draw()
{
    if(!mLoopState) return;

    mLoopState->draw();
}


void StateManager::popAllStates()
{
    while(!mActiveStates.empty())
    {
        pop();
    }
}



void StateManager::clear()
{
    while(!mDeadStates.empty())
    {
        // Get the actual state
        GameState* state = mDeadStates.back();

        delete state;
        state = NULL;

        // Remove from stack
        mDeadStates.pop_back();
    }
}






