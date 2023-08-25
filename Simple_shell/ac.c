#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
/*	(void)argc;i*/
	int i = 0;

/*	printf("%d\n", argc)*/;
	while (*argv != NULL)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
		argv++;
		i++;
	}
	return (0);
}
