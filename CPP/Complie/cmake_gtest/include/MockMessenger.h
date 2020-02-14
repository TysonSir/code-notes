#ifndef SRC_MOCKMESSENGER_H_
#define SRC_MOCKMESSENGER_H_
 
#include "Messenger.h"
#include <string>
#include <gmock/gmock.h>
using namespace std;
 
class MockMessenger : public Messenger
{
public:
    MOCK_METHOD0(getMessage, string());
};
 
#endif /* SRC_MOCKMESSENGER_H_ */