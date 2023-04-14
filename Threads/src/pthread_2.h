/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#ifndef __P_THREAD_2_H__
#define __P_THREAD_2_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    double  *a;
    double  *b;
    double  sum;
    int     veclen;
}sDOTDATA;

#define NUM_THREAD  5
#define VEC_LEN     100
sDOTDATA            g_dotstr;
pthread_mutex_t     g_mutex;

void* dotprod(void *threadArg)
{
    int start, end, len;
    long offset;
    double mysum = 0, *x = NULL, *y = NULL;
    
    offset = (long)threadArg;
    
    len = g_dotstr.veclen;
    start = offset*len;
    end = start + len;
    
    x = g_dotstr.a;
    y = g_dotstr.b;
    
    for(start; start < end; ++start)
    {
        mysum += (x[start] * y[start]);
    }
    
    pthread_mutex_lock(&g_mutex);
    g_dotstr.sum += mysum;
    pthread_mutex_unlock(&g_mutex);
    
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t threads[NUM_THREAD];
    long i;
    double *a = NULL, *b = NULL;
    
    a = (double *)malloc(NUM_THREAD * VEC_LEN * sizeof(double));
    b = (double *)malloc(NUM_THREAD * VEC_LEN * sizeof(double));
    
    for(i = 0; i < VEC_LEN * NUM_THREAD; ++i)
    {
        a[i] = 1.0;
        b[i] = a[i];
    }
    
    g_dotstr.veclen = VEC_LEN;
    g_dotstr.a = a;
    g_dotstr.b = b;
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_mutex_init(&g_mutex, NULL);
    
    for(i = 0; i < NUM_THREAD; ++i)
    {
        printf("Main : creating new thread #%ld\n", i);
        int rc;    
        if( (rc = pthread_create(&threads[i], &attr, dotprod, (void *)i)) != 0)
        {
            printf("ERROR : thread create error code %d\n", rc);
            exit(-1);
        }
    }
 
    pthread_attr_destroy(&attr);    // Clean up code

    for(i = 0; i < NUM_THREAD; ++i)
    {
        int rc;
        if( (rc = pthread_join(threads[i], NULL)) != 0 )
        {
            printf("ERROR: join error code = %d\n", rc);
            exit(-1);
        }
    }
    
    printf("The sum calculated by all thread is %f\n", g_dotstr.sum);
    
    free(a);
    free(b);
    
    pthread_mutex_destroy(&g_mutex);
    pthread_exit(NULL);
    return 0;
}
#endif //#ifndef __P_THREAD_1_H__