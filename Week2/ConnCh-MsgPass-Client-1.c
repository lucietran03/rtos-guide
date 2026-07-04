#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/dispatch.h>
#include <inttypes.h>	// for clock cycles calculation
#include <sys/neutrino.h>	// for clock cycles calculation
#include <sys/syspage.h>	// for clock cycles calculation


//#define ATTACH_POINT "myname"  // Not used in this example - Need to put the PID of the server in on line 40
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

  my_data msg;
  my_reply reply;
  msg.ClientID = 600;      // unique number for this client
  msg.hdr.type = 0x22;     // We would have pre-defined data to stuff here
  msg.hdr.subtype = 0x00;  // more stuff we can define
  int server_coid=0, i=0;

  int serverPID  = 90133;	// CHANGE THIS Value to PID of the server process
  int	serverCHID = 1;		// CHANGE THIS Value to Channel ID of the server process (typically 1)

  printf("       --> on process ID: %d\n",   serverPID);
  printf("       --> on channel ID: %d\n\n", serverCHID);
  //printf("  ---> Trying to connect to server named: %s\n", ATTACH_POINT);

  cycle1=ClockCycles();                      // Get Start TIME

  server_coid = ConnectAttach(0, serverPID, serverCHID, 0, 0);
  //server_coid = name_open(ATTACH_POINT, 0);  // Open connection
  if (server_coid == -1)
  {
    printf("\n    ERROR, could not connect to server!\n\n");
    return 1;
  }


  if(server_coid != -1)
  {
     printf("Connection established to server with PID: %d Ch: %d\n", serverPID,serverCHID);
	 //printf("Connection established to: %s\n", ATTACH_POINT);
     for(i=0; i < 5; i++) // send data packets
     {
        msg.data = 10+i;   // Make some data to send
        // the data we are sending is in msg.data
        printf("Client (ID:%d), sending data: %d ", msg.ClientID, msg.data);

        if(MsgSend(server_coid, &msg, sizeof(msg), &reply, sizeof(reply)) == -1)
        {
           printf(" Error sending data '%d' to server\n", msg.data);
           // maybe we did not get a reply from the server
           break;
        }
        else
        {                 // now process the reply
           printf(" --> Reply from server is: '%s'\n", reply.buf);
        }
        if(UseSleeps) sleep(1);         // wait a second before sending the next data packet
     }
     printf("Client (ID:%d), sending PULSE requesting server to close connection\n", msg.ClientID);
     ConnectDetach(server_coid);
     //name_close(server_coid);
  }
  cycle2=ClockCycles();                      // Get End TIME and preform time calc
  ncycles=cycle2-cycle1;
  cps = SYSPAGE_ENTRY(qtime)->cycles_per_sec;
  sec=(double)ncycles/cps * 1000;
  printf("This system has %lld cycles/sec.\n",cps );
  printf("Computation time = %f milliseconds.\n",sec);
  printf("Main (Client) Terminated....\n");
}
