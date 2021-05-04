/*
	This program outputs information based on the command that is passed to it
    from user input. 

	Author: Reema Amhaz
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 

/*
	This function finds the path to the home directory and outputs, depending on the function, info of the directory
	using the binary executable.
	Parameters: none
	Return value: information on files/the cpu
*/

int main()
{
    while(1)
    {
        char buffer[10];
    
        printf("lab1>");
        scanf("%s", buffer); // get user input
        printf("Parent Process %d\n", getpid());

        char printid[] = "printid";
        char ex[] = "exit";
        char greet[] = "greet";
        char list[] = "ls";
        char cmd_pwd[] = "pwd";
        char cmd_ps[] = "ps";
        char cmd_date[] = "date";
        char cmd_lscpu[] = "lscpu";

        // in the case that it is a built in function 
        if((strcmp(buffer, printid) == 0) | (strcmp(buffer, ex) == 0)  | (strcmp(buffer, greet) == 0))
        {
            if(strcmp(buffer, printid) == 0)
            {
                printf("%d\n", getpid());
            }
            else if(strcmp(buffer, greet) == 0)
            {
                printf("Hello\n");
            }
            else
            {
                exit(0);
            } 
        }
        // access the binary executable to execute the function
        else
        {
            int ret = 0;
            // create a new process
            int pid = fork();
            // find the child process
            if (pid == 0)
            {
                printf("Child process %d will execute the command %s\n", getpid(), buffer);
                //call ls on this process to list files
                if (strcmp(buffer, list) == 0)
                {
                    char* args[] = {"ls", NULL};
                    ret = execve("/bin/ls", args, NULL);
                }
                else if (strcmp(buffer, cmd_pwd) == 0)
                {
                    char* args[] = {"pwd", NULL};
                    ret = execve("/bin/pwd", args, NULL);
                }
                else if (strcmp(buffer, cmd_ps) == 0)
                {
                    char* args[] = {"ps", NULL};
                    ret = execve("/bin/ps", args, NULL);
                }
                else if (strcmp(buffer, cmd_date) == 0)
                {
                    char* args[] = {"date", NULL};
                    ret = execve("/bin/date", args, NULL);
                }
                else if (strcmp(buffer, cmd_lscpu) == 0)
                {
                    char* args[] = {"lscpu", NULL};
                    ret = execve("/bin/lscpu", args, NULL);
                }
                else
                {
                    /* only executed if execve fails */
                    printf("Command Not Found!\n");
                    exit(ret);
                }
            }
        }
        wait(NULL);
    }
    
    return 0;
}
