#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "client.h"

class UdpClient : public Client
{
    sockaddr_in addr;

public:
    UdpClient();

    bool makeConnect() override;
    bool sendMsg(std::string msg) override;
    void recieveMsg() override;

    ~UdpClient();
};

#endif // UDPCLIENT_H
