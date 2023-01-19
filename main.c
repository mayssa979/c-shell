#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "header.h"
#include "input.c"
#include "basic.c"
#include "pwd.c"
#include "cd.c"
#include "execute_inst.c"
#include "ls.c"
#include "echo.c"
#include "pinfo.c"
#include "foreground.c" 
#include "history.c" 
#include "background.c" 
#include "jobs.c" 
#include "kjob.c" 
#include "quit.c" 
#include "overkill.c"
#include "fg.c" 
//#include "nightwatch.c" 
#include "piping.c" 
#include "redirection.c" 
#include "signal_handlers.c" 
#include "bg.c" 
#include "chaining.c"

int isBatch;

void run_shell() // Execute the shell
{
    signal(SIGCHLD,sigchld_handler);  // Track background process
    signal(SIGINT,sigint_handler);    // Does nothing but sets status=0, do not ignore as child will inherit behavior
    signal(SIGTSTP,sigtstp_handler);  // Same as above **DONT IGNORE
    prompt();
    get_input();
}

int main(int argc, char* argv[]) 
{   
    printf("\n\n%s\t\t\t\t   ***************** Welcome to our Shell ******************%s\n\n",BLUE,NORMAL);
    status=1;
    curr_fore = -1;
    get_val();
    SHELL_PID = getpid();
    FILE* file;
    file = fopen(".history.txt","r");
    if(file==NULL)
    {
        file = fopen(".history.txt","w");
        if(file==NULL)
        {
            printf("Error opening history.txt");
            exit(0);
        }
        fclose(file);
    }
    else
    {
       fclose(file);
    }
    
    history = malloc(21*sizeof(char*));
    if(history==NULL)
    {
        printf("Error in assigning memory");
        exit(0);
    }
    read_history();
    
    while(1)
    {
         if (argc > 1 && (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "--batch") == 0)) {
        // open script file
        FILE* script = fopen(argv[2], "r");
        if (script == NULL) {
            fprintf(stderr,"Error: No batch file\n");
            return 1;
        }
        // read commands from script file, print them and execute them
        char command[256];
        while (fgets(command, sizeof(command), script) != NULL) {
         if (strcmp(command, "EOF\n") == 0 || strcmp(command, "quit\n") == 0) {
            break;
        }
            printf("%s", command);
            system(command);
        }
        fclose(script);
        return 0;
    }else {
          run_shell();  
        }
    }
    return 0; 
} 
