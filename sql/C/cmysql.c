
#include <stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<string.h>
#define INSERT_QUERY "INSERT INTO tblTest(text) values(?)"

int main(void)
{
	size_t break_point = 0;
	printf("Hello World!\n");
	MYSQL *conn;
	MYSQL mysql;
	MYSQL_RES *mysql_res;
	MYSQL_ROW *mysql_row;
	MYSQL_FIELD *mysql_field;
	MYSQL_STMT *mysql_stmt;
	unsigned int num_fields;
	const char * server = "localhost";
	const char *user = "wallace";
	const char *passwd = "";
	const char *dataBase = "test_db";
	const char *query_select = "select * from Persons";
	
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,passwd,dataBase,0,NULL,0))
	{
		fprintf(stdout,"Error connecting to Mysql: %s\n",mysql_error(conn));
	}
	
	int t = mysql_query(conn,query_select);
	if(t)   //t=0 means correct
	{
		fprintf(stderr,"Query error occurs:%s\n",mysql_error(conn));
	}

	mysql_res = mysql_use_result(conn);
	if(mysql_res == NULL)
	{
		fprintf(stderr,"Query error occurs: %s!\n",mysql_error(conn));
	}
	num_fields = mysql_num_fields(mysql_res);
	unsigned int num_rows = mysql_num_rows(mysql_res);
	printf("There're %d columns in the table tblTest\n",num_fields);
	
	//The code below won't return correct result until all rows in result_Set have been retieved
	printf("There're %d rows affected in the table tblTest\n",num_rows);
	mysql_field = mysql_fetch_fields(mysql_res);
	unsigned int i=0;
	for(i=0; i< num_fields; i++)
	{
		printf("Field %u is %s\t",i,mysql_field[i].name);
	}
	printf("\n");
	size_t i_temp=0;
	while((mysql_row=mysql_fetch_row(mysql_res)))
	{
		printf("The ID %d is %s\n",++i_temp,mysql_row[1]);
	}
	num_rows = mysql_num_rows(mysql_res);
	printf("There're %d rows affected in the table tblTest\n",num_rows); //Now ,it's correct

#if 0
	//Insert operation//////////////////////////////////////////////////////////////////////////
	if(!(mysql_stmt=mysql_stmt_init(conn)))
	{
		fprintf(stderr,"Statement initialization failed: %s\n",mysql_stmt_error(mysql_stmt));
		exit(0);
	}
	if(mysql_stmt_prepare(mysql_stmt,INSERT_QUERY,strlen(INSERT_QUERY))) //0 means correct
	{
		fprintf(stderr,"Statament preparation failed:%s and %s\n",mysql_error(conn),mysql_stmt_error(mysql_stmt));
		exit(0);
	}
	fprintf(stdout,"Init and preparation succeeded!\n");
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	char *ch = "test_in";
	int lengthCH = strlen(ch);
	bind[0].buffer_type = MYSQL_TYPE_VARCHAR;
	bind[0].buffer = ch;
	bind[0].is_null = 0;
	bind[0].length = &lengthCH;
	if (mysql_stmt_bind_param(mysql_stmt, bind))
	{
		fprintf(stderr, " mysql_stmt_bind_param() failed\n");
		fprintf(stderr, " %s\n", mysql_stmt_error(mysql_stmt));
		exit(0);
	}

	if(mysql_stmt_execute(mysql_stmt))
	{
		fprintf(stderr,"Execution failed:%s\n",mysql_stmt_error(mysql_stmt));
		exit(0);
	}
	my_ulonglong affected_rows= mysql_stmt_affected_rows(mysql_stmt);
	fprintf(stdout, " total affected rows(insert 1): %l\n",	(unsigned long) affected_rows);

	if (mysql_stmt_close(mysql_stmt))
	{
		fprintf(stderr, " failed while closing the statement\n");
		fprintf(stderr, " %s\n", mysql_stmt_error(mysql_stmt));
		exit(0);
	}
#endif
	//Insert opration success////////////////////////////////////////////////////////////
	mysql_close(conn);
	printf("End of the file\n");

	return 0;
}
