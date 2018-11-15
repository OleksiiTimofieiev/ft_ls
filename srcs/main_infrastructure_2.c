/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_infrastructure_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 19:16:58 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 19:17:00 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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
