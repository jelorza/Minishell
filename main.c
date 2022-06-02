#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

// gcc -lreadline main.c para compilar todo

int	main(void)
{
	const char *str = "enter";
	
	while (strcmp("exit", str))
	{
		str = readline("proyectX@jon % ");
		printf("%s\n",str);
	}
	return (0);
}
