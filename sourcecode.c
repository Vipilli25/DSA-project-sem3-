#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
#define db_size 100


struct tvshows{
	char name[30]; //(primary key)
	char first_telecast_date[20];
	int  total_eps;
	char telecast_days[10]; //(use array) - days like monday.. etc
	char original_release_date[10]; // (if it has been already telecasted on TV)
	char cast[30];
	char producer[30];
	char writer[30];
	char pro_comp[30];
};


struct Awards// (use separate structure to maintain details such as year, for which TV show or movies, use same fields as award category in movie structure)
{
		char title[30];
        int year;
        char for_the[30]; //for which TV show or movie,
        char category[30];
        int result;
};

struct movies{
    char name[30]; // (primary key)
    char release_date[10];
    char cast[30];
    char producer[30];
    char writer[30];
    char soundtrack[30];
    char pro_comp[50];
    char budget[20];
    char box_coll[20];
    struct Awards A;
    
}movies;

struct Cast{
    char name[50]; // (you can use separate structure to store personal information about star cast) (primary key)
    char tvshows[10];
    char movies[100];
    struct Awards A;
};

struct user{
    char id_no[50]; //(primary key)
    int sub_plan;   //no.of years    
    char sub_details[10];  // month or year
    char reg_date[10];     //  for month - integer [1== january..etc] for  year 4 digit integer [2021]
    struct sub_database{ //(use separate structure to maintain date and amount of subscription transactions till date.)
        char date[10];
        int amount;
    }sub_db;
    struct preferences{
        char language[10];
        char fav_genre[10];
    }pref;
    struct viewing_details{// (separate structure should be maintained for storing  shows/movies viewed, viewing time,rating given etc.)
        char movies_watched[100];
        int total_view_time;
    }vd[100];
    
};

void intialize_shows(struct tvshows s[])
{
	int i;
	for(i=0;i<db_size;i++)
    {
       s[i].name[0] = '\0';
       s[i].first_telecast_date[0] = '\0';
       s[i].total_eps = 0;
       s[i].telecast_days[0] = '\0';
       s[i].original_release_date[0] = '\0';
       s[i].cast[0] = '\0';
       s[i].producer[0] = '\0';
       s[i].writer[0] = '\0';
       s[i].pro_comp[0] = '\0';
    }
  
}

void intialise_movies(struct movies m[])
{
    int i=0;
    for(i=0;i<db_size;i++)
    {
        m[i].name[0] = '\0';
        m[i].release_date[0] = '\0';
        m[i].cast[0] = '\0';
        m[i].producer[0] = '\0';
        m[i].writer[0] = '\0';
        m[i].soundtrack[0] = '\0';
        m[i].pro_comp[0] = '\0';
        m[i].budget[0] = '\0';
        m[i].box_coll[0] = '\0';
        m[i].A.title[0] = '\0';
        m[i].A.year= 0;
        m[i].A.for_the[0] = '\0'; // for which TV show or Movie award is won
        m[i].A.category[0] = '\0';
        
    }
}

void intialise_cast(struct Cast c[])
{
   int i=0,SIZE;
   for(i=0;i<db_size;i++)
   {
    c[i].name[0]='\0';
    c[i].tvshows[SIZE];
    c[i].movies[SIZE];
    c[i].A.title[0]='\0';
    c[i].A.year=0;
    c[i].A.for_the[0]='\0';
    c[i].A.category[0]='\0';
   }
}

void intialise_user(struct user u[])
{
  int i=0;
  for(i=0;i<db_size;i++)
   {
       u[i].id_no[0] = 0;
       u[i].reg_date[0] = '\0';
       u[i].sub_details[0] = '\0';
       u[i].sub_plan = 0; //no of years
       u[i].sub_db.date[0] = '\0';
       u[i].sub_db.amount = 0;
       u[i].pref.language[0] = '\0';
       u[i].pref.fav_genre[0] = '\0';
       u[i].vd[i].movies_watched[0] = '\0';
       u[i].vd[i].total_view_time = 0;
   }
   
}

void intialize_Awards(struct Awards A[])
{
	int j;
	for (j=0;j<db_size;j++)
        {
          A[j].title[0]   ='\0'; 
          A[j].year    = 0; 
	      A[j].for_the[0] ='\0'; 
	      A[j].category[0] ='\0';
		  A[j].result = 0; 
     	}
}

int add_show(struct tvshows s[], char name[],char cast[],char pro_comp[],int size)//This function will return position at which record should be added in Tv_Show_DB and adds Tv_Show record in Tv_Show_Db
{
    int i=0,found =0,loc=0,stop=0;
    struct tvshows tmp;
    while(i<db_size&&!stop)
    {
        if(strcmp(s[i].name,name)>=0)
        {
            loc=i;
            stop=1;
        }
        i++;
    }
    for(i=size-1;i>=loc;i--)
    {
        s[i+1]=s[i];
    }
    i=loc;
    strcpy(s[i].name,name);
    strcpy(s[i].cast,cast);
    strcpy(s[i].pro_comp,pro_comp);
    return loc;
}
void add_show_cast(struct Cast c[],char name[],char cast_name[],int size)
{
    int i=0,stop=0,loc=0;
    while(i<db_size&&!stop)
    {
        if(strcmp(c[i].name,cast_name)>0||strcmp(c[i].name,"\0")==0)
        {
            loc=i;
            stop=1;
        }
        i++;
    }
    for(i=size-1;i>=loc;i--)
    {
        c[i+1]=c[i];
    }
    i=loc;
    strcpy(c[i].name,name);
    strcpy(c[i].tvshows,name);
}
//1a
void update_cast(struct tvshows s[],struct Cast c[],int loc,int size)
{
    int i=0,j=0,loc1=0,stop=0;
    int found=0;
    while(i<db_size&&!found)
    {
        if(strcmp(c[i].name,s[loc].cast)==0)
        {
            found=1;
            loc1=i;
        }
        i+=1;
    }
    if(found==1)
    {
        //update the fileds of the cast found
        strcpy(c[loc1].tvshows,s[loc].cast);
    }
    else
    {
        // add the new cast to the cast data base with their show given
        add_show_cast(c,s[loc].name,s[loc].cast,size);
    }
        
}
void add_mov(struct movies m[], char name[],char cast[],char title[],int year,int size)
{
    int i=0,found =0,loc=0,stop=0;
    
    while(i<db_size&&!stop)
    {
        if(strcmp(m[i].name,name)>=0)
        {
            loc=i;
            stop=1;
        }
        i++;
    }
    for(i=size-1;i>=loc;i--)
    {
        m[i+1]=m[i];
    }
    i=loc;
    strcpy(m[i].name,name);
    strcpy(m[i].cast,cast);
    strcpy(m[i].A.title,title);
    m[i].A.year=year;
}
int add_cast(struct Cast c[],char name[],char movies[],char title[] ,int year,int size )
{
    int i=0,found =0,loc=0,stop=0;
    struct Cast tmp;
    while(i<db_size&&!stop)
    {
        if(strcmp(c[i].name,name)>0||strcmp(c[i].name,"\0")==0)
        {
            loc=i;
            stop=1;
        }
        i++;
    }
    for(i=size-1;i>=loc;i--)
    {
        c[i+1]=c[i];
    }
    i=loc;
    strcpy(c[i].name,name);
    strcpy(c[i].movies,movies);
    strcpy(c[i].A.title,title);
    c[i].A.year=year;
    return loc;
}
int validate(struct movies m[],struct Cast c[],int loc)
{
    int i=0,found=0,status,loc1=0;
    while(i<db_size&&!found)
    {
        if(strcmp(m[i].name,c[loc].movies)==0)
        {
            found=1;
            loc1=i;
        }
        i++;
    }
    if(found==1&&m[loc1].A.year==c[loc].A.year&&strcmp(m[loc1].A.title,c[loc].A.title)==0)
    {
        status=1;
    }
    else
    {
        status=0;
    }
    return status;
}

//1b
//q1b
void add_user(struct user u[],char id_no[],char language[],char fav_genre[],int size)
{
    int i=0,found =0,loc=0,stop=0;
    struct user tmp;
    while(i<db_size&&!stop)
    {
        if(strcmp(u[i].id_no,id_no)>=0)
        {
            loc=i;
            stop=1;
        }
        i++;
    }
    for(i=size-1;i>=loc;i--)
    {
        u[i+1]=u[i];
    }
    i=loc;
    strcpy(u[i].id_no,id_no);
    strcpy(u[i].pref.language,language);
    strcpy(u[i].pref.fav_genre,fav_genre);
    i=0;
    while(i<db_size&&!stop)
    {
        if(strcmp(u[i].pref.language,u[loc].pref.language)==0)
        {
            int x;
            printf("%s",u[i].pref.fav_genre);
            printf("if u want to pick the genre enter 1 else enter 0\n");
            scanf("%d",x);
            if(x==1)
            {
                strcpy(u[loc].pref.fav_genre,u[i].pref.fav_genre);
            }
        }
        else
        {
            printf("Match not found \n");
        }
    }
}

//q2a
void list_by_cast(struct Cast c[],char cast[])
{
    int i=0,found=0,loc=0;
    while(i<db_size&&!found)
    {
        if(strcmp(c[i].name,cast)==0)
        {
            found=1;
            loc=i;
        }
        i++;
    }
    if(found==1)
    {
        printf("%s %s \n",c[loc].tvshows,c[loc].movies);
    }
    else
    {
        printf("Enterd cast is not found in data base\n");
    }

}
//q2c
void list_by_company(struct tvshows s[],struct movies m[],char cast[])
{
    int i=0,found=0,loc1=0,loc2=0;
    while(i<db_size&&!found)
    {
        if(strcmp(s[i].cast,cast)==0)
        {
            found=1;
            loc1=i;
        }
        i++;
    }
    i=0;
    int found1=0;
    while(i<db_size&&!found)
    {
        if(strcmp(m[i].cast,cast)==0)
        {
            found1=1;
            loc2=i;
        }
        i++;
    }
    if(strcmp(s[loc1].pro_comp,m[loc2].pro_comp)==0)
    {
        printf("%s %s \n",s[loc1].name,m[loc2].name);
    }
    else
    {
        printf("No production company produced a both Tv_show and Movie with the given cast\n");
    }
}
// q2 d
// sacnf movies name in main and call function
void list_by_movie_awd(struct movies m[],char movies[])
{
    int i,found=0,loc=0;
    while(i<db_size&&!found)
    {
        if(strcmp(m[i].name,movies)==0)
        {
            found=1;
            loc=i;
        }
    }
    if(found==1&&m[loc].A.result==1)
    {
        printf("%s \n",m[loc].A.title);
    }
    else
    {
        printf("No award won\n");
    }
}
//q3 a
void awd_question(struct Cast c[])
{
    int i=0,j=0,max,loc=0;
    struct Cast temp;
    max=c[0].A.year;
    while(i<db_size&&strcmp(c[i].name,"\0")!=0)
    {
       loc=i;
       j=i+1;
       while(j<db_size&&strcmp(c[j].name,"\0")!=0)
       {
            if(c[j].A.year>max)
            {
                loc=j;
                max=c[j].A.year;
            }
            j++;
        }

         temp=c[i];
         c[i]=c[loc];
         c[loc]=temp;
         i++;
    }
    i=0;
    while(i<db_size&&strcmp(c[i].name,"\0")!=0)
    {
        printf("%s %s %s %d \n",c[i].tvshows,c[i].movies,c[i].A.title,c[i].A.year);
        i++;
    }
}
//3b
void category_div(struct user u[])
{
    int i=0,j=0,max,loc=0;
    struct user temp;
    while(i<db_size&&u[i].id_no!=0)
    {
       loc=i;
       j=i+1;
       while(j<db_size&&u[i].id_no!=0!=0)
       {
            if(u[j].sub_plan>max)
            {
                loc=j;
                max=u[j].sub_plan;
            }
            j++;
        }

         temp=u[i];
         u[i]=u[loc];
         u[loc]=temp;
         i++;
    }
    i=0;
    while(i<db_size&&u[i].id_no!=0!=0)
    {
        if(u[i].sub_plan>3)
        {
            printf("%d platinum u \n",u[i].sub_plan);
        }
        else if(u[i].sub_plan<=3 && u[i].sub_plan>=1.5)
        {
            printf("%d gold u \n",u[i].sub_plan);
        }
        else if(u[i].sub_plan<1.5)
        {
            printf("%d silver u \n",u[i].sub_plan);
        }

        i++;
    }

}
//3c

//4b
void display_4b(struct tvshows s[],struct movies m[])
{
    int i=0,j=0,fd=0;
    while(i<db_size&&strcmp(s[i].name,"\0")==0)
    {
       int found=0;
       while(j<db_size&&strcmp(m[j].name,"\0")==0&&!found)
       {
           if(strcmp(s[i].cast,m[j].cast)==0)
           {
                printf("%s %s %s \n",s[i].name,m[j].name,s[i].cast);
                found=1;
                fd=1;
           }
           j++;
       }
       i++;
    }
    if(fd==0)
    {
        printf("Sorry !! match not found\n");
    }
}

int rec_in_cast_db(struct Cast c[])
{
    int size=1,i=0;
    while(i<db_size&&strcmp(c[i].name,"\0")!=0)
    {
        i++;
        size++;
    }
    return size;
}

//4a

void list_movie(struct tvshows s[],struct movies mov[])
{
    int i=0,j=0,exist=0;
    while(i<db_size&&strcmp(s[i].name,"\0")==0)
    {
       int found=0;
       while(j<db_size&&strcmp(mov[j].name,"\0")==0&&!found)
       {
           if(strcmp(s[i].cast,mov[j].cast)==0)
           {
                printf("%s %s %s \n",s[i].name,mov[j].name,s[i].cast);
                found=1;
                exist=1;
           }
           j++;
       }
       i++;
    }
    if(exist==0)
    {
        printf("No match found\n");
    }
}

int main()
{
    printf("\n\n******** WELCOME TO NETFLIX ********\n");
	
	 struct tvshows s[db_size];
	 struct movies m[db_size];
     struct Cast c[db_size];
     struct user u[db_size];
     char name[30], cast[30],pro_comp[50],movie_name[50], movies[50],title[50];
     int i,n,x,year,y,temp;
     
                    printf("Enter number of tv show records you want to add\n");
     				scanf("%d",&n);
     						for(i=0;i<n;i++)
     						{
       							//1a
       							printf("Enter the name of Tv Show\n");
       							scanf("%s",name);
       							printf("Enter the cast\n");
       							scanf("%s",cast);
       							x=add_show(s,name,cast,pro_comp,i+1);
       							update_cast(s,c,x,i+1);   						
       					    }
       					 		   
					printf("Enter number of movie records you want to add\n");
					scanf("%d",&n);
							for(i=0;i<n;i++)
							{
								//1c
       							printf("Enter the name of Movie\n");
       							scanf("%s",name);
       							printf("Enter the cast\n");
       							scanf("%s",cast);
       							printf("Enter the title of award\n");
       							scanf("%s",title);
       							printf("Enter award winning year \n");
       							scanf("%d",&year);
       							add_mov(m,name,cast,title,year,i+1);
       							
							}
					printf("Enter number of tv show records you want to add\n");
					scanf("%d",&n);		

							for(i=0;i<n;i++)
							{
								
       							printf("Enter the cast\n");
       							scanf("%s",name);
      							printf("Enter the movies\n");
       							scanf("%s",movie_name);
       							printf("Enter the title of award\n\n");
       							scanf("%s",title);
      							printf("Enter the year in which award is won \n");
       							scanf("%d",&year);
       							y=add_cast(c,name,movies,title,year,rec_in_cast_db(c));
       							temp=validate(m,c,y);
       							printf("%d",temp);
							}
	
						//2a
						printf("Enter the cast name for listing \n");
						scanf("%s",cast);
						list_by_cast(c,cast);
						
						//2b
						//2c
						printf("Enter the movie name for which u want to list award won\n");
						scanf("%s",cast);
						list_by_company(s,m,cast);
				      
				        //2d
                		printf("Enter the cast name for which u want to list Tv_show and movies produced by common producer\n");
						scanf("%s",cast);
						list_by_movie_awd(m,movies);
						
						
						 //3a
                         awd_question(c);
                         
                         //3b
                         category_div(u);
                         
                         //4b
                         list_movie(s,m);
                         
				                			
 	return 0;
}


