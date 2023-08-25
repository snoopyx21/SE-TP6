#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX 1000

void n_process(int descripteur_entree, int i )
{
    char buffer[MAX];
    int tube[2];   
    size_t n;
    int status;
 
    if( pipe(tube) == -1) perror("pipe");
    switch(fork())
    {
        case -1 : 
            perror("fork()");
            exit(1);
        case 0 :     
                if(i<= 0)
                {
                    if(close(tube[1]) == -1)
                    { 
                        perror("close");
                        exit(1);
                    }
            
                    while( (n=read(tube[0],buffer,MAX)) > 0 )
                    {
                        if ( write(1,buffer,n) == -1)
                        {
                            perror("write");    
                            exit(1);
                        }
                    }
                    if(close(tube[0]) == -1)
                    {
                        perror("close");
                        exit(1);
                    }
                }   
            else n_process(tube[0],i-1);
    
        default :
            if (close(tube[0]) == -1)
            {
                perror("close");
                exit(1);;
            } 
            while( (n=read(descripteur_entree,buffer,MAX)) > 0 )
            {
                if( write(tube[1],buffer,n) == -1)
                {
                    perror("write");
                    exit(1);
                }
            }
            if((wait(&status)) ==-1) 
            {
                perror("wait(&status");
                exit(0);
            }
    }
    exit(0);
}

int main(int i)
{
    char buffer[MAX];
    int tube[2];   
    size_t n;
    int status;
 
    if( pipe(tube) == -1) perror("pipe");
    switch(fork())
    {
        case -1 : 
            perror("fork()");
            return -1;
        case 0 :
                 
        default :
            if (close(tube[1]) == -1)
            {
                perror("close");
                return -1;
            } 
            while( (n=read(0,buffer,MAX)) > 0 )
            {
                if( write(1,buffer,n) == -1)
                {
                    perror("write");
                    return -1;
                }
            }
            if((wait(&status)) ==-1) perror("wait(&status");
    }
    return 0;
}
 
    return 0;
}
