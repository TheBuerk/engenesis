#include "entity.h"
#include "system.h"
#include "entity_manager.h"

using namespace egn;

unsigned int Entity::_nextId = 0;

Entity::Entity(EntityManager* mng) : mManager(mng), mId(++_nextId)
{

}


Entity::~Entity()
{
    dropAllSystems();
    dropAllComponents();
}

const unsigned int Entity::id() const { return mId; }







void Entity::addComponent(Component* comp)
{
    if(!comp)
    {
        FLOG << "Trying to push NULL Component. Exiting game..." << std::endl;
        throw( egn::exception("Trying to push NULL Component", __FILE__, __LINE__) );
    }

    if(mComponents.find(comp->id()) == mComponents.end()) // If not already registered
    {
        comp->setOwner(this);
        comp->init();

        mComponents[comp->id()] = comp;
    }
    else
    {
        FLOG << "Trying to push a Component already registerd. Exiting game..." << std::endl;
        throw( egn::exception("Trying to push a Component already registerd", __FILE__, __LINE__) );
    }
}


bool Entity::hasComponent(const std::string& id) const
{
    return (mComponents.find(id) != mComponents.end());
}


void Entity::dropComponent(const std::string& id)
{
    std::unordered_map<std::string, Component*>::iterator it = mComponents.find(id);
    if(it != mComponents.end())
    {
        it->second->deinit();
        delete it->second;
        mComponents.erase(it);
    }
}

void Entity::dropComponentWithoutDeletion(const std::string& id)
{
    std::unordered_map<std::string, Component*>::iterator it = mComponents.find(id);
    if(it != mComponents.end())
    {
        it->second->deinit();
        mComponents.erase(it);
    }
}

void Entity::dropAllComponents()
{
    std::unordered_map<std::string, Component*>::iterator it = mComponents.begin();
    while(it != mComponents.end())
    {
        it->second->deinit();
        delete it->second;
        mComponents.erase(it++);
    }
    mComponents.clear();
}










void Entity::addSystem(System* system)
{
    if(mSystems.find(system->id()) == mSystems.end()) // If not already registered
    {
        mSystems[system->id()] = system;
    }
}

bool Entity::hasSystem(const std::string& ID) const
{
    return ( mSystems.find(ID) != mSystems.end() );
}


void Entity::dropSystem(const std::string& ID)
{
    std::unordered_map<std::string, System*>::iterator it = mSystems.find(ID);

    if(it != mSystems.end())
    {
        eraseSystem(it);
    }
}


void Entity::dropAllSystems()
{
    std::unordered_map<std::string, System*>::iterator it = mSystems.begin();
    while(it != mSystems.end())
    {
        eraseSystem(it++);
    }
    mSystems.clear();
}



void Entity::eraseSystem(std::unordered_map<std::string, System*>::iterator it)
{
    // Stores the System
    System* system = it->second;

    // Erase the system from the map
    mSystems.erase(it);

    // If the System still has the Entity, it has to drop it
    if(system->has(id()))
    {
        system->drop(id());
    }
}







// Messages


void Entity::registerMessage(const MessageType& type, Component* reciever)
{
    mManager->registerMessage(type, reciever);
}


void Entity::unregisterMessage(const MessageType& type, Component* reciever)
{
    mManager->unregisterMessage(type, reciever);
}


void Entity::sendMessage(const Message& message)
{
    mManager->broadcast(message);
}












