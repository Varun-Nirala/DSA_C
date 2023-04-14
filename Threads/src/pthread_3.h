/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#ifndef __P_THREAD_3_H__
#ifndef __P_THREAD_3_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3
#define TCOUNT      10
#define COUNT_LIMIT 12

int g_count = 0;
int g_thread_ids[NUM_THREADS] = {0,1,2};

pthread_mutex_t g_count_mutex;
pthread_cond_t  g_count_threshold_cv;

void* inc_count(void *t)
{
    int i;
    long my_id = (long)t;
    
    for(i = 0; i < TCOUNT; ++i)
    {
        pthread_mutex_lock(&g_count_mutex);
        g_count++;
        
        /*
        Check the value of count and signal waiting thread when condition is 
        reached. Note that this occurs while mutext is locked.
        */
        
        if(g_count == COUNT_LIMIT)
        {
            pthread_cond_signal(&g_count_threshold_cv);
            printf("inc_count: thread %ld, count = %d, i = %d, threadshold reached.\n", my_id, g_count, i);
        }
        
        printf("inc_count: thread %ld, count = %d, i = %d unlocking mutex.\n", my_id, g_count, i);
        pthread_mutex_unlock(&g_count_mutex);
        
        // Do some work so threads can alternate on mutex lock
        sleep(1);
    }
    
    pthread_exit(NULL);
}

void *watch_count(void *t)
{
    long my_id = (long)t;
    
    printf("Starting watch_count(): thread %ld\n", my_id);
    
    /*
    Lock mutex and wait for signal. Note that the pthread_cond_wait 
    routine will automatically and automatically unlock mutex while it waits.
    Alos, note that if COUNT_LIMIT is reached before this routine is run by
    waiting thread, the loop will be skipped to prevent pthread_cond_wait
    from never returning.
    */
    pthread_mutex_lock(&g_count_mutex);
    while(g_count < COUNT_LIMIT)
    {
        pthread_cond_wait(&g_count_threshold_cv, &g_count_mutex);
        printf("watch_count(): thread %ld count now is %d\n", my_id, g_count);
    }
    g_count += 125;
    printf("watch_count(): thread %ld count now = %d\n", my_id, g_count);
    pthread_mutex_unlock(&g_count_mutex);

    pthread_exit(NULL);
    
}

int main(int argc, char *argv[])
{
    int i, rc;
    long t1 = 1, t2 = 2, t3 = 3;
    
    pthread_t threads[NUM_THREADS];
    
    pthread_attr_t attr;
    
    pthread_mutex_init(&g_count_mutex, NULL);
    pthread_cond_init(&g_count_threshold_cv, NULL);
    pthread_attr_init(&attr);
    
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_create(&threads[0], &attr, watch_count, (void *)t1);
    pthread_create(&threads[1], &attr, inc_count, (void *)t2);
    pthread_create(&threads[2], &attr, inc_count, (void *)t3);
    
    for(int i = 0; i<  NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    
    printf("Main: Waited on %d threads. Done. \n", NUM_THREADS);
    
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&g_count_mutex);
    pthread_cond_destroy(&g_count_threshold_cv);
    
    pthread_exit(NULL);
return 0;
}
#endif //#ifndef __P_THREAD_1_H__