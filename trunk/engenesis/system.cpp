#include "system.h"
#include "entity.h"

#include <cassert>


using namespace egn;


System::System(const std::string& ID, Game* game)
:   mGame(game),
    mSystemId(ID)
{
    ILOG << "System " << ID << " created !" << std::endl;
}

System::~System()
{
    dropAllEntities();
}



void System::add(Entity* entity)
{
    if(!entity)
    {
        FLOG << "NULL Entity given to System " << id() << " ! Exiting the game..." << std::endl;
        exit(StatusError);
    }

    if(mEntities.find(entity->id()) ==  mEntities.end()) // If the Entity isn't already registered
    {
        // We add reuired properties to the Entity
        addComponents(entity);

        // Initialisation of the properties (if needed)
        init(entity);

        // Add this System to the Entity
        entity->addSystem(this);

        // Add the Entity to this System
        mEntities[entity->id()] = entity;
    }
    else
    {
        WLOG << "Entity " << entity->id() << " already registered in System " << id() << " !" << std::endl;
    }
}



bool System::has(const unsigned int ID) const
{
    return ( mEntities.find(ID) != mEntities.end() );
}



void System::drop(const unsigned int ID)
{
    std::unordered_map<unsigned int, Entity*>::iterator it = mEntities.find(ID);

    if(it != mEntities.end()) // If entity is registered
    {
        eraseEntity(it);
    }
}


void System::dropAllEntities()
{
    std::unordered_map<unsigned int, Entity*>::iterator it = mEntities.begin();

    while(it != mEntities.end())
    {
        eraseEntity(it++);
    }
    mEntities.clear();
}


void System::eraseEntity(std::unordered_map<unsigned int, Entity*>::iterator it)
{
    // Stores the entity
    Entity* entity = it->second;

    // Remove it from map
    mEntities.erase(it);

    // Cleanup the entity attributes
    clean(entity);

    // If the Entity still has this System registered, we remove it
    if(entity->hasSystem(id()))
    {
        entity->dropSystem(id());
    }
}



