#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

/*
 * ??? mariadb??
 */
int main(int argc, char *argv[]) 
{
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(EXIT_FAILURE);
	}

	if (!mysql_real_connect(con, "localhost", "root", "", NULL, 0, NULL, 0)) 
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(EXIT_FAILURE);
	}  

	if (mysql_query(con, "show databases;")) 
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(EXIT_FAILURE);
	}

	puts("mariadb is connect and run succesed!");
	mysql_close(con);    

	return 0;
} 

