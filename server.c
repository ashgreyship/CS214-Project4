#include <stdio.h>
#include <string.h>   
#include <stdlib.h>    
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>   
#include <pthread.h> 
 
void *serverfunc(void *socketfd)
{
    //Get the socket descriptor
    int sock = *(int*)socketfd;
    int read_size;
    char content[10000];
    //Receive a message from client
    while( (read_size = recv(sock , content ,10000, 0)) > 0 )
    {
        content[read_size] = '<';
        printf("%s\n",content );
        memset(content, 0, 2000);
    }
     
    if(read_size == 0||read_size==-1)
    {
        perror("error receive data or client disconnected");
        fflush(stdout);
    }
   
         
    return 0;
} 
 
int main(int argc , char *argv[])
{    if(argc!=3){
        printf("incorrect input" );
        return 0;
    }
    int portnum=atoi(argv[2]);
    printf("%d\n",portnum );
    int socketfd ;
    int clientfd;
    int c;
    struct sockaddr_in server , client;
     
    //create socket
    if((socketfd = socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        printf("error making socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( portnum );
     
    //Bind
    if( bind(socketfd,(struct sockaddr *)&server , sizeof(server)) == -1)
    {
        perror("error binding socket");
        return 0;
    }
   
     /*listen on the socket*/
    if(listen(socketfd,128)==-1)
    {
        perror("error listening");
        return 0;
    }

     
     
    //Accept and incoming connection
    c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	
    while( (clientfd = accept(socketfd, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
    
         
        if( pthread_create( &thread_id , NULL ,  serverfunc , (void*) &clientfd) < 0)
        {
            perror("error creating thread");
            return 0;
        }
         
        pthread_join( thread_id , NULL);
    }
     
    if (clientfd ==-1)
    {
        perror("error accepting");
        return 0;
    }
     
    return 0;
}
