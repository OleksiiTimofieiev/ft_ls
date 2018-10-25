#include "../includes/ft_ls.h"

#include <stdio.h>

// sorting after reading the root on the each step of the recursion (lexicographical.c);

typedef     struct s_temp
{
    char *data;
    struct s_temp *next;
}                  t_temp;

void add(t_temp** head_ref, char *new_data) 
{ 
    /* 1. allocate node */
    t_temp* new_node = (t_temp*) malloc(sizeof(t_temp)); 
  
    t_temp *last = *head_ref;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->data  = strdup(new_data); 
  
    /* 3. This new node is going to be the last node, so make next of 
          it as NULL*/
    new_node->next = NULL; 
  
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL) 
    { 
       *head_ref = new_node; 
       return; 
    } 
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL) 
        last = last->next; 
  
    /* 6. Change the next of last node */
    last->next = new_node; 
    return; 
} 

void    print_list(t_temp *tmp)
{
    // printf("\n%s\n", "start");
    while(tmp)
    {
        ft_printf("%s\n", tmp->data);
        tmp = tmp->next;
    }
    ft_printf("\n");

}

void listdir(const char *name, int indent /* flags */)
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

    while ((entry = readdir(dir)) != NULL) 
    {
            add(&list, entry->d_name); 
    }
    closedir(dir);
    // sort(&list);
    print_list(list);

    free(entry);

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR)
        {
            char path[1024];

            if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            ft_printf("%s\n", path);

            // printf("%*s[%s]\n", indent, "", entry->d_name);

            // add(&list, entry->d_name); 

            listdir(path, indent + 2);
        } 
        else 
        {
            // printf("%*s- %s\n", indent, "", entry->d_name);
            // add(&list, entry->d_name);
        }
    }


    closedir(dir);
    // x--;

    // if (x > 0)
    //     print_list(list);
}

int main(int argc, char **argv) 
{
	if (argc == 1)
    	listdir(".", 0);
	else
		ft_printf(argv[1]);
    return 0;
}


