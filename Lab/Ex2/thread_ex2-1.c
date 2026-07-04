/*
 * thread_ex2.c
 *
 * Simple example of creating multiple threads.
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* Define a data structure type that is used to create variables
 * to pass parameters to threads.
*/
 typedef struct
 {
	 int a;
	 int b;
	 int d;
 } app_data;

 /* This is the code for the thread.  It is not called directly
  * but passed as a parameter to pthread_create in the main thread.
  * Parameters are passed through the single void parameter.
 */
  void *thread_ex (void *data)
  {
	  int count = 1;
	  /* Type casting is used here to cast the void parameter
	   * to a pointer to a structure of type app_data.
	   */
	  app_data *td = (app_data*) data;

	  while (count <= td->b)
	  /* Thread executes for b times */
	  {
		  /* printf prints to the output (screen by default).
		   * The text to be printed is within quotes and may contain
		   * place-holders for printing the value of variables.
		   * %d is a place holder for an integer.
		   * Each place-holder is matched, in order, with the variables
		   * listed.  Here a is used as the thread number.
		   */
		  printf ("Thread %d, Iteration %d\n", td->a, count);
		  count++;

		  sleep(td->d);
		  /* Thread sleeps for d seconds */
	  }

	  printf ("Thread %d terminated\n", td->a);
	  return 0;
  }


int main(int argc, char *argv[]) {
	printf("Welcome to the QNX Momentics thread-ex2\n");
	pthread_t  th1, th2;
	app_data td1 = {1, 10, 2};
	app_data td2 = {2, 5, 3};

	void *retval;
	  /*
	   *  Shows how to create threads and pass parameters to them
	   * (in this case using a structure of type app_data).
	   *
	   * In this case the same function is used for each thread.
	   *
	   * Note that because the thread attributes parameter is NULL
	   * each thread starts with the default priority (10) and default
	   * scheduling strategy (round-robin).
	   */
	pthread_create (&th1, NULL, thread_ex, &td1);
	pthread_create (&th2, NULL, thread_ex, &td2);
	  /*
	   * Shows how to suspend main program (itself a thread)
	   * until all threads have terminated.
	   */
	pthread_join (th1, &retval);
	pthread_join (th2, &retval);

	printf ("Main terminated\n");

	return EXIT_SUCCESS;
}








