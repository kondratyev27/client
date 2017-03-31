#include "udpclient.h"

using namespace std;

UdpClient::UdpClient()
{

}

bool UdpClient::makeConnect(){
    sockD = socket(AF_INET, SOCK_DGRAM, 0);
    bool isError = 0;
    if(sockD == -1){
        cout << "Error initializing socket! \n";
        isError = 1;
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET ;
    addr.sin_port = htons(hostPort);
    addr.sin_addr.s_addr =  inet_addr(hostIp) ;
    if(!isError){
        if( connect( sockD, (sockaddr*)&addr, sizeof(addr)) == -1 ){
            cout << "Error connecting socket! \n";
            isError = 1;
        }
    }
    return !isError;
}

bool UdpClient::sendMsg(string msg)
{
    if(sendto(sockD, msg.c_str(), msg.length(), 0 ,(sockaddr*) &addr, sizeof(addr)) == -1){
        cout << "Error sending data! \n";
        return 0;
    } else{
        cout << "Sending succesfull! \n";
    }
    return 1;
}

void UdpClient::recieveMsg(){
    char buf[maxMsgSize];
    if(recvfrom(sockD, (void*)buf, maxMsgSize, 0, (sockaddr *) NULL, NULL) < 0){
        cout << "Error recieving data! \n";
    }else{
        cout<< "Recieve msg from server: "<< buf << endl;
    }
}

UdpClient::~UdpClient()
{
    close(sockD);
}
