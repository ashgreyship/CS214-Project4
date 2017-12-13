#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include "client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
pthread_t * threads;
int numofthreads=2000;
int countthreads=0;
struct list ** linkedlists;
int numoflists=2000;
int countlists=0;
pthread_mutex_t key;

char *repathfree(char *s1, char *s2) {
    char *path = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(path, s1);
    strcat(path, s2);
    free(s1);
    free(s2);
    return path;
}

char* cleanWord( char *word )
{
    int i = strlen(word) - 1;
    while ( i > 0 )
    {
        if ( isspace(word[i]) )
        {
            word[i] = '\0';
        }
        else
        {
            break;
        }
        i--;
    }
    return word;
}




struct film * add(struct film * movie,int count, char * content){
    int length=(strlen(content)+5);
    if(strlen(content) == 0) {
        return movie;
    }
    if(count==1){
        movie->color=malloc(length*sizeof(char));
        strcpy(movie->color,content);
        return movie;
    }
    if(count==2){
        movie->director_name=malloc(length*sizeof(char));
        strcpy(movie->director_name,content);
        return movie;
    }
    if(count==3){
        if(content[0]==-1){
            movie->num_critic_for_reviews=-1;
            return movie;
        }
        else{movie->num_critic_for_reviews=atoi(content);
            return movie;}
    }
    if(count==4){
        if(content[0]==-1){
            movie->duration=-1;
            return movie;
        }
        else{movie->duration=atoi(content);
            return movie;}
    }
    if(count==5){
        if(content[0]==-1){
            movie->director_facebook_likes=-1;
            return movie;
        }
        else{movie->director_facebook_likes=atoi(content);
            return movie;}
    }
    if(count==6){
        if(content[0]==-1){
            movie->actor_3_facebook_likes=-1;
            return movie;
        }
        else{movie->actor_3_facebook_likes=atoi(content);
            return movie;}
    }
    if(count==7){
        movie->actor_2_name=malloc(length*sizeof(char));
        strcpy(movie->actor_2_name,content);
        return movie;
    }
    if(count==8){
        if(content[0]==-1){
            movie->actor_1_facebook_likes=-1;
            return movie;
        }
        else{movie->actor_1_facebook_likes=atoi(content);
            return movie;}
    }
    if(count==9){
        if(content[0]==-1){
            movie->gross=-1;
            return movie;
        }
        else{movie->gross=atoi(content);
            return movie;}
    }
    if(count==10){
        movie->generes=malloc(length*sizeof(char));
        strcpy(movie->generes,content);
        return movie;
    }
    if(count==11){
        movie->actor_1_name=malloc(length*sizeof(char));
        strcpy(movie->actor_1_name,content);
        return movie;
    }
    if(count==12){
        movie->movie_title=malloc(length*sizeof(char));
        strcpy(movie->movie_title,content);
        return movie;
    }
    if(count==13){
        if(content[0]==-1){
            movie->num_voted_users=-1;
            return movie;
        }
        else{movie->num_voted_users=atoi(content);
            return movie;}
    }
    if(count==14){
        if(content[0]==-1){
            movie->cast_total_facebook_likes=-1;
            return movie;
        }
        else{movie->cast_total_facebook_likes=atoi(content);
            return movie;}
    }
    if(count==15){
        movie->actor_3_name=malloc(length*sizeof(char));
        strcpy(movie->actor_3_name,content);
        return movie;
    }
    if(count==16){
        if(content[0]==-1){
            movie->facenumber_in_poster=-1;
            return movie;
        }
        else{movie->facenumber_in_poster=atoi(content);
            return movie;}
    }
    if(count==17){
        movie->plot_keywords=malloc(length*sizeof(char));
        strcpy(movie->plot_keywords,content);
        return movie;
    }
    if(count==18){
        movie->movie_imdb_link=malloc(length*sizeof(char));
        strcpy(movie->movie_imdb_link,content);
        return movie;
    }
    if(count==19){
        if(content[0]==-1){
            movie->num_user_for_reviews=-1;
            return movie;
        }
        else{movie->num_user_for_reviews=atoi(content);
            return movie;}
    }
    if(count==20){
        movie->language=malloc(length*sizeof(char));
        strcpy(movie->language,content);
        return movie;
    }
    if(count==21){
        movie->country=malloc(length*sizeof(char));
        strcpy(movie->country,content);
        return movie;
    }
    if(count==22){
        movie->content_rating=malloc(length*sizeof(char));
        strcpy(movie->content_rating,content);
        return movie;
    }
    if(count==23){
        if(content[0]==-1){
            movie->budget=-1;
            return movie;
        }
        else{movie->budget=atoi(content);
            return movie;}
    }
    if(count==24){
        if(content[0]==-1){
            movie->title_year=-1;
            return movie;
        }
        else{movie->title_year=atoi(content);
            return movie;}
    }
    if(count==25){
        if(content[0]==-1){
            movie->actor_2_facebook_likes=-1;
            return movie;
        }
        else{movie->actor_2_facebook_likes=atoi(content);
            return movie;}
    }
    if(count==26){
        double c2;
        sscanf(content, "%lf", &c2);
        movie->imdb_score=c2;
        return movie;
    }
    if(count==27){
        double c2;
        if(content[0]==-1){
            movie->aspect_ratio=-1;
        }else{
            sscanf(content, "%lf", &c2);
            movie->aspect_ratio=c2;}
        return movie;
    }
    if(count==28){
        if(content[0]==-1){
            movie->movie_facebook_likes=-1;
            return movie;
        }
        else{movie->movie_facebook_likes=atoi(content);
            return movie;}
    }
    return movie;
}

//sortingfunctions

void split(struct film* root, struct film** front, struct film** back)
{
    struct film* fast;
    struct film* slow;
    if (root==NULL || root->next==NULL)
    {
        *front= root;
        *back= NULL;
    }
    else
    {
        slow = root;
        fast = root -> next;
        while (fast != NULL)
        {
            fast = fast -> next;
            if (fast != NULL)
            {
                slow = slow -> next;
                fast = fast -> next;
            }
        }

        *front = root;
        *back = slow -> next;
        slow -> next = NULL;
    }
}
struct film* sortedmerge(struct film* a, struct film* b)
{
    struct film* result = NULL;

    if (a == NULL)
        return(b);
    else if (b == NULL)
        return(a);

    if ( a-> compareint <= b -> compareint)
    {
        result = a;
        result -> next = sortedmerge(a -> next, b);
    }
    else
    {
        result = b;
        result -> next = sortedmerge(a, b -> next);
    }
    return(result);
}


void mergeint(struct film** root)
{
    struct film* head = *root;
    struct film* a;
    struct film* b;
    if ((head == NULL) || (head -> next == NULL))
    {
        return;
    }
    split(head, &a, &b);
    mergeint(&a);
    mergeint(&b);
    *root = sortedmerge(a, b);
}
struct film* sortedmergedouble(struct film* a, struct film* b)
{
    struct film* result = NULL;

    if (a == NULL)
        return(b);
    else if (b == NULL)
        return(a);

    if ( a-> comparedouble <= b -> comparedouble)
    {
        result = a;
        result -> next = sortedmergedouble(a -> next, b);
    }
    else
    {
        result = b;
        result -> next = sortedmergedouble(a, b -> next);
    }
    return(result);
}


void mergedouble(struct film** root)
{
    struct film* head = *root;
    struct film* n;
    struct film* m;
    if ((head == NULL) || (head -> next == NULL))
    {
        return;
    }
    split(head, &n, &m);
    mergedouble(&n);
    mergedouble(&m);
    *root = sortedmergedouble(n, m);
}

struct film* sortedmergestring(struct film* a, struct film* b)
{  
    int special=0;
    struct film* result = NULL;

    if (a == NULL)
        return(b);
    else if (b == NULL)
        return(a);
if(a->comparechar == NULL&&b->comparechar != NULL){

if(b->comparechar[0]=='"'){
    special=2;
    b->comparechar++;
}

    result = a;
    result -> next = sortedmergestring(a -> next, b);
   if(special==2){
b->comparechar--;} 
}

else if(a->comparechar != NULL&&b->comparechar == NULL){
if(a->comparechar[0]=='"'){
    a->comparechar++;
    special=1;
}
     result = b;
     result -> next = sortedmergestring(a, b -> next);
 if(special==1){
a->comparechar--;}   
}
else if(a->comparechar == NULL&&b->comparechar == NULL){
    result = a;
    result -> next = sortedmergestring(a -> next, b);
    
}
else if(a->comparechar != NULL&&b->comparechar != NULL){
if(a->comparechar[0]=='"'){
    a->comparechar++;
    special=1;
}
if(b->comparechar[0]=='"'){
    b->comparechar++;
    special=2;
}

if (strcmp(a->comparechar, b->comparechar) <=0) {
            result = a;
            result -> next = sortedmergestring(a -> next, b);
        } else
        {
            result = b;
            result -> next = sortedmergestring(a, b -> next);
        }
if(special==1){
a->comparechar--;} 
if(special==2){
b->comparechar--;} 
    }
    return(result);
}

void mergestring(struct film** root)
{
    struct film* head = *root;
    struct film* a;
    struct film* b;
    if ((head == NULL) || (head -> next == NULL))
    {
        return;
    }
    split(head, &a, &b);
    mergestring(&a);
    mergestring(&b);
    *root= sortedmergestring(a, b);
}

//end of sorting functions

struct film * createlist(char * content){
    struct film *movie=(struct film *)malloc(sizeof(struct film));
    struct film *temp;
    temp=movie;
    char word[200];
    int read=0;
    int c;
    double c2;
    int length=0;
    int count=1;
    int special=0;
    int jump=0;
    word[0]=-1;
    char column[4];
    char ip[255];
    int com=0;
    int initial=0;
    while ((c = content[read]) )
    {   
        if(initial==0&&c!='>'){
            read++;
            continue;
        }
        if(initial==0&&c=='>'){
            initial=1;
            read++;
            continue;
        }
        if(initial==1&&c!='~'){
             column[length]=content[read];
             length++;
             read++;
            continue;
        }
        if(initial==1&&c=='~'){
             column[length]='\0';
             length=0;
             initial=2;
             read++;
             com=atoi(column);
            continue;
        }
        if(c=='<'){
            ip[length+1]='\0';
            break;
        }
        if(c=='@'){
            special=5;
            read++;
            length=0;
            continue;
        }
        if(special==5){
           ip[length]=c;
           read++;
           length++;
           continue;
        }

//Getting sorting criteria
       // if(c=='~'){
   //         printf("%d\n",length );
     //       strcpy(column,word);
    //        memset(word,0,strlen(word));
    //        word[0]=-1;
    //        read++;
    //    }
     //   if(column[0]==-1){
      //      word[read]=c;
       //     read++;
      //      continue;
       // }
//jump over the header
         if(jump!=418){
           jump++;
         }
         else{
        //**************************************************************Reading content*************************************************************************************
        //special cases
        if(special==3){
            special=0;
            continue;
        }
        if(length==0&&c=='"'){
            special=1;

        }
        if(length!=0&&c=='"'){
            special=3;
            word[length]=c;
            length=0;
            //*******************************************************************Add special case String*******************************************************
            if(word[0]==-1){
                memset(word,0,strlen(word));
            }

            temp=add(temp,count,cleanWord(word));
            temp->empty=1;
            //compare criteria
            if(count==com){
                temp->comparechar=malloc((strlen(word)+5)*sizeof(char));
                strcpy(temp->comparechar,cleanWord(word));
            }
            memset(word,0,strlen(word));
            word[0]=-1;
            count++;
            continue;
        }
        //when complete a word before comma
        if((special==0&& c==',')||(special==0&& c=='^')||(special==0&& c==EOF)){
            length=0;
            //empty value
            //*********
            //numberic value
            //int
            if(count==3||count==4||count==5||count==6||count==8||count==9||count==13||count==14||count==16||count==19||count==23||count==24||count==25||count==28)
            {
                c=atoi(word);
                //*******************************************************************Add Int*******************************************************
                //compare criteria
                if(count==com&&word[0]==-1){
                    temp->compareint=-1;

                }
                else if(count==com&&word[0]!=-1){
                    temp->compareint=c;
                }
                temp=add(temp,count,word);
                temp->empty=1;
            }
                //double
            else if(count==26||count==27){

                sscanf(word, "%lf", &c2);

                //*******************************************************************Add Double*******************************************************

                //compare criteria

                if(count==com&&word[0]==-1){
                    temp->comparedouble=-1;

                }
                else if(count==com&&word[0]!=-1){
                    temp->comparedouble=c2;
                }

                temp=add(temp,count,word);
                temp->empty=1;
            }
            else{
                //*******************************************************************Add String*******************************************************
                if(word[0]==-1){
                    memset(word,0,strlen(word));
                }
                temp=add(temp,count,cleanWord(word));
                temp->empty=1;
                //compare criteria
                if(count==com){
                    temp->comparechar=malloc((strlen(word)+5)*sizeof(char));
                    strcpy(temp->comparechar,cleanWord(word));
                }
            }
            //reset count
            count++;

            if(count==29){

                count=1;
                temp->next=(struct film *)malloc(sizeof(struct film));
                
                temp=temp->next;
            }

            memset(word,0,strlen(word));
            word[0]=-1;
        }
            //reading characters
        else{
            word[length]=c;
            length++;
        }
    }
    read++;
}
printf("The column is: %d\n",com );
printf("IP adderss is: %s\n",ip );

    if(com==3||com==4||com==5||com==6||com==8||com==9||com==13||com==14||com==16||com==19||com==23||com==24||com==25||com==28)
     {
    mergeint(&movie);}
    if(com==26||com==27){
    mergedouble(&movie);
    }
    else{
    mergestring(&movie);
    }
return movie;
}




void *serverfunc(void *socketfd)
{
    //Get the socket descriptor
    int sock = *(int*)socketfd;
    int read_size;
    int bufsize=30;
    char *content=malloc(35*sizeof(char));
    char * firstpart=malloc(35*sizeof(char));
    int count=0;
    //Receive a message from client
    while( (read_size = recv(sock , content ,bufsize, 0)) > 0 )
    {
        //read size number
        if(count==0||read_size==bufsize){
            char * number=malloc(35*sizeof(char));
            int i=0;
            while(content[i]!='>'){
                number[i]=content[i];
                i++;
            }
            bufsize=atoi(number);
            content=realloc(content,bufsize*sizeof(char));
            count++;
            strcpy(firstpart,content);
        }

    }
    content=repathfree(firstpart,content);
    if(read_size == 0||read_size==-1)
    {
        perror("error receive data or client disconnected");
        fflush(stdout);
    }
   struct film* movie=createlist(content);

   //Create list
   struct film *temp;
   temp=movie;
    while(temp->next){
      temp=temp->next;
     }  
   struct list* result=malloc(sizeof(struct list*));
   result->start=movie;
   result->end=temp;
   //Critical Section(Add linked list)
   pthread_mutex_lock(&key);
   linkedlists[countlists]=result;
   if(numoflists==countlists){
        numoflists=numoflists*2;
        linkedlists = realloc(linkedlists, sizeof(struct film*)*numoflists);
             }
   pthread_mutex_unlock(&key);
   //Critical Section Ends
   //close(socketfd);
    return 0;
} 
 
int main(int argc , char *argv[])
{   
    //Initialize global
    linkedlists=malloc((sizeof(struct list *) * (2000)));
    //Initialize mutex 
    if (pthread_mutex_init(&key, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    //Allocate threads arrat
    threads=malloc((sizeof(pthread_t ) * (2000)));
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
    pthread_t thread_id=threads[countthreads];
    while( (clientfd = accept(socketfd, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
     
        
        if( pthread_create( &thread_id , NULL ,  serverfunc , (void*) &clientfd) < 0)
        {
            perror("error creating thread");
            return 0;
        }  
        countthreads++;
        //Check if Threads Array needs resizeing
            if(numofthreads==countthreads){
                numofthreads=numofthreads*2;
                threads = realloc(threads, sizeof(pthread_t*)*numofthreads);
            }
        
    }
//joint threads
    int s=0;
    while(threads[s]){
      if(threads[s]){
      pthread_join(threads[s],NULL);}
      s++;
    }
    if (clientfd ==-1)
    {
        perror("error accepting");
        return 0;
    }
     
    return 0;
}
