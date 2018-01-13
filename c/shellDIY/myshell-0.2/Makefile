src/Myshell:
	@echo start compiling MyShell...
	(cd ./src;make)
	(cd ./src;mv MyShell ../)
	@echo compiling end,now you can type \"./MyShell\" to run MyShell
clean:
	@echo rm .o file...
	(cd ./src;make clean)
	@echo rm end.
install:
	@echo install \"MyShell\"...
	mv ./MyShell /bin/
	@echo install end.you can uninstall to mv \"MyShell\".
uninstall:
	rm  -f /bin/MyShell
