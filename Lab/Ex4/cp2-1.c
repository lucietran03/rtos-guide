/*
 * Modified Conditional Variables Example
 *
 * Very simple producer-consumer example
 * showing use of condition variables
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int data_ready = 0;

typedef struct
{
	 char ch;
	 int bit;
	 pthread_mutex_t mutex;  // needs to be set to PTHREAD_MUTEX_INITIALIZER;
	 pthread_cond_t condvar; // needs to be set to PTHREAD_COND_INITIALIZER;
}app_data;

void *consumer(void *Data)
{
    printf("->Consumer thread started...\n");

    app_data *tdc = (app_data*) Data;

    while(1)
	{
        pthread_mutex_lock(&tdc->mutex);

		// test the condition and wait until it is true
        while(!data_ready)
		{
            pthread_cond_wait(&tdc->condvar, &tdc->mutex);
        }

		// process data
        printf("consumer:  got data from producer : %c\t%i\n", tdc->ch, tdc->bit);

		// now change the condition and signal that it has changed
        data_ready = 0;
        pthread_cond_signal(&tdc->condvar);
        pthread_mutex_unlock(&tdc->mutex);
    }
}

void *producer(void *Data)
{
    printf("->Producer thread started...\n");

    // initialize the fake data:
    app_data *tdp = (app_data*) Data;
	tdp->ch = '@';
	tdp->bit = 0;

	data_ready = 1;

    while(1)
	{
        pthread_mutex_lock(&tdp->mutex);

        // get data from hardware
        // we'll simulate this with a just incrementing the data and use sleep(1) to simulate time lag
    	tdp->ch++;
    	tdp->bit++;
        sleep(1);

        printf ("producer:  Data(%c,%i) from simulated h/w ready\n",tdp->ch, tdp->bit);


		// test the condition and wait until it is true
        while(data_ready)
        {
        	pthread_cond_wait(&tdp->condvar, &tdp->mutex);
        }

		// now change the condition and signal that it has changed
        data_ready = 1;
        pthread_cond_signal(&tdp->condvar);
        pthread_mutex_unlock(&tdp->mutex);
    }
}


int main(int argc, char *argv[])
{
	printf("Welcome to the QNX Momentics Conditional Variables Example\n");

	// set up location for data
	data_ready = 0;

	// initialize the data, mutex and condvar
	app_data data = {0,0,PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};

    printf("Starting consumer/producer example...\n");

	pthread_t  th1, th2;
    
    // create the producer and consumer threads
    pthread_create(&th1, NULL, producer, &data);
    pthread_create(&th2, NULL, consumer, &data);

    // let the threads run for a bit
    sleep(20);

	printf("\nMain Terminating....");
	return EXIT_SUCCESS;
}
