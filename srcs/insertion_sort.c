#include "../includes/ft_ls.h"

// function to sort a singly linked list using insertion sort 


/* C program for insertion sort on a linked list */
#include<stdio.h> 
#include<stdlib.h> 
  
/* function to insert a new_node in a list. Note that this 
  function expects a pointer to head_ref as this can modify the 
  head of the input linked list (similar to push())*/
void sortedInsert(t_temp** head_ref, t_temp* new_node) 
{ 
    t_temp* current; 
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->mod_time_data >= new_node->mod_time_data) 
    { 
        new_node->next = *head_ref; 
        *head_ref = new_node; 
    } 
    else
    { 
        /* Locate the node before the point of insertion */
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
void insertionSort(t_temp **head_ref) 
{ 
    // Initialize sorted linked list 
    t_temp *sorted = NULL; 
  
    // Traverse the given linked list and insert every 
    // node to sorted 
    t_temp *current = *head_ref; 
    while (current != NULL) 
    { 
        // Store next for next iteration 
        t_temp *next = current->next; 
  
        // insert current in sorted linked list 
        sortedInsert(&sorted, current); 
  
        // Update current 
        current = next; 
    } 
  
    // Update head_ref to point to sorted linked list 
    *head_ref = sorted; 
} 