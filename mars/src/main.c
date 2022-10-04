#include "../include/common.h"
#include "test/inc/test.h"
#include <getopt.h>
//#include <popt.h>   //TODO using popt

/* Flag set by ‘--verbose’. */
static int verbose_flag;

#define VERSION "0.1"

typedef void (*fun_ptr)(int);

static void usage(void)
{
   fprintf(stderr,
	"marswalker [option]... URL\n"
	"  -f|--force               Don't wait for reply from server.\n"
	"  -r|--reload              Send reload request - Pragma: no-cache.\n"
	"  -t|--test                Run test.\n"
	"  -p|--proxy <server:port> Use proxy server for request.\n"
	"  -c|--clients <n>         Run <n> HTTP clients at once. Default one.\n"
	"  -9|--http09              Use HTTP/0.9 style requests.\n"
	"  -1|--http10              Use HTTP/1.0 protocol.\n"
	"  -2|--http11              Use HTTP/1.1 protocol.\n"
	"  --get                    Use GET request method.\n"
	"  --head                   Use HEAD request method.\n"
	"  --options                Use OPTIONS request method.\n"
	"  --trace                  Use TRACE request method.\n"
	"  -?|-h|--help             This information.\n"
	"  -V|--version             Display program version.\n"
	);
};

int main(int argc, char **argv) {
    int c;
    
    if(argc == 1) {
        usage();
        return 2;
    }

    int option_index = 0;

    /* getopt_long stores the option index here. */
    static struct option long_options[] = {
            /* These options set a flag. */
            {"verbose",     no_argument, &verbose_flag, 1},
            {"brief",       no_argument, &verbose_flag, 0},
            /* These options don’t set a flag.
                We distinguish them by their indices. */
            {"add",         required_argument, 0, 'a'},
            {"append",      no_argument, 0, 'b'},
            {"delete",      required_argument, 0, 'd'},
            {"create",      required_argument, 0, 'c'},
            {"file",        required_argument, 0, 'f'},
            {"help",        no_argument, 0, 'h'},
            {"version",     no_argument, NULL, 'v'},
            {"test",     no_argument, NULL, 't'},
            {0, 0, 0, 0}};

    while((c = getopt_long(argc, argv, "a:bc:d:f:hvt", long_options, &option_index)) != -1) {
        switch (c) {
        case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0)
                break;
            printf("option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;

        case 'a':
            puts("run linked list\n");
            optind--;
            for(; optind < argc && *argv[optind] != ' '; optind++) {
                printf("%s\n", argv[optind]);
            }
            break;

        case 'b':
            puts("option -b\n");
            break;

        case 'c':
            printf("option -c with value `%s'\n", optarg);
            break;

        case 'd':
            printf("option -d with value `%s'\n", optarg);
            break;

        case 'f':
            printf("option -f with value `%s'\n", optarg);
            break;

        case '?':
            break;

        case 'h':
            usage();
            break;

        case 'v':
            printf("version: %s\n", VERSION);
            break;

        case 't':
            printf("run test ...\n");
            //void (*fun_ptr)() = &quicksort_2;
            fun_ptr x = &quicksort;
            x(999);
            break;

        default:
            abort();
        }
    }

    //(*fun_ptr)();
    //x();

    /* Instead of reporting ‘--verbose’
        and ‘--brief’ as they are encountered,
        we report the final status resulting from them. */
    if (verbose_flag)
        puts("verbose flag is set");

    //printf("argc = %d\n", argc);
    //printf("optind = %d\n", optind);

    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        putchar('\n');
    }

    //create_linkedlist(argv[]);

    exit(0);
}