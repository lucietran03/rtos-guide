#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <sys/syspage.h>
#include <malloc.h>

#include <inttypes.h>		// for clock cycles calculation
#include <sys/neutrino.h>	// for clock cycles calculation

#define ITERATIONS 50000000
#define NUM_THREADS 6

#define TRUE 1
#define FALSE 0

void *calculate_pi(void *threadID)
{
	double i;
    double pi;
    int add = 0;

    pi = 4;
    for (i = 0; i < ITERATIONS; i++)
    {
    	if (add == 1)
        {
    		pi = pi + (4/(3+i*2));
            add = 0;
        }
    	else
        {
    		pi = pi - (4/(3+i*2));
            add = 1;
        }
    }
    printf("pi from thread %d = %20lf in %20lf iterations\n", (int)threadID, pi, i);
    pthread_exit(NULL);
}


int LockThreads(int lock, int CPU)
{
	if(CPU > _syspage_ptr->num_cpu)
	{
		printf("ERROR - System does not have %d CPU cores\n", CPU);
		printf("Threads running on all available CPU cores\n\n");
		return 1;
	}
	if(lock==TRUE)
	{
		printf("Threads LOCKED to CPU core %d\n\n", CPU);
		int *rsizep, rsize, size_tot;
	    unsigned *rmaskp, *inheritp;
	    unsigned buf[8];
	    void *freep;

	    // struct _thread_runmask is not uniquely sized, so we construct our own.
	    rsize = RMSK_SIZE(_syspage_ptr->num_cpu);

	    size_tot = sizeof(*rsizep);
	    size_tot += sizeof(*rmaskp) * rsize;
	    size_tot += sizeof(*inheritp) * rsize;

	    if (size_tot <= sizeof(buf))
	    {
	    	rsizep = buf;
	    	freep = NULL;
	    }
	    else if ((rsizep = freep = malloc(size_tot)) == NULL)
	    {
	    	perror("malloc");
	    	return 1;
	    }

	    memset(rsizep, 0x00, size_tot);

	    *rsizep = rsize;
	    rmaskp = (unsigned *)(rsizep + 1);
	    inheritp = rmaskp + rsize;

	    // Both masks set to 0 means get the current values without alteration.
	    if (ThreadCtl(_NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT, rsizep) == -1)
	    {
	    	perror("_NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT");
	        free(freep);
	        return 1;
	    }

	    // Restrict our inherit mask to the last cpu; leave the runmask unaltered.
 	    memset(rsizep, 0x00, size_tot);
	    *rsizep = rsize;
	    RMSK_SET(CPU, inheritp);  // use the macro to set which CPU to lock thread too

	    if (ThreadCtl(_NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT, rsizep) == -1)
	    {
	    	perror("_NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT");
	        free(freep);
	        return 1;
	    }

	    free(freep);
	}
	else
		printf("Threads running on all available CPU cores\n\n");
}

int main( void )
{

	printf("Stress CPU test\n\n");

	LockThreads(TRUE, 1);  // Lock all process threads to CPU core #1

	// Variables for timing
	uint64_t cps, cycle1, cycle2, ncycles;
	double sec;

	cycle1=ClockCycles(); // start the timer

	// Start stressing the CPU cores - perform calculations
    pthread_t threads[NUM_THREADS];
    int rc;
    int i;

    for ( i = 0 ; i < NUM_THREADS; i++)
    {
    	rc = pthread_create(&threads[i], NULL, calculate_pi, (void *)i);
    	if (rc)
        {
    		printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    // wait for all threads to finish
    for ( i = 0 ; i < NUM_THREADS; i++)
    {
            pthread_join(threads[i], NULL);
    }

    // Calculate elapsed time
    cycle2=ClockCycles();
    ncycles=cycle2-cycle1;
    cps = SYSPAGE_ENTRY(qtime)->cycles_per_sec;
    sec=(double)ncycles/cps;

    printf( "\n\nThis system has %lld cycles/sec.\n",cps );
    printf("Stress test lasted for %f seconds.\n",sec);

    printf("Main Terminated...\n");
	return 0;
}




