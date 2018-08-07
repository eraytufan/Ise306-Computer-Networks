
#include <iostream>    
#include <stdio.h> 
#include <string.h>    
#include <string>  
#include <sys/socket.h>    
#include <arpa/inet.h> 
#include <netdb.h> 
#include "sha1.h"
 
using namespace std;
 

class tcp_client
{
private:
    int sock;
    string address;
    int port;
    struct sockaddr_in server;
     
public:
    tcp_client();
    void conn(string, int);
    void send_data(string data);
    string receive(int);
};
 
tcp_client::tcp_client()
{
    sock = -1;
    port = 80;
    address = "";
}
 
/**
    Connect to the host given by parameter
*/
void tcp_client::conn(string address , int port)
{
    
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    
    server.sin_addr.s_addr = inet_addr( address.c_str() );
    
     
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
     
    connect(sock , (struct sockaddr *)&server , sizeof(server));
     
    cout<<"Connected\n";
    return;
}
 
/**
    Send data
*/
void tcp_client::send_data(string data)
{
    
    send(sock , data.c_str() , strlen( data.c_str() ) , 0);
    cout<<"Data send\n";
     
    return;
}
 
/**
    Receive data
*/
string tcp_client::receive(int size=512)
{
    char buffer[size];
    string reply;
     
    recv(sock , buffer , sizeof(buffer) , 0);
     
    reply = buffer;
    return reply;
}
 
int main(int argc , char *argv[])
{
    tcp_client c;
    string host;
     
    host = "160.75.26.117";
     
    //connect to host
    c.conn(host , 2016);
     
    //send data
    c.send_data("Start_Connection");
     

    string hex1 =  "9ddb6053fad1087f958553c4a13d5b41";
    string hex2 = c.receive(1024);
    hex2 = hex2.substr(0,32);
    cout << "hex2: " << hex2 << endl;
    hex2.append(hex1);

    unsigned char hash[20];
    char stringhash[40];
    const char *cstr = hex2.c_str();
    cout << "cstr:" << cstr << "\n";
    //cout << "cstr size: " << strlen(cstr) << "\n";
    sha1::calc(cstr, strlen(cstr), hash);
    sha1::toHexString(hash, stringhash);
    cout << "stringhash: "<< stringhash << "\n";

    string answer(stringhash);
    answer.append("#150120204");
    c.send_data(answer);

    cout<<"----------------------------\n\n";
    cout<<c.receive(1024);
    cout<<"\n\n----------------------------\n\n";

    string ans;
    cin >> ans;
    c.send_data(ans);

    for(int i=0; i<6; i++){
        cout<<c.receive(1024);
        cin >> ans;
        c.send_data(ans);
        cout<<c.receive(1024);
    }
     
    return 0;
}
