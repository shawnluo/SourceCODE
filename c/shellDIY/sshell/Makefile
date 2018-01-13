sshell: sshell.h sshell.c type_prompt.c read_command.c setup_command.c parsing.c
	gcc sshell.c type_prompt.c read_command.c setup_command.c parsing.c -o sshell #-D DEBUG


sshell_readline: sshell.h sshell.c type_prompt.c read_command.c setup_command.c parsing.c test
	gcc sshell.c type_prompt.c read_command.c setup_command.c parsing.c -o sshell -D READLINE_ON -I /usr/include -lreadline -ltermcap


test: test.c
	gcc test.c -o test

clean:
	rm -f sshell test
