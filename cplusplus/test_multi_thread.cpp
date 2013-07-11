#include "stdio.h"
#include "stdlib.h"
#include <pthread.h>

int f = 0;
int x=  0;

void* t1(void*)
{
        while(f==0)
        {
                if(x!=0) printf("error");
        }
        return NULL;
};

void* t2(void*)
{
        x=1;
        f=1;
        return NULL;
};


int main(void)
{
         pthread_t* worker =  (pthread_t*) malloc(2*sizeof( pthread_t));
         pthread_create(&worker[0],NULL,t1,NULL);
         pthread_create(&worker[1],NULL,t2,NULL);

         pthread_join(worker[0],NULL);
         pthread_join(worker[1],NULL);

         free(worker);

        return 0;

}

