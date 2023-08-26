#include "main.h"

/**
* Error_U32_Status - Prints error message
* @Copy_U32_ErrNum: Error number
* Return: the error status
*/
int Error_U32_Status(int Copy_U32_ErrNum)
{
	int Local_U32_Num;
	int Local_U32_Counter = 0;

	if (Copy_U32_ErrNum < 0)
	{
		Local_U32_Counter++;
		String_U32_PutChar('-');
		Local_U32_Num = -Copy_U32_ErrNum;
	}
	else
		Local_U32_Num = Copy_U32_ErrNum;
	if (Local_U32_Num / 10 != '\0')
		Local_U32_Counter = Local_U32_Counter + Error_U32_Status(Local_U32_Num / 10);
	String_U32_PutChar(Local_U32_Num % 10 + '0');
	Local_U32_Counter++;
	return (Local_U32_Counter);
}

/**
 * Error_U32_Print - prints error message
 * @Copy_PPU8_Args: inpust user command
 * @Copy_U32_Counter: shell counter
 * Return: Exit status
 */
int Error_U32_Print(char **Copy_PPU8_Args, int Copy_U32_Counter)
{
	int Local_U32_Counter = 0;

	if (isatty(STDIN_FILENO))
		write(2, "hsh: ", 5);
	else
		write(2, "./hsh: ", 7);
	Error_U32_Status(Copy_U32_Counter);
	write(2, ": ", 2);
	for (Local_U32_Counter = 0; Copy_PPU8_Args[0][Local_U32_Counter] != '\0';
		Local_U32_Counter++)
		;
	write(2, Copy_PPU8_Args[0], Local_U32_Counter);
	write(2, ": not found\n", 12);
	return (127);
}
