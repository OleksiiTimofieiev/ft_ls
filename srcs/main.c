#include "../includes/ft_ls.h"

#include <stdio.h> // for snprintf;

// if from last month -> year without time;

// flags management;
// ls -laRrt
// ls -l -a -r -t ... -> adopt to the list of directories to be worked out;
// parse and use;
// flags = // struct options;

// manage errors: func to detect cyrcular link; work out if have the link;
// errors in dev directory;
// work with errors from Liubomir
// chmod 000 -> no rights
// not exists
// dev -> last directories;

// redo snprintf;

// hex in dev;

// link -> dir, hindu has the solution
// ➜  ft_ls git:(master) ✗ ls -laR /etc
// lrwxr-xr-x@ 1 root  wheel  11 Mar  4  2018 /etc -> private/etc

// ➜  ft_ls git:(master) ✗ ls -la LinkDir
// lrwxr-xr-x  1 otimofie  2017  3 Nov  3 15:01 LinkDir -> Dir

// ➜  ft_ls git:(master) ✗ ls -la LinkDir/
// total 0
// drwxr-xr-x   2 otimofie  2017    68 Nov  3 15:01 .
// drwxr-xr-x  36 otimofie  2017  1224 Nov  4 15:47 ..

// drwx------+   5 otimofie  2017        170 Aug 29 14:11 

// norminette;

void	listdir(char *name/*, int indent  flags */) // ? go from the first element of the list;
{
	DIR *dir;
	struct dirent *entry;
	t_temp *list;
	t_temp *t_list;
	char path[1024];
	char *path2; // make in ono init func
	char *buffer;

	init_path2(&path2, name);
	if (!(dir = opendir(name))) // separate func;
	{
		free(path2);
		ft_printf("error->>>>>>>>>>>>>>\n");
		perror("open");
		return ;
	}
	list = NULL; // to more general func above // add to func above;
	while ((entry = readdir(dir)) != NULL)
	{
		buffer = ft_strjoin(path2, entry->d_name);
		add(&list, entry->d_name, entry->d_type, get_stats(buffer));
		free(buffer);
	}
	q_sort(&list);
	print_list(list);
	t_list = list;
	while(t_list)
	{
		if (t_list->type_and_permissions_data[0] == 'd')
		{
			if (ft_strcmp(t_list->d_name, ".") == 0 || ft_strcmp(t_list->d_name, "..") == 0)
			{
				t_list = t_list->next;
				continue ;
			}
			snprintf(path, sizeof(path), "%s/%s", name, t_list->d_name);
			ft_printf("\n%s:\n", path); 
			listdir(path);
		}
		t_list = t_list->next;
	}
	ft_dump_cleaner(&list, &path2, &dir);
}

int		main(int argc, char **argv)
{
	int		arguments_quantity;

	if (argc == 1)
		listdir(".");
	else
	{
		arguments_quantity = 1;
		while (arguments_quantity < argc)
			listdir(argv[arguments_quantity++]);
	}
	system("leaks -q ft_ls");
	return (0);
}


