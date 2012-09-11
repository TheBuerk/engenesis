#include "game_state.h"


using namespace egn;


GameState::GameState(Game* game) : mGame(game), mPaused(false)
{
    if(!game)
    {
        FLOG << "Trying to construct GameState with NULL Game value. Exiting game..." << std::endl;
        throw egn::exception("Trying to construct GameState with NULL Game value.", __FILE__, __LINE__);
    }
}


GameState::~GameState()
{
    removeSystems();
}

void GameState::addSystem(System* system)
{
    if(!system)
    {
        FLOG << "Trying to push a NULL System. Exiting game..." << std::endl;
        throw egn::exception("Trying to push a NULL System.", __FILE__, __LINE__);
    }

    mSystems.push_back(system);

    ILOG << "System " << system->id() << " added to the GameState !" << std::endl;
}

void GameState::updateSystems(sf::Time elapsedTime)
{
    for(std::vector<System*>::iterator it = mSystems.begin(); it != mSystems.end(); ++it)
    {
        (*it)->update(elapsedTime);
    }
}

void GameState::removeSystems()
{
    for(std::vector<System*>::iterator it = mSystems.begin(); it != mSystems.end(); ++it)
    {
        delete (*it);
    }
}
