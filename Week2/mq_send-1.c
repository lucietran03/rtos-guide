//  2020 update for multi node IPC using mqueues - new path name convention
#include <stdlib.h>
#include <stdio.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <string.h>

#define  MESSAGESIZE 1000
#define  Q_FLAGS O_RDWR  | O_CREAT
#define  Q_Mode  S_IRUSR | S_IWUSR

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
  mqd_t qd;                  // Declare mqueue object
  char  buf[MESSAGESIZE] = {};   // buffer
  int   i = 0;

  struct  mq_attr  attr;         // struct containing message queue's attributes
  attr.mq_maxmsg  = 100;         // Maximum number of messages
  attr.mq_msgsize = MESSAGESIZE; // Maximum size of a message
  attr.mq_flags   = 0;
  attr.mq_curmsgs = 0;
  attr.mq_sendwait = 0;
  attr.mq_recvwait = 0;

  qd = mq_open(MqueueLocation, Q_FLAGS, Q_Mode, &attr); // Open a connection at /test_queue
  if(qd != -1)
  {
    for(i=1; i <= 5; ++i)
    {
      sprintf(buf, "message %d", i);           // Create the message packet
      printf ("Send to mqueue: '%s'\n", buf);  // print message being sent to console
      mq_send(qd, buf, MESSAGESIZE, 0);        // send message packet
      sleep(5);
    }
    mq_send  (qd, "done", 5, 0);               // send msg to tell client we are all done
    mq_close (qd);                             // Close the connection
    mq_unlink(MqueueLocation);                  // Remove a message queue
  }
  printf("Send Process Terminated...\n");
}

