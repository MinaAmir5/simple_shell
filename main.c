#include "main.h"
/**
 * main - Entry point for the simple shell project created
 * for ALX sprint one final Project.
 * Return: 0 on success
 */
int main(void)
{
	ssize_t bytes_rd = 0; /** Bytes read from a getline*/
	size_t bf_size = 0; /**Buffer size*/
	char *entry = NULL, *arguments[20]; /**String of args that enters the usr*/
	int counter = 1, vf_stat = 0, exist_stat = 0, exit_stat = 0, blt_stat = 0;

	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);
	bytes_rd = getline(&entry, &bf_size, stdin); /**sizeof entry, o -1 (EOF))*/
	while (bytes_rd != -1)
	{
		if (*entry != '\n')
		{
			String_U32_StrSplit(entry, arguments);
			if (arguments[0] != NULL)
			{
				exist_stat = Path_U32_CheckPath(arguments[0]);/*checks if the path entered exists*/
				if (exist_stat != 0)/**Did not find the file*/
				{
					vf_stat = Path_U32_GetPath(arguments);
					if (vf_stat == 0)
						exit_stat = Execution_U32_Execute(arguments), free(entry), free(*arguments);
					else
					{
					blt_stat = Execution_U32_ChechBuiltin(arguments, exit_stat);
					if (blt_stat != 0)
						exit_stat = Error_U32_Print(arguments, counter), free(entry);
					}
				}
				else /**Found the file*/
					exit_stat = Execution_U32_Execute(arguments), free(entry);
			}
			else
				free(entry);
		}
		else if (*entry == '\n')
			free(entry);
		entry = NULL, counter++;
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		bytes_rd = getline(&entry, &bf_size, stdin);
	}
	Memory_Void_FreePU8(entry);
	return (exit_stat);
}
