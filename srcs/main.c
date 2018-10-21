#include "../includes/ft_ls.h"

int		main(void)
{
	DIR		*dir;
	struct dirent	*sd;

	dir = opendir(".");

	if (dir == NULL)
	{
		ft_printf("Can not open the directoty\n");
		exit(1);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		ft_printf(">> %s\n", sd->d_name);		
	}

	closedir(dir);
	return (1);
}


