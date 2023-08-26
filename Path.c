#include "main.h"
/**
* Path_PU8_GetEnv - gets a global variable from environment
* @Copy_PU8_Var: The global variable
* Return: Pointer to the variable, NULL otherwise
*/

char *Path_PU8_GetEnv(char *Copy_PU8_Var)
{
	char *Local_PU8_Token, *Local_PU8_Dup, *Local_PU8_TokDup;
	int Local_U32_Counter = 0;

	if (environ == NULL)
		return (NULL);
	if (Copy_PU8_Var != NULL)
	{
		Local_PU8_Dup = String_PU8_StrDup(environ[Local_U32_Counter]);
		for (Local_U32_Counter = 0; Local_PU8_Dup != NULL; )
		{
			Local_PU8_Token = strtok(Local_PU8_Dup, "=");
			if (String_PU8_StrCmp(Local_PU8_Token, Copy_PU8_Var) == 0)
			{
				Local_PU8_Token = strtok(NULL, "=");

				Local_PU8_TokDup = String_PU8_StrDup(Local_PU8_Token);
				free(Local_PU8_Dup);
				return (Local_PU8_TokDup);
			}
			free(Local_PU8_Dup);
			Local_U32_Counter++;
			Local_PU8_Dup = String_PU8_StrDup(environ[Local_U32_Counter]);
		}
	}
	return (NULL);
}

/**
* Path_U32_CheckPath - checks existence of file
* @Copy_PU8_Path: input path to the file
* Return: 0 if the file exist, -1 otherwise
*/
int Path_U32_CheckPath(char *Copy_PU8_Path)
{
	int Local_U32_Status;

	Local_U32_Status = (open(Copy_PU8_Path, O_RDONLY));
	if (Local_U32_Status != -1)
	{
		close(Local_U32_Status);
		return (0);
	}
	else
		return (-1);
	}

/**
* Path_U32_GetPath - get command path from environment
* @Copy_PU8_Command: the command line
*
* Return: 0 if success, -1 otherwise
*/
int Path_U32_GetPath(char **Copy_PU8_Command)
{
	char *Local_PU8_EnvPath = NULL, *Local_PU8_Dup = NULL,
		*Local_PU8_CommPath = NULL, *Local_PU8_FullPath = NULL;

	Local_PU8_EnvPath = Path_PU8_GetEnv("PATH");
	if (Local_PU8_EnvPath == NULL)
		return (-1);
	Local_PU8_Dup = (String_PU8_StrDup(Local_PU8_EnvPath));
	Local_PU8_CommPath = strtok(Local_PU8_Dup, ":");
	if (Local_PU8_CommPath == NULL)
		return (-1);
	free(Local_PU8_EnvPath);
	while (Local_PU8_CommPath != NULL)
	{
		Local_PU8_FullPath = String_PU8_StrConcat(Local_PU8_CommPath,
			Copy_PU8_Command[0]);
		if (Path_U32_CheckPath(Local_PU8_FullPath) == 0)
		{
			Copy_PU8_Command[0] = Local_PU8_FullPath;
			free(Local_PU8_FullPath);
			free(Local_PU8_Dup);
			return (0);
		}
		free(Local_PU8_FullPath);
		Local_PU8_CommPath = strtok(NULL, ":");
	}
	free(Local_PU8_Dup);
	return (-1);
}
