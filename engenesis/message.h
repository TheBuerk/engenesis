#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

#include <boost/any.hpp>
#include "component.h"
#include <string>
#include <functional>

namespace egn
{
    typedef std::string MessageType; ///< Defines what is a MessageType (enum, string, int, ...)



    /**
    * A Message with more or less data
    */
    struct EGNAPI Message
    {
        Message(MessageType type) : Type(type), Sender(NULL), Value() { }
        Message(MessageType type, Component* c) : Type(type), Sender(c), Value() { }
        Message(MessageType type, Component* c, boost::any d) : Type(type), Sender(c), Value(d) { }


        const MessageType       Type;
        Component*              Sender;
        boost::any              Value;
    };
}





#endif // MESSAGE_H_INCLUDED
