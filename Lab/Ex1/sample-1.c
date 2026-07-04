#include <stdlib.h>
#include <stdio.h>

#include <sys/syspage.h> // for number of CPUs

int main(int argc, char *argv[])
{
	printf("Welcome to the QNX Momentics IDE\n");

	// This is a sample 'QNX C Project'

	// It will compile for x86 (i.e. VMs) and armv7 targets (BeagleBone Black, DE10, etc.).

	// To run the code on this Live image you will need to start VMware player and lunch one
	// of the provide QNX Targets or have an a QNX hardware target running on the same network
	// subnet as this machine (The host PC - which in this case is this Ubuntu VM). That is,
	// Momentics and the target need to be on the same IP subnet (eg. 192.168.xxx.xxx).
	//Your network could be setup differently, so you can use the command ifconfig to confirm
	// under linux/QNX or ipconfig under windows to confirm the IP address of the Host PC
	// (this VM/computer) and the QNX targets. You might have to set the VMs to Bridged mode
	// depending on your setup. More information can be found in the following PDF files:
	//    -  Quickstart_Guide.pdf
	//    -  IDE_Users_Guide.pdf
	//    -  Getting_Started_with_QNX_Neutrino.pdf
	//    -  The_QNX_Neutrino_Cookbook.pdf

	// Once the target/s are running you will need to add them to this project as a target.
	// You can do this by changing to the "QNX System Information" Perspective:
	//    Window->Perspective->Open Perspective->QNX System Information
	// Then right click in the left hand panel and select: 'New QNX Target...'
	// Enter the IP address of the target you want to deploy too.
	// To get back to this Perspective (i.e. C/C++), select:
	//    Window->Perspective->Open Perspective->C/C++

	// Once you have built the project, then you have to setup a 'Run Configuration':
	//    Run->Run Configurations...
	// See the page 16 of the Quickstart_Guide.pdf for the full details.

	// After launching this program to the QNX target, remember to press the stop button and
	// the 'x' button to clear the gdb console (bottom panel) after each lunch to the target.
	// Else the thread might still be running, and it can get confusing if you have multiple
	// threads launched to the same target.

	// Also if you are working off a Live DVD or Live USB, you will need to save your files
	// on another USB key before shutting down as your work will be lost.
	   // note: Every time you start QNX Momentics, it might be better to create a new
	   // directory workspace each time. That way you simply have a single workspace directory
	   // to backup when you finish.

	// After you are finished with a QNX Target, please remember to shut down each of the targets
	// your started by typing 'shutdown -b' at the prompt. If the target is a VM you can power it
	// down by selecting Power off selection from the drop down menu:
	// Virtual Machine -> Power -> Power Off Guest


	// Now for some test code
	printf("\n"); // print a blank line to the console

	// get the number of CPUs
	int num_cpus;
	num_cpus = _syspage_ptr -> num_cpu;
	printf ("--> Number of CPUs available is: %d\n", num_cpus);

	printf ("--> The pid of this process is %d\n", getpid() );

	char hostnm[100];
    memset(hostnm, '\0', 100);
    hostnm[99] = '\n';
    gethostname(hostnm, sizeof(hostnm));

	printf("--> Machine hostname is: '%s'\n", hostnm);

	printf("\n");

	sleep(10); // wait here for 10 seconds

	// Your test code can go here

	// ...

	// end program
	printf("All good. Main Terminating.\n");
	return EXIT_SUCCESS;
}

