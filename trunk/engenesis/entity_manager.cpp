#include "entity_manager.h"
#include "message.h"


using namespace egn;


EntityManager::EntityManager()
{
    ILOG << "EntityManager::ctor()" << std::endl;
}

EntityManager::~EntityManager()
{
    ILOG << "EntityManager::dtor()" << std::endl;
    reset();
}




Entity* EntityManager::create()
{
    Entity* e = new Entity(this);
    mEntities[e->id()] = e;

    return e;
}

Entity* EntityManager::get(const unsigned int ID)
{
    std::unordered_map<unsigned int, Entity*>::iterator it = mEntities.find(ID);
    if(it != mEntities.end())
    {
        return it->second;
    }
    return NULL;
}

void EntityManager::remove(const unsigned int ID)
{
    std::unordered_map<unsigned int, Entity*>::iterator it = mEntities.find(ID);
    if(it != mEntities.end())
    {
        remove(it);
    }
}

void EntityManager::reset()
{
    ILOG << "EntityManager::reset()" << std::endl;

    std::unordered_map<unsigned int, Entity*>::iterator it = mEntities.begin();

    while(it != mEntities.end())
    {
        remove(it++);
    }

    mEntities.clear();
    mDispatcher.clear();
}

void EntityManager::remove(std::unordered_map<unsigned int, Entity*>::iterator it)
{
    ILOG << "EntityManager deleting entity " << it->second->id() << std::endl;
    delete it->second;
    mEntities.erase(it);
}



// Messages


void EntityManager::registerMessage(const MessageType& type, Component* reciever)
{
    if(reciever)
        mDispatcher.insert( std::pair<MessageType,Component*>(type,reciever) );
    else
    {
        FLOG << "Trying to push a Component with NULL Reciever. Exiting game..." << std::endl;
        throw(egn::exception("Trying to push a Component with NULL Reciever.", __FILE__, __LINE__));
    }
}

void EntityManager::unregisterMessage(const MessageType& type, Component* reciever)
{
    std::pair< std::unordered_multimap<MessageType, Component*>::iterator , std::unordered_multimap<MessageType, Component*>::iterator> range = mDispatcher.equal_range(type);

    for(std::unordered_multimap<MessageType, Component*>::iterator it = range.first; it != range.second; ++it)
    {
        if(it->second == reciever)
        {
            mDispatcher.erase(it);
            break;
        }
    }

}

void EntityManager::broadcast(const Message& message)
{
    std::pair< std::unordered_multimap<MessageType, Component*>::iterator , std::unordered_multimap<MessageType, Component*>::iterator> range = mDispatcher.equal_range(message.Type);

    for(std::unordered_multimap<MessageType, Component*>::iterator it = range.first; it != range.second; ++it)
    {
        it->second->message(message);
    }
}

