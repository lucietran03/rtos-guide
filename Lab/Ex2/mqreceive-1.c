/*  2020 update for multi node IPC using mqueues - new path name convention
 *
 *  mqreceive.c
 *
 *  Simple example of using mqueue messaging between processes
 *
 *  Run mqsend in one terminal window, then after a few messages
 *  are queued (less than 5) run mqreceive in another terminal window
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>

#define  MESSAGESIZE 1000

int main(int argc, char *argv[])
{
	printf("Welcome to the QNX Momentics mqueue receive process\n");

	mqd_t	qd;
	char	buf[MESSAGESIZE]= {};  // buffer needs to be bigger or same size as message being sent

	struct	mq_attr	attr;

	// example using the default path notation.
	const char * MqueueLocation = "/test_queue";
	//const char * MqueueLocation = "/net/VM_x86_Target02/test_queue";

	// http://www.qnx.com/developers/docs/7.0.0/#com.qnx.doc.neutrino.lib_ref/topic/m/mq_open.html
	// If you want to open a queue on another node, you have to use the traditional (mqueue) implementation
	// and specify the name as /net/node/mqueue_location. Here, node is the node name and mqeueue_location
	// is the device entry for the queue under /dev/mqueue (on the remote node). For instance, if you want
	// to open the queue at /dev/mqueue/mylocalqueue on a node named NTO1, you must use the name
	// /net/NTO1/mylocalqueue in calling mq_open().
	// Note the difference in the path syntax required for QNX SDP 7.0 as compared to earlier releases
	// (i.e., 6.X). In this later release, you must not include /dev/mqueue in the path of the message queue.
    	
	// NOTE: Use the above line for networked (qnet) MqueueLocation
	// the command 'hostname <name>' to set hostname. here it is 'M1'
	// You mast also have qnet running. to do this execute the following
	// command: mount -T io-pkt lsm-qnet.so

	
	qd = mq_open(MqueueLocation, O_RDONLY);		//MqueueLocation should be opened on the node where the queue was established
    if (qd != -1)
	{
		mq_getattr(qd, &attr);
		printf ("max. %ld msgs, %ld bytes; waiting: %ld\n", attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

		while (mq_receive(qd, buf, attr.mq_msgsize, NULL) > 0)  //wait for the messages
		{
			printf("dequeue: '%s'\n", buf);					//print out the messages to this terminal
			if (!strcmp(buf, "done"))			//once we get this message we know not to expect any more mqueue data
				break;
		}
		mq_close(qd);
	}
	else
	{
	  printf("Error %i: %s\n", errno, strerror(errno));
	}

	printf("mqueue receive process exited\n");
	return EXIT_SUCCESS;
}
