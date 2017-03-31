#include "tcpclient.h"

using namespace std;

TcpClient::TcpClient()
{

}

bool TcpClient:: makeConnect(){
    sockD = socket(AF_INET, SOCK_STREAM, 0);
    bool isError = 0;
    if(sockD == -1){
        cout << "Error initializing socket! \n";
        isError = 1;
    }
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET ;
    addr.sin_port = htons(hostPort);
    addr.sin_addr.s_addr =  inet_addr(hostIp) ;
    if(!isError){
        if( connect( sockD, (struct sockaddr*)&addr, sizeof(addr)) == -1 ){
            cout << "Error connecting socket! \n";
            isError = 1;
        }
    }
    return !isError;
}

bool TcpClient::sendMsg(string msg)
{int bytecount;
    if( (bytecount = send(sockD, msg.c_str(), msg.length(), 0))== -1){
        cout << "Error sending data! \n";
        return 0;
    }else{
        cout << "Sending succesfull! \n";
    }
    printf("Sent bytes %d\n", bytecount);
    return 1;
}

void TcpClient::recieveMsg(){
    string recMsg;
    char buf[maxMsgSize];
    int bytecount;
    if((bytecount = recv(sockD, buf, maxMsgSize, 0))== -1){
        cout << "Error recieving data! \n";
    }else{
        cout<< "Recieve msg from server: " << buf << endl;
    }
}

TcpClient::~TcpClient()
{
    close(sockD);
}
