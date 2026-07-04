// Client 2020
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/dispatch.h>

// Define where the "local" attach point is located
#define LOCAL_ATTACH_POINT "myname"  // change myname to the same name used on the server code.
// You can also use the full QNET name in the Client if you want to test connections between
// different nodes on the same network:
//#define QNET_ATTACH_POINT  "/net/RMIT_BBB_v5_04/dev/name/local/myname"   // hostname using full path, change myname to the name used on the server
//#define QNET_ATTACH_POINT  "/net/cycloneV512_g01/dev/name/local/myname"  // hostname using full path, change myname to the name used on the server
//#define QNET_ATTACH_POINT  "/net/VM_x86_Target01/dev/name/local/myname"  // hostname using full path, change myname to the name used on the server

// Note: If you want to use global attach points, you need to start the GNS server on the server node
// and use the full attach point name under the "global" directory on the client. For example:
//#define GLOBAL_ATTACH_POINT  "/net/VM_x86_Target01/dev/name/global/myname"  // hostname using full path, change myname to the name used on the server
//#define GLOBAL_ATTACH_POINT  "/net/cycloneV512_g01/dev/name/global/myname"  // hostname using full path, change myname to the name used on the server
// Note: BeagleBone Black does not have a GNS server.

#define BUF_SIZE 100

typedef union {	  			// This replaced the standard:  union sigval
	union{
		_Uint32t sival_int;
		void *sival_ptr;	// This has a different size in 32-bit and 64-bit systems
	};
	_Uint32t dummy[4]; 		// Hence, we need this dummy variable to create space
}_mysigval;

typedef struct _Mypulse {   // This replaced the standard:  typedef struct _pulse msg_header_t;
   _Uint16t type;
   _Uint16t subtype;
   _Int8t code;
   _Uint8t zero[3];         // Same padding that is used in standard _pulse struct
   _mysigval value;
   _Uint8t zero2[2];		// Extra padding to ensure alignment access.
   _Int32t scoid;
} msg_header_t;

typedef struct {
   msg_header_t hdr;  // Custom header
   int ClientID;      // our data (unique id from client)
   int data;          // our data <-- This is what we are here for
} my_data;

typedef struct {
   msg_header_t hdr;   // Custom header
   char buf[BUF_SIZE]; // Message to send back to send back to other thread
} my_reply;

// prototypes
int client(char *sname);

int main(int argc, char *argv[])
{
	printf("_mysigval size= %d\n", sizeof(_mysigval));

	printf("header size= %d\n", sizeof(msg_header_t));
	printf("my_data size= %d\n", sizeof(my_data));
	printf("my_reply size= %d\n", sizeof(my_reply));

	printf("This is A Client running\n");

    int ret = 0;

    ret = client(LOCAL_ATTACH_POINT);  // use for local connection "myname"
  //ret = client(QNET_ATTACH_POINT);   // use for QNET local connection "myname"
  //ret = client(GLOBAL_ATTACH_POINT); // use for global connection only


	printf("Main (client) Terminated....\n");
	return ret;
}

/*** Client code ***/
int client(char *sname)
{
    my_data msg;

    my_reply reply; // replymsg structure for sending back to client

    msg.ClientID = 600;      // unique number for this client
    msg.hdr.type = 0x22;     // We would have pre-defined data to stuff here

    msg.ClientID = 600; 	 // unique number for this client

    int server_coid;
    int index = 0;

    printf("  ---> Trying to connect to server named: %s\n", sname);
    if ((server_coid = name_open(sname, 0)) == -1)
    {
        printf("\n    ERROR, could not connect to server!\n\n");
        return EXIT_FAILURE;
    }

    printf("Connection established to: %s\n", sname);

    // Do whatever work you wanted with server connection
    for (index=0; index < 5; index++) // send data packets
    {
    	// set up data packet
    	msg.data=10+index;

    	// the data we are sending is in msg.data
        printf("Client (ID:%d), sending data packet with the integer value: %d \n", msg.ClientID, msg.data);
        fflush(stdout);

        if (MsgSend(server_coid, &msg, sizeof(msg), &reply, sizeof(reply)) == -1)
        {
            printf(" Error data '%d' NOT sent to server\n", msg.data);
            	// maybe we did not get a reply from the server
            break;
        }
        else
        { // now process the reply
            printf("   -->Reply is: '%s'\n", reply.buf);
        }

        //sleep(5);	// wait a few seconds before sending the next data packet
    }

    // Close the connection
    printf("\n Sending message to server to tell it to close the connection\n");
    name_close(server_coid);

    return EXIT_SUCCESS;
}
