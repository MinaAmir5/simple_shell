#include "main.h"

/**
 *Memory_Void_FreePPU8 - Free allocated memory
 *@Copy_PPU_P2P: pointer to pointer
 *@Copy_U32_Size: size of the pointer
 */
void Memory_Void_FreePPU8(char **Copy_PPU_P2P, int Copy_U32_Size)
{
	int Local_U32_Counter = 0;

	if (Copy_PPU_P2P == NULL)
		return;
	for (Local_U32_Counter = 0; Local_U32_Counter < Copy_U32_Size;
		Local_U32_Counter++)
		free(Copy_PPU_P2P[Local_U32_Counter]);
}

/**
 * Memory_Void_FreePU8 - Free allocated memory
 * @Copy_PU8_Array: Input array
 */
void Memory_Void_FreePU8(char *Copy_PU8_Array)
{
	if (isatty(STDIN_FILENO))
		String_U32_PutChar('\n');
	free(Copy_PU8_Array);
}
