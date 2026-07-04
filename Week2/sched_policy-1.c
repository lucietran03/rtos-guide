#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>

#define PRIORITY_ADJUSTMENT 5

void Get_thread_params(struct sched_param *p, int size)
{
	// clear param structure
	memset(p, '\0', size);
	int retcode = 0;

	// Find out what the current priority is
	retcode = sched_getparam(0, p);
	if (retcode !=0 )
		 printf("sched_getparam() ERROR: %s.\n", strerror(errno));

	// Find out what the scheduling policy for the current process is
	retcode = sched_getscheduler(0);
	if (retcode == -1)
	 	 printf("sched_getscheduler() ERROR: %s.\n", strerror(errno));
	else printf("The assigned scheduling policy for this process is %d.\n", retcode);

	printf("The assigned priority is %d.\n", p->sched_priority);
	printf("The current priority is %d.\n", p->sched_curpriority);
}

int main (void)
{
	int retcode = 0;
	errno = EOK; // Initialize the errno global value
	int max_priority=0, min_priority=0;
	struct sched_param param;

	// Find out the MAX/MIN priority for the FIFO scheduler
	min_priority = sched_get_priority_min(SCHED_FIFO);
	max_priority = sched_get_priority_max(SCHED_FIFO);
	printf("FIFO: max priority= %d, min priority= %d\n", max_priority, min_priority);

	Get_thread_params(&param, sizeof(param));

	sleep(1); // wait here for a bit (no real reason)

	// try to increase the priority of the thread by a set amount
	param.sched_priority = ((param.sched_curpriority + PRIORITY_ADJUSTMENT) <= max_priority)
		?
	(param.sched_curpriority + PRIORITY_ADJUSTMENT) : -1;

	if (param.sched_priority == -1) // check if we were successful
	{
		printf("param.sched_priority ERROR: %s.\n", strerror(errno));
		printf("Cannot increase the priority by %d. Try a smaller value\n", PRIORITY_ADJUSTMENT);
	}
	// set the scheduling policy FIFO
	retcode = sched_setscheduler(0, SCHED_FIFO, &param);
	if (retcode == -1)
	 	 printf("sched_setscheduler() ERROR: %s.\n", strerror(errno));

	Get_thread_params(&param, sizeof(param));

	printf("Main terminated\n");
	return EXIT_SUCCESS;
}
