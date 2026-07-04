#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/dispatch.h>
#include <inttypes.h>	// for clock cycles calculation
#include <sys/neutrino.h>	// for clock cycles calculation
#include <sys/syspage.h>	// for clock cycles calculation


//#define ATTACH_POINT "myname"  // Not used in this example
#define BUF_SIZE 100  // size of reply message string

typedef struct
{
   struct _pulse hdr; // Our real data comes after this header
   int ClientID;      // our data (unique id from client)
   int data;          // our data <-- This is what where here for
} my_data;

typedef struct
{
   struct _pulse hdr;  // Our real data comes after this header
   char buf[BUF_SIZE]; // Message to send back to send back to other thread
} my_reply;

#define UseSleeps 0

void main( void )
{
  uint64_t cps, cycle1, cycle2, ncycles;     // Define variables used for timing
  double sec;

  name_attach_t *attach;
  my_data msg;                    // message structure
  my_reply replymsg;              // replymsg structure for sending back to client
  replymsg.hdr.type = 0x01;       // some number to help client process reply msg
  replymsg.hdr.subtype = 0x00;    // some number to help client process reply msg
  int rcvid=0, msgnum=0;          // no message received yet


  attach = ChannelCreate(_NTO_CHF_DISCONNECT);   // create the connection
//  attach = name_attach(NULL, ATTACH_POINT, 0);   // create the connection
  if(attach != NULL)
  {
	printf("Server Listening for Clients on:\n");
	printf("  --> Process ID   : %d \n", getpid());
	printf("  --> Channel ID   : %d \n\n", attach);
    while(1)
    {
       rcvid = MsgReceive(attach, &msg, sizeof(msg), NULL);
       if(rcvid == 0)              // A Pulse was received, workout what type
       {
         printf("Received a PULSE of type: %d\n", msg.hdr.code);
         if(msg.hdr.code == _PULSE_CODE_DISCONNECT)
         {
            printf("Received detach PULSE - Bye!\n");
            ConnectDetach(msg.hdr.scoid);
            break;
         }
       }
       else if(rcvid > 0)           // A message was received, workout what type
       {
     	 if(msgnum==0) cycle1=ClockCycles();  // Get Start TIME when the first message is received
         msgnum++;                  // keep track of how many message we receive
         printf("Received a MESSAGE of type: %d, ", msg.hdr.type);
         printf("with value of '%d' from client (ID:%d)", msg.data, msg.ClientID);
         sprintf(replymsg.buf, "Message %d received", msgnum);
         if(UseSleeps) sleep(1); // Delay the reply by a second (just for demonstration purposes)
         printf(" -> replying with: '%s'\n",replymsg.buf);
         MsgReply(rcvid, EOK, &replymsg, sizeof(replymsg));
       }
       else if(rcvid == -1)         // Error condition, exit
       {
         printf("\nFailed to MsgReceive\n");
         break;
       }
    }
    ChannelDestroy(attach);
    //name_detach(attach, 0);
  }
  cycle2=ClockCycles();                      // Get End TIME and preform time calc
  ncycles=cycle2-cycle1;
  cps = SYSPAGE_ENTRY(qtime)->cycles_per_sec;
  sec=(double)ncycles/cps * 1000;
  printf("This system has %lld cycles/sec.\n",cps );
  printf("Computation time = %f milliseconds.\n",sec);
  printf("Main (Server) Terminated....\n");
}
