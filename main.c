#include "main.h"

void shit(int *Local_U32_ExitStat, int *Local_U32_BuiltinStat,
int Local_U32_Counter, char *Local_PU8_Line, char *Local_PU8_Args[])
{
	int Local_U32_PathStat;

	Local_U32_PathStat = Path_U32_GetPath(Local_PU8_Args);
	if (Local_U32_PathStat != 0)
	{
		*Local_U32_BuiltinStat = Execution_U32_ChechBuiltin(
		Local_PU8_Args, *Local_U32_ExitStat);
		if (Local_U32_BuiltinStat != 0)
		{
			*Local_U32_ExitStat = Error_U32_Print(Local_PU8_Args, Local_U32_Counter);
			free(Local_PU8_Line);
		}
	}
	else
		*Local_U32_ExitStat = Execution_U32_Execute(Local_PU8_Args),
		free(Local_PU8_Line), free(*Local_PU8_Args);
}
/**
 * main - main shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	size_t Local_size_BuffSize = 0;
	ssize_t Local_ssize_ByteNum = 0;
	char *Local_PU8_Line = NULL, *Local_PU8_Args[20];
	int Local_U32_FileStat = 0, Local_U32_Counter = 1,
	Local_U32_BuiltinStat = 0, Local_U32_ExitStat = 0;

	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);
	Local_ssize_ByteNum = getline(&Local_PU8_Line, &Local_size_BuffSize, stdin);
	while (Local_ssize_ByteNum != -1)
	{
		if (*Local_PU8_Line == '\n')
			free(Local_PU8_Line);
		else if (*Local_PU8_Line != '\n')
		{
			String_U32_StrSplit(Local_PU8_Line, Local_PU8_Args);
			if (Local_PU8_Args[0] == NULL)
				free(Local_PU8_Line);
			else
			{
				Local_U32_FileStat = Path_U32_CheckPath(Local_PU8_Args[0]);
				if (Local_U32_FileStat == 0)
					Local_U32_ExitStat = Execution_U32_Execute(Local_PU8_Args),
						free(Local_PU8_Line);
				else
					shit(&Local_U32_ExitStat, &Local_U32_BuiltinStat,
						Local_U32_Counter, Local_PU8_Line, Local_PU8_Args);
			}
		}
		Local_U32_Counter++;
		Local_PU8_Line = NULL;
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		Local_ssize_ByteNum = getline(&Local_PU8_Line, &Local_size_BuffSize, stdin);
	}
	Memory_Void_FreePU8(Local_PU8_Line);
	return (Local_U32_ExitStat);
}
