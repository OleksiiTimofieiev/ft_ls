#include "../includes/ft_ls.h"

#include <stdio.h>

// Returns the last t_temp of the list 

void deleteList(t_temp** head_ref) 
{ 
   /* deref head_ref to get the real head */
   t_temp* current = *head_ref; 
   t_temp* next; 
  
   while (current != NULL)  
   { 
       next = current->next; 
       free(current->d_name); 
       free(current);
       current = next; 
   } 
}
    
   /* deref head_ref to affect the real head back 
      in the caller. */

void add(t_temp** head_ref, char *new_d_name, unsigned char d_type) 
{ 
    /* 1. allocate t_temp */
    t_temp* new_t_temp = (t_temp*) malloc(sizeof(t_temp)); 
  
    t_temp *last = *head_ref;  /* used in step 5*/
  
    /* 2. put in the d_name  */
    new_t_temp->d_name  = strdup(new_d_name); 
    new_t_temp->d_type = d_type;
  
    /* 3. This new t_temp is going to be the last t_temp, so make next of 
          it as NULL*/
    new_t_temp->next = NULL; 
  
    /* 4. If the Linked List is empty, then make the new t_temp as head */
    if (*head_ref == NULL) 
    { 
       *head_ref = new_t_temp; 
       return; 
    } 
  
    /* 5. Else traverse till the last t_temp */
    while (last->next != NULL) 
        last = last->next; 
  
    /* 6. Change the next of last t_temp */
    last->next = new_t_temp; 
    return; 
} 

void    print_list(t_temp *tmp)
{
    // printf("\n%s\n", "start");
    while(tmp)
    {
        ft_printf("%s\n", tmp->d_name);
        tmp = tmp->next;
    }
    ft_printf("\n");
}

void listdir(const char *name, int indent /* flags */) // ? go from the first element of the list;
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

            listdir(path, indent + 2);
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

int main(int argc, char **argv) 
{
	if (argc == 1)
    	listdir("./libft", 0);
	else
		ft_printf(argv[1]);
	// system("leaks -q ft_ls");
    system("leaks -q ft_ls");
    return 0;
}


