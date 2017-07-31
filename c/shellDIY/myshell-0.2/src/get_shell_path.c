/*输入：shell_path－－保存shell环境变量
 *输出：无
 *功能：取得shell环境变量并分割。
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
void get_shell_path( char **shell_path )
{
	char path[ MAX_READ_LEN ];
	char strtok_str[] = ":";
	char *p,*s_path=path;
	int len=0;

	if( ( s_path=getenv( "PATH" ) ) ==NULL )  {
		perror( "getenv" );
		exit( ERROR );
	}

	strcpy( path,s_path );
	p = strtok(  path, strtok_str );

	for( len=0;p!=NULL&&len<SHELL_PATH_NUM;len++ )  {
		shell_path[ len ] =( char * ) malloc( strlen( p ) *sizeof( char ) );

		if( !shell_path[ len ] )  {
			fprintf( stderr,"malloc error!...\n" );
			exit( ERROR );
		}

		strcpy( shell_path[ len ],p );
		p=strtok( NULL,strtok_str );
	}

	shell_path[ len ] =NULL;
	return;
}/*void get_shell_path(char *shell_path[])*/
