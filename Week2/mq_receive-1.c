//  2020 update for multi node IPC using mqueues - new path name convention
#include <stdio.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>


#define  MESSAGESIZE 1000

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

void main( void )
{
  mqd_t qd;                               // Declare mqueue object
  char  buf[MESSAGESIZE] = {};            // buffer

  struct mq_attr attr;                    // struct containing message queue's attributes

  qd = mq_open(MqueueLocation, O_RDONLY);  // Open a connection to a known location
  if(qd != -1)
  {
     mq_getattr(qd, &attr);       // Get the attributes of the mqueue (from the sender)
     printf ("max. %u msgs, %u bytes; waiting: %u\n",
                                        attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

     while (mq_receive(qd, buf, MESSAGESIZE, NULL) > 0)
     {
        printf("Received from mqueue: '%s'\n", buf);
        if (!strcmp(buf, "done")) // Check if the message indicates we got the last msg
            break;                // "done" is the expected value for the last msg
     }
     mq_close(qd);                // Close message queue connection
  }
  else
  {
      printf("Error %i: %s\n", errno, strerror(errno));
  }
  printf("Receive Process Terminated...\n");
}

