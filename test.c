#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

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
        printf("%s\n", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");

}

void listdir(const char *name, int indent /* flags */)
{
    DIR *dir;

    static int x = 0;

    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    t_temp *list = NULL;
    t_temp *list2 = NULL;
    // error handler;
    // id of error
    // *S_IROTH

    while ((entry = readdir(dir)) != NULL) 
    {
            add(&list2, entry->d_name); 
    }
    closedir(dir);
    // sort(&list);
    print_list(list2);

    free(entry);

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR)
        {
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%s\n", path);

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

int main(void) 
{
    listdir(".", 0);
    return 0;
}

// // // #include <stdlib.h>
// // // #include <stdio.h>
// // // #include <unistd.h>
// // // #include <sys/stat.h>
// // // #include <dirent.h>
// // // #include <string.h>
// // // #include <sys/dir.h>
// // // #include <sys/types.h>
// // // #include <pwd.h>
// // // #include <grp.h>
// // // #include <time.h>
// // // #include <locale.h>
 
// // // // void print_perms(mode_t st) {
// // // //     char perms[11];
// // // //     if(st & S_ISREG(st)) perms[0]='-';
// // // //     else if(st & S_ISDIR(st)) perms[0]='d';
// // // //     else if(st & S_ISFIFO(st)) perms[0]='|';
// // // //     else if(st & S_ISSOCK(st)) perms[0]='s';
// // // //     else if(st & S_ISCHR(st)) perms[0]='c';
// // // //     else if(st & S_ISBLK(st)) perms[0]='b';
// // // //     else perms[0]='l';  // S_ISLNK
// // // //     perms[1] = (st & S_IRUSR) ? 'r':'-';
// // // //     perms[2] = (st & S_IWUSR) ? 'w':'-';
// // // //     perms[3] = (st & S_IXUSR) ? 'x':'-';
// // // //     perms[4] = (st & S_IRGRP) ? 'r':'-';
// // // //     perms[5] = (st & S_IWGRP) ? 'w':'-';
// // // //     perms[6] = (st & S_IXGRP) ? 'x':'-';
// // // //     perms[7] = (st & S_IROTH) ? 'r':'-';
// // // //     perms[8] = (st & S_IWOTH) ? 'w':'-';
// // // //     perms[9] = (st & S_IXOTH) ? 'x':'-';
// // // //     perms[10] = '\0';
// // // //     printf("%s", perms);
// // // // }
 
// // // // void ls(char path[], int flag) {
// // // //     DIR * dir; struct dirent * file;
// // // //     dir = opendir(path);
// // // //     while((file=readdir(dir))) {
// // // //         if(file->d_name[0] != '.' || flag) {
// // // //             printf("%s  ", file->d_name);
// // // //         }
// // // //     }
// // // //     free(file);
// // // //     free(dir);
// // // // }
// // // // void ls_l(char path[]) {
// // // //     DIR * dir; struct dirent * file; struct stat sbuf;
// // // //     char buf[128];
// // // //     struct passwd pwent, * pwentp;
// // // //     struct group grp, * grpt;
// // // //     char datestring[256];
// // // //     struct tm time;
// // // //     dir = opendir(path);
// // // //     while((file=readdir(dir))) {
// // // //         stat(file->d_name, &sbuf);
// // // //         print_perms(sbuf.st_mode);
// // // //         printf(" %d", (int)sbuf.st_nlink);
// // // //         if (!getpwuid_r(sbuf.st_uid, &pwent, buf, sizeof(buf), &pwentp))
// // // //             printf(" %s", pwent.pw_name);
// // // //         else
// // // //             printf(" %d", sbuf.st_uid);
 
// // // //         if (!getgrgid_r (sbuf.st_gid, &grp, buf, sizeof(buf), &grpt))
// // // //             printf(" %s", grp.gr_name);
// // // //         else
// // // //             printf(" %d", sbuf.st_gid);
// // // //         printf(" %5d", (int)sbuf.st_size);
        
// // // //         localtime_r(&sbuf.st_mtime, &time);
// // // //         /* Get localized date string. */
// // // //         strftime(datestring, sizeof(datestring), "%F %T", &time);
 
// // // //         printf(" %s %s\n", datestring, file->d_name);
// // // //     }
// // // // }
// // // // void ls_r(char path[]) {
// // // //     DIR * dir; struct dirent * file; struct stat sbuf;
// // // //     char tmp[128];
// // // //     dir = opendir(path);
// // // //     while((file=readdir(dir))) {
// // // //         if(file->d_name[0] == '.') continue;
// // // //         strcpy(tmp, path);
// // // //         strcat(tmp, "/");
// // // //         strcat(tmp, file->d_name);
// // // //         //printf("%s\n", tmp);
// // // //         stat(tmp, &sbuf);
// // // //         if(sbuf.st_mode && S_ISDIR(sbuf.st_mode)) {
// // // //             printf("\n%s/\n", tmp);
// // // //             ls_r(tmp);
// // // //         } else 
// // // //             printf("%s  ", file->d_name);
// // // //     }
// // // // }
// // // // int main(int argc, char * argv[]) {
// // // //     char pathname[128];
// // // //     getcwd(pathname, 128);
// // // //     if(argc == 1){
// // // //         ls(pathname, 0);
// // // //     } else {
// // // //         if(strcmp(argv[1], "-l") == 0) {
// // // //             ls_l(pathname);
// // // //         } else if(strcmp(argv[1], "-r") == 0) {
// // // //             ls_r(pathname);
// // // //         } else {
// // // //             ls(pathname, 1);  // ls -a
// // // //         }
// // // //     }
// // // //     printf("\n");
// // // //     return 0;
// // // // }

// // // typedef struct s_list
// // // {
// // //     char        *a;
// // //     struct s_list      *next;

// // // }               t_list;

// // // #define SEPARATOR "/"

// // // void ls(const char *path)
// // // {
// // //     // t_list  *list = NULL;

// // //     // if (!list)
// // //     //     printf("%s\n", "list->>>>>>>>>>>>>>>");

// // //     DIR *directory = opendir(path);

// // //     if (directory != NULL)  
// // //     {
// // //         struct dirent *filei;

// // //         while ((filei = readdir(directory)) != NULL)
// // //         {

// // //             if (strcmp(filei->d_name, ".") == 0 || strcmp(filei->d_name, "..") == 0)
// // //             {
// // //                 continue;
// // //             }
// // //             char *buffer = malloc(strlen(path) + strlen(filei->d_name) + strlen(SEPARATOR) + 1);
// // //             strcat(strcat(strcpy(buffer, path), SEPARATOR), filei->d_name);

// // //             struct stat stat_buffer;

// // //             if (stat(buffer, &stat_buffer) == 0)
// // //             {   
// // //                 printf("%s\n", buffer); 
                

// // //                 if (S_ISDIR(stat_buffer.st_mode))
// // //                 {
// // //                     ls(buffer);
// // //                 }
// // //             }
// // //             else
// // //             {
// // //                 perror(NULL);
// // //             }

// // //             free(buffer);
// // //         }
// // //         closedir(directory);
// // //     }
// // //     else
// // //     {
// // //         perror(NULL);     
// // //     }
// // // }

// // int main()
// // {
// //     ls(".");
// //     return 0;
// }