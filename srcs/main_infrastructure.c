/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_infrastructure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 19:19:07 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 19:19:08 by otimofie         ###   ########.fr       */
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
