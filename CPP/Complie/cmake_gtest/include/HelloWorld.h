#ifndef SRC_HELLOWORLD_H_
#define SRC_HELLOWORLD_H_
 
#include <string>
#include "MockMessenger.h"
using namespace std;
 
class HelloWorld
{
public:
    HelloWorld();
    virtual ~HelloWorld();
    string getMessage(Messenger* messenger) const;
};
 
#endif /* SRC_HELLOWORLD_H_ */