#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int sock;      // client socket discriptor
    int a,b,c,i;
    unsigned int len;
    char ch[3]="no";
    char ch1[3];
    struct sockaddr_in client;
    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
    {  // client socket is created..
        perror("socket: ");
        exit(-1);
    }

    client.sin_family=AF_INET;
    client.sin_port=htons(10005);        // initializing  socket  parameters 
    client.sin_addr.s_addr=INADDR_ANY;
    //inet_addr("127.0.0.1");
    bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 
    len=sizeof(struct sockaddr_in);
    if((connect(sock,(struct sockaddr *)&client,len))==-1)
    {  //conneting to client
        perror("connect: ");
        exit(-1);
    }
    ofstream outfile;
    outfile.open("dest.txt");
    while(1)
    {
        int buffer;
        recv(sock,&buffer,sizeof(buffer),0);
        while(buffer!=-1&&buffer!=-2)
        {
            outfile<<buffer<<" ";
            recv(sock,&buffer,sizeof(buffer),0);
        }
        if(buffer==-2)
            break;
        outfile<<endl;
    }
    z:
    {
    }
    outfile.close();
}
