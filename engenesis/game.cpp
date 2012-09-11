#include "game.h"
#include "game_state.h"
#include "exception.h"



namespace egn
{
    /****************************************************
                            Game
    ****************************************************/

    Game::Game(const std::string& title, int width, int height, unsigned long style)
    {
        ILOG << "Game::ctor()" << std::endl;

        // Render Window
        mApp.create(sf::VideoMode(width, height), title, style);

        // Some configurations and declarations
        mEntityManager = new EntityManager();
        mStateManager = new StateManager(this);
        mApp.setFramerateLimit(60);
    }

    Game::~Game()
    {
        ILOG << "Game::dtor()" << std::endl;

        delete mEntityManager;
        delete mStateManager;
    }




    void Game::gameloop()
    {
        ILOG << "Game is starting ! Have Fun !" << std::endl;

        // Initialisation
        initialize();
        load();

        // A clock to know the frame time
        sf::Clock clock;
        while(mApp.isOpen())
        {
            // Get Frame Time
            sf::Time frameTime = clock.restart();

            // Check if there still is at least a state
            if(mStateManager->empty())
            {
                mApp.close();
            }
            else
            {
                // Start State GameLoop
                mStateManager->startGameLoop();

                // Update State
                mStateManager->update(frameTime);

                // Draw State
				mApp.clear();
                mStateManager->draw();
				mApp.display();
            }
        }

        //De-intialisation
        unload();

        ILOG << "Game is stopping ! Goodbye !" << std::endl;
    }


    void Game::initialize()
    {

    }

    void Game::load()
    {

    }

    void Game::unload()
    {

    }






}
