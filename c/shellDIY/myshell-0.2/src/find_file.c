/*输入:cmd－包含要执行的命令的数据
 ****shell_path－用户shel的环境变量
 ****current_path－shell命令解释器当前工作目录
 *输出:无
 *功能:搜索命令文件路径
 *作者：牛涛<niutao0602@gmail.com>
 *修改:
 */
#include"head.h"
extern char internal_cmd[INTERNAL_CMD_NUM][5];
void find_file( Command *cmd,char *current_path,char *shell_path[] )
{
	int i,j;
	int is_internal_cmd;
	Command *L=cmd;

	while( L!=NULL )  {/*start while*/
		for( i=0;i<MAX_CMD_NUM&&cmd->cmd[ i ] !=NULL;i++ )  {/*start for*/
			is_internal_cmd=0;
			for( j=0;j<INTERNAL_CMD_NUM;j++ )
				if( strcmp( cmd->cmd[ i ],internal_cmd[ j ] ) ==0 )  {
					strcpy( cmd->cmd_path[ i ],"internal_cmd" );
					is_internal_cmd=1;
				}
				
			if( is_internal_cmd )
				continue;

			strcpy( cmd->cmd_path[ i ],current_path );
			strcat( cmd->cmd_path[ i ],"/" );
			strcat( cmd->cmd_path[ i ],cmd->cmd[ i ] );

			if( ( access( cmd->cmd_path[ i ],F_OK|X_OK ) ) ==-1 )  {
				strcpy( cmd->cmd_path[ i ],cmd->cmd[ i ] );
				strcat( cmd->cmd_path[ i ],":No such application file!..." );
			} else
				continue;

			for( j=0;j<SHELL_PATH_NUM&&shell_path[ j ] !=( char* ) NULL;j++ )  {
				memset( cmd->cmd_path[ i ],'\0',CMD_PATH_LEN );
				strcpy( cmd->cmd_path[ i ],shell_path[ j ] );
				strcat( cmd->cmd_path[ i ],"/" );
				strcat( cmd->cmd_path[ i ],cmd->cmd[ i ] );

				if( ( access( cmd->cmd_path[ i ],F_OK|X_OK ) ) ==-1 )  {
					strcpy( cmd->cmd_path[ i ],cmd->cmd[ i ] );
					strcat( cmd->cmd_path[ i ],
						":No such application file!..." );
				} else
					break;
			}
		}/*end for*/

		L=L->next_command;
	}/*end while*/

	return ;
}/*void find_file(Command *cmd,char *current_path,char *shell_path[])*/

