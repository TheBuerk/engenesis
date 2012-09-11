#include "component.h"
#include "entity.h"
#include "message.h"

using namespace egn;


Component::Component(const std::string& ID) : mId(ID), mOwner(NULL)
{

}

Component::~Component()
{

}


void Component::setOwner(Entity* owner)
{
    if(!mOwner)
    {
        mOwner = owner;
    }
    else
    {
        FLOG << "Trying to set Owner that is already set in Component " << id() << ". Exiting game..." << std::endl;
        throw( egn::exception("Trying to set Owner that is already set", __FILE__, __LINE__) );
    }
}

void Component::changeOwner(Entity* newowner)
{
    // Verification before doing some shit
    if(newowner->hasComponent(id()))
    {
        WLOG << "Component " << id() << " tried to change owner but this owner already had a similar component !" << std::endl;
        return;
    }

    // Drop ouserlf from owner. It will deinit this component
    mOwner->dropComponentWithoutDeletion(id());

    mOwner = NULL;

    // Adding new owner. It will set mOwner and init this component
    newowner->addComponent(this);
}
