#include "../includes/ft_ls.h"

#include <stdio.h>

// sorting after reading the root on the each step of the recursion (lexicographical.c);

typedef     struct s_temp
{
    char *d_name;
    unsigned char d_type;
    struct s_temp *next;
}                  t_temp;

// Returns the last t_temp of the list 
t_temp *getTail(t_temp *cur) 
{ 
    while (cur != NULL && cur->next != NULL) 
        cur = cur->next; 
    return cur; 
} 
  
// Partitions the list taking the last element as the pivot 
t_temp *partition(t_temp *head, t_temp *end, t_temp **newHead, t_temp **newEnd) 
{ 
    t_temp *pivot = end; 
    t_temp *prev = NULL, *cur = head, *tail = pivot; 
  
    // During partition, both the head and end of the list might change 
    // which is updated in the newHead and newEnd variables 
    while (cur != pivot) 
    { 
        if (strcmp(cur->d_name, pivot->d_name) < 0) 
        { 
            // First t_temp that has a value less than the pivot - becomes 
            // the new head 
            if ((*newHead) == NULL) 
                (*newHead) = cur; 
  
            prev = cur;   
            cur = cur->next; 
        } 
        else // If cur t_temp is greater than pivot 
        { 
            // Move cur t_temp to next of tail, and change tail 
            if (prev) 
                prev->next = cur->next; 
            t_temp *tmp = cur->next; 
            cur->next = NULL; 
            tail->next = cur; 
            tail = cur; 
            cur = tmp; 
        } 
    } 
  
    // If the pivot d_name is the smallest element in the current list, 
    // pivot becomes the head 
    if ((*newHead) == NULL) 
        (*newHead) = pivot; 
  
    // Update newEnd to the current last t_temp 
    (*newEnd) = tail; 
  
    // Return the pivot t_temp 
    return pivot; 
} 
  
  
//here the sorting happens exclusive of the end t_temp 
t_temp *quickSortRecur(t_temp *head, t_temp *end) 
{ 
    // base condition 
    if (!head || head == end) 
        return head; 
  
    t_temp *newHead = NULL, *newEnd = NULL; 
  
    // Partition the list, newHead and newEnd will be updated 
    // by the partition function 
    t_temp *pivot = partition(head, end, &newHead, &newEnd); 
  
    // If pivot is the smallest element - no need to recur for 
    // the left part. 
    if (newHead != pivot) 
    { 
        // Set the t_temp before the pivot t_temp as NULL 
        t_temp *tmp = newHead; 
        while (tmp->next != pivot) 
            tmp = tmp->next; 
        tmp->next = NULL; 
  
        // Recur for the list before pivot 
        newHead = quickSortRecur(newHead, tmp); 
  
        // Change next of last t_temp of the left half to pivot 
        tmp = getTail(newHead); 
        tmp->next =  pivot; 
    } 
  
    // Recur for the list after the pivot element 
    pivot->next = quickSortRecur(pivot->next, newEnd); 
  
    return newHead; 
} 
  
// The main function for quick sort. This is a wrapper over recursive 
// function quickSortRecur() 
// we need an additional list to save the 


void quickSort(t_temp **headRef) 
{ 
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef)); 
    return; 
} 

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

    while ((entry = readdir(dir)) != NULL) 
    {
            add(&list, entry->d_name, entry->d_type); 
    }


    // sort(&list);

    // path is to be opened, not the name;
    // path for each directory;

    quickSort(&list); 
    print_list(list);

    free(entry);

    // if (!(dir = opendir(name))) // name == path;
    //     return;

    while(list)
    {
    	if (list->d_type == DT_DIR)
    	{
    		char path[1024];

            if (ft_strcmp(list->d_name, ".") == 0 || ft_strcmp(list->d_name, "..") == 0)
            {
                list = list->next;
                continue ;
            }
            snprintf(path, sizeof(path), "%s/%s", name, list->d_name);

            ft_printf("%s\n", path);

            listdir(path, indent + 2);
    	}
    	list = list->next;
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


