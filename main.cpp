//#include </home/kondratiev/protei/client/tcpclient.h>
//#include </home/kondratiev/protei/client/udpclient.h>

#include <udpclient.h>
#include <tcpclient.h>


using namespace std;

int main(int argv, char** argc){
    Client *client = nullptr;
    string symb;
    while(symb != "1" && symb != "2"){
        cout << "Choose client protocol. For TCP enter \"1\", for UDP enter \"2\" : ";
        (cin >> symb).get();
    }

    if(symb == "1"){
        client = new TcpClient;
    }else if(symb == "2"){
        client = new UdpClient;
    }

    if(client->makeConnect()){
        cout << "Enter your message: \n";
        string msg;
        while(msg.size()==0 || msg.size() > client->getMaxMsgSize() ){
            getline(cin, msg);
            if(msg.size()==0 || msg.size() > client->getMaxMsgSize()){
                msg.clear();
                cout << "Error! It should be not empty and less then 64kb! Try again: \n";
            }
        }

        if(client->sendMsg(msg)){
            client->recieveMsg();
        }
    }

    if(client){
        delete client;
    }
    return 0;
}
