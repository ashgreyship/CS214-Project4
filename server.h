#ifndef SORTER_H
#define SORTER_H

struct film
{
    int empty;

    char * comparechar;
    int compareint;
    double comparedouble;

    char * color;
    char * director_name;
    int num_critic_for_reviews;
    int duration;
    int director_facebook_likes;
    int actor_3_facebook_likes;
    char * actor_2_name;
    int actor_1_facebook_likes;
    int gross;
    char * generes;
    char * actor_1_name;
    char * movie_title;
    int num_voted_users;
    int cast_total_facebook_likes;
    char * actor_3_name;
    int facenumber_in_poster;
    char * plot_keywords;
    char * movie_imdb_link;
    int num_user_for_reviews;
    char * language;
    char * country;
    char * content_rating;
    int budget;
    int title_year;
    int actor_2_facebook_likes;
    double imdb_score;
    double aspect_ratio;
    int movie_facebook_likes;
    struct film *next;

};

struct list{
    struct  film * start;
    struct  film * end;
};
struct input{
    void * p;
    int com;
    char *portnum;
};

char* cleanWord(char*);
struct film* add(struct film*, int, char*);
int comparestring(char*);
void split(struct film*, struct film**, struct film**);
struct film* sortedmerge(struct film*, struct film*);
void mergeint(struct film**);
struct film* sortedmergedouble(struct film*, struct film*);
void mergedouble(struct film**);
struct film* sortedmergestring(struct film*, struct film*);
void mergestring(struct film**);
void print(struct film*,char * );
int checkFile(FILE*);
int sortFile(FILE*, int,char*,char*, char* );
void *mergeFiles(void *in);
void * addFile(void*);
int main(int, char*[]);


#endif
