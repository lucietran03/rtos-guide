#include <cstdlib>
#include <iostream>

#include <unistd.h>      // used for Cpp version of program
#include <string>
#include <sys/syspage.h> // for number of CPUs

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Welcome to the QNX Momentics IDE" << endl;

	// This is a sample 'QNX C++ Project'

	// You can use it to test if you have correctly setup a QNX C++ project.
	
	cout << endl; // print a blank line to the console

	// get the number of CPUs
	int num_cpus;
	num_cpus = _syspage_ptr -> num_cpu;
	cout << "--> Number of CPUs available is: "<< num_cpus << endl;

	cout << "--> The pid of this process is " << getpid() << endl;

	char hostnm[100];
    memset(hostnm, '\0', 100);
    hostnm[99] = '\n';
    gethostname(hostnm, sizeof(hostnm));

	cout << "--> Machine hostname is: " << hostnm << endl;

	cout << endl;

	sleep(10); // wait here for 10 seconds

	// Your test code can go here

	// ...

	// end program

	string str = "All good. Main Terminating.";

	cout << str << endl;

	return EXIT_SUCCESS;
}

