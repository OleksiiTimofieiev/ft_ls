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

int		ft_opendir(t_variables *var, char *name)
{
	var->list = NULL;
	if (!(var->dir = opendir(name)))
	{
		free(var->path2);
		ft_printf("error->>>>>>>>>>>>>>\n");
		return (0);
	}
	return (1);
}

void	fill_the_list(t_variables *var)
{
	while ((var->entry = readdir(var->dir)) != NULL)
	{
		var->buffer = ft_strjoin(var->path2, var->entry->d_name);
		add(&var->list, var->entry->d_name, get_stats(var->buffer));
		free(var->buffer);
	}
	var->t_list = var->list;
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

void	listdir(char *name) // flags;
{
	t_variables var;

	init_path2(&var.path2, name);
	if (!ft_opendir(&var, name))
		return ;
	fill_the_list(&var);
	q_sort(&var.list);
	print_list(var.list);
	while (var.t_list) // && R;
	{
		if (var.t_list->type_and_permissions_data[0] == 'd')
		{
			if (ft_strcmp(var.t_list->d_name, ".") == 0 || ft_strcmp(var.t_list->d_name, "..") == 0)
			{
				var.t_list = var.t_list->next;
				continue ;
			}
			snprintf(var.path, sizeof(var.path), "%s/%s", name, var.t_list->d_name);
			ft_printf("\n%s:\n", var.path);
			listdir(var.path);
		}
		var.t_list = var.t_list->next;
	}
	ft_dump_cleaner(&var.list, &var.path2, &var.dir);
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
