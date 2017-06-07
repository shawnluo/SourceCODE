#include <ma_global.h>
#include <ma_sys.h>
#include <getopt.h>
#include <stdio.h>
#include <mariadb_version.h>

static char *mariadb_progname;

#define INCLUDE "-I/usr/local/include/mariadb -I/usr/local/include/mariadb/mysql"
#define LIBS    "-L/usr/local/lib/mariadb -lmariadb " \
                "-lpthread -ldl -lm -lssl -lcrypto"
#define LIBS_SYS "-lpthread -ldl -lm -lssl -lcrypto"
#define CFLAGS  INCLUDE "  -Wunused -Wno-uninitialized"
#define VERSION "10.1.7"
#define PLUGIN_DIR "/usr/local/mariadb/lib/plugin"
#define SOCKET  ""
#define PORT "3306"

static struct option long_options[]=
{
  {"cflags", no_argument, 0, 'a'},
  {"help", no_argument, 0, 'b'},
  {"include", no_argument, 0, 'c'},
  {"libs", no_argument, 0, 'd'},
  {"libs_r", no_argument, 0, 'e'},
  {"libs_sys", no_argument, 0, 'y'},
  {"version", no_argument, 0, 'f'},
  {"socket", no_argument, 0, 'g'},
  {"port", no_argument, 0, 'h'},
  {"plugindir", no_argument, 0, 'p'},
  {NULL, 0, 0, 0}
};

static char *values[]=
{
  CFLAGS,
  NULL,
  INCLUDE,
  LIBS,
  LIBS,
  LIBS_SYS,
  VERSION,
  SOCKET,
  PORT,
  PLUGIN_DIR
};
  
void usage(void)
{
  int i=0;
  puts("Copyright 2011-2015 MariaDB Corporation AB");
  puts("Get compiler flags for using the MariaDB Connector/C.");
  printf("Usage: %s [OPTIONS]\n", mariadb_progname);
  while (long_options[i].name)
  {
    if (values[i])
      printf("  --%-12s  [%s]\n", long_options[i].name, values[i]);
    i++;
  }
}


int main(int argc, char **argv)
{
  int c;
  mariadb_progname= argv[0];

  if (argc <= 1)
  {
    usage();
    exit(1);
  }

  while(1)
  {
    int option_index= 0;
    c= getopt_long(argc, argv, "abcdef", long_options, &option_index);

    switch(c) {
    case 'a':
      puts(CFLAGS);
      break;
    case 'b':
      usage();
      break;
    case 'c':
      puts(INCLUDE);
      break;
    case 'd':
    case 'e':
      puts(LIBS);
      break;
    case 'f':
      puts(VERSION);
      break;
    case 'g':
      puts(SOCKET);
      break;
    case 'h':
      puts(PORT);
      break;
    case 'p':
      puts(MARIADB_PLUGINDIR);
      break;
    case 'y':
      puts(LIBS_SYS);
      break;
    default:
      exit(0);
    }
  }

  exit(0);
}

