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
#include <ifaddrs.h>


pthread_t **threads;
int numofthreads = 2000;
int countthreads = 0;
struct list **linkedlists;
int numoflists = 2000;
int countlists = 0;
int numoftotalthreads = 0;
int sockfd;
int SERVER_PORT;

char *content = "Color,James Cameron,723,178,0,855,Joel David Moore,1000,760505847,Action|Adventure|Fantasy|Sci-Fi,CCH Pounder,Avatar ,886204,4834,Wes Studi,0,avatar|future|marine|native|paraplegic,http://www.imdb.com/title/tt0499549/?ref_=fn_tt_tt_1,3054,English,USA,PG-13,237000000,2009,936,7.9,1.78,33000^Color,Gore Verbinski,302,169,563,1000,Orlando Bloom,40000,309404152,Action|Adventure|Fantasy,Johnny Depp,Pirates of the Caribbean: At World's End ,471220,48350,Jack Davenport,0,goddess|marriage ceremony|marriage proposal|pirate|singapore,http://www.imdb.com/title/tt0449088/?ref_=fn_tt_tt_1,1238,English,USA,PG-13,300000000,2007,5000,7.1,2.35,0^Color,Sam Mendes,602,148,0,161,Rory Kinnear,11000,200074175,Action|Adventure|Thriller,Christoph Waltz,Spectre ,275868,11700,Stephanie Sigman,1,bomb|espionage|sequel|spy|terrorist,http://www.imdb.com/title/tt2379713/?ref_=fn_tt_tt_1,994,English,UK,PG-13,245000000,2015,393,6.8,2.35,85000^Color,Christopher Nolan,813,164,22000,23000,Christian Bale,27000,448130642,Action|Thriller,Tom Hardy,The Dark Knight Rises ,1144337,106759,Joseph Gordon-Levitt,0,deception|imprisonment|lawlessness|police officer|terrorist plot,http://www.imdb.com/title/tt1345836/?ref_=fn_tt_tt_1,2701,English,USA,PG-13,250000000,2012,23000,8.5,2.35,164000^,Doug Walker,,,131,,Rob Walker,131,,Documentary,Doug Walker,Star Wars: Episode VII - The Force Awakens             ,8,143,,0,,http://www.imdb.com/title/tt5289954/?ref_=fn_tt_tt_1,,,,,,,12,7.1,,0^Color,Andrew Stanton,462,132,475,530,Samantha Morton,640,73058679,Action|Adventure|Sci-Fi,Daryl Sabara,John Carter ,212204,1873,Polly Walker,1,alien|american civil war|male nipple|mars|princess,http://www.imdb.com/title/tt0401729/?ref_=fn_tt_tt_1,738,English,USA,PG-13,263700000,2012,632,6.6,2.35,24000^";
char *mergeAllOnetime = "@";
pthread_mutex_t m;
pthread_mutex_t p;
pthread_mutex_t key;
pthread_t *TIDofFinal;


char *repath(const char *s1, const char *s2) {
    char *path = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(path, s1);
    strcat(path, s2);
    return path;
}

char *cleanWord(char *word) {
    int i = strlen(word) - 1;
    while (i > 0) {
        if (isspace(word[i])) {
            word[i] = '\0';
        } else {
            break;
        }
        i--;
    }
    return word;
}


struct film *add(struct film *movie, int count, char *content) {
    int length = (strlen(content) + 5);
    if (strlen(content) == 0) {
        return movie;
    }
    if (count == 1) {
        movie->color = malloc(length * sizeof(char));
        strcpy(movie->color, content);
        return movie;
    }
    if (count == 2) {
        movie->director_name = malloc(length * sizeof(char));
        strcpy(movie->director_name, content);
        return movie;
    }
    if (count == 3) {
        if (content[0] == -1) {
            movie->num_critic_for_reviews = -1;
            return movie;
        } else {
            movie->num_critic_for_reviews = atoi(content);
            return movie;
        }
    }
    if (count == 4) {
        if (content[0] == -1) {
            movie->duration = -1;
            return movie;
        } else {
            movie->duration = atoi(content);
            return movie;
        }
    }
    if (count == 5) {
        if (content[0] == -1) {
            movie->director_facebook_likes = -1;
            return movie;
        } else {
            movie->director_facebook_likes = atoi(content);
            return movie;
        }
    }
    if (count == 6) {
        if (content[0] == -1) {
            movie->actor_3_facebook_likes = -1;
            return movie;
        } else {
            movie->actor_3_facebook_likes = atoi(content);
            return movie;
        }
    }
    if (count == 7) {
        movie->actor_2_name = malloc(length * sizeof(char));
        strcpy(movie->actor_2_name, content);
        return movie;
    }
    if (count == 8) {
        if (content[0] == -1) {
            movie->actor_1_facebook_likes = -1;
            return movie;
        } else {
            movie->actor_1_facebook_likes = atoi(content);
            return movie;
        }
    }
    if (count == 9) {
        if (content[0] == -1) {
            movie->gross = -1;
            return movie;
        } else {
            movie->gross = atoi(content);
            return movie;
        }
    }
    if (count == 10) {
        movie->generes = malloc(length * sizeof(char));
        strcpy(movie->generes, content);
        return movie;
    }
    if (count == 11) {
        movie->actor_1_name = malloc(length * sizeof(char));
        strcpy(movie->actor_1_name, content);
        return movie;
    }
    if (count == 12) {
        movie->movie_title = malloc(length * sizeof(char));
        strcpy(movie->movie_title, content);
        return movie;
    }
    if (count == 13) {
        if (content[0] == -1) {
            movie->num_voted_users = -1;
            return movie;
        } else {
            movie->num_voted_users = atoi(content);
            return movie;
        }
    }
    if (count == 14) {
        if (content[0] == -1) {
            movie->cast_total_facebook_likes = -1;
            return movie;
        } else {
            movie->cast_total_facebook_likes = atoi(content);
            return movie;
        }
    }
    if (count == 15) {
        movie->actor_3_name = malloc(length * sizeof(char));
        strcpy(movie->actor_3_name, content);
        return movie;
    }
    if (count == 16) {
        if (content[0] == -1) {
            movie->facenumber_in_poster = -1;
            return movie;
        } else {
            movie->facenumber_in_poster = atoi(content);
            return movie;
        }
    }
    if (count == 17) {
        movie->plot_keywords = malloc(length * sizeof(char));
        strcpy(movie->plot_keywords, content);
        return movie;
    }
    if (count == 18) {
        movie->movie_imdb_link = malloc(length * sizeof(char));
        strcpy(movie->movie_imdb_link, content);
        return movie;
    }
    if (count == 19) {
        if (content[0] == -1) {
            movie->num_user_for_reviews = -1;
            return movie;
        } else {
            movie->num_user_for_reviews = atoi(content);
            return movie;
        }
    }
    if (count == 20) {
        movie->language = malloc(length * sizeof(char));
        strcpy(movie->language, content);
        return movie;
    }
    if (count == 21) {
        movie->country = malloc(length * sizeof(char));
        strcpy(movie->country, content);
        return movie;
    }
    if (count == 22) {
        movie->content_rating = malloc(length * sizeof(char));
        strcpy(movie->content_rating, content);
        return movie;
    }
    if (count == 23) {
        if (content[0] == -1) {
            movie->budget = -1;
            return movie;
        } else {
            movie->budget = atoi(content);
            return movie;
        }
    }
    if (count == 24) {
        if (content[0] == -1) {
            movie->title_year = -1;
            return movie;
        } else {
            movie->title_year = atoi(content);
            return movie;
        }
    }
    if (count == 25) {
        if (content[0] == -1) {
            movie->actor_2_facebook_likes = -1;
            return movie;
        } else {
            movie->actor_2_facebook_likes = atoi(content);
            return movie;
        }
    }
    if (count == 26) {
        double c2;
        sscanf(content, "%lf", &c2);
        movie->imdb_score = c2;
        return movie;
    }
    if (count == 27) {
        double c2;
        if (content[0] == -1) {
            movie->aspect_ratio = -1;
        } else {
            sscanf(content, "%lf", &c2);
            movie->aspect_ratio = c2;
        }
        return movie;
    }
    if (count == 28) {
        if (content[0] == -1) {
            movie->movie_facebook_likes = -1;
            return movie;
        } else {
            movie->movie_facebook_likes = atoi(content);
            return movie;
        }
    }
    return movie;
}


int comparestring(char *word) {
    int count = 0;
    if (strcmp(word, "color") == 0) {
        count = 1;
    } else if (strcmp(word, "director_name") == 0) {
        count = 2;
    } else if (strcmp(word, "num_critic_for_reviews") == 0) {
        count = 3;
    } else if (strcmp(word, "duration") == 0) {
        count = 4;
    } else if (strcmp(word, "director_facebook_likes") == 0) {
        count = 5;
    } else if (strcmp(word, "actor_3_facebook_likes") == 0) {
        count = 6;
    } else if (strcmp(word, "actor_2_name") == 0) {
        count = 7;
    } else if (strcmp(word, "actor_1_facebook_likes") == 0) {
        count = 8;
    } else if (strcmp(word, "gross") == 0) {
        count = 9;
    } else if (strcmp(word, "generes") == 0) {
        count = 10;
    } else if (strcmp(word, "actor_1_name") == 0) {
        count = 11;
    } else if (strcmp(word, "movie_title") == 0) {
        count = 12;
    } else if (strcmp(word, "num_voted_users") == 0) {
        count = 13;
    } else if (strcmp(word, "cast_total_facebook_likes") == 0) {
        count = 14;
    } else if (strcmp(word, "actor_3_name") == 0) {
        count = 15;
    } else if (strcmp(word, "facenumber_in_poster") == 0) {
        count = 16;
    } else if (strcmp(word, "plot_keywords") == 0) {
        count = 17;
    } else if (strcmp(word, "movie_imdb_link") == 0) {
        count = 18;
    } else if (strcmp(word, "num_user_for_reviews") == 0) {
        count = 19;
    } else if (strcmp(word, "language") == 0) {
        count = 20;
    } else if (strcmp(word, "country") == 0) {
        count = 21;
    } else if (strcmp(word, "content_rating") == 0) {
        count = 22;
    } else if (strcmp(word, "budget") == 0) {
        count = 23;
    } else if (strcmp(word, "title_year") == 0) {
        count = 24;
    } else if (strcmp(word, "actor_2_facebook_likes") == 0) {
        count = 25;
    } else if (strcmp(word, "imdb_score") == 0) {
        count = 26;
    } else if (strcmp(word, "aspect_ratio") == 0) {
        count = 27;
    } else if (strcmp(word, "movie_facebook_likes") == 0) {
        count = 28;
    }


    return count;
}

void split(struct film *root, struct film **front, struct film **back) {
    struct film *fast;
    struct film *slow;
    if (root == NULL || root->next == NULL) {
        *front = root;
        *back = NULL;
    } else {
        slow = root;
        fast = root->next;
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = root;
        *back = slow->next;
        slow->next = NULL;
    }
}

struct film *sortedmerge(struct film *a, struct film *b) {
    struct film *result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (a->compareint <= b->compareint) {
        result = a;
        result->next = sortedmerge(a->next, b);
    } else {
        result = b;
        result->next = sortedmerge(a, b->next);
    }
    return (result);
}


void mergeint(struct film **root) {
    struct film *head = *root;
    struct film *a;
    struct film *b;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    split(head, &a, &b);
    mergeint(&a);
    mergeint(&b);
    *root = sortedmerge(a, b);
}

struct film *sortedmergedouble(struct film *a, struct film *b) {
    struct film *result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (a->comparedouble <= b->comparedouble) {
        result = a;
        result->next = sortedmergedouble(a->next, b);
    } else {
        result = b;
        result->next = sortedmergedouble(a, b->next);
    }
    return (result);
}


void mergedouble(struct film **root) {
    struct film *head = *root;
    struct film *n;
    struct film *m;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    split(head, &n, &m);
    mergedouble(&n);
    mergedouble(&m);
    *root = sortedmergedouble(n, m);
}

struct film *sortedmergestring(struct film *a, struct film *b) {
    int special = 0;
    struct film *result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (a->comparechar == NULL && b->comparechar != NULL) {

        if (b->comparechar[0] == '"') {
            special = 2;
            b->comparechar++;
        }

        result = a;
        result->next = sortedmergestring(a->next, b);
        if (special == 2) {
            b->comparechar--;
        }
    } else if (a->comparechar != NULL && b->comparechar == NULL) {
        if (a->comparechar[0] == '"') {
            a->comparechar++;
            special = 1;
        }
        result = b;
        result->next = sortedmergestring(a, b->next);
        if (special == 1) {
            a->comparechar--;
        }
    } else if (a->comparechar == NULL && b->comparechar == NULL) {
        result = a;
        result->next = sortedmergestring(a->next, b);

    } else if (a->comparechar != NULL && b->comparechar != NULL) {
        if (a->comparechar[0] == '"') {
            a->comparechar++;
            special = 1;
        }
        if (b->comparechar[0] == '"') {
            b->comparechar++;
            special = 2;
        }

        if (strcmp(a->comparechar, b->comparechar) <= 0) {
            result = a;
            result->next = sortedmergestring(a->next, b);
        } else {
            result = b;
            result->next = sortedmergestring(a, b->next);
        }
        if (special == 1) {
            a->comparechar--;
        }
        if (special == 2) {
            b->comparechar--;
        }
    }
    return (result);
}

void mergestring(struct film **root) {
    struct film *head = *root;
    struct film *a;
    struct film *b;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    split(head, &a, &b);
    mergestring(&a);
    mergestring(&b);
    *root = sortedmergestring(a, b);
}


char *convertToString(FILE *fp) {
    char c;
    char *fullStr = malloc(5000 * (sizeof(char)));
    int num = 5000;
    int count = 0;
    int jump = 0;
    while ((c = getc(fp)) != EOF) {
        if (jump != 418) {
            jump++;
            continue;
        }
        if (c == '\n') { c = '^'; }
        fullStr[count] = c;
        count++;
        if (count == num) {
            num = num * 2;
            fullStr = realloc(fullStr, num * (sizeof(char)));
        }
    }
    if (fullStr[count] == '^' && fullStr[count - 1] == '^') {
        fullStr[count] = '\0';
    }
    return fullStr;
}


char *getIP() {
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs(&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family == AF_INET ) {
         if (strcmp((char *)ifa->ifa_name, "eth0") == 0) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            //printf("Interface: %s\tAddress: %s\n", ifa->ifa_name, addr);
            break;
         }
        }
    }
    freeifaddrs(ifap);
    return addr;
}

void print2(struct film *list) {
    struct film *movie;
    movie = list;
    printf("%s\n",
           "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes");
    while (movie) {
        if (movie->empty == 1) {
            if (movie->color == NULL) {

                printf(",");
            } else {
                printf("%s,", movie->color);
            }

            if (movie->director_name == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->director_name);
            }

            if (movie->num_critic_for_reviews == -1) {
                printf(",");
            } else {
                printf("%d,", movie->num_critic_for_reviews);
            }


            if (movie->duration == -1) {
                printf(",");
            } else {
                printf("%d,", movie->duration);
            }


            if (movie->director_facebook_likes == -1) {
                printf(",");
            } else {
                printf("%d,", movie->director_facebook_likes);
            }


            if (movie->actor_3_facebook_likes == -1) {
                printf(",");
            } else {
                printf("%d,", movie->actor_3_facebook_likes);
            }

            if (movie->actor_2_name == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->actor_2_name);
            }


            if (movie->actor_1_facebook_likes == -1) {
                printf(",");
            } else {
                printf("%d,", movie->actor_1_facebook_likes);
            }

            if (movie->gross == -1) {
                printf(",");
            } else {
                printf("%d,", movie->gross);
            }
            if (movie->generes == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->generes);
            }

            if (movie->actor_1_name == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->actor_1_name);
            }

            if (movie->movie_title == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->movie_title);
            }


            if (movie->num_voted_users == -1) {
                printf(",");
            } else {
                printf("%d,", movie->num_voted_users);
            }


            if (movie->cast_total_facebook_likes == -1) {
                printf(",");
            } else {
                printf("%d,", movie->cast_total_facebook_likes);
            }

            if (movie->actor_3_name == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->actor_3_name);
            }

            if (movie->facenumber_in_poster == -1) {
                printf(",");
            } else {
                printf("%d,", movie->facenumber_in_poster);
            }

            if (movie->plot_keywords == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->plot_keywords);
            }

            if (movie->movie_imdb_link == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->movie_imdb_link);
            }


            if (movie->num_user_for_reviews == -1) {
                printf(",");
            } else {
                printf("%d,", movie->num_user_for_reviews);
            }
            if (movie->language == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->language);
            }

            if (movie->country == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->country);
            }

            if (movie->content_rating == NULL) {
                printf(",");
            } else {
                printf("%s,", movie->content_rating);
            }

            if (movie->budget == -1) {
                printf(",");
            } else {
                printf("%d,", movie->budget);
            }

            if (movie->title_year == -1) {
                printf(",");
            } else {
                printf("%d,", movie->title_year);
            }

            if (movie->actor_2_facebook_likes == -1) {
                printf(",");
            } else {
                printf("%d,", movie->actor_2_facebook_likes);
            }


            printf("%g,", movie->imdb_score);

            if (movie->aspect_ratio == -1) { printf(","); }
            else { printf("%g,", movie->aspect_ratio); }

            if (movie->movie_facebook_likes == -1) {
                printf(",");
            } else {
                printf("%d,", movie->movie_facebook_likes);
            }
            printf("\n");
        }
        movie = movie->next;
    }
}


void print(struct film *movie, char *filepath) {
    FILE *output;

    /* open the file */
    output = fopen(filepath, "wb");
    if (output == NULL) return; /* fopen failed */

    fputs("color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n",
          output);
    while (movie) {
        if (movie->empty == 1) {
            if (movie->color == NULL) {

                fputs(",", output);
            } else {
                fputs(movie->color, output);
                fputs(",", output);
            }

            if (movie->director_name == NULL) {
                fputs(",", output);
            } else {

                fputs(movie->director_name, output);
                fputs(",", output);
            }

            if (movie->num_critic_for_reviews == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->num_critic_for_reviews);
                fputs(",", output);
            }


            if (movie->duration == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->duration);
                fputs(",", output);
            }


            if (movie->director_facebook_likes == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->director_facebook_likes);
                fputs(",", output);
            }


            if (movie->actor_3_facebook_likes == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->actor_3_facebook_likes);
                fputs(",", output);
            }

            if (movie->actor_2_name == NULL) {
                fputs(",", output);
            } else {
                fputs(movie->actor_2_name, output);
                fputs(",", output);
            }


            if (movie->actor_1_facebook_likes == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->actor_1_facebook_likes);
            }
            fputs(",", output);

            if (movie->gross == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->gross);
                fputs(",", output);
            }
            if (movie->generes == NULL) {
                fputs(",", output);
            } else {
                fputs(movie->generes, output);
                fputs(",", output);
            }

            if (movie->actor_1_name == NULL) {
                fputs(",", output);
            } else {
                fputs(movie->actor_1_name, output);
                fputs(",", output);
            }

            if (movie->movie_title == NULL) {
                fputs(",", output);
            } else {
                fputs(movie->movie_title, output);
                fputs(",", output);
            }


            if (movie->num_voted_users == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->num_voted_users);
                fputs(",", output);
            }


            if (movie->cast_total_facebook_likes == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->cast_total_facebook_likes);
                fputs(",", output);
            }

            if (movie->actor_3_name == NULL) {
                fputs(",", output);
            } else {
                fputs(movie->actor_3_name, output);
                fputs(",", output);
            }

            if (movie->facenumber_in_poster == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->facenumber_in_poster);
                fputs(",", output);
            }

            if (movie->plot_keywords == NULL) {
                fputs(",", output);
            } else {
                fputs(movie->plot_keywords, output);
                fputs(",", output);
            }

            if (movie->movie_imdb_link == NULL) {
                fputs(",", output);
            } else {
                fputs(movie->movie_imdb_link, output);
                fputs(",", output);
            }


            if (movie->num_user_for_reviews == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->num_user_for_reviews);
                fputs(",", output);
            }
            if (movie->language == NULL) {
                fputs(",", output);
            } else {
                fputs(movie->language, output);
                fputs(",", output);
            }

            if (movie->country == NULL) {
                fputs(",", output);
            } else {
                fputs(movie->country, output);
                fputs(",", output);
            }

            if (movie->content_rating == NULL) {
                fputs(",", output);
            } else {
                fputs(movie->content_rating, output);
                fputs(",", output);
            }

            if (movie->budget == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->budget);
                fputs(",", output);
            }

            if (movie->title_year == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->title_year);
                fputs(",", output);
            }

            if (movie->actor_2_facebook_likes == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->actor_2_facebook_likes);
                fputs(",", output);
            }

            fprintf(output, "%g", movie->imdb_score);
            fputs(",", output);

            if (movie->aspect_ratio == -1) { fputs(",", output); }
            else {
                fprintf(output, "%g", movie->aspect_ratio);
                fputs(",", output);
            }

            if (movie->movie_facebook_likes == -1) {
                fputs(",", output);
            } else {
                fprintf(output, "%d", movie->movie_facebook_likes);
                fputs("\n", output);
            }

        }
        movie = movie->next;

    }
    fclose(output);
}


void freelist(struct film *root) {
    while (root) {
        struct film *temp = root;
        root = root->next;
        free(temp);
    }
}

void *addFile(void *in) {
    struct input *input = in;
    char col[50];
    sprintf(col, "%d", input->com);
    FILE *fp = input->p;

    pthread_mutex_lock(&p);
    char *stringTosend = convertToString(fp);
    if (send(sockfd, stringTosend, strlen(stringTosend), 0) == -1) {
        perror("fail to send datas.");
        exit(-1);
    }
    pthread_mutex_unlock(&p);
    pthread_exit(NULL);
}


void *mergeFiles(void *in) {
    char *mergeAllCommand = "@";
    if (send(sockfd, mergeAllCommand, strlen(mergeAllCommand), 0) == -1) {
        perror("fail to send datas.");
        exit(-1);
    }

    pthread_exit(NULL);
}


void *dirthread(void *in) {
    DIR *d;
    struct dirent *dir;
    struct input *input = in;
    char *inputpath = input->p;
    d = opendir(inputpath);
    int com = input->com;
//Check all items
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            int length = strlen(dir->d_name);
//found csv file
            if (strncmp(dir->d_name + length - 4, ".csv", 4) == 0) {
//Do Stuff
                char *path = repath(inputpath, "/");
                path = repath(path, dir->d_name);
                FILE *fp;
                fp = fopen(path, "r");
                struct input *in = malloc(sizeof(struct input));
                in->p = fp;
                in->com = com;

//Critical Section
                pthread_mutex_lock(&key);
                threads[countthreads] = malloc(sizeof(pthread_t));
                pthread_create(threads[countthreads], NULL, addFile, (void *) in);
                numoftotalthreads++;
                countthreads++;
                //Check if Threads Array needs resizeing
                if (numofthreads == countthreads) {
                    numofthreads = numofthreads * 2;
                    threads = realloc(threads, sizeof(pthread_t *) * numofthreads);
                }
                pthread_mutex_unlock(&key);
//Critical Section Ends
            }



//list directories
            struct stat st;

            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
                continue;

            if (fstatat(dirfd(d), dir->d_name, &st, 0) < 0) {
                perror(dir->d_name);

                continue;
            }
//Found directory
            if (S_ISDIR(st.st_mode)) {
//Do Stuff

                char *newinputpath = repath(inputpath, "/");
                newinputpath = repath(newinputpath, dir->d_name);
                struct input *in = malloc(sizeof(struct input));
                in->p = newinputpath;
                in->com = com;
//Critical Section
                pthread_mutex_lock(&key);
                threads[countthreads] = malloc(sizeof(pthread_t));
                pthread_create(threads[countthreads], NULL, dirthread, (void *) in);
                numoftotalthreads++;
                countthreads++;
                //Check if Threads Array needs resizeing
                if (numofthreads == countthreads) {
                    numofthreads = numofthreads * 2;
                    threads = realloc(threads, sizeof(pthread_t *) * numofthreads);
                }
                pthread_mutex_unlock(&key);
//Critical Section Ends
            }
        }

//close
        closedir(d);
    }

    pthread_exit(NULL);
}


int main(int argc, char **argv) {
    if (pthread_mutex_init(&m, NULL) != 0) {
        printf("\n mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&p, NULL) != 0) {
        printf("\n mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&key, NULL) != 0) {
        printf("\n mutex init failed\n");
        return 1;
    }


    threads = malloc((sizeof(pthread_t *) * (2000)));
//***********************************************************MAIN***************************************************************************
    linkedlists = malloc((sizeof(struct list *) * (2000)));
//*****************************************Command Line Checking*****************************************
    char *inputpath;
    char *outputpath;
    char *column;
    char *portnum;
    if (argc != 7 && argc != 9 && argc != 11) {
        printf("Incorrect Input\n");
        return 0;
    }
    if (argc == 7) {
        inputpath = ".";
        outputpath = ".";
        column = argv[2];
        portnum = argv[6];
    }
    if (argc == 9) {
        if (strcmp(argv[7], "-d") == 0) {
            inputpath = argv[8];
            outputpath = ".";
        }
        if (strcmp(argv[7], "-o") == 0) {
            outputpath = argv[8];
            inputpath = ".";
        }
        column = argv[2];
        portnum = argv[6];
    }
    if (argc == 11) {
        if (strcmp(argv[7], "-d") == 0) {
            inputpath = argv[8];
            outputpath = argv[10];
        }
        if (strcmp(argv[7], "-o") == 0) {
            outputpath = argv[8];
            inputpath = argv[10];
        }
        column = argv[2];
        portnum = argv[6];
    }

//*****************************************Command Line Checking Complete{FINNALLY!!!}*****************************************
//calculate sorting criteria
    int com;
    com = comparestring(column);
    if (com == 0) {
        printf("error\n");
        return 0;
    }


//***************************************** Initialize socket**********
    SERVER_PORT = atoi(portnum);

    //char sendBuf[MAX_BUF];
    //int sendSize;
    struct hostent *host;
    host = gethostbyname(argv[4]);
    struct sockaddr_in servAddr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("fail to establish a socket");
        exit(1);
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERVER_PORT);
    servAddr.sin_addr = *((struct in_addr *) host->h_addr);
    bzero(&(servAddr.sin_zero), 8);

    if (connect(sockfd, (struct sockaddr *) &servAddr, sizeof(struct sockaddr_in)) == -1) {
        perror("fail to connect the socket");
        exit(1);
    }

//**************************************Send IP and column name(char *onetime = "1234567<duration~";)**********************

    char *IP = getIP();
    char *IPCol = malloc(100);
    char comInt[10];
    IPCol[0] = '\0';
    strcat(IPCol, IP);
    strcat(IPCol, "<");
    sprintf(comInt, "%d", com);
    strcat(IPCol, comInt);
    strcat(IPCol, "~");
    
    if (send(sockfd, IPCol, strlen(IPCol), 0) == -1) {
        perror("fail to send datas.");
        exit(-1);
    }
    free(IPCol);

//*****************************************Start Traversing Directory**********************************************************
    DIR *d;
    struct dirent *dir;
    d = opendir(inputpath);

//Check all items
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            int length = strlen(dir->d_name);
//found csv file
            if (strncmp(dir->d_name + length - 4, ".csv", 4) == 0) {
//Do Stuff
                char *path = repath(inputpath, "/");
                path = repath(path, dir->d_name);
                FILE *fp;
                fp = fopen(path, "r");
                struct input *in = malloc(sizeof(struct input));
                in->p = fp;
                in->com = com;

//Critical Section
                pthread_mutex_lock(&key);
                threads[countthreads] = malloc(sizeof(pthread_t));
                pthread_create(threads[countthreads], NULL, addFile, (void *) in);
                numoftotalthreads++;
                countthreads++;
                //Check if Threads Array needs resizeing
                if (numofthreads == countthreads) {
                    numofthreads = numofthreads * 2;
                    threads = realloc(threads, sizeof(pthread_t *) * numofthreads);
                }
                pthread_mutex_unlock(&key);
//Critical Section Ends
            }



//list directories
            struct stat st;

            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
                continue;

            if (fstatat(dirfd(d), dir->d_name, &st, 0) < 0) {
                perror(dir->d_name);

                continue;
            }
//Found directory
            if (S_ISDIR(st.st_mode)) {
//Do Stuff

                char *newinputpath = repath(inputpath, "/");
                newinputpath = repath(newinputpath, dir->d_name);
                struct input *in = malloc(sizeof(struct input));
                in->p = newinputpath;
                in->com = com;
//Critical Section
                pthread_mutex_lock(&key);
                threads[countthreads] = malloc(sizeof(pthread_t));
                pthread_create(threads[countthreads], NULL, dirthread, (void *) in);
                numoftotalthreads++;
                countthreads++;
                //Check if Threads Array needs resizeing
                if (numofthreads == countthreads) {
                    numofthreads = numofthreads * 2;
                    threads = realloc(threads, sizeof(pthread_t *) * numofthreads);
                }
                pthread_mutex_unlock(&key);
//Critical Section Ends
            }
        }
//Need to join threads
        int s = 0;
        while (threads[s]) {
            if (threads[s]) {
                pthread_join(*threads[s], NULL);
            }
            s++;
        }
        s++;

//**********************Send signal of merging all sorted files****************************************
        struct input *inputFinal = malloc(sizeof(struct input));
        pthread_t lastthread;
        pthread_create(&lastthread, NULL, mergeFiles, (void *) inputFinal);
        pthread_join(lastthread, NULL);

        //  free(in);

        free(threads);
        closedir(d);
    }


    char buf;
    FILE *output;
    char *outputFileName = malloc(sizeof(char) * 1000);
    outputFileName[0] = '\0';
    strcpy(outputFileName, outputpath);
    strcat(outputFileName, "/AllFiles-sorted-<");
    strcat(outputFileName, column);
    strcat(outputFileName, ">.csv");
    output = fopen(outputFileName, "wb");
    int specialCount = 0;
    int specialsecond=0;
    while (read(sockfd, &buf, 1)!=-1) {

        if (specialsecond == 0 && '^' == buf) {
            specialsecond++;
            continue;
        }
        if (specialsecond == 1 &&'^'!=buf) {
            specialsecond=0;
        }
        if (specialsecond == 1 && '^' == buf) {
            buf = '\n';
        }



        if (specialCount == 0 && '}' == buf) {
            specialCount++;
            continue;
        }
        if (specialCount == 1 &&'}'!=buf) {
            specialCount=0;
            continue;
        }
        if (specialCount == 1 && '}' == buf) {
            buf = '\n';
            break;
        }
   
        fprintf(output, "%c",buf );
        //printf("%c",buf );
    }

    fclose(output);
    free(outputFileName);

    close(sockfd);
  //  printf("\nTotal number of threads:%d\n", (numoftotalthreads + 1));
  //  printf("%s\n", outputpath);
    return 0;
}

