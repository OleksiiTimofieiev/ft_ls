/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:34:49 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 19:16:20 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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
