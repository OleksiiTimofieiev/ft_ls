/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:34:49 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 18:36:22 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	reverse(t_temp **head_ref)
{
	t_temp	*prev;
	t_temp	*current;
	t_temp	*next;

	prev = NULL;
	current = *head_ref;
	while (current != NULL)
	{
		next = current->next;
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

void	handle_flags(t_flags *flags, t_variables *var)
{
	if (!(flags->time_sorting))
		q_sort(&var->list);
	if (!flags->freedom)
	{
		if (flags->time_sorting)
		{
			q_sort(&var->list);
			r_q_sort(&var->list);
		}
		if (flags->reversed)
			reverse(&var->list);
	}
	else
	{
		flags->include_dot = 1;
	}
	print_list(var->list, *flags);
}

void	current_dir_print(t_variables *var, t_flags *flags)
{
	if (var->path[0] && var->path[0] == '/'
		&& var->path[1] && var->path[1] == '/')
	{
		if (!flags->colors)
			ft_printf("\n%s:\n", &var->path[1]);
		else
			ft_printf("\n%s%s%s:\n", MAGENTA, &var->path[1], RESET);
	}
	else
	{
		if (!flags->colors)
			ft_printf("\n%s:\n", &var->path[1]);
		else
			ft_printf("\n%s%s%s:\n", MAGENTA, &var->path, RESET);
	}
}

void	listdir(char *name, t_flags flags)
{
	t_variables var;

	init_path2(&var.path2, name);
	if (!ft_opendir(&var, name))
		return ;
	fill_the_list(&var);
	handle_flags(&flags, &var);
	var.t_list = var.list;
	while (flags.recursive && var.t_list)
	{
		if (var.t_list->type_and_permissions_data[0] == 'd')
		{
			if (ft_strcmp(var.t_list->d_name, ".") == 0
				|| ft_strcmp(var.t_list->d_name, "..") == 0)
			{
				var.t_list = var.t_list->next;
				continue ;
			}
			ft_concatenation(&var, name);
			current_dir_print(&var, &flags);
			listdir(var.path, flags);
		}
		var.t_list = var.t_list->next;
	}
	ft_dump_cleaner(&var.list, &var.path2, &var.dir);
}

void	handler_not_dir(t_flags *flags, char **argv,
		t_temp *list, int *arguments_quantity)
{
	char *remove_dot;

	remove_dot = NULL;
	flags->no_total = 1;
	if (argv[(*arguments_quantity)][0] == '.')
	{
		remove_dot = ft_strdup(&argv[(*arguments_quantity)][2]);
		add(&list, remove_dot, get_stats(remove_dot));
		ft_putchar('.');
	}
	else
		add(&list, argv[(*arguments_quantity)],
			get_stats(argv[(*arguments_quantity)]));
	print_list(list, *flags);
	if (remove_dot)
		free(remove_dot);
	delete_list(&list);
	list = NULL;
	(*arguments_quantity)++;
}

void	handler_link(t_flags *flags, char **argv,
		t_temp *list, int *arguments_quantity)
{
	flags->no_total = 1;
	add(&list, argv[(*arguments_quantity)],
		get_stats(argv[(*arguments_quantity)]));
	print_list(list, *flags);
	free(list->d_name);
	free(list);
	list = NULL;
	(*arguments_quantity)++;
}

int		not_valid_input(char **argv, int *arguments_quantity, struct stat *buf)
{
	if (lstat(argv[(*arguments_quantity)], buf) == -1)
	{
		ft_printf("ft_ls: %s: %s\n",
			argv[(*arguments_quantity)++], strerror(errno));
		return (1);
	}
	return (0);
}

void	while_loop(int *arguments_quantity, int argc,
		char **argv, t_flags *flags)
{
	struct stat buf;
	t_temp		*list;

	list = NULL;
	while ((*arguments_quantity) < argc)
	{
		if (not_valid_input(argv, arguments_quantity, &buf))
		{
			continue ;
		}
		else if (!find_char(argv[(*arguments_quantity)])
			&& ((buf.st_mode & S_IFMT) == S_IFLNK))
		{
			handler_link(flags, argv, list, &(*arguments_quantity));
			continue ;
		}
		else if ((buf.st_mode & S_IFMT) != S_IFDIR)
		{
			handler_not_dir(flags, argv, list, &(*arguments_quantity));
			continue ;
		}
		listdir(argv[(*arguments_quantity)++], *flags);
		if ((argc - (*arguments_quantity)) > 0)
			ft_printf("\n");
	}
}

void	ft_ls(int argc, char **argv, t_flags flags, int move_to_the_arguments)
{
	int			arguments_quantity;

	arguments_quantity = 0;
	if ((argc - move_to_the_arguments) == 1)
		listdir(".", flags);
	else
	{
		arguments_quantity += (move_to_the_arguments + 1);
		while_loop(&arguments_quantity, argc, argv, &flags);
	}
}

int		check_flags_validiry(char *str, char *invalid)
{
	while (*str)
	{
		if (*str == 'l' || *str == 'a'
			|| *str == 'r' || *str == 'R'
			|| *str == 't' || *str == 'c'
			|| *str == 'f' || *str == 'o')
			str++;
		else
		{
			*invalid = *str;
			return (0);
		}
	}
	return (1);
}

void	activate_the_flags(char *str, t_flags *flags)
{
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
}

int		set_flag_structure(char *str, t_flags *flags, char *invalid)
{
	int i;

	i = 1;
	if (!check_flags_validiry(str, invalid))
	{
		i = 0;
		return (i);
	}
	activate_the_flags(str, flags);
	return (i);
}

void	init_flags(char **argv, t_flags *flags,
		int argc, int *move_to_the_arguments)
{
	int		i;
	char	invalid;

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
		return ;
	while (argv[i] && argv[i][1] && argv[i][0] == '-')
	{
		if (!set_flag_structure(&argv[i][1], flags, &invalid))
		{
			ft_printf("ft_ls: illegal option -- %c\n", invalid);
			ft_printf("usage: ft_ls [-Racfolrt] [file ...]\n");
			exit(0);
		}
		*move_to_the_arguments = *move_to_the_arguments + 1;
		i++;
	}
}

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
