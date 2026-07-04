/*
 * How to get the current information about resource utilization
 * 
 * From http://www.qnx.com/developers/docs/660/index.jsp?topic=%2Fcom.qnx.doc.neutrino.lib_ref%2Ftopic%2Fg%2Fgetrusage.html
 * and  http://www.openqnx.com/phpbbforum/viewtopic.php?t=7715
 * 
 */
#include <sys/time.h>
#include <stdio.h>

#define RUSAGE_SELF 0
#define RUSAGE_CHILDREN -1

typedef struct rusage
{
	struct timeval ru_utime; // user time used
	struct timeval ru_stime; // system time used
	long ru_maxrss;   // max resident set size
	long ru_ixrss;    // integral shared memory size
	long ru_idrss;    // integral unshared data size
	long ru_isrss;    // integral unshared stack size
	long ru_minflt;   // page reclaims
	long ru_majflt;   // page faults
	long ru_nswap;    // swaps
	long ru_inblock;  // block input operations
	long ru_oublock;  // block output operations
	long ru_msgsnd;   // messages sent
	long ru_msgrcv;   // messages received
	long ru_nsignals; // signals received
	long ru_nvcsw;    // voluntary context switches
	long ru_nivcsw;   // involuntary switches
} rusage;

main()
{
	int who = RUSAGE_SELF;
	struct rusage usage;
	int ret;

	ret = getrusage(who, &usage);

	printf("result %d\n", ret);

	printf("user time used %d sec %d usec\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
	printf("system time used %d sec %d usec\n", usage.ru_stime.tv_sec, usage.ru_utime.tv_usec);

	printf("max resident set size %d\n", usage.ru_maxrss);
	printf("integral shared memory size %d\n", usage.ru_ixrss);
	printf("integral unshared data %d\n", usage.ru_idrss);
	printf("integral unshared stack %d\n", usage.ru_isrss);
	printf("page reclaims %d\n", usage.ru_minflt);
	printf("page faults %d\n", usage.ru_majflt);
	printf("swaps %d\n", usage.ru_nswap);
	printf("block input operations %d\n", usage.ru_inblock);
	printf("block output operations %d\n", usage.ru_oublock);
	printf("messages sent %d\n", usage.ru_msgsnd);
	printf("messages received %d\n", usage.ru_msgrcv);
	printf("signals received %d\n", usage.ru_nsignals);
	printf("voluntary context switches %d\n", usage.ru_nvcsw);
	printf("involuntary %d\n", usage.ru_nivcsw);
}
