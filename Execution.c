#include "main.h"

/**
 * Execution_U32_Execute - Execute the given arguments
 * @Copy_PPU8_Command:Input command
 * Return: 0 if success
 */
int Execution_U32_Execute(char **Copy_PPU8_Command)
{
	int Local_U32_PID = 0;
	int stat = 0, Local_U32_Status = 0;

	Local_U32_PID = fork();
	if (Local_U32_PID == 0)
	{
		if (execve(Copy_PPU8_Command[0], Copy_PPU8_Command, environ) == -1)
		{
			perror("hsh");
			Local_U32_Status = 126;
			exit(Local_U32_Status);
		}
		exit(0);
	}
	else if (Local_U32_PID == -1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "failed\n", 7);
	}
	else
		wait(&stat);
	return (WEXITSTATUS(stat));
}

/**
 * Execution_U32_ChechBuiltin - Check if command is a builtin
 * @Copy_PPU8_Command: input user command
 * @Copy_U32_Exit: Current exit status
 * Return: -1 if builtin, 0 otherwise
 */
int Execution_U32_ChechBuiltin(char **Copy_PPU8_Command, int Copy_U32_Exit)
{
	char *Local_PU8_Exit = "exit", *Local_PU8_Env = "env";
	int Local_U32_Counter = 0, Local_U32_Counter2 = 0, Local_U32_Counter3 = 0;
	char *Local_PU8_Ptr = Copy_PPU8_Command[0];

	for (Local_U32_Counter = 0; Local_PU8_Ptr[Local_U32_Counter] != '\0';
		Local_U32_Counter++)
	{
		if (Local_PU8_Ptr[Local_U32_Counter] == Local_PU8_Exit[Local_U32_Counter])
			Local_U32_Counter2++;
		if (Local_PU8_Ptr[Local_U32_Counter] == Local_PU8_Env[Local_U32_Counter])
			Local_U32_Counter3++;
	}
	if (Local_PU8_Exit[Local_U32_Counter2] == '\0')
	{
		free(Copy_PPU8_Command[0]);
		exit(Copy_U32_Exit);
	}
	else if (Local_PU8_Env[Local_U32_Counter3] == '\0')
	{
		if (environ == NULL)
			return (0);
		write(1, environ, 1000);
	}
	else
		return (-1);
	return (0);
}
