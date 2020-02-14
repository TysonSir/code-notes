#include "HelloWorld.h"
#include "Messenger.h"
 
HelloWorld::HelloWorld()
{
}
 
HelloWorld::~HelloWorld()
{
}
 
string HelloWorld::getMessage(Messenger* messenger) const
{
    return messenger->getMessage();
}