#include "../includes/ft_ls.h"

#include <stdio.h>

void listdir(const char *name/*, int indent  flags */) // ? go from the first element of the list;
{
	DIR *dir;

	// static int x = 0;

	struct dirent *entry;

	if (!(dir = opendir(name)))
		return;

	t_temp *list = NULL;
	// t_temp *list2 = NULL;
	// error handler;
	// id of error
	// *S_IROTH

	while ((entry = readdir(dir)) != NULL) // uses stat here;
	{
			add(&list, entry->d_name, entry->d_type); 
	}


	// sort(&list);

	// path is to be opened, not the name;
	// path for each directory;

	
	q_sort(&list); 


	print_list(list);

	free(entry);

	// if (!(dir = opendir(name))) // name == path;
	//     return;
	t_temp *t_list = list;


	while(t_list)
	{
		if (t_list->d_type == DT_DIR)
		{
			char path[1024];

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



	// while ((entry = readdir(dir)) != NULL) 
	// {
	//     if (entry->d_type == DT_DIR)
	//     {
	//         char path[1024];

	//         if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
	//             continue;

	//         snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

	//         ft_printf("%s\n", path);

	//         // printf("%*s[%s]\n", indent, "", entry->d_name);

	//         // add(&list, entry->d_name); 

	//         listdir(path, indent + 2);
	//     } 
	//     // else 
	//     // {
	//     //     // printf("%*s- %s\n", indent, "", entry->d_name);
	//     //     // add(&list, entry->d_name);
	//     // }
	// }

	closedir(dir);
	deleteList(&list);
	// x--;

	// if (x > 0)
	//     print_list(list);
}

// trash handler;
// leaks: list pointer withing the recursion work, list while printing;
// manage errors;

int main(int argc, char **argv)
{
	if (argc == 1)
		listdir(".");
	else
		listdir(argv[1]);
	system("leaks -q ft_ls");
	return 0;
}


