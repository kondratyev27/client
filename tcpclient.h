#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "client.h"

class TcpClient: public Client
{
public:
    TcpClient();

    bool makeConnect() override;

    bool sendMsg(std::string msg) override;
    void recieveMsg() override;

    ~TcpClient();
};

#endif // TCPCLIENT_H
