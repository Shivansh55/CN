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
    client.sin_port=htons(10000);        // initializing  socket  parameters 
    client.sin_addr.s_addr=INADDR_ANY;
    //inet_addr("127.0.0.1");
    bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 
    len=sizeof(struct sockaddr_in);
    if((connect(sock,(struct sockaddr *)&client,len))==-1)
    {  //conneting to client
        perror("connect: ");
        exit(-1);
    }
    while(1)
    {
        char word[512];
        char mean[512];
        cout<<"Enter the word"<<endl;
        cin>>word;
        send(sock,&word,sizeof(word),0);
        recv(sock,&mean,sizeof(mean),0);
        cout<<mean<<endl;
        if(strcmp(mean,"no")==0)
        {
            char msg[512];
            cout<<"Enter the meaning of the word"<<endl;
            cin>>msg;
            send(sock,&msg,sizeof(msg),0);
        }
        printf("\nTo exit...press 'no'\n");
        scanf("%s",ch1);
        if((i=strcmp(ch,ch1))==0)
        {
            close(sock);
            exit(0);
        }
    }
}
