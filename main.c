#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int	main(void)
{
	DIR		*dir;
	struct dirent	*sd;

	dir = opendir(".");

	if (dir == NULL)
	{
		printf("Can not open the directoty\n");
		exit(1);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		printf(">> %s\n", sd->d_name);		
	}

	closedir(dir);
	return (1);
}


