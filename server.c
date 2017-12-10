#include <stdio.h>
#include <string.h>   
#include <stdlib.h>    
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>   
#include <pthread.h> 
pthread_t ** threads;
int numofthreads=2000;
int countthreads=0;
pthread_mutex_t key;

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
        memset(content, 0, 10000);
    }
     
    if(read_size == 0||read_size==-1)
    {
        perror("error receive data or client disconnected");
        fflush(stdout);
    }

   //Critical Section(Add linked list)
   pthread_mutex_lock(&key);
   pthread_mutex_unlock(&key);
   //Critical Section Ends
    return 0;
} 
 
int main(int argc , char *argv[])
{   
    //Initialize mutex 
    if (pthread_mutex_init(&key, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    //Allocate threads arrat
    threads=malloc((sizeof(struct list *) * (2000)));
    //check commandline input
    if(argc!=3){
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
   
     //listen on the socket
    if(listen(socketfd,128)==-1)
    {
        perror("error listening");
        return 0;
    }

    //Accept 
    c = sizeof(struct sockaddr_in);
    pthread_t thread_id;
    while( (clientfd = accept(socketfd, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {

       thread_id=*threads[countthreads];
       countthreads++;
       //Check if Threads Array needs resizeing
       if(numofthreads==countthreads){
        numofthreads=numofthreads*2;
        threads = realloc(threads, sizeof(pthread_t*)*numofthreads);
        }


        if( pthread_create( &thread_id , NULL ,  serverfunc , (void*) &clientfd) < 0)
        {
            perror("error creating thread");
            return 0;
        }  
        
    }

    int s=0;
    while(threads[s]){
      if(threads[s]){
      pthread_join(*threads[s],NULL);}
      s++;
    }
    if (clientfd ==-1)
    {
        perror("error accepting");
        return 0;
    }
     
    return 0;
}
