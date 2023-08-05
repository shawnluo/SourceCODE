

#include <stdio.h>
#include <stdlib.h>      /* exit */
#include <sys/time.h>    /* setitimer */
#include <unistd.h>      /* sleep */
#include <signal.h>      /* signal */

unsigned long elapsed_rsecs = 0;
unsigned long elapsed_vsecs = 0;
unsigned long elapsed_psecs = 0;
unsigned long elapsed_rmsecs;
unsigned long elapsed_vmsecs;
unsigned long elapsed_pmsecs;


void timer_expire(int signo)
{
    switch (signo)
    {
    case SIGALRM:
        ++elapsed_rsecs;
        break;

    case SIGVTALRM:
        ++elapsed_vsecs;
        break;

    case SIGPROF:
        ++elapsed_psecs;
        break;

    default:
        printf("Unexpected signal %d\n", signo);
    }
}

/*
 * set >= 1 to set the timer,
 * set =  0 to reset it
 */
int set_timer(int which, int set)
{
    struct itimerval r_itimer;
    struct itimerval r_o_itimer;
    unsigned long    ret;

    if (set > 0)
    {
        r_itimer.it_interval.tv_sec  = set;
        r_itimer.it_interval.tv_usec = 0;
        r_itimer.it_value.tv_sec     = set;
        r_itimer.it_value.tv_usec    = 0;

        switch (which)
        {
        case ITIMER_REAL:
            signal(SIGALRM, timer_expire);
            break;

        case ITIMER_VIRTUAL:
            signal(SIGVTALRM, timer_expire);
            break;

        case ITIMER_PROF:
            signal(SIGPROF, timer_expire);
            break;

        default:
            printf("Illegal type: %d\n", which);
            return -1;
        }
    }
    else
    {
        r_itimer.it_interval.tv_sec  = 0;
        r_itimer.it_interval.tv_usec = 0;
        r_itimer.it_value.tv_sec     = 0;
        r_itimer.it_value.tv_usec    = 0;

        switch (which)
        {
        case ITIMER_REAL:
            signal(SIGALRM, SIG_DFL);
            break;

        case ITIMER_VIRTUAL:
            signal(SIGVTALRM, SIG_DFL);
            break;

        case ITIMER_PROF:
            signal(SIGPROF, SIG_DFL);
            break;

        default:
            break;
        }
    }

    setitimer(which, &r_itimer, &r_o_itimer);

    printf("Previous itimer interval %d %d value %d %d\n",
           r_o_itimer.it_interval.tv_sec, r_o_itimer.it_interval.tv_usec,
           r_o_itimer.it_value.tv_sec, r_o_itimer.it_value.tv_usec);

    ret = r_o_itimer.it_value.tv_sec * 1000 +
          r_o_itimer.it_value.tv_usec / 1000;
    return ret;
}

int fibonacci(int n)
{
    FILE *fp;
    char line[128];

    if (n == 1 || n == 2)
    {
        return 1;
    }

#if 1
    fp = fopen("itimer.c", "r");
    while (fgets(line, 128, fp) != NULL)
    {                                   /* nothing */
        ;
    }
//	puts(line);
	
    fclose(fp);
#endif

    return fibonacci(n - 1) + fibonacci(n - 2);
}


int main(int argc, char **argv)
{
    int    i, j;
    double rtime, vtime, ptime;

    if (argc <= 1)
    {
        fprintf(stderr, "Usage: %s <list_of_integers> \n", argv[0]);
        exit(1);
    }

    set_timer(ITIMER_REAL, 1);
    set_timer(ITIMER_VIRTUAL, 1);
    set_timer(ITIMER_PROF, 1);

    for (i = 1; i < argc; ++i)
    {
        j = atoi(argv[i]);
        printf("Fibonacci(%d) = %d\n", j, fibonacci(j));
    }

    //sleep(100);
/*	while(1)
	{
	}
*/
    elapsed_pmsecs = set_timer(ITIMER_PROF, 0);
    elapsed_vmsecs = set_timer(ITIMER_VIRTUAL, 0);
    elapsed_rmsecs = set_timer(ITIMER_REAL, 0);

    rtime = elapsed_rsecs + elapsed_rmsecs / 1000.0;
    vtime = elapsed_vsecs + elapsed_vmsecs / 1000.0;
    ptime = elapsed_psecs + elapsed_pmsecs / 1000.0;

    printf("Real: %10.3f\nVirtual %10.3f\nProfile %10.3f\n",
           rtime, vtime, ptime);
}
