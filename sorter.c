#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sorter.h"

pthread_t **threads;
int numofthreads = 2000;
int countthreads = 0;
struct list **linkedlists;
int numoflists = 2000;
int countlists = 0;
int numoftotalthreads = 0;
pthread_mutex_t m;
pthread_mutex_t p;
pthread_mutex_t key;

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
    pthread_mutex_lock(&p);
    printf("%lu,", pthread_self());
    pthread_mutex_unlock(&p);
    struct film *movie = (struct film *) malloc(sizeof(struct film));
    struct film *temp;
    temp = movie;
    struct input *input = in;
    FILE *fp = input->p;
    int com = input->com;

    //read the file
    char word[200];
    int c;
    double c2;
    int length = 0;
    int count = 1;
    int special = 0;
    int jump = 0;
    word[0] = -1;
    while ((c = getc(fp)) != EOF) {
        if (jump != 418) {
            jump++;
        } else {
            //**************************************************************Reading content*************************************************************************************
            //special cases
            if (special == 3) {
                special = 0;
                continue;
            }
            if (length == 0 && c == '"') {
                special = 1;

            }
            if (length != 0 && c == '"') {
                special = 3;
                word[length] = c;
                length = 0;
                //*******************************************************************Add special case String*******************************************************
                if (word[0] == -1) {
                    memset(word, 0, strlen(word));
                }

                temp = add(temp, count, cleanWord(word));
                temp->empty = 1;
                //compare criteria
                if (count == com) {
                    temp->comparechar = malloc((strlen(word) + 5) * sizeof(char));
                    strcpy(temp->comparechar, cleanWord(word));
                }
                memset(word, 0, strlen(word));
                word[0] = -1;
                count++;
                continue;
            }
            //when complete a word before comma
            if ((special == 0 && c == ',') || (special == 0 && c == '\n') || (special == 0 && c == EOF)) {
                length = 0;
                //empty value
                //*********
                //numberic value
                //int
                if (count == 3 || count == 4 || count == 5 || count == 6 || count == 8 || count == 9 || count == 13 ||
                    count == 14 || count == 16 || count == 19 || count == 23 || count == 24 || count == 25 ||
                    count == 28) {
                    c = atoi(word);
                    //*******************************************************************Add Int*******************************************************
                    //compare criteria
                    if (count == com && word[0] == -1) {
                        temp->compareint = -1;

                    } else if (count == com && word[0] != -1) {
                        temp->compareint = c;
                    }
                    temp = add(temp, count, word);
                    temp->empty = 1;


                }
                    //double
                else if (count == 26 || count == 27) {

                    sscanf(word, "%lf", &c2);

                    //*******************************************************************Add Double*******************************************************

                    //compare criteria

                    if (count == com && word[0] == -1) {
                        temp->comparedouble = -1;

                    } else if (count == com && word[0] != -1) {
                        temp->comparedouble = c2;
                    }

                    temp = add(temp, count, word);
                    temp->empty = 1;

                } else {
                    //*******************************************************************Add String*******************************************************
                    if (word[0] == -1) {
                        memset(word, 0, strlen(word));
                    }
                    temp = add(temp, count, cleanWord(word));
                    temp->empty = 1;
                    //compare criteria
                    if (count == com) {
                        temp->comparechar = malloc((strlen(word) + 5) * sizeof(char));
                        strcpy(temp->comparechar, cleanWord(word));
                    }
                }
                //reset count
                count++;

                if (count == 29) {

                    count = 1;
                    temp->next = (struct film *) malloc(sizeof(struct film));

                    temp = temp->next;
                }

                memset(word, 0, strlen(word));
                word[0] = -1;
            }
                //reading characters
            else {
                word[length] = c;
                length++;
            }
        }
    }
    if (com == 3 || com == 4 || com == 5 || com == 6 || com == 8 || com == 9 || com == 13 || com == 14 || com == 16 ||
        com == 19 || com == 23 || com == 24 || com == 25 || com == 28) {
        mergeint(&movie);
    }
    if (com == 26 || com == 27) {
        mergedouble(&movie);
    } else {
        mergestring(&movie);
    }
    temp = movie;
    while (temp->next) {
        temp = temp->next;
    }

    struct list *result = (struct list *) malloc(sizeof(struct list));
    result->start = movie;
    result->end = temp;

//Critical section!!!
    pthread_mutex_lock(&m);
    linkedlists[countlists] = result;
    countlists++;
    //check if data structure need resizing
    if (numoflists == countlists) {
        numoflists = numoflists * 2;
        linkedlists = realloc(linkedlists, sizeof(struct list *) * numoflists);
    }
    pthread_mutex_unlock(&m);
//Critical section Ends!!!!
    pthread_exit(NULL);
}


void *dirthread(void *in) {
    pthread_mutex_lock(&p);
    printf("%lu,", pthread_self());
    pthread_mutex_unlock(&p);
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
    printf("Initial PID:%d\n", getpid());
    printf("TIDS of all child threads:");

    threads = malloc((sizeof(pthread_t *) * (2000)));
//***********************************************************MAIN***************************************************************************
    linkedlists = malloc((sizeof(struct list *) * (2000)));
//*****************************************Command Line Checking*****************************************
    char *inputpath;
    char *outputpath;
    char *column;
    if (argc != 7 && argc != 9 && argc != 11) {
        printf("Incorrect Input\n");
        return 0;
    }
    if (argc == 7) {
        inputpath = ".";
        outputpath = ".";
        column = argv[2];
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
    }
//*****************************************Command Line Checking Complete{FINNALLY!!!}*****************************************
//calculate sorting criteria
    int com;
    com = comparestring(column);
    if (com == 0) {
        printf("error\n");
        return 0;
    }

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

        s = 0;
//Integrate all data structures
        while (linkedlists[s]) {
            if (linkedlists[s + 1]) {
                linkedlists[s]->end->next = linkedlists[s + 1]->start;
            }
            s++;
        }

//Final Sort
        if (com == 3 || com == 4 || com == 5 || com == 6 || com == 8 || com == 9 || com == 13 || com == 14 ||
            com == 16 || com == 19 || com == 23 || com == 24 || com == 25 || com == 28) {
            mergeint(&linkedlists[0]->start);
        }
        if (com == 26 || com == 27) {
            mergedouble(&linkedlists[0]->start);
        } else {
            mergestring(&linkedlists[0]->start);
        }

        outputpath = repath(outputpath, "/");
        outputpath = repath(outputpath, "AllFiles-sorted-<");
        outputpath = repath(outputpath, column);
        outputpath = repath(outputpath, ">.csv");
        print(linkedlists[0]->start, "./out.csv");
//close
        free(threads);
        freelist(linkedlists[0]->start);
        closedir(d);
    }
    printf("\nTotal number of threads:%d\n", (numoftotalthreads + 1));
    return 0;
}




