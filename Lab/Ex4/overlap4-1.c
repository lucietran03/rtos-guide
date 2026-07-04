/*
 * see: Protecting Your Data in a Multi-Threaded App, by John Fehr
 * http://www.qnx.com/developers/articles/article_301_2.html
 *
 * overlap4.c
 *
 * See "Protecting Your Data in a Multi-Threaded App"
 *
 *  Uses reader and writer lock (rwlock) to ensure safety (result is correct)
 *  and has two separate threads using a and b
 *
 *  Here the subtracter_thread and the user_thread can read the data at the same
 *  time, but the changer_thread can't access the data at the same time as either
 *  the subtracter_thread or the user_thread.
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

 typedef struct {
  int a;
  int b;
  int result;
  int result2;
  int use_count;
  int use_count2;
  int max_use;
  int max_use2;
  pthread_rwlock_t rwl; // add a Rwlock into the structure we want to protect
} app_data;


void *subtracter_thread(void *data)
{
	int use=0;
	app_data *td=(app_data*)data;
	while(use<td->max_use2)
	{
		pthread_rwlock_rdlock(&td->rwl);	//Implement Read_lock
		if (td->a==50)
		{
			td->result2-=(td->a+td->b);
			use++;
			td->use_count2++;
		}
		pthread_rwlock_unlock(&td->rwl);	//Unlock_read_lock
		usleep(1);
	}
	return 0;
}


void *user_thread(void *data)
{
	 int uses=0;
	 app_data *td=(app_data*)data;
	 while(uses<td->max_use)
	 {
		 pthread_rwlock_rdlock(&td->rwl);	//Implement Read_lock
		 if (td->a==5)
		 {
			 td->result+=(td->a+td->b);
			 td->use_count++;
			 uses++;
		 }
		 pthread_rwlock_unlock(&td->rwl);	//Unlock_read_lock
		 usleep(1);
	 }
	 return 0;
}

void *changer_thread(void *data)
{
	 app_data *td=(app_data*)data;
	 while ((td->use_count+td->use_count2)<(td->max_use+td->max_use2))
	 {
		 pthread_rwlock_wrlock(&td->rwl);	//Implement Read-Write_lock
		 if (td->a==5)
		 {
			 td->a=50;
			 td->b=td->a+usleep(1000);
		 }
		 else
		 {
			 td->a=5;
			 td->b=td->a+usleep(1000);
		 }
		 pthread_rwlock_unlock(&td->rwl);	//Unlock_Read-Write_lock
		 usleep(1);
	 }
	 return 0;
}

int main(int argc, char *argv[]) {
	printf("Welcome to the QNX Momentics IDE\n");

	pthread_t ct,ut,st;
	app_data td={5,5,0,0,0,0,100,100};		// changed the max_use2 value from 0 (in previous examples) to 100
	void *retval;

	// Create the Rwlock
	pthread_rwlock_init(&td.rwl,NULL);			// pass NULL as the attr parameter to use the default attributes

	pthread_create(&ut,NULL,user_thread,&td);
	pthread_create(&ct,NULL,changer_thread,&td);
	pthread_create(&st,NULL,subtracter_thread,&td);

	// wait for all threads to finish
	pthread_join(ct,&retval);
	pthread_join(ut,&retval);
	pthread_join(st,&retval);

	// Destroy the Rwlock
	 pthread_rwlock_destroy(&td.rwl);

	// print results
	printf("result should be %d, is %d\n",td.max_use*(5+5),td.result);
	printf("result2 should be %d, is %d\n",-(td.max_use2*(50+50)),td.result2);

	printf("\nMain Terminating....");
	return EXIT_SUCCESS;
}
