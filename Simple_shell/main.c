#include "main.h"
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
/* add unused to suppress unused errors*/
	char *prompt = "(Sshell) $ ";
/* implement getline function to get anything the user prints*/
	/* ssize_t getline(char **lineptr, size_t *n, FILE *stream-stdin,stout,stderr)*/
	char *lineptr;
	size_t n;

	n = 0;/*allocates a buff for string*/

	printf("%s", prompt);
	getline(&lineptr, &n, stdin);
	/*& passes value to getline*/
	printf("%s", lineptr);
	free(lineptr);/*free buffer*/

	return (0);
}
