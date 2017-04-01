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
{
    if(msg.empty()){
        return 0;
    }
    int byteCount = 0;
    int msgSize = msg.size();
    string sizeOfSendData = to_string( msgSize) ;
    if( ( send(sockD, sizeOfSendData.c_str(), sizeOfSendData.length(), 0))== -1){
        cout << "Error sending data! \n";
        return 0;
    }

    char flag[2];
    if(recv(sockD, flag, sizeof(flag), 0)== -1){ // just to synchronize
        cout << "Error recieving flag! \n";
        return 0;
    }

    while (byteCount != msgSize){
        int tmpByteCount = 0;
        if( (tmpByteCount = send(sockD, msg.c_str(), msg.length(), 0))== -1){
            cout << "Error sending data! \n";
            return 0;
        }else{
            cout << "Send full " <<msg.c_str()<< "\n";
            byteCount += tmpByteCount;
            msg = msg.substr(tmpByteCount);
        }
    }
    cout << "Sending of " << byteCount << "bytes succesfull! \n";

    return 1;
}

void TcpClient::recieveMsg(){
    string recMsg;
    char buf[maxMsgSize];
    int byteCount = 0;

    if(( recv(sockD, buf, maxMsgSize, 0))== -1){ //try to recieve msg size
        cout << "Error recieving data! \n";
        return;
    }else{
        char succesFlag[]  = "1";
        if( send(sockD, succesFlag, sizeof(succesFlag) , 0) == -1){
            cout << "Error sending flag! \n";
            return;
        }

        int recievingSize =  atoi(buf);
        while (byteCount != recievingSize ){ // whait until all bytes would'n be recieved
            int tmpByteCount = 0;
            memset(buf, 0, maxMsgSize);
            if(( tmpByteCount = recv(sockD, buf, maxMsgSize, 0))== -1){
                cout << "Error recieving data! \n";
                return;
            }else{
                byteCount += tmpByteCount;
                recMsg += string(buf);
            }
        }
        cout<< "Recieve msg from server: " << recMsg << endl;
    }
}

TcpClient::~TcpClient()
{
    close(sockD);
}
