#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);

// a shell needs builtin functionality for changes to take effect on itself

//list of builtin commands

char *builtin_cmd[] = {"cd", "help", "exit"};

int(*builtin_func[]) (char **) = {&sh_cd,&sh_help, &sh_exit};

int sh_num_builtins(){
    return sizeof(builtin_cmd)/sizeof(char *);
}

//builtin function implementations

int sh_cd(char **args){
    if (args[1] == NULL){
        fprintf(stderr, "sh: expected argument to \"cd\"\n");
    }
    else{
        if (chdir(args[1]) != 0){
            perror("sh");
        }
    }
    return 1;
}

int sh_help(char **args){
    int i;
    printf("MyShell\n");
    printf("Enter the name of the program you wish to run and hit ENTER.\n");
    printf("The following are builtin commands: \n");

    for (i = 0; i < sh_num_builtins(); i ++){
        printf("%s\n", builtin_cmd[i]);
    }
    printf("Use the man command for more");
    return 1;
}

int sh_exit(char **args){
    return 0;
}

int sh_launch(char **args){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0){
        //child process
        if (execvp(args[0], args) == -1){
            perror("sh");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0){
        //error forking
        perror("sh");
    }
    else{
        //parent process
        do{
            wpid =waitpid(pid, &status, WUNTRACED); 
        }while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}



int sh_execute(char **args){
    int i;

    if (args[0] == NULL){
        //no command
        return 1;
    }
    for (i = 0; i <sh_num_builtins(); i++){
        if (strcmp(args[0], builtin_cmd[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }
    return sh_launch(args);
}

//using getline() to implement sh_read_line()
//getline() takes a line of text as input from a stream - in this case 'stdin', which is a special variable
//in the stdio library that stores input from the command line.

char *sh_read_line(void){
    char *line  = NULL;
    ssize_t buffer = 0; 
    // the size of the buffer is optional as getline expands the size corresponding to the input
    getline(&line, &buffer, stdin);
    return line;
}

//parse the line from sh_read_line() with sh_split_line()
//the shell does not process quotations but only uses space as a delimiter
//the only thing being done is tokenization of the line

#define SH_TOK_BUFSIZE 64
#define SH_TOK_DELIM "\t\n\r\a"
char **sh_split_line(char *line){
    int tok_bufsize = SH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(tok_bufsize * sizeof(char *));
    char *token;

    if (!tokens){
        fprintf(stderr, "sh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SH_TOK_DELIM);
    //strtok splits the string into tokens
    while (token != NULL){
        tokens[position] = token;
        position++;
    }
    if (position >= tok_bufsize){
        tok_bufsize = tok_bufsize + SH_TOK_BUFSIZE;
        tokens = realloc(tokens, tok_bufsize * sizeof(char *));
        if (!tokens){
            fprintf(stderr,"sh: allocation error\n");
            exit(EXIT_FAILURE);
        }
    }
    token = strtok(NULL, SH_TOK_DELIM);
    tokens[position] = NULL;
    return tokens;
}

//shell loop - takes no arguments 
void loop_shell(void){
    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = sh_read_line();
        args = sh_split_line(line);
        status = sh_execute(args);

        free(line);
        free(args);
    }while (status);
}



int main(int argc, char **argv){
    //command loop
    loop_shell();
    //cleanup and exit
    return EXIT_SUCCESS;
}
