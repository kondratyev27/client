#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>

class Client
{
protected:
    const int hostPort = 4321;
    const char* hostIp = "127.0.0.1";
    int sockD;
    const uint maxMsgSize = 1024*64;
public:
    virtual bool sendMsg(std::string msg) = 0;
    virtual void recieveMsg() = 0;
    virtual bool makeConnect() = 0;
    uint getMaxMsgSize() const;
    Client();
    virtual ~Client(){}
};

#endif // CLIENT_H
