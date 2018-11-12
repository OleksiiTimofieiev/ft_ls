#include "../includes/ft_ls.h"

void	sortedInsert(t_temp **head_ref, t_temp *new_node)
{
	t_temp  *current;

	if (*head_ref == NULL || (*head_ref)->mod_time_data >= new_node->mod_time_data)
	{
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	else
	{
		current = *head_ref;
		while (current->next!=NULL &&
			current->next->mod_time_data < new_node->mod_time_data) 
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

void	insertionSort(t_temp **head_ref)
{
	t_temp *sorted = NULL;

	t_temp *current = *head_ref;
	while (current != NULL)
	{
		t_temp *next = current->next; 
		sortedInsert(&sorted, current);
		current = next;
	}
	*head_ref = sorted; 
}
