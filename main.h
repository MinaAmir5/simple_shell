#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>

extern char **environ;

int String_PU8_StrCmp(char *str1, char *str2);
int Path_U32_GetPath(char **arguments);
int Execution_U32_ChechBuiltin(char **arguments, int exit_stat);
char *Path_PU8_GetEnv(char *global_var);
char *String_PU8_StrDup(char *str);
char *String_PU8_StrConcat(char *dir_path, char *command);
void Memory_Void_FreePU8(char *entry);
int String_U32_StrSplit(char *entry, char **arguments);
int Error_U32_Status(int n);
int Error_U32_Print(char **arguments, int counter);
int String_U32_PutChar(char c);
int Path_U32_CheckPath(char *pathname);
int Execution_U32_Execute(char **arguments);
void Memory_Void_FreePPU8(char **grid, int heigth);

#endif
