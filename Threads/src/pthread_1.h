/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#ifndef __P_THREAD_1_H__
#define __P_THREAD_1_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD 5

static pthread_once_t once_control = PTHREAD_ONCE_INIT;

typedef struct s_ThreadArg
{
    int         m_id;
    char        m_msg[256];
}s_ThreadArg;

void runOnceOnly()
{
    printf("I am executed by thread %ld\n", (long)pthread_self());
}

void threadFun(void *threadArg)
{
    s_ThreadArg *arg = (s_ThreadArg *)threadArg;
    
    if(arg)
    {
        pthread_once(&once_control, runOnceOnly);
        
        printf("I am alive with id #%d, and actual id = %ld\n", arg->m_id, (long)pthread_self());
        sprintf(arg->m_msg, "My actual id is %ld", (long)pthread_self());
    }
    else
    {
        printf("ERROR : arg is NULL.\n");
    }
    
    pthread_exit((void *)arg);
}

int main(int argc, char **argv)
{
    pthread_t threads[NUM_THREAD];
    int i, rc;
    size_t stackSize;
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    pthread_attr_getstacksize(&attr, &stackSize);
    printf("The default stack size is %li\n", (long)stackSize);
    
    
    pthread_attr_setstacksize(&attr, stackSize * 10);
    pthread_attr_getstacksize(&attr, &stackSize);
    printf("The new stack size is %li\n", (long)stackSize);
    
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for(i = 0; i < NUM_THREAD; ++i)
    {
        printf("Main : creating new thread #%d\n", i);
        
        s_ThreadArg *arg = malloc(sizeof(s_ThreadArg));
        memset(arg, 0, sizeof(s_ThreadArg));
        arg->m_id = i;
        if( (rc = pthread_create(&threads[i], &attr, threadFun, (void *)arg)) != 0)
        {
            printf("ERROR : thread create error code %d\n", rc);
            exit(-1);
        }
    }
 
    pthread_attr_destroy(&Attr);    // Clean up code
    
    printf("All thread created\n");
    s_ThreadArg *argArray[NUM_THREAD];
    
    for(i = 0; i < NUM_THREAD; ++i)
    {
        if( (rc = pthread_join(threads[i], &argArray[i])) != 0 )
        {
            printf("ERROR: join error code = %d\n", rc);
            exit(-1);
        }
        printf("Msg from thread %d is : %s\n", i, argArray[i]->m_msg);
    }
    
    pthread_exit(NULL);
    return 0;
}

#endif //#ifndef __P_THREAD_1_H__