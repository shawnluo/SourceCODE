#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <unistd.h>

#include <string.h>

#include <errno.h>

struct itimerval interval;
struct sigaction act;
struct itimerval curr_value;

#define DelayTime    4
#define Interval     1

void handler_sigvalrm(int signo)
{
    //getitimer (ITIMER_VIRTUAL, &curr_value, NULL);
    static i = 0;

    if (!i)
    {
        printf("First, after %ds... \n", DelayTime);
        getitimer(ITIMER_VIRTUAL, &curr_value);
		printf("%d\t%d\n", curr_value.it_interval.tv_sec, curr_value.it_value.tv_sec);
    }
    else
    {
        printf("%ds after...\n", Interval);
    }
    i++;

    if (i == 5)
    {
        exit(0);
    }
}




int main()
{
    act.sa_handler = handler_sigvalrm;


    interval.it_interval.tv_sec  = Interval;
    interval.it_interval.tv_usec = 0;
    interval.it_value.tv_sec     = DelayTime;
    interval.it_value.tv_usec    = 0;


    sigaction(SIGVTALRM, &act, NULL);
    setitimer(ITIMER_VIRTUAL, &interval, NULL);

	getitimer(ITIMER_VIRTUAL, &curr_value);
	printf("AFTER %d\t%d\n", curr_value.it_interval.tv_sec, curr_value.it_value.tv_sec);

    while (1)
    {
        ;
    }
    return(0);
}
