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
    unsigned int len;
    char ch[3]="no";
    struct sockaddr_in client;
    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
    {  // client socket is created..
        perror("socket: ");
        exit(-1);
    }

    client.sin_family=AF_INET;
    client.sin_port=htons(10001);        // initializing  socket  parameters 
    client.sin_addr.s_addr=INADDR_ANY;
    //inet_addr("127.0.0.1");
    bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 
    len=sizeof(struct sockaddr_in);
    if((connect(sock,(struct sockaddr *)&client,len))==-1)
    {  //conneting to client
        perror("connect: ");
        exit(-1);
    }
    char s[512];
    char t[512];
    cout<<"Enter the password"<<endl;
    cin>>s;
    send(sock,&s,sizeof(s),0);
    send(sock,&"Hi",sizeof("Hi"),0);
    recv(sock,&t,sizeof(t),0);
    cout<<t<<endl;
    if(strcmp(t,"Hello")==0)
    {
        while(1)
        {
            char word[512];
            int num;char c;
            //cout<<"Enter the number and string"<<endl;
            cin>>num>>word;
            send(sock,&word,sizeof(word),0);
            send(sock,&num,sizeof(num),0);       // sending data back to client...
            recv(sock,&c,sizeof(c),0);
            printf("Received character is %c\n",c);                   // receiving data from client
            printf("\nTo exit...press 'no'\n");
            char ch1[3];
            scanf("%s",ch1);
            if(strcmp(ch,ch1)==0)
            {
                close(sock);
                exit(0);
            }
        }
    }
}
