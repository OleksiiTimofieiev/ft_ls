#include "../includes/ft_ls.h"

// flags management;
// ls -laRrt
// ls -l -a -r -t ... -> adopt to the list of directories to be worked out;
// parse and use;
// flags = // struct options;
// no total if link, not a directory

// manage errors: func to detect cyrcular link; work out if have the link;
// errors in dev directory;
// work with errors from Liubomir
// chmod 000 -> no rights
// not exists
// dev -> last directories;

// redo snprintf;

// hex in dev;

// norminette;

#include <stdio.h>

void	listdir(char *name)
{
	DIR *dir;
	struct dirent *entry;
	t_temp *list;
	t_temp *t_list;
	char path[1024];
	char *path2;
	char *buffer;

	init_path2(&path2, name);
	if (!(dir = opendir(name)))
	{
		free(path2);
		ft_printf("error->>>>>>>>>>>>>>\n");
		return ;
	}
	list = NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		buffer = ft_strjoin(path2, entry->d_name);
		add(&list, entry->d_name, get_stats(buffer));
		free(buffer);
	}
	q_sort(&list);
	print_list(list);
	t_list = list;
	while (t_list)
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

int		find_char(char *str)
{
	int i;

	i = 2;
	while (str[i])
	{
		if (str[i] == 47)
			return (1);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int		arguments_quantity = 0;
	struct stat buf;
	t_temp *list = NULL;

	if (argc == 1)
		listdir(".");
	else
	{
		arguments_quantity = 1;
		while (arguments_quantity < argc)
		{
			lstat(argv[arguments_quantity], &buf);
			if (!find_char(argv[arguments_quantity]) && ((buf.st_mode & S_IFMT) == S_IFLNK))
			{
				add(&list, argv[arguments_quantity], get_stats(argv[arguments_quantity]));
				print_list(list);
				arguments_quantity++;
				continue;
			}
			listdir(argv[arguments_quantity++]);
		}
	}
	system("leaks -q ft_ls");
	return (0);
}
