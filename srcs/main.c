#include "../includes/ft_ls.h"

#include <stdio.h>

void listdir(const char *name/*, int indent  flags */) // ? go from the first element of the list;
{
	DIR *dir;
	struct dirent *entry;
	t_temp *list;
	t_temp *t_list;
	char path[1024];

	if (!(dir = opendir(name)))
		return;
	list = NULL;
	while ((entry = readdir(dir)) != NULL) // uses stat here;
	{
			add(&list, entry->d_name, entry->d_type); 
	}
	q_sort(&list);
	print_list(list);
	free(entry);
	t_list = list;
	while(t_list)
	{
		if (t_list->d_type == DT_DIR)
		{
			if (ft_strcmp(t_list->d_name, ".") == 0 || ft_strcmp(t_list->d_name, "..") == 0)
			{
				t_list = t_list->next;
				continue ;
			}
			snprintf(path, sizeof(path), "%s/%s", name, t_list->d_name);
			ft_printf("%s\n", path);
			listdir(path);
		}
		t_list = t_list->next;
	}
	closedir(dir);
	delete_list(&list);
}

// trash handler;
// leaks: list pointer withing the recursion work, list while printing;
// manage errors;
// make it in a cycle for each command line argument;
// norminetter leaks;

int main(int argc, char **argv)
{
	(argc == 1) ? listdir(".") : listdir(argv[1]); 

	system("leaks -q ft_ls");
	
	return 0;
}


