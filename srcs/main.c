#include "../includes/ft_ls.h"

/*
bonus:
-c	->	colors: dir, binary, file;
-f  ->	Output is not sorted.
		This option turns on the -a option. -> no filters;
-o	->	omit the group and user id.
*/

// manage errors:

// func to detect cyrcular link; work out if have the link;
// through pointer pass illegal flag to the printing func

// norminette;

void	reverse(t_temp** head_ref) 
{ 
    t_temp* prev   = NULL; 
    t_temp* current = *head_ref; 
    t_temp* next; 
    while (current != NULL) 
    { 
        next  = current->next;   
        current->next = prev;    
        prev = current; 
        current = next; 
    } 
    *head_ref = prev; 
} 


int		ft_opendir(t_variables *var, char *name)
{
	var->list = NULL;
	if (!(var->dir = opendir(name)))
	{
		free(var->path2);
		ft_printf("ft_ls: %s: %s\n", name, strerror(errno));
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

void	ft_concatenation(t_variables *var, char *name)
{
	char	buf[1024];
	char	*result;
	int		i;

	i = 0;
	ft_memset(buf, '\0', sizeof(buf));
	ft_memset(var->path, '\0', sizeof(var->path));
	result = ft_strcat(buf, name);
	result = ft_strcat(result, "/");
	result = ft_strcat(result, var->t_list->d_name);
	while (*result)
	{
		var->path[i] = *result;
		i++;
		result++;
	}
}

void	listdir(char *name, t_flags flags)
{
	t_variables var;

	init_path2(&var.path2, name);
	if (!ft_opendir(&var, name))
		return ;
	fill_the_list(&var);

	if (!flags.freedom)
	{
		q_sort(&var.list);
		if (flags.time_sorting)
		{
			insertionSort(&var.list);
			reverse(&var.list);
		}
		if (flags.reversed)
			reverse(&var.list);
	}
	else
	{
		flags.include_dot = 1;
	}
	print_list(var.list, flags);
	var.t_list = var.list;
	while (flags.recursive && var.t_list)
	{
		if (var.t_list->type_and_permissions_data[0] == 'd')
		{
			if (ft_strcmp(var.t_list->d_name, ".") == 0 || ft_strcmp(var.t_list->d_name, "..") == 0)
			{
				var.t_list = var.t_list->next;
				continue ;
			}
		    ft_concatenation(&var, name);
		    if (var.path[0] && var.path[0] == '/' && var.path[1] && var.path[1] == '/')
				ft_printf("\n%s:\n", &var.path[1]);
			else
				ft_printf("\n%s:\n", var.path);

			listdir(var.path, flags);
		}
		var.t_list = var.t_list->next;
	}
	ft_dump_cleaner(&var.list, &var.path2, &var.dir);
}

void	ft_ls(int argc, char **argv, t_flags flags, int move_to_the_arguments)
{
	int			arguments_quantity = 0;
	struct stat buf;
	t_temp 		*list;

	list = NULL;
	if ((argc - move_to_the_arguments) == 1)
	{
		listdir(".", flags);
	}
	else
	{
		arguments_quantity += (move_to_the_arguments + 1);
		while (arguments_quantity < argc)
		{
			if (lstat(argv[arguments_quantity], &buf) == -1)
			{
				ft_printf("ft_ls: %s: %s\n", argv[arguments_quantity] , strerror(errno));
				arguments_quantity++;
				continue ;
			}
			if (!find_char(argv[arguments_quantity]) && ((buf.st_mode & S_IFMT) == S_IFLNK))
			{
				flags.no_total = 1;
				add(&list, argv[arguments_quantity], get_stats(argv[arguments_quantity]));
				print_list(list, flags);
				free(list->d_name);
				free(list);
				list = NULL;
				// ft_putstr("here1\n");
				arguments_quantity++;
				continue ;
			}
			else if ((buf.st_mode & S_IFMT) != S_IFDIR)
			{
				// ft_putstr("here1\n");
				char *remove_dot = NULL;
				// ft_putstr("wtf\n");
				flags.no_total = 1;
				if (argv[arguments_quantity][0] == '.')
				{
					remove_dot = ft_strdup(&argv[arguments_quantity][2]);
					add(&list, remove_dot, get_stats(remove_dot));
					ft_putchar('.');
				}
				else
					add(&list, argv[arguments_quantity], get_stats(argv[arguments_quantity]));

				print_list(list, flags);
				// ft_putstr("here2\n");

				if (remove_dot)
					free(remove_dot);
				delete_list(&list);
				list = NULL;
				arguments_quantity++;
				continue ;	
			}
			listdir(argv[arguments_quantity], flags);
			arguments_quantity++;
			if ((argc - arguments_quantity) > 0)
				ft_printf("\n");
		}
	}
}

int		check_flags_validiry(char *str)
{
	while (*str)
	{
		if (*str == 'l' || *str == 'a' || *str == 'r' || *str == 'R' || *str == 't' || *str == 'c' || *str == 'f' || *str == 'o')
			str++;
		else
			return (0);
	}
	return (1);
}

int		set_flag_structure(char *str, t_flags *flags)
{
	int i;

	i = 1;
	if (!check_flags_validiry(str))
	{
		i = 0;
		return (i);
	}
	while (*str)
	{
		if (*str == 'l')
			flags->long_format = 1;
		else if (*str == 'a')
			flags->include_dot = 1;
		else if (*str == 'R')
			flags->recursive = 1;
		else if (*str == 'r')
			flags->reversed = 1;
		else if (*str == 't')
			flags->time_sorting = 1;
		else if (*str == 'c')
			flags->colors = 1;
		else if (*str == 'f')
			flags->freedom = 1;
		else if (*str == 'o')
			flags->no_group_user_name = 1;
		str++;
	}
	return (i);
}

void	init_flags(char **argv, t_flags *flags, int argc, int *move_to_the_arguments)
{
	int i;

	i = 1;
	flags->long_format = 0;
	flags->include_dot = 0;
	flags->recursive = 0;
	flags->reversed = 0;
	flags->time_sorting = 0;
	flags->no_total = 0;
	flags->freedom = 0;
	flags->no_group_user_name = 0;
	 if (argc == 1) 
	 return;
	 while (argv[i] && argv[i][1] && argv[i][0] == '-')
	 {
		 if (!set_flag_structure(&argv[i][1], flags)) 
		 {
			 ft_printf("ft_ls: illegal option -- %c\n", &argv[i][1]); ////// here;
			 ft_printf("usage: ft_ls [-Racfolrt] [file ...]\n");
			 exit(0);
		 }
		 *move_to_the_arguments = *move_to_the_arguments + 1;
		 i++;
	}
}

// void	print_flags(t_flags *flags)
// {
// 	ft_printf("long_format->%d,include_dot->%d,recursive->%d,reversed->%d,time_sorting->%d\n",
// 				flags->long_format, flags->include_dot, flags->recursive, flags->reversed, flags->time_sorting);
// }

int		main(int argc, char **argv)
{
	t_flags flags;
	int		move_to_the_arguments;

	move_to_the_arguments = 0;
	init_flags(argv, &flags, argc, &move_to_the_arguments);
	ft_ls(argc, argv, flags, move_to_the_arguments);
	system("leaks -q ft_ls");
	return (0);
}
