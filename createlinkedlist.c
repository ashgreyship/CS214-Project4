
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
    char column[35];
    char ip[255];
    column[0]=-1;
    int com;
   
    while ((c = content[read]) != '<')
    {   
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
        if(c=='~'){
            strcpy(column,word);
            com=comparestring(column);
            memset(word,0,strlen(word));
            word[0]=-1;
            read++;
        }
        if(column[0]==-1){
            word[read]=c;
            read++;
            continue;
        }
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
    printf("IP adderss is :%s\n",ip );
    return movie;
}
