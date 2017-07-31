CC=gcc
CFLAGS= -Wall -O2
LINK=-lreadline -ltermcap
OBJ= main.o init_shell.o get_shell_path.o init_command.o print_prompt.o \
	read_cmd.o split_command.o find_file.o  do_cmd.o do_redirect.o \
	do_pipeline.o do_internal_cmd.o do_li.o do_cd.o  do_help.o \
	do_pwd.o history_cmd.o current_exit.o exit_shell.o

object=MyShell
$(object):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $(object) $(LINK)
main.o:main.c 
	$(CC) $(CFLAGS)  -c $<   -o $@ 
init_shell.o :init_shell.c 
	$(CC) $(CFLAGS) -c $<  -o $@  
get_shell_path.o : get_shell_path.c 
	$(CC) $(CFLAGS) -c $<   -o $@  
init_command.o : init_command.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
print_prompt.o : print_prompt.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
read_cmd.o : read_cmd.c 
	$(CC) $(CFLAGS) -c $<   -o $@  
split_command.o : split_command.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
find_file.o : find_file.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
do_cmd.o : do_cmd.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
do_redirect.o : do_redirect.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
do_pipeline.o : do_pipeline.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
do_internal_cmd.o : do_internal_cmd.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
do_li.o : do_li.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
do_cd.o : do_cd.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
do_help.o : do_help.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
do_pwd.o : do_pwd.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
history_cmd.o : history_cmd.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
current_exit.o : current_exit.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 
exit_shell.o : exit_shell.c 
	$(CC) $(CFLAGS) -c $<   -o $@ 

clean:
	rm -f *.o

