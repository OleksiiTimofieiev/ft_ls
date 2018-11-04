/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_infrastructure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:16:12 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/04 13:06:43 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static long long	get_total_blocks(t_temp *list)
{
	long long sum = 0;


	while(list)
	{
		sum += list->blocks_data;
		list = list->next;
	}
	return (sum);
}

void	delete_list(t_temp **head_ref)
{
	t_temp *current;
	t_temp *next;

	current = *head_ref;
	while (current != NULL)
	{
		next = current->next;
		free(current->d_name);
		free(current);
		current = next;
	}
}
static void	str_copy(char *dst, char *src)
{
	int i;

	i = 0;
	while (i < 20)
	{
		dst[i] = src[i];
		i++;
	}
	dst[19] = '\0';
}

void add(t_temp **head_ref, char *new_d_name, unsigned char d_type, t_data var/*, char *path*/)
{
	t_temp *new;
	t_temp *last;

	new = (t_temp*)malloc(sizeof(t_temp));
	last = *head_ref;
	new->blocks_data = var.blocks_buf;
	new->bytes_data = var.bytes_buf;
	new->d_name = ft_strdup(new_d_name);
	ft_strcpy(new->type_and_permissions_data, var.type_and_permissions_buf);
	new->d_type = d_type;
	new->hard_links_data = var.hard_links_buf;

	ft_strcpy(new->owner_name_data, var.owner_name_buf);
	ft_strcpy(new->group_name_data, var.group_name_buf);

	new->size_data = var.size_buf;
	str_copy(new->time_data, var.time_buf);
	new->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return ;
}

void	print_date(char *time_str)
{
	int i;

	i = 4;
	while (i < 16)
		ft_printf("%c", time_str[i++]);
	ft_printf(" ");
}

void	print_list(t_temp *list) //TODO: modify with *;
{
	long long total = 0;

	total = get_total_blocks(list);
	ft_printf("total %lld\n", total);
	while (list)
	{
		ft_printf("%s ", list->type_and_permissions_data);
		ft_printf("%*d ", 2, list->hard_links_data);
		ft_printf("%s ", list->owner_name_data);
		ft_printf("%s ", list->group_name_data);
		ft_printf("%d ", list->size_data);
		print_date(list->time_data);
		ft_printf("%s \n", list->d_name);
		list = list->next;
	}
}
